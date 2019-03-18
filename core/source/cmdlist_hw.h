#pragma once
#define CMD_LIST_INTERNAL
#include "cmdlist_imp.h"
#undef CMD_LIST_INTERNAL
#include "igfxfmid.h"

namespace L0 {

template <GFXCORE_FAMILY gfxCoreFamily>
struct CommandListCoreFamily : public CommandListImp {
    using BaseClass = CommandListImp;

    using CommandListImp::CommandListImp;

    bool initialize(Device *device) override;
    void programL3();
    void enableGpgpu();
    void programFrontEndState();
    void *getHeapSpaceAllowGrow(OCLRT::IndirectHeap &indirectHeap, size_t size);

    xe_result_t close() override;
    xe_result_t appendCommandLists(uint32_t numCommandLists,
                                   xe_command_list_handle_t *phCommandLists) override;
    xe_result_t appendEventReset(xe_event_handle_t hEvent) override;
    xe_result_t appendExecutionBarrier() override;
    xe_result_t appendImageCopyFromMemory(xe_image_handle_t hDstImage,
                                          xe_image_region_t *pDstRegion,
                                          const void *srcptr) override;
    xe_result_t appendImageCopyToMemory(void *dstptr,
                                        xe_image_handle_t hSrcImage,
                                        xe_image_region_t *pSrcRegion) override;
    xe_result_t appendImageCopyRegion(xe_image_handle_t hDstImage,
                                      xe_image_region_t *pDstRegion,
                                      xe_image_handle_t hSrcImage,
                                      xe_image_region_t *pSrcRegion) override;
    xe_result_t appendImageCopy(xe_image_handle_t hDstImage,
                                xe_image_handle_t hSrcImage) override;
    xe_result_t appendLaunchFunction(xe_function_handle_t hFunction,
                                     const xe_thread_group_dimensions_t *pDispatchFuncArgs,
                                     xe_event_handle_t hEvent) override;
    xe_result_t appendLaunchFunctionIndirect(xe_function_handle_t hFunction,
                                             const xe_thread_group_dimensions_t *pDispatchArgumentsBuffer,
                                             xe_event_handle_t hEvent) override;
    xe_result_t appendLaunchHostFunction(xe_host_pfn_t pfnHostFunc,
                                         void *pUserData) override;
    xe_result_t appendLaunchMultipleFunctionsIndirect(uint32_t numFunctions,
                                                      const xe_function_handle_t *phFunctions,
                                                      const size_t *pNumLaunchArguments,
                                                      const xe_thread_group_dimensions_t *pLaunchArgumentsBuffer,
                                                      xe_event_handle_t hEvent) override;
    xe_result_t appendMemAdvise(xe_device_handle_t hDevice,
                                const void *ptr,
                                size_t size,
                                xe_memory_advice_t advice) override;
    xe_result_t appendMemoryCopy(void *dstptr,
                                 const void *srcptr,
                                 size_t size) override;
    xe_result_t appendMemoryPrefetch(const void *ptr,
                                     size_t count) override;
    xe_result_t appendMemorySet(void *ptr,
                                int value,
                                size_t size) override;
    xe_result_t appendSignalEvent(xe_event_handle_t hEvent) override;
    xe_result_t appendWaitOnEvent(xe_event_handle_t hEvent) override;
    xe_result_t getParameter(xe_command_list_parameter_t parameter, uint32_t *value) override;
    xe_result_t reserveSpace(size_t size,
                             void **ptr) override;
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
