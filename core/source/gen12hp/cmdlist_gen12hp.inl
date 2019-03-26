#include "runtime/gen12hp/hw_cmds.h"
#include "runtime/gen12hp/hw_info.h"
#include "runtime/indirect_heap/indirect_heap.h"
#include "cmdlist_hw.inl"
#include "module.h"
#include "igfxfmid.h"

namespace L0 {

template <>
void CommandListCoreFamily<IGFX_GEN12_CORE>::programFrontEndState() {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<IGFX_GEN12_CORE>::GfxFamily;

    {
        using CFE_STATE = typename GfxFamily::CFE_STATE;
        CFE_STATE cmd = GfxFamily::cmdInitCfeState;
        auto buffer = commandStream->getSpace(sizeof(cmd));
        *(CFE_STATE *)buffer = cmd;
    }
}

template <>
void CommandListCoreFamily<IGFX_GEN12_CORE>::programPreemption() {
    // TODO : Reuse NEO's PreemptionHelper (requires refactoring because of linker problems)
}

template <>
xe_result_t CommandListCoreFamily<IGFX_GEN12_CORE>::appendLaunchFunction(xe_function_handle_t hFunction,
                                                                         const xe_thread_group_dimensions_t *pThreadGroupDimensions,
                                                                         xe_event_handle_t hEvent) {
    constexpr GFXCORE_FAMILY gfxCoreFamily = IGFX_GEN12_CORE;
    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using COMPUTE_WALKER = typename GfxFamily::COMPUTE_WALKER;
    using INTERFACE_DESCRIPTOR_DATA = typename GfxFamily::INTERFACE_DESCRIPTOR_DATA;
    using STATE_BASE_ADDRESS = typename GfxFamily::STATE_BASE_ADDRESS;

    const auto function = Function::fromHandle(hFunction);
    assert(function);
    auto sizeCrossThreadData = function->getCrossThreadDataSize();
    auto sizePerThreadData = function->getPerThreadDataSize();
    auto sizePerThreadDataForWholeGroup = function->getPerThreadDataSizeForWholeThreadGroup();

    COMPUTE_WALKER cmd = GfxFamily::cmdInitGpgpuWalker;
    auto &idd = cmd.getInterfaceDescriptor();

    // Point kernel start pointer to the proper offset of instruction heap
    {
        auto alloc = function->getIsaGraphicsAllocation();
        assert(nullptr != alloc);
        auto offset = alloc->getGpuAddressOffsetFromHeapBase();
        idd.setKernelStartPointer(offset);
        idd.setKernelStartPointerHigh(0u);
    }

    auto threadsPerThreadGroup = function->getThreadsPerThreadGroup();
    idd.setNumberOfThreadsInGpgpuThreadGroup(threadsPerThreadGroup);

    idd.setBarrierEnable(function->getHasBarriers());
    idd.setSharedLocalMemorySize(function->getSlmSize() > 0
                                     ? INTERFACE_DESCRIPTOR_DATA::SHARED_LOCAL_MEMORY_SIZE_ENCODES_64K
                                     : INTERFACE_DESCRIPTOR_DATA::SHARED_LOCAL_MEMORY_SIZE_ENCODES_0K);

    // Set up binding table and surface states
    {
        auto bindingTableStateCount = function->getBindingTableStateCount();
        uint32_t bindingTablePointer = 0u;

        if (bindingTableStateCount > 0u) {
            auto ssh = indirectHeaps[SURFACE_STATE];
            assert(ssh);
            bindingTablePointer = copyBindingTableAndSurfaceStates(ssh,
                                                                   function->getSurfaceStateHeap(),
                                                                   function->getSurfaceStateHeapSize(),
                                                                   bindingTableStateCount,
                                                                   function->getBindingTableOffset());
        }

        idd.setBindingTablePointer(bindingTablePointer);

        auto bindingTableStatePrefetchCount = std::min(31u, 0u); //TODO: bindingTableStateCount
        idd.setBindingTableEntryCount(bindingTableStatePrefetchCount);
    }

    // Copy the threadData to the indirect heap
    uint32_t sizeThreadData = sizePerThreadDataForWholeGroup + sizeCrossThreadData;
    uint32_t offsetThreadData = 0u;
    {
        function->setGroupCount(pThreadGroupDimensions->groupCountX,
                                pThreadGroupDimensions->groupCountY,
                                pThreadGroupDimensions->groupCountZ);

        auto heap = indirectHeaps[GENERAL_STATE];
        assert(heap);
        heap->align(COMPUTE_WALKER::INDIRECTDATASTARTADDRESS_ALIGN_SIZE);

        auto ptr = getHeapSpaceAllowGrow(GENERAL_STATE, sizeThreadData);
        assert(ptr);
        offsetThreadData = static_cast<uint32_t>(ptrDiff(ptr, heap->getCpuBase()));
        assert(offsetThreadData + sizeThreadData <= heap->getMaxAvailableSpace());

        memcpy(ptr, function->getCrossThreadDataHostMem(), sizeCrossThreadData);
        ptr = ptrOffset(ptr, sizeCrossThreadData);
        memcpy(ptr, function->getPerThreadDataHostMem(), sizePerThreadDataForWholeGroup);
    }

    if (this->dirtyHeaps) {
        EncodeFlush<gfxCoreFamily>::encode(*this);
        EncodeStateBaseAddress<gfxCoreFamily>::encode(*this);
        this->dirtyHeaps = 0u;
    }

    assert(sizePerThreadData && "TODO: enable HW generated local IDs");
    cmd.setEmitLocalId(!sizePerThreadData);
    cmd.setIndirectDataStartAddress(offsetThreadData);
    cmd.setIndirectDataLength(sizeThreadData);

    // Set # of threadgroups in each dimension
    assert(pThreadGroupDimensions);
    cmd.setThreadGroupIdXDimension(pThreadGroupDimensions->groupCountX);
    cmd.setThreadGroupIdYDimension(pThreadGroupDimensions->groupCountY);
    cmd.setThreadGroupIdZDimension(pThreadGroupDimensions->groupCountZ);

    // Set simd size
    auto simdSize = function->getSimdSize();
    auto simdSizeOp =
        COMPUTE_WALKER::SIMD_SIZE_SIMD32 * (simdSize == 32) |
        COMPUTE_WALKER::SIMD_SIZE_SIMD16 * (simdSize == 16) |
        COMPUTE_WALKER::SIMD_SIZE_SIMD8 * (simdSize == 8);
    cmd.setSimdSize(static_cast<COMPUTE_WALKER::SIMD_SIZE>(simdSizeOp));

    // Set the last thread execution mask
    cmd.setExecutionMask(function->getThreadExecutionMask());

    using POSTSYNC_DATA = typename GfxFamily::POSTSYNC_DATA;
    auto &postSync = cmd.getPostSync();
    if (hEvent) {
        auto event = Event::fromHandle(hEvent);
        assert(event);

        postSync.setOperation(POSTSYNC_DATA::OPERATION_WRITE_TIMESTAMP);
        auto gpuAddress = event->getGpuAddress();
        assert((gpuAddress & 63u) == 0u);
        postSync.setDestinationAddress(event->getGpuAddress());
    }

    // Commit our command to the commandStream
    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(decltype(cmd) *)buffer = cmd;

    // Attach Function residency to our CommandList residency
    {
        addToResidencyContainer(function->getIsaGraphicsAllocation().get());
        auto &residencyContainer = function->getResidencyContainer();
        for (auto resource : residencyContainer) {
            addToResidencyContainer(resource);
        }
    }

    // Store PrintfBuffer from a function
    {
        if (function->hasPrintfOutput()) {
            this->storePrintfFunction(function);
        }
    }

    return XE_RESULT_SUCCESS;
}

} // namespace L0
