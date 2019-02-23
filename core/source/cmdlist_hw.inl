#include "cmdlist_hw.h"
#include "event.h"
#include "graphics_allocation.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/helpers/hw_info.h"
#include "runtime/indirect_heap/indirect_heap.h"
#include <cassert>

namespace xe {

template <uint32_t gfxCoreFamily>
bool CommandListHw<gfxCoreFamily>::initialize() {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(gfxCoreFamily)>::GfxFamily;

    if (!BaseClass::initialize()) {
        return false;
    }

    {
        using STATE_BASE_ADDRESS = typename GfxFamily::STATE_BASE_ADDRESS;
        STATE_BASE_ADDRESS cmd = GfxFamily::cmdInitStateBaseAddress;

        {
            auto heap = this->indirectHeaps[INSTRUCTION];
            assert(heap != nullptr);
            cmd.setInstructionBaseAddressModifyEnable(true);
            cmd.setInstructionBaseAddress(heap->getHeapGpuBase());
            cmd.setInstructionBufferSizeModifyEnable(true);
            cmd.setInstructionBufferSize(static_cast<uint32_t>(heap->getMaxAvailableSpace()));
        }

        {
            auto heap = this->indirectHeaps[GENERAL_STATE];
            assert(heap != nullptr);
            cmd.setGeneralStateBaseAddressModifyEnable(true);
            cmd.setGeneralStateBaseAddress(heap->getHeapGpuBase());
            cmd.setGeneralStateBufferSizeModifyEnable(true);
            cmd.setGeneralStateBufferSize(static_cast<uint32_t>(heap->getMaxAvailableSpace()));
        }

        auto buffer = commandStream->getSpace(sizeof(cmd));
        *(STATE_BASE_ADDRESS *)buffer = cmd;
    }

    return true;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::close() {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(gfxCoreFamily)>::GfxFamily;
    using MI_BATCH_BUFFER_END = typename GfxFamily::MI_BATCH_BUFFER_END;
    MI_BATCH_BUFFER_END cmd = GfxFamily::cmdInitBatchBufferEnd;
    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(MI_BATCH_BUFFER_END *)buffer = cmd;

    return XE_RESULT_SUCCESS;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeCommandLists(uint32_t numCommandLists,
                                                             xe_command_list_handle_t *phCommandLists) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeCommands(xe_command_format_t format,
                                                         size_t size,
                                                         void *pBlob) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeDispatchFunction(xe_function_handle_t hFunction,
                                                                 xe_function_args_handle_t hFunctionArgs,
                                                                 const xe_dispatch_function_arguments_t *pDispatchFuncArgs,
                                                                 xe_event_handle_t hEvent) {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(gfxCoreFamily)>::GfxFamily;

    return XE_RESULT_SUCCESS;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeDispatchFunctionIndirect(xe_function_handle_t hFunction,
                                                                         xe_function_args_handle_t hFunctionArgs,
                                                                         const xe_dispatch_function_indirect_arguments_t *pDispatchArgumentsBuffer,
                                                                         xe_event_handle_t hEvent) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeDispatchHostFunction(xe_host_pfn_t pfnHostFunc,
                                                                     void *pUserData) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeEventReset(xe_event_handle_t hEvent) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeExecutionBarrier() {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeImageCopyFromMemory(xe_image_handle_t hDstImage,
                                                                    xe_image_region_t *pDstRegion,
                                                                    void *srcptr) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeImageCopyToMemory(void *dstptr,
                                                                  xe_image_handle_t hSrcImage,
                                                                  xe_image_region_t *pSrcRegion) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeImageCopyRegion(xe_image_handle_t hDstImage,
                                                                xe_image_region_t *pDstRegion,
                                                                xe_image_handle_t hSrcImage,
                                                                xe_image_region_t *pSrcRegion) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeImageCopy(xe_image_handle_t hDstImage,
                                                          xe_image_handle_t hSrcImage) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeMemAdvise(xe_device_handle_t hDevice,
                                                          const void *ptr,
                                                          size_t size,
                                                          xe_memory_advice_t advice) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeMemoryCopy(void *dstptr,
                                                           const void *srcptr,
                                                           size_t size) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeMemoryPrefetch(const void *ptr,
                                                               size_t count) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeMemorySet(void *ptr,
                                                          int value,
                                                          size_t size) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeSemaphoreSignal(xe_semaphore_handle_t hSemaphore,
                                                                xe_semaphore_value_t value) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeSemaphoreWait(xe_semaphore_handle_t hSemaphore,
                                                              xe_semaphore_wait_operation_t operation,
                                                              xe_semaphore_value_t value) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeSignalEvent(xe_event_handle_t hEvent) {
    auto event = Event::fromHandle(hEvent);
    assert(event);
    residencyContainer.push_back(event->getAllocation().allocationRT);

    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(gfxCoreFamily)>::GfxFamily;
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

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeSignalMultipleEvents(uint32_t numEvents,
                                                                     xe_event_handle_t *phEvents) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeWaitOnEvent(xe_event_handle_t hEvent) {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(gfxCoreFamily)>::GfxFamily;
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

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeWaitOnMultipleEvents(uint32_t numEvents,
                                                                     xe_event_handle_t *phEvents) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::getParameter(xe_command_list_parameter_t parameter, uint32_t *value) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::reset() {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::resetParameters() {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::setParameter(xe_command_list_parameter_t parameter,
                                                       uint32_t value) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

} // namespace xe
