#pragma once
#define CMD_LIST_INTERNAL
#include "cmdlist_imp.h"
#undef CMD_LIST_INTERNAL

namespace L0 {

template <uint32_t gfxCoreFamily>
struct CommandListCoreFamily : public CommandListImp {
    using BaseClass = CommandListImp;

    using CommandListImp::CommandListImp;

    bool initialize(Device *device) override;
    void programL3();
    void enableGpgpu();
    void programFrontEndState();
    void *getHeapSpaceAllowGrow(OCLRT::IndirectHeap &indirectHeap, size_t size);

    xe_result_t close() override;
    xe_result_t encodeCommandLists(uint32_t numCommandLists,
                                   xe_command_list_handle_t *phCommandLists) override;
    xe_result_t encodeCommands(xe_command_format_t format,
                               size_t size,
                               void *pBlob) override;
    xe_result_t encodeDispatchFunction(xe_function_handle_t hFunction,
                                       const xe_dispatch_function_arguments_t *pDispatchFuncArgs,
                                       xe_event_handle_t hEvent) override;
    xe_result_t encodeDispatchFunctionIndirect(xe_function_handle_t hFunction,
                                               const xe_dispatch_function_indirect_arguments_t *pDispatchArgumentsBuffer,
                                               xe_event_handle_t hEvent) override;
    xe_result_t encodeDispatchHostFunction(xe_host_pfn_t pfnHostFunc,
                                           void *pUserData) override;
    xe_result_t encodeEventReset(xe_event_handle_t hEvent) override;
    xe_result_t encodeExecutionBarrier() override;
    xe_result_t encodeImageCopyFromMemory(xe_image_handle_t hDstImage,
                                          xe_image_region_t *pDstRegion,
                                          const void *srcptr) override;
    xe_result_t encodeImageCopyToMemory(void *dstptr,
                                        xe_image_handle_t hSrcImage,
                                        xe_image_region_t *pSrcRegion) override;
    xe_result_t encodeImageCopyRegion(xe_image_handle_t hDstImage,
                                      xe_image_region_t *pDstRegion,
                                      xe_image_handle_t hSrcImage,
                                      xe_image_region_t *pSrcRegion) override;
    xe_result_t encodeImageCopy(xe_image_handle_t hDstImage,
                                xe_image_handle_t hSrcImage) override;
    xe_result_t encodeMemAdvise(xe_device_handle_t hDevice,
                                const void *ptr,
                                size_t size,
                                xe_memory_advice_t advice) override;
    xe_result_t encodeMemoryCopy(void *dstptr,
                                 const void *srcptr,
                                 size_t size) override;
    xe_result_t encodeMemoryPrefetch(const void *ptr,
                                     size_t count) override;
    xe_result_t encodeMemorySet(void *ptr,
                                int value,
                                size_t size) override;
    xe_result_t encodeSemaphoreSignal(xe_semaphore_handle_t hSemaphore,
                                      xe_semaphore_value_t value) override;
    xe_result_t encodeSemaphoreWait(xe_semaphore_handle_t hSemaphore,
                                    xe_semaphore_wait_operation_t operation,
                                    xe_semaphore_value_t value) override;
    xe_result_t encodeSignalEvent(xe_event_handle_t hEvent) override;
    xe_result_t encodeSignalMultipleEvents(uint32_t numEvents,
                                           xe_event_handle_t *phEvents) override;
    xe_result_t encodeWaitOnEvent(xe_event_handle_t hEvent) override;
    xe_result_t encodeWaitOnMultipleEvents(uint32_t numEvents,
                                           xe_event_handle_t *phEvents) override;
    xe_result_t getParameter(xe_command_list_parameter_t parameter, uint32_t *value) override;
    xe_result_t reset() override;
    xe_result_t resetParameters() override;
    xe_result_t setParameter(xe_command_list_parameter_t parameter,
                             uint32_t value) override;

  protected:
    void *sba = nullptr;
};

template <uint32_t gfxProductFamily>
struct CommandListProductFamily;

} // namespace L0
