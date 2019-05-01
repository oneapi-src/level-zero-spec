#pragma once
#define CMD_LIST_INTERNAL
#include "cmdlist_imp.h"
#undef CMD_LIST_INTERNAL
#include "white_box.h"
#include "mock.h"

namespace L0 {
struct GraphicsAllocation;

namespace ult {

template <>
struct WhiteBox<::L0::CommandList> : public ::L0::CommandListImp {
    using BaseClass = ::L0::CommandListImp;
    using BaseClass::allocation;
    using BaseClass::allocationIndirectHeaps;
    using BaseClass::commandStream;
    using BaseClass::device;
    using BaseClass::indirectHeaps;
    using BaseClass::printfFunctionContainer;
    using BaseClass::residencyContainer;
    using BaseClass::deallocationContainer;

    WhiteBox(Device *device);
    virtual ~WhiteBox();
};

using CommandList = WhiteBox<::L0::CommandList>;

template <>
struct Mock<CommandList> : public CommandList {
    Mock(Device *device = nullptr);
    virtual ~Mock();

    MOCK_METHOD0(close, xe_result_t());
    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD2(appendCommandLists, xe_result_t(uint32_t numCommandLists,
                                                 xe_command_list_handle_t *phCommandLists));
    MOCK_METHOD5(appendLaunchFunction, xe_result_t(xe_function_handle_t hFunction,
                                                   const xe_thread_group_dimensions_t *pThreadGroupDimensions,
                                                   xe_event_handle_t hEvent,
                                              uint32_t numWaitEvents,
                                              xe_event_handle_t* phWaitEvents));
    MOCK_METHOD5(appendLaunchFunctionIndirect, xe_result_t(xe_function_handle_t hFunction,
                                                           const xe_thread_group_dimensions_t *pDispatchArgumentsBuffer,
                                                           xe_event_handle_t hEvent,
                                                            uint32_t numWaitEvents,
                                                            xe_event_handle_t* phWaitEvents));
    MOCK_METHOD2(appendLaunchHostFunction, xe_result_t(xe_host_pfn_t pfnHostFunc,
                                                       void *pUserData));
    MOCK_METHOD7(appendLaunchMultipleFunctionsIndirect, xe_result_t(uint32_t numFunctions,
                                                                    const xe_function_handle_t *phFunctions,
                                                                    const size_t *pNumLaunchArguments,
                                                                    const xe_thread_group_dimensions_t *pLaunchArgumentsBuffer,
                                                                    xe_event_handle_t hEvent,
                                                                    uint32_t numWaitEvents,
                                                                    xe_event_handle_t* phWaitEvents));
    MOCK_METHOD1(appendEventReset, xe_result_t(xe_event_handle_t hEvent));
    MOCK_METHOD3(appendBarrier, xe_result_t(xe_event_handle_t hSignalEvent,
                                        uint32_t numWaitEvents,
                                        xe_event_handle_t* phWaitEvents));
    MOCK_METHOD6(appendMemoryRangesBarrier, xe_result_t(uint32_t numRanges,
                                        const size_t* pRangeSizes,
                                        const void** pRanges,
                                        xe_event_handle_t hSignalEvent,
                                        uint32_t numWaitEvents,
                                        xe_event_handle_t* phWaitEvents));
    MOCK_METHOD6(appendImageCopyFromMemory, xe_result_t(xe_image_handle_t hDstImage,
                                                        const void *srcptr,
                                                        xe_image_region_t *pDstRegion,
                                                        xe_event_handle_t hEvent,
                                                        uint32_t numWaitEvents,
                                                        xe_event_handle_t* phWaitEvents));
    MOCK_METHOD6(appendImageCopyToMemory, xe_result_t(void *dstptr,
                                                      xe_image_handle_t hSrcImage,
                                                      xe_image_region_t *pSrcRegion,
                                                      xe_event_handle_t hEvent,
                                                      uint32_t numWaitEvents,
                                                      xe_event_handle_t* phWaitEvents));
    MOCK_METHOD7(appendImageCopyRegion, xe_result_t(xe_image_handle_t hDstImage,
                                              xe_image_handle_t hSrcImage,
                                              xe_image_region_t* pDstRegion,
                                              xe_image_region_t* pSrcRegion,
                                              xe_event_handle_t hSignalEvent,
                                              uint32_t numWaitEvents,
                                              xe_event_handle_t* phWaitEvents));
    MOCK_METHOD5(appendImageCopy, xe_result_t(xe_image_handle_t hDstImage,
                                              xe_image_handle_t hSrcImage,
                                              xe_event_handle_t hEvent,
                                              uint32_t numWaitEvents,
                                              xe_event_handle_t* phWaitEvents));
    MOCK_METHOD4(appendMemAdvise, xe_result_t(xe_device_handle_t hDevice,
                                              const void *ptr,
                                              size_t size,
                                              xe_memory_advice_t advice));
    MOCK_METHOD6(appendMemoryCopy, xe_result_t(void *dstptr,
                                               const void *srcptr,
                                               size_t size,
                                               xe_event_handle_t hEvent,
                                              uint32_t numWaitEvents,
                                              xe_event_handle_t* phWaitEvents));
    MOCK_METHOD2(appendMemoryPrefetch, xe_result_t(const void *ptr,
                                                   size_t count));
    MOCK_METHOD6(appendMemorySet, xe_result_t(void *ptr,
                                              int value,
                                              size_t size,
                                              xe_event_handle_t hEvent,
                                              uint32_t numWaitEvents,
                                              xe_event_handle_t* phWaitEvents));
    MOCK_METHOD1(appendSignalEvent, xe_result_t(xe_event_handle_t hEvent));
    MOCK_METHOD2(appendWaitOnEvents, xe_result_t(uint32_t numEvents, xe_event_handle_t* phEvent));
    MOCK_METHOD2(getParameter, xe_result_t(xe_command_list_parameter_t parameter, uint32_t *value));
    MOCK_METHOD2(reserveSpace, xe_result_t(size_t size,
                                           void **ptr));
    MOCK_METHOD0(reset, xe_result_t());
    MOCK_METHOD0(resetParameters, xe_result_t());
    MOCK_METHOD2(setParameter, xe_result_t(xe_command_list_parameter_t parameter,
                                           uint32_t value));

    uint8_t *batchBuffer = nullptr;
    GraphicsAllocation *mockAllocation = nullptr;
};

} // namespace ult
} // namespace L0
