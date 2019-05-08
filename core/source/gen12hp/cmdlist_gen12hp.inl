#include "runtime/gen12hp/hw_cmds.h"
#include "runtime/gen12hp/hw_info.h"
#include "runtime/indirect_heap/indirect_heap.h"
#include "cmdlist_hw.inl"
#include "module.h"
#include "igfxfmid.h"

namespace L0 {

template <> struct EncodeStateBaseAddress<IGFX_GEN12_CORE> {
    static const GFXCORE_FAMILY gfxCoreFamily = IGFX_GEN12_CORE;
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using STATE_BASE_ADDRESS = typename GfxFamily::STATE_BASE_ADDRESS;
    using _3DSTATE_BINDING_TABLE_POOL_ALLOC = typename GfxFamily::_3DSTATE_BINDING_TABLE_POOL_ALLOC;

    static const size_t size =
        sizeof(STATE_BASE_ADDRESS) + sizeof(_3DSTATE_BINDING_TABLE_POOL_ALLOC);

    static void encode(CommandContainer &container) {
        STATE_BASE_ADDRESS cmd = GfxFamily::cmdInitStateBaseAddress;

        if (container.dirtyHeaps & (1u << CommandContainer::DYNAMIC_STATE)) {
            auto &heap = container.getIndirectHeap(CommandContainer::DYNAMIC_STATE);
            cmd.setDynamicStateBaseAddressModifyEnable(true);
            cmd.setDynamicStateBaseAddress(heap.getHeapGpuBase());
            cmd.setDynamicStateBufferSizeModifyEnable(true);
            cmd.setDynamicStateBufferSize(static_cast<uint32_t>(heap.getMaxAvailableSpace()));
        }

        if (container.dirtyHeaps & (1u << CommandContainer::GENERAL_STATE)) {
            auto &heap = container.getIndirectHeap(CommandContainer::GENERAL_STATE);
            cmd.setGeneralStateBaseAddressModifyEnable(true);
            cmd.setGeneralStateBaseAddress(heap.getHeapGpuBase());
            cmd.setGeneralStateBufferSizeModifyEnable(true);
            cmd.setGeneralStateBufferSize(static_cast<uint32_t>(heap.getMaxAvailableSpace()));
        }

        if (container.dirtyHeaps & (1u << CommandContainer::INDIRECT_OBJECT)) {
            auto &heap = container.getIndirectHeap(CommandContainer::INDIRECT_OBJECT);
            cmd.setIndirectObjectBaseAddressModifyEnable(true);
            cmd.setIndirectObjectBaseAddress(heap.getHeapGpuBase());
            cmd.setIndirectObjectBufferSizeModifyEnable(true);
            cmd.setIndirectObjectBufferSize(static_cast<uint32_t>(heap.getMaxAvailableSpace()));
        }

        if (container.dirtyHeaps & (1u << CommandContainer::SURFACE_STATE)) {
            auto &heap = container.getIndirectHeap(CommandContainer::SURFACE_STATE);
            cmd.setSurfaceStateBaseAddressModifyEnable(true);
            cmd.setSurfaceStateBaseAddress(heap.getHeapGpuBase());
        }

        {
            // note : this doesn't change
            cmd.setInstructionBaseAddressModifyEnable(true);
            cmd.setInstructionBaseAddress(container.getInstructionHeapBaseAddress());
            cmd.setInstructionBufferSizeModifyEnable(true);
            cmd.setInstructionBufferSize(
                MemoryConstants::sizeOf4GBinPageEntities); // no bounds checking
        }

        // Program caches
        auto mocsMapper = container.getDevice()->getMOCSMapper();
        cmd.setInstructionMemoryObjectControlState(mocsMapper->getCachedInstructionHeapMOCS());
        // TODO : Stateless MOCS can't be cached unconditionally for e.g. when false cacheline
        // sharing with CPU (hotptrs)
        cmd.setStatelessDataPortAccessMemoryObjectControlState(mocsMapper->getFullyCachedMOCS());

        auto buffer = container.getCommandStream().getSpace(sizeof(cmd));
        *(STATE_BASE_ADDRESS *)buffer = cmd;

        // Have to program _3DSTATE_BINDING_TABLE_POOL_ALLOC to match STATE_BASE_ADDRESS for SSH
        if (container.dirtyHeaps & (1u << CommandContainer::SURFACE_STATE)) {
            auto &heap = container.getIndirectHeap(CommandContainer::SURFACE_STATE);
            auto cmd = GfxFamily::cmdInitStateBindingTablePoolAlloc;
            cmd.setBindingTablePoolBaseAddress(heap.getHeapGpuBase());
            cmd.setBindingTablePoolBufferSize(heap.getHeapSizeInPages());
            cmd.setSurfaceObjectControlStateIndexToMocsTables(mocsMapper->getCachedStateHeapMOCS());

            auto buffer = container.getCommandStream().getSpace(sizeof(cmd));
            *(_3DSTATE_BINDING_TABLE_POOL_ALLOC *)buffer = cmd;
        }
    }
};

template <> void CommandListCoreFamily<IGFX_GEN12_CORE>::programFrontEndState() {
    using GfxFamily = typename NEO::GfxFamilyMapper<IGFX_GEN12_CORE>::GfxFamily;

    {
        using CFE_STATE = typename GfxFamily::CFE_STATE;
        CFE_STATE cmd = GfxFamily::cmdInitCfeState;
        auto buffer = commandStream->getSpace(sizeof(cmd));
        *(CFE_STATE *)buffer = cmd;
    }
}

template <> void CommandListCoreFamily<IGFX_GEN12_CORE>::programPreemption() {
    // TODO : Reuse NEO's PreemptionHelper (requires refactoring because of linker problems)
}

template <>
xe_result_t CommandListCoreFamily<IGFX_GEN12_CORE>::appendLaunchFunction(
    xe_function_handle_t hFunction, const xe_thread_group_dimensions_t *pThreadGroupDimensions,
    xe_event_handle_t hEvent, uint32_t numWaitEvents, xe_event_handle_t *phWaitEvents) {
    constexpr GFXCORE_FAMILY gfxCoreFamily = IGFX_GEN12_CORE;
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using COMPUTE_WALKER = typename GfxFamily::COMPUTE_WALKER;
    using INTERFACE_DESCRIPTOR_DATA = typename GfxFamily::INTERFACE_DESCRIPTOR_DATA;
    using STATE_BASE_ADDRESS = typename GfxFamily::STATE_BASE_ADDRESS;

    const auto function = Function::fromHandle(hFunction);
    assert(function);
    const auto functionImmutableData = function->getImmutableData();
    const auto &functionSignature = functionImmutableData->getSignature();
    auto sizeCrossThreadData = function->getCrossThreadDataSize();
    auto sizePerThreadData = function->getPerThreadDataSize();
    auto sizePerThreadDataForWholeGroup = function->getPerThreadDataSizeForWholeThreadGroup();

    COMPUTE_WALKER cmd = GfxFamily::cmdInitGpgpuWalker;
    auto &idd = cmd.getInterfaceDescriptor();

    // Point kernel start pointer to the proper offset of instruction heap
    {
        auto alloc = function->getImmutableData()->getIsaGraphicsAllocation();
        assert(nullptr != alloc);
        auto offset = alloc->getGpuAddressOffsetFromHeapBase();
        idd.setKernelStartPointer(offset);
        idd.setKernelStartPointerHigh(0u);
    }

    auto threadsPerThreadGroup = function->getThreadsPerThreadGroup();
    idd.setNumberOfThreadsInGpgpuThreadGroup(threadsPerThreadGroup);

    idd.setBarrierEnable(functionSignature.attributes.flags.hasBarriers);
    idd.setSharedLocalMemorySize(
        functionSignature.attributes.slmInlineSize > 0
            ? INTERFACE_DESCRIPTOR_DATA::SHARED_LOCAL_MEMORY_SIZE_ENCODES_64K
            : INTERFACE_DESCRIPTOR_DATA::SHARED_LOCAL_MEMORY_SIZE_ENCODES_0K);

    // Set up binding table and surface states
    {
        auto bindingTableStateCount = functionSignature.bindingTable.numSurfaceStates;
        uint32_t bindingTablePointer = 0u;

        if (bindingTableStateCount > 0u) {
            auto ssh = indirectHeaps[SURFACE_STATE];
            assert(ssh);
            bindingTablePointer = copyBindingTableAndSurfaceStates(
                ssh, function->getSurfaceStateHeapData().get(),
                function->getSurfaceStateHeapDataSize(), bindingTableStateCount,
                functionSignature.bindingTable.tableOffset);
        }

        idd.setBindingTablePointer(bindingTablePointer);

        auto bindingTableStatePrefetchCount = std::min(31u, 0u); // TODO: bindingTableStateCount
        idd.setBindingTableEntryCount(bindingTableStatePrefetchCount);
    }

    uint32_t samplerStateOffset = 0;
    uint32_t samplerCount = 0;

    // Copy our sampler state if it exists
    if (functionSignature.samplerTable.numSamplers > 0) {
        samplerCount = functionSignature.samplerTable.numSamplers;
        samplerStateOffset = copySamplerState(
            indirectHeaps[DYNAMIC_STATE], functionSignature.samplerTable.tableOffset,
            functionSignature.samplerTable.numSamplers, functionSignature.samplerTable.borderColor,
            function->getDynamicStateHeapData().get());
    }

    idd.setSamplerStatePointer(samplerStateOffset);
    auto samplerCountState =
        static_cast<typename INTERFACE_DESCRIPTOR_DATA::SAMPLER_COUNT>((samplerCount + 3) / 4);
    idd.setSamplerCount(samplerCountState);

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

        memcpy(ptr, function->getCrossThreadData().get(), sizeCrossThreadData);
        ptr = ptrOffset(ptr, sizeCrossThreadData);
        memcpy(ptr, function->getPerThreadData().get(), sizePerThreadDataForWholeGroup);
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
    auto simdSize = functionSignature.attributes.simdSize;
    auto simdSizeOp = COMPUTE_WALKER::SIMD_SIZE_SIMD32 * (simdSize == 32) |
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

        addToResidencyContainer(&event->getAllocation());
    }

    // Commit our command to the commandStream
    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(decltype(cmd) *)buffer = cmd;

    // Attach Function residency to our CommandList residency
    {
        addToResidencyContainer(functionImmutableData->getIsaGraphicsAllocation().get());
        auto &residencyContainer = function->getResidencyContainer();
        for (auto resource : residencyContainer) {
            addToResidencyContainer(resource);
        }
    }

    // Store PrintfBuffer from a function
    {
        if (functionImmutableData->getSignature().attributes.flags.hasPrintf) {
            this->storePrintfFunction(function);
        }
    }

    return XE_RESULT_SUCCESS;
}

} // namespace L0
