#pragma once
#define CMD_LIST_INTERNAL
#include "cmdlist_imp.h"
#undef CMD_LIST_INTERNAL
#include "igfxfmid.h"
#include "builtin_functions_lib.h"

namespace L0 {

template <GFXCORE_FAMILY gfxCoreFamily> struct CommandListCoreFamily : public CommandListImp {
    using BaseClass = CommandListImp;

    using CommandListImp::CommandListImp;

    bool initialize(Device *device) override;
    virtual void programL3(bool isSLMused);
    void enableGpgpu();
    void programFrontEndState();
    void programPreemption();
    void *getHeapSpaceAllowGrow(CommandContainer::HeapType heapType, size_t size);

    xe_result_t close() override;
    xe_result_t appendCommandLists(uint32_t numCommandLists,
                                   xe_command_list_handle_t *phCommandLists) override;
    xe_result_t appendEventReset(xe_event_handle_t hEvent) override;
    xe_result_t appendBarrier(xe_event_handle_t hSignalEvent, uint32_t numWaitEvents,
                              xe_event_handle_t *phWaitEvents) override;
    xe_result_t appendMemoryRangesBarrier(uint32_t numRanges, const size_t *pRangeSizes,
                                          const void **pRanges, xe_event_handle_t hSignalEvent,
                                          uint32_t numWaitEvents,
                                          xe_event_handle_t *phWaitEvents) override;
    xe_result_t appendImageCopyFromMemory(xe_image_handle_t hDstImage, const void *srcptr,
                                          xe_image_region_t *pDstRegion, xe_event_handle_t hEvent,
                                          uint32_t numWaitEvents,
                                          xe_event_handle_t *phWaitEvents) override;
    xe_result_t appendImageCopyToMemory(void *dstptr, xe_image_handle_t hSrcImage,
                                        xe_image_region_t *pSrcRegion, xe_event_handle_t hEvent,
                                        uint32_t numWaitEvents,
                                        xe_event_handle_t *phWaitEvents) override;
    xe_result_t appendImageCopyRegion(xe_image_handle_t hDstImage, xe_image_handle_t hSrcImage,
                                      xe_image_region_t *pDstRegion, xe_image_region_t *pSrcRegion,
                                      xe_event_handle_t hSignalEvent, uint32_t numWaitEvents,
                                      xe_event_handle_t *phWaitEvents) override;
    xe_result_t appendImageCopy(xe_image_handle_t hDstImage, xe_image_handle_t hSrcImage,
                                xe_event_handle_t hEvent, uint32_t numWaitEvents,
                                xe_event_handle_t *phWaitEvents) override;
    xe_result_t appendLaunchFunction(xe_function_handle_t hFunction,
                                     const xe_thread_group_dimensions_t *pThreadGroupDimensions,
                                     xe_event_handle_t hEvent, uint32_t numWaitEvents,
                                     xe_event_handle_t *phWaitEvents) override;
    xe_result_t
    appendLaunchFunctionIndirect(xe_function_handle_t hFunction,
                                 const xe_thread_group_dimensions_t *pDispatchArgumentsBuffer,
                                 xe_event_handle_t hEvent, uint32_t numWaitEvents,
                                 xe_event_handle_t *phWaitEvents) override;
    xe_result_t appendLaunchHostFunction(xe_host_pfn_t pfnHostFunc, void *pUserData) override;
    xe_result_t appendLaunchMultipleFunctionsIndirect(
        uint32_t numFunctions, const xe_function_handle_t *phFunctions,
        const size_t *pNumLaunchArguments,
        const xe_thread_group_dimensions_t *pLaunchArgumentsBuffer, xe_event_handle_t hEvent,
        uint32_t numWaitEvents, xe_event_handle_t *phWaitEvents) override;
    xe_result_t appendMemAdvise(xe_device_handle_t hDevice, const void *ptr, size_t size,
                                xe_memory_advice_t advice) override;
    xe_result_t appendMemoryCopy(void *dstptr, const void *srcptr, size_t size,
                                 xe_event_handle_t hSignalEvent, uint32_t numWaitEvents,
                                 xe_event_handle_t *phWaitEvents) override;
    xe_result_t appendMemoryPrefetch(const void *ptr, size_t count) override;
    xe_result_t appendMemorySet(void *ptr, int value, size_t size, xe_event_handle_t hEvent,
                                uint32_t numWaitEvents, xe_event_handle_t *phWaitEvents) override;
    xe_result_t appendSignalEvent(xe_event_handle_t hEvent) override;
    xe_result_t appendWaitOnEvents(uint32_t numEvents, xe_event_handle_t *phEvent) override;
    xe_result_t getParameter(xe_command_list_parameter_t parameter, uint32_t *value) override;
    xe_result_t reserveSpace(size_t size, void **ptr) override;
    xe_result_t reset() override;
    xe_result_t resetParameters() override;
    xe_result_t setParameter(xe_command_list_parameter_t parameter, uint32_t value) override;

  protected:
    uint32_t copyBindingTableAndSurfaceStates(NEO::IndirectHeap *ssh, const void *srcKernelSsh,
                                              uint32_t srcKernelSshSize,
                                              uint32_t numberOfBindingTableStates,
                                              uint32_t offsetOfBindingTable);
    uint32_t copySamplerState(NEO::IndirectHeap *dsh, uint32_t samplerStateOffset,
                              uint32_t samplerCount, uint32_t borderColorOffset,
                              const void *fnDynamicStateHeap);
    void copySamplerState(NEO::IndirectHeap *dsh, Function *function);

    xe_result_t appendMemoryCopyKernel(void *dstptr, const void *srcptr, uint32_t size,
                                       Builtin builtin, uint32_t elementSize);

    static const uint32_t alignIndirectStatePointer = 64 * sizeof(uint8_t);
};

template <uint32_t gfxProductFamily> struct CommandListProductFamily;

} // namespace L0
