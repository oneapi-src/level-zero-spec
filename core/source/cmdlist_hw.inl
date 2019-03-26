#include "cmdlist_hw.h"
#include "event.h"
#include "graphics_allocation.h"
#include "memory_manager.h"
#include "module.h"
#include "builtins.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/command_stream/preemption.h"
#include "runtime/helpers/hw_info.h"
#include "runtime/helpers/kernel_commands.h"
#include "runtime/helpers/hw_helper.h"
#include "runtime/helpers/string.h"
#include "runtime/indirect_heap/indirect_heap.h"
#include <cassert>

namespace L0 {

template <CommandContainer::HeapType HeapType>
struct StateBaseAddressHeap {
    template <GFXCORE_FAMILY gfxCoreFamily>
    static void set(void *sbaAddress, OCLRT::IndirectHeap &heap);
};

template <>
template <GFXCORE_FAMILY gfxCoreFamily>
inline void StateBaseAddressHeap<CommandContainer::DYNAMIC_STATE>::set(void *sbaAddress, OCLRT::IndirectHeap &heap) {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using STATE_BASE_ADDRESS = typename GfxFamily::STATE_BASE_ADDRESS;
    STATE_BASE_ADDRESS *cmd = static_cast<STATE_BASE_ADDRESS *>(sbaAddress);
    cmd->setDynamicStateBaseAddressModifyEnable(true);
    cmd->setDynamicStateBaseAddress(heap.getHeapGpuBase());
    cmd->setDynamicStateBufferSizeModifyEnable(true);
    cmd->setDynamicStateBufferSize(static_cast<uint32_t>(heap.getMaxAvailableSpace()));
}

template <>
template <GFXCORE_FAMILY gfxCoreFamily>
inline void StateBaseAddressHeap<CommandContainer::GENERAL_STATE>::set(void *sbaAddress, OCLRT::IndirectHeap &heap) {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using STATE_BASE_ADDRESS = typename GfxFamily::STATE_BASE_ADDRESS;
    STATE_BASE_ADDRESS *cmd = static_cast<STATE_BASE_ADDRESS *>(sbaAddress);
    cmd->setGeneralStateBaseAddressModifyEnable(true);
    cmd->setGeneralStateBaseAddress(heap.getHeapGpuBase());
    cmd->setGeneralStateBufferSizeModifyEnable(true);
    cmd->setGeneralStateBufferSize(static_cast<uint32_t>(heap.getMaxAvailableSpace()));
}

template <>
template <GFXCORE_FAMILY gfxCoreFamily>
inline void StateBaseAddressHeap<CommandContainer::INDIRECT_OBJECT>::set(void *sbaAddress, OCLRT::IndirectHeap &heap) {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using STATE_BASE_ADDRESS = typename GfxFamily::STATE_BASE_ADDRESS;
    STATE_BASE_ADDRESS *cmd = static_cast<STATE_BASE_ADDRESS *>(sbaAddress);
    cmd->setIndirectObjectBaseAddressModifyEnable(true);
    cmd->setIndirectObjectBaseAddress(heap.getHeapGpuBase());
    cmd->setIndirectObjectBufferSizeModifyEnable(true);
    cmd->setIndirectObjectBufferSize(static_cast<uint32_t>(heap.getMaxAvailableSpace()));
}

template <>
template <GFXCORE_FAMILY gfxCoreFamily>
inline void StateBaseAddressHeap<CommandContainer::SURFACE_STATE>::set(void *sbaAddress, OCLRT::IndirectHeap &heap) {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using STATE_BASE_ADDRESS = typename GfxFamily::STATE_BASE_ADDRESS;
    STATE_BASE_ADDRESS *cmd = static_cast<STATE_BASE_ADDRESS *>(sbaAddress);
    cmd->setSurfaceStateBaseAddressModifyEnable(true);
    cmd->setSurfaceStateBaseAddress(heap.getHeapGpuBase());
}

template <GFXCORE_FAMILY gfxCoreFamily>
void setHeap(void *sbaAddress, CommandList::HeapType heapType, OCLRT::IndirectHeap &heap) {
    switch (heapType) {
    default:
        assert(0);
        break;
    case CommandList::DYNAMIC_STATE:
        StateBaseAddressHeap<CommandList::DYNAMIC_STATE>::set<gfxCoreFamily>(sbaAddress, heap);
        break;
    case CommandList::GENERAL_STATE:
        StateBaseAddressHeap<CommandList::GENERAL_STATE>::set<gfxCoreFamily>(sbaAddress, heap);
        break;
    case CommandList::INDIRECT_OBJECT:
        StateBaseAddressHeap<CommandList::INDIRECT_OBJECT>::set<gfxCoreFamily>(sbaAddress, heap);
        break;
    case CommandList::SURFACE_STATE:
        StateBaseAddressHeap<CommandList::SURFACE_STATE>::set<gfxCoreFamily>(sbaAddress, heap);
        break;
    }
}

template <GFXCORE_FAMILY gfxCoreFamily>
bool CommandListCoreFamily<gfxCoreFamily>::initialize(Device *device) {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;

    if (!BaseClass::initialize(device)) {
        return false;
    }

    {
        using STATE_BASE_ADDRESS = typename GfxFamily::STATE_BASE_ADDRESS;
        STATE_BASE_ADDRESS cmd = GfxFamily::cmdInitStateBaseAddress;

        {
            auto heap = this->indirectHeaps[DYNAMIC_STATE];
            assert(heap != nullptr);
            StateBaseAddressHeap<DYNAMIC_STATE>::set<gfxCoreFamily>(&cmd, *heap);
        }

        {
            // note : this doesn't change
            cmd.setInstructionBaseAddressModifyEnable(true);
            cmd.setInstructionBaseAddress(this->device->getMemoryManager()->getIsaHeapGpuAddress());
            cmd.setInstructionBufferSizeModifyEnable(true);
            cmd.setInstructionBufferSize(MemoryConstants::sizeOf4GBinPageEntities); // no bounds checking
        }

        {
            auto heap = this->indirectHeaps[GENERAL_STATE];
            assert(heap != nullptr);
            StateBaseAddressHeap<GENERAL_STATE>::set<gfxCoreFamily>(&cmd, *heap);
        }

        {
            auto heap = this->indirectHeaps[INDIRECT_OBJECT];
            assert(heap != nullptr);
            StateBaseAddressHeap<INDIRECT_OBJECT>::set<gfxCoreFamily>(&cmd, *heap);
        }

        {
            auto heap = this->indirectHeaps[SURFACE_STATE];
            assert(heap != nullptr);
            StateBaseAddressHeap<SURFACE_STATE>::set<gfxCoreFamily>(&cmd, *heap);
        }

        auto buffer = commandStream->getSpace(sizeof(cmd));
        *(STATE_BASE_ADDRESS *)buffer = cmd;
        this->sba = buffer;
    }

    enableGpgpu();
    programFrontEndState();
    programPreemption();

    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
void *CommandListCoreFamily<gfxCoreFamily>::getHeapSpaceAllowGrow(CommandContainer::HeapType heapType, size_t size) {
    auto &indirectHeap = *indirectHeaps[heapType];

    if (indirectHeap.getAvailableSpace() < size) {
        // grow
        auto memoryManager = device->getMemoryManager();

        size_t newSize = indirectHeap.getUsed() + indirectHeap.getAvailableSpace();
        newSize *= 2; // grow by factor of 2
        newSize = std::max(newSize, indirectHeap.getAvailableSpace() + size);
        newSize = alignUp(newSize, 4096U);
        auto oldAlloc = indirectHeap.getGraphicsAllocation();
        auto newAlloc = memoryManager->allocateDeviceMemory(newSize, 4096u);
        assert(oldAlloc);
        assert(newAlloc);
        auto alreadyUsedSize = indirectHeap.getUsed();
        indirectHeap.replaceGraphicsAllocation(newAlloc->allocationRT);
        indirectHeap.replaceBuffer(newAlloc->allocationRT->getUnderlyingBuffer(), newAlloc->allocationRT->getUnderlyingBufferSize());
        memcpy_s(indirectHeap.getSpace(alreadyUsedSize), alreadyUsedSize, oldAlloc->getUnderlyingBuffer(), alreadyUsedSize);
        *std::find(residencyContainer.begin(), residencyContainer.end(), oldAlloc) = newAlloc->allocationRT;
        if (this->allocationIndirectHeaps[heapType]->allocationRT == oldAlloc) {
            allocationIndirectHeaps[heapType] = newAlloc;
            setHeap<gfxCoreFamily>(this->sba, heapType, indirectHeap);
        }
        delete oldAlloc;
    }
    return indirectHeap.getSpace(size);
}

template <GFXCORE_FAMILY gfxCoreFamily>
void CommandListCoreFamily<gfxCoreFamily>::enableGpgpu() {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;

    using PIPELINE_SELECT = typename GfxFamily::PIPELINE_SELECT;
    PIPELINE_SELECT cmd = GfxFamily::cmdInitPipelineSelect;
    cmd.setPipelineSelection(PIPELINE_SELECT::PIPELINE_SELECTION_GPGPU);
    cmd.setMaskBits(3u); //TODO:  Add support for DOP clock gating

    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(PIPELINE_SELECT *)buffer = cmd;
}

template <GFXCORE_FAMILY gfxCoreFamily>
void CommandListCoreFamily<gfxCoreFamily>::programFrontEndState() {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;

    using MEDIA_VFE_STATE = typename GfxFamily::MEDIA_VFE_STATE;
    MEDIA_VFE_STATE cmd = GfxFamily::cmdInitMediaVfeState;
    cmd.setNumberOfUrbEntries(1u);
    uint32_t urbEntryAllocationSize = 0x782; //TODO:  Gen family specific
    cmd.setUrbEntryAllocationSize(urbEntryAllocationSize);
    uint32_t maxNumThreads = 16u; //TODO:  get this from HwInfo
    cmd.setMaximumNumberOfThreads(maxNumThreads);

    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(MEDIA_VFE_STATE *)buffer = cmd;
}

template <GFXCORE_FAMILY gfxCoreFamily>
void CommandListCoreFamily<gfxCoreFamily>::programPreemption() {
    // TODO : Add support for midthread preemption
    // TODO : Reuse NEO's PreemptionHelper (requires refactoring because of linker problems)
    constexpr uint32_t mmioAddress = 0x2580;
    constexpr uint32_t maskVal = (1 << 1) | (1 << 2);
    constexpr uint32_t maskShift = 16;
    constexpr uint32_t mask = maskVal << maskShift;
    constexpr uint32_t threadGroupVal = (1 << 1);
    constexpr uint32_t regVal = threadGroupVal | mask;
    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    OCLRT::LriHelper<GfxFamily>::program(commandStream, mmioAddress, regVal);
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::close() {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using MI_BATCH_BUFFER_END = typename GfxFamily::MI_BATCH_BUFFER_END;
    MI_BATCH_BUFFER_END cmd = GfxFamily::cmdInitBatchBufferEnd;
    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(MI_BATCH_BUFFER_END *)buffer = cmd;

    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
void CommandListCoreFamily<gfxCoreFamily>::programL3(bool isSLMused) {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    {
        using PIPE_CONTROL = typename GfxFamily::PIPE_CONTROL;
        PIPE_CONTROL cmd = GfxFamily::cmdInitPipeControl;
        cmd.setCommandStreamerStallEnable(true);
        cmd.setDcFlushEnable(true);
        auto buffer = commandStream->getSpace(sizeof(cmd));
        *(PIPE_CONTROL *)buffer = cmd;
    }

    {
        using MI_LOAD_REGISTER_IMM = typename GfxFamily::MI_LOAD_REGISTER_IMM;
        MI_LOAD_REGISTER_IMM cmd = GfxFamily::cmdInitLoadRegisterImm;
        uint32_t offsetL3CNTL = 0x7013u;
        uint32_t dataL3CNTL = 0x80000140u;
        cmd.setRegisterOffset(offsetL3CNTL);
        cmd.setDataDword(dataL3CNTL);
        auto buffer = commandStream->getSpace(sizeof(cmd));
        *(MI_LOAD_REGISTER_IMM *)buffer = cmd;
    }
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendCommandLists(uint32_t numCommandLists,
                                                                     xe_command_list_handle_t *phCommandLists) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

// Returned binding table pointer is relative to given heap (which is assumed to be the Surface state base addess)
// as required by the INTERFACE_DESCRIPTOR_DATA.
template <GFXCORE_FAMILY gfxCoreFamily>
uint32_t CommandListCoreFamily<gfxCoreFamily>::copyBindingTableAndSurfaceStates(OCLRT::IndirectHeap *ssh,
                                                                                const void *srcSsh, uint32_t srcSshSize,
                                                                                uint32_t numberOfBindingTableStates, uint32_t offsetOfBindingTable) {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using BINDING_TABLE_STATE = typename GfxFamily::BINDING_TABLE_STATE;
    using INTERFACE_DESCRIPTOR_DATA = typename GfxFamily::INTERFACE_DESCRIPTOR_DATA;

    assert(ssh);
    assert(srcSsh);

    // Align the heap and allocate space for new ssh data
    ssh->align(BINDING_TABLE_STATE::SURFACESTATEPOINTER_ALIGN_SIZE);
    auto dstSurfaceState = ssh->getSpace(srcSshSize);

    // Compiler sends BTI table that is already populated with surface state pointers relative to local SSH.
    // We may need to patch these pointers so that they are relative to surface state base address
    if (dstSurfaceState == ssh->getCpuBase()) {
        // nothing to patch, we're at the start of heap (which is assumed to be the surface state base address)
        // we need to simply copy the ssh (including BTIs from compiler)
        memcpy_s(dstSurfaceState, srcSshSize, srcSsh, srcSshSize);
        return offsetOfBindingTable;
    }

    // We can copy-over the surface states, but BTIs will need to be patched
    memcpy_s(dstSurfaceState, srcSshSize, srcSsh, offsetOfBindingTable);

    uint32_t surfaceStatesOffset = static_cast<uint32_t>(ptrDiff(dstSurfaceState, ssh->getCpuBase()));

    // march over BTIs and offset the pointers based on surface state base address
    auto *dstBindingTable = reinterpret_cast<BINDING_TABLE_STATE *>(ptrOffset(dstSurfaceState, offsetOfBindingTable));
    assert(reinterpret_cast<uintptr_t>(dstBindingTable) % INTERFACE_DESCRIPTOR_DATA::BINDINGTABLEPOINTER_ALIGN_SIZE == 0);

    auto *srcBindingTable = reinterpret_cast<const BINDING_TABLE_STATE *>(ptrOffset(srcSsh, offsetOfBindingTable));
    BINDING_TABLE_STATE bts = GfxFamily::cmdInitBindingTableState;

    for (uint32_t i = 0; i < numberOfBindingTableStates; ++i) {
        uint32_t localSurfaceStateOffset = srcBindingTable[i].getSurfaceStatePointer();
        uint32_t offsetedSurfaceStateOffset = localSurfaceStateOffset + surfaceStatesOffset;

        bts.setSurfaceStatePointer(offsetedSurfaceStateOffset);
        dstBindingTable[i] = bts;
        assert(bts.getRawData(0) % sizeof(BINDING_TABLE_STATE::SURFACESTATEPOINTER_ALIGN_SIZE) == 0);
    }

    return static_cast<uint32_t>(ptrDiff(dstBindingTable, ssh->getCpuBase()));
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendLaunchFunction(xe_function_handle_t hFunction,
                                                                       const xe_thread_group_dimensions_t *pThreadGroupDimensions,
                                                                       xe_event_handle_t hEvent) {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using GPGPU_WALKER = typename GfxFamily::GPGPU_WALKER;
    using MEDIA_STATE_FLUSH = typename GfxFamily::MEDIA_STATE_FLUSH;
    using MEDIA_INTERFACE_DESCRIPTOR_LOAD = typename GfxFamily::MEDIA_INTERFACE_DESCRIPTOR_LOAD;
    using INTERFACE_DESCRIPTOR_DATA = typename GfxFamily::INTERFACE_DESCRIPTOR_DATA;
    using STATE_BASE_ADDRESS = typename GfxFamily::STATE_BASE_ADDRESS;

    const auto function = Function::fromHandle(hFunction);
    assert(function);

    // For now program L3 here.
    bool slmUsage = function->getSlmSize() > 0;
    programL3(slmUsage);

    auto threadsPerThreadGroup = function->getThreadsPerThreadGroup();

    uint32_t numIDD = 0u;
    auto sizeCrossThreadData = function->getCrossThreadDataSize();
    auto sizePerThreadData = function->getPerThreadDataSize();
    auto sizePerThreadDataForWholeGroup = function->getPerThreadDataSizeForWholeThreadGroup();
    {
        auto heap = indirectHeaps[DYNAMIC_STATE];
        assert(heap);
        heap->align(OCLRT::KernelCommandsHelper<GfxFamily>::alignInterfaceDescriptorData);

        auto sizeIDD = sizeof(INTERFACE_DESCRIPTOR_DATA);
        auto ptr = getHeapSpaceAllowGrow(DYNAMIC_STATE, sizeIDD);
        assert(ptr);
        auto offsetIDD = ptrDiff(ptr, heap->getCpuBase());
        assert(offsetIDD + sizeIDD <= heap->getMaxAvailableSpace());
        assert(0 == offsetIDD % sizeof(INTERFACE_DESCRIPTOR_DATA));

        INTERFACE_DESCRIPTOR_DATA idd = GfxFamily::cmdInitInterfaceDescriptorData;

        // Point kernel start pointer to the proper offset of instruction heap
        {
            auto alloc = function->getIsaGraphicsAllocation();
            assert(nullptr != alloc);
            auto offset = alloc->getGpuAddressOffsetFromHeapBase();
            idd.setKernelStartPointer(offset);
            idd.setKernelStartPointerHigh(0u);
        }
        idd.setNumberOfThreadsInGpgpuThreadGroup(threadsPerThreadGroup);

        auto numGrfCrossThreadData = static_cast<uint32_t>(sizeCrossThreadData / sizeof(float[8]));
        assert(numGrfCrossThreadData > 0u);
        idd.setCrossThreadConstantDataReadLength(numGrfCrossThreadData);

        auto numGrfPerThreadData = static_cast<uint32_t>(sizePerThreadData / sizeof(float[8]));
        assert(numGrfPerThreadData > 0u);
        idd.setConstantIndirectUrbEntryReadLength(numGrfPerThreadData);
        idd.setBarrierEnable(function->getHasBarriers());

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

        memcpy(ptr, &idd, sizeof(idd));

        // A Media_State_Flush should be used before MEDIA_INTERFACE_DESCRIPTOR_LOAD to ensure that
        // the temporary Interface Descriptor storage is cleared.
        auto mediaStateFlush = commandStream->getSpace(sizeof(MEDIA_STATE_FLUSH));
        *reinterpret_cast<MEDIA_STATE_FLUSH *>(mediaStateFlush) = GfxFamily::cmdInitMediaStateFlush;

        MEDIA_INTERFACE_DESCRIPTOR_LOAD cmd = GfxFamily::cmdInitMediaInterfaceDescriptorLoad;
        cmd.setInterfaceDescriptorDataStartAddress(static_cast<uint32_t>(offsetIDD));
        cmd.setInterfaceDescriptorTotalLength(sizeof(INTERFACE_DESCRIPTOR_DATA));
        numIDD = 0U; // change to IDD within MEDIA_INTERFACE_DESCRIPTOR_LOAD once we start grouping IDDs

        auto buffer = commandStream->getSpace(sizeof(cmd));
        *(decltype(cmd) *)buffer = cmd;
    }

    GPGPU_WALKER cmd = GfxFamily::cmdInitGpgpuWalker;
    cmd.setInterfaceDescriptorOffset(numIDD);

    function->setGroupCount(pThreadGroupDimensions->groupCountX,
                            pThreadGroupDimensions->groupCountY,
                            pThreadGroupDimensions->groupCountZ);
    // Copy the threadData to the indirect heap
    {
        auto heap = indirectHeaps[INDIRECT_OBJECT];
        assert(heap);
        heap->align(GPGPU_WALKER::INDIRECTDATASTARTADDRESS_ALIGN_SIZE);

        auto sizeThreadData = sizePerThreadDataForWholeGroup + sizeCrossThreadData;

        auto ptr = getHeapSpaceAllowGrow(INDIRECT_OBJECT, sizeThreadData);
        assert(ptr);
        auto offset = ptrDiff(ptr, heap->getCpuBase());
        assert(offset + sizeThreadData <= heap->getMaxAvailableSpace());

        memcpy(ptr, function->getCrossThreadDataHostMem(), sizeCrossThreadData);
        ptr = ptrOffset(ptr, sizeCrossThreadData);
        memcpy(ptr, function->getPerThreadDataHostMem(), sizePerThreadDataForWholeGroup);
        ptr = ptrOffset(ptr, sizePerThreadDataForWholeGroup);

        cmd.setIndirectDataLength(sizeThreadData);
        cmd.setIndirectDataStartAddress(static_cast<uint32_t>(offset));
    }

    // Set # of threadgroups in each dimension
    assert(pThreadGroupDimensions);
    cmd.setThreadWidthCounterMaximum(threadsPerThreadGroup);
    cmd.setThreadGroupIdXDimension(pThreadGroupDimensions->groupCountX);
    cmd.setThreadGroupIdYDimension(pThreadGroupDimensions->groupCountY);
    cmd.setThreadGroupIdZDimension(pThreadGroupDimensions->groupCountZ);

    // Set simd size
    auto simdSize = function->getSimdSize();
    auto simdSizeOp =
        GPGPU_WALKER::SIMD_SIZE_SIMD32 * (simdSize == 32) |
        GPGPU_WALKER::SIMD_SIZE_SIMD16 * (simdSize == 16) |
        GPGPU_WALKER::SIMD_SIZE_SIMD8 * (simdSize == 8);
    cmd.setSimdSize(static_cast<typename GPGPU_WALKER::SIMD_SIZE>(simdSizeOp));
    cmd.setRightExecutionMask(function->getThreadExecutionMask());
    cmd.setBottomExecutionMask(0xffffffff);

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

    // Commit our command to the commandStream
    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(decltype(cmd) *)buffer = cmd;

    {
        // A MEDIA_STATE_FLUSH with no options must be added after a GPGPU_WALKER command which doesn't use either SLM or barriers.
        auto mediaStateFlush = commandStream->getSpace(sizeof(MEDIA_STATE_FLUSH));
        *reinterpret_cast<MEDIA_STATE_FLUSH *>(mediaStateFlush) = GfxFamily::cmdInitMediaStateFlush;
    }

    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendLaunchFunctionIndirect(xe_function_handle_t hFunction,
                                                                               const xe_thread_group_dimensions_t *pDispatchArgumentsBuffer,
                                                                               xe_event_handle_t hEvent) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendLaunchHostFunction(xe_host_pfn_t pfnHostFunc,
                                                                           void *pUserData) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendLaunchMultipleFunctionsIndirect(uint32_t numFunctions,
                                                                                        const xe_function_handle_t *phFunctions,
                                                                                        const size_t *pNumLaunchArguments,
                                                                                        const xe_thread_group_dimensions_t *pLaunchArgumentsBuffer,
                                                                                        xe_event_handle_t hEvent) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendEventReset(xe_event_handle_t hEvent) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendExecutionBarrier() {

    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using PIPE_CONTROL = typename GfxFamily::PIPE_CONTROL;
    PIPE_CONTROL cmd = GfxFamily::cmdInitPipeControl;
    cmd.setCommandStreamerStallEnable(true);
    cmd.setDcFlushEnable(true);
    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(PIPE_CONTROL *)buffer = cmd;

    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendImageCopyFromMemory(xe_image_handle_t hDstImage,
                                                                            xe_image_region_t *pDstRegion,
                                                                            const void *srcptr) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendImageCopyToMemory(void *dstptr,
                                                                          xe_image_handle_t hSrcImage,
                                                                          xe_image_region_t *pSrcRegion) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendImageCopyRegion(xe_image_handle_t hDstImage,
                                                                        xe_image_region_t *pDstRegion,
                                                                        xe_image_handle_t hSrcImage,
                                                                        xe_image_region_t *pSrcRegion) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendImageCopy(xe_image_handle_t hDstImage,
                                                                  xe_image_handle_t hSrcImage) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendMemAdvise(xe_device_handle_t hDevice,
                                                                  const void *ptr,
                                                                  size_t size,
                                                                  xe_memory_advice_t advice) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendMemoryCopy(void *dstptr,
                                                                   const void *srcptr,
                                                                   size_t size) {
    xe_module_handle_t module;
    xe_function_handle_t functionHandle;
    // TODO : Make these persisten
    //        * can't do compilations at each appendMemoryCopy
    //        * who is responsible for freeing module/function?
    xe_module_desc_t moduleDesc = {XE_MODULE_DESC_VERSION_CURRENT};
    moduleDesc.format = XE_MODULE_FORMAT_IL_SPIRV;
    moduleDesc.pInputModule = compileCopyBufferToBufferBin.getModule();
    moduleDesc.inputSize = compileCopyBufferToBufferBin.getSize();
    if (xeDeviceCreateModule(this->device, &moduleDesc, &module, nullptr))
        return XE_RESULT_ERROR_UNKNOWN;

    xe_function_desc_t functionDesc = {XE_FUNCTION_DESC_VERSION_CURRENT};
    functionDesc.pFunctionName = compileCopyBufferToBufferBin.getFunctionName();
    if (xeModuleCreateFunction(module, &functionDesc, &functionHandle))
        return XE_RESULT_ERROR_UNKNOWN;

    /* Using defaults for now. We need to change this */
    auto func = Function::fromHandle(functionHandle);
    uint32_t groupSizeX = func->getSimdSize(); // TODO : consider ATS fused threads
    uint32_t groupSizeY = 1u;
    uint32_t groupSizeZ = 1u;
    if (func->setGroupSize(groupSizeX, groupSizeY, groupSizeZ))
        return XE_RESULT_ERROR_UNKNOWN;

    GraphicsAllocation *alloc = this->device->getMemoryManager()->findAllocation(dstptr);
    if (alloc == nullptr) {
        // Trying to access non-driver memallocated for dstptr: Allocate managed memory using the host's buffer
        auto allocation = this->device->getMemoryManager()->allocateManagedMemoryFromFault(dstptr, size);
    }
    func->setArgumentValue(0, sizeof(dstptr), &dstptr);

    alloc = this->device->getMemoryManager()->findAllocation(srcptr);
    if (alloc == nullptr) {
        // Trying to access non-driver memallocated for dstptr: Allocate managed memory using the host's buffer
        auto allocation = this->device->getMemoryManager()->allocateManagedMemoryFromFault(const_cast<void *>(srcptr), size);
    }
    func->setArgumentValue(1, sizeof(srcptr), &srcptr);

    constexpr auto elementSize = sizeof(char);
    assert(size / (groupSizeX * elementSize) < MemoryConstants::gigaByte);
    uint32_t whole = static_cast<uint32_t>(size / (groupSizeX * elementSize));
    uint32_t rest = static_cast<uint32_t>(size - whole * groupSizeX * elementSize);
    xe_thread_group_dimensions_t dispatchFuncArgs{whole, 1u, 1u};

    auto ret = XE_RESULT_SUCCESS;
    if (whole > 0) {
        ret = this->appendLaunchFunction(functionHandle, &dispatchFuncArgs, nullptr);
    }
    if ((XE_RESULT_SUCCESS != ret) || (rest == 0)) {
        return ret;
    }
    dstptr = ptrOffset(dstptr, whole * groupSizeX * elementSize);
    srcptr = ptrOffset(srcptr, whole * groupSizeX * elementSize);
    func->setArgumentValue(0, sizeof(dstptr), &dstptr);
    func->setArgumentValue(1, sizeof(srcptr), &srcptr);
    if (func->setGroupSize(rest, 1u, 1u)) {
        return XE_RESULT_ERROR_UNKNOWN;
    }
    dispatchFuncArgs.groupCountX = 1;

    return this->appendLaunchFunction(functionHandle, &dispatchFuncArgs, nullptr);
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendMemoryPrefetch(const void *ptr,
                                                                       size_t count) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendMemorySet(void *ptr,
                                                                  int value,
                                                                  size_t size) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendSignalEvent(xe_event_handle_t hEvent) {
    auto event = Event::fromHandle(hEvent);
    assert(event);
    addToResidencyContainer(&event->getAllocation());

    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using PIPE_CONTROL = typename GfxFamily::PIPE_CONTROL;
    using POST_SYNC_OPERATION = typename PIPE_CONTROL::POST_SYNC_OPERATION;
    PIPE_CONTROL cmd = GfxFamily::cmdInitPipeControl;
    cmd.setPostSyncOperation(POST_SYNC_OPERATION::POST_SYNC_OPERATION_WRITE_IMMEDIATE_DATA);
    cmd.setImmediateData(0u);
    cmd.setCommandStreamerStallEnable(true);
    auto gpuAddress = event->getGpuAddress();
    cmd.setAddressHigh(gpuAddress >> 32u);
    cmd.setAddress(uint32_t(gpuAddress));

    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(PIPE_CONTROL *)buffer = cmd;
    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendWaitOnEvent(xe_event_handle_t hEvent) {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using MI_SEMAPHORE_WAIT = typename GfxFamily::MI_SEMAPHORE_WAIT;
    MI_SEMAPHORE_WAIT cmd = GfxFamily::cmdInitMiSemaphoreWait;
    auto event = Event::fromHandle(hEvent);
    assert(event);
    addToResidencyContainer(&event->getAllocation());

    cmd.setSemaphoreGraphicsAddress(event->getGpuAddress());
    cmd.setSemaphoreDataDword(1u);
    cmd.setCompareOperation(MI_SEMAPHORE_WAIT::COMPARE_OPERATION::COMPARE_OPERATION_SAD_NOT_EQUAL_SDD);

    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(MI_SEMAPHORE_WAIT *)buffer = cmd;
    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::getParameter(xe_command_list_parameter_t parameter, uint32_t *value) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::reserveSpace(size_t size,
                                                               void **ptr) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::reset() {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::resetParameters() {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::setParameter(xe_command_list_parameter_t parameter,
                                                               uint32_t value) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

} // namespace L0
