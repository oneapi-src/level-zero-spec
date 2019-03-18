#include "cmdlist_hw.h"
#include "event.h"
#include "graphics_allocation.h"
#include "memory_manager.h"
#include "module.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/helpers/hw_info.h"
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

    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
void *CommandListCoreFamily<gfxCoreFamily>::getHeapSpaceAllowGrow(OCLRT::IndirectHeap &indirectHeap, size_t size) {
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
        for (uint32_t heapType = 0; heapType < NUM_HEAPS; ++heapType) {
            if (this->allocationIndirectHeaps[heapType]->allocationRT == oldAlloc) {
                allocationIndirectHeaps[heapType] = newAlloc;
                setHeap<gfxCoreFamily>(this->sba, static_cast<HeapType>(heapType), *indirectHeaps[heapType]);
                break;
            }
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
xe_result_t CommandListCoreFamily<gfxCoreFamily>::close() {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using MI_BATCH_BUFFER_END = typename GfxFamily::MI_BATCH_BUFFER_END;
    MI_BATCH_BUFFER_END cmd = GfxFamily::cmdInitBatchBufferEnd;
    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(MI_BATCH_BUFFER_END *)buffer = cmd;

    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
void CommandListCoreFamily<gfxCoreFamily>::programL3() {
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

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendLaunchFunction(xe_function_handle_t hFunction,
                                                                       const xe_thread_group_dimensions_t *pDispatchFuncArgs,
                                                                       xe_event_handle_t hEvent) {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using GPGPU_WALKER = typename GfxFamily::GPGPU_WALKER;
    using MEDIA_INTERFACE_DESCRIPTOR_LOAD = typename GfxFamily::MEDIA_INTERFACE_DESCRIPTOR_LOAD;
    using INTERFACE_DESCRIPTOR_DATA = typename GfxFamily::INTERFACE_DESCRIPTOR_DATA;

    // For now program L3 here.
    programL3();

    const auto function = Function::fromHandle(hFunction);
    assert(function);

    uint32_t offsetIDD = 0u;
    auto sizeCrossThreadData = static_cast<uint32_t>(function->getCrossThreadDataSize());
    auto sizePerThreadData = static_cast<uint32_t>(function->getPerThreadDataSize());
    {
        auto heap = indirectHeaps[OCLRT::IndirectHeap::DYNAMIC_STATE];
        assert(heap);

        auto sizeIDD = sizeof(INTERFACE_DESCRIPTOR_DATA);
        auto ptr = getHeapSpaceAllowGrow(*heap, sizeIDD);
        assert(ptr);
        auto offset = ptrDiff(ptr, heap->getCpuBase());
        assert(offset + sizeIDD <= heap->getMaxAvailableSpace());

        INTERFACE_DESCRIPTOR_DATA idd = GfxFamily::cmdInitInterfaceDescriptorData;

        // Point kernel start pointer to the proper offset of instruction heap
        {
            auto alloc = function->getIsaGraphicsAllocation();
            assert(nullptr != alloc);
            auto offset = alloc->getGpuAddressOffsetFromHeapBase();
            idd.setKernelStartPointer(offset);
            idd.setKernelStartPointerHigh(0u);
        }
        idd.setNumberOfThreadsInGpgpuThreadGroup(function->getThreadsPerThreadGroup());

        auto numGrfCrossThreadData = static_cast<uint32_t>(sizeCrossThreadData / sizeof(float[8]));
        assert(numGrfCrossThreadData > 0u);
        idd.setCrossThreadConstantDataReadLength(numGrfCrossThreadData);

        auto numGrfPerThreadData = static_cast<uint32_t>(sizePerThreadData / sizeof(float[8]));
        assert(numGrfPerThreadData > 0u);
        idd.setConstantIndirectUrbEntryReadLength(numGrfPerThreadData);
        idd.setBarrierEnable(function->getHasBarriers());

        memcpy(ptr, &idd, sizeof(idd));

        MEDIA_INTERFACE_DESCRIPTOR_LOAD cmd = GfxFamily::cmdInitMediaInterfaceDescriptorLoad;
        cmd.setInterfaceDescriptorDataStartAddress(offsetIDD);
        cmd.setInterfaceDescriptorTotalLength(sizeof(INTERFACE_DESCRIPTOR_DATA));

        auto buffer = commandStream->getSpace(sizeof(cmd));
        *(decltype(cmd) *)buffer = cmd;
    }

    GPGPU_WALKER cmd = GfxFamily::cmdInitGpgpuWalker;

    // Copy the threadData to the indirect heap
    {
        auto heap = indirectHeaps[INDIRECT_OBJECT];
        assert(heap);
        heap->align(GPGPU_WALKER::INDIRECTDATASTARTADDRESS_ALIGN_SIZE);

        auto sizeThreadData = sizePerThreadData + sizeCrossThreadData;

        auto ptr = getHeapSpaceAllowGrow(*heap, sizeThreadData);
        assert(ptr);
        auto offset = ptrDiff(ptr, heap->getCpuBase());
        assert(offset + sizeThreadData <= heap->getMaxAvailableSpace());

        memcpy(ptr, function->getCrossThreadDataHostMem(), sizeCrossThreadData);
        ptr = ptrOffset(ptr, sizeCrossThreadData);
        memcpy(ptr, function->getPerThreadDataHostMem(), sizePerThreadData);
        ptr = ptrOffset(ptr, sizePerThreadData);

        cmd.setIndirectDataLength(sizeThreadData);
        cmd.setIndirectDataStartAddress(static_cast<uint32_t>(offset));
    }

    // Set # of threadgroups in each dimension
    assert(pDispatchFuncArgs);
    cmd.setThreadGroupIdXDimension(pDispatchFuncArgs->groupCountX);
    cmd.setThreadGroupIdYDimension(pDispatchFuncArgs->groupCountY);
    cmd.setThreadGroupIdZDimension(pDispatchFuncArgs->groupCountZ);

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
        this->residencyContainer.push_back(function->getIsaGraphicsAllocation()->allocationRT);
        auto &residencyContainer = function->getResidencyContainer();
        for (auto resource : residencyContainer) {
            if (resource) {
                this->residencyContainer.push_back(resource->allocationRT);
            }
        }
    }

    // Commit our command to the commandStream
    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(decltype(cmd) *)buffer = cmd;

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
    return XE_RESULT_ERROR_UNSUPPORTED;
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
    residencyContainer.push_back(event->getAllocation().allocationRT);

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
    residencyContainer.push_back(event->getAllocation().allocationRT);

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
