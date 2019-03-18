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
    using BaseClass::residencyContainer;

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
    MOCK_METHOD3(appendLaunchFunction, xe_result_t(xe_function_handle_t hFunction,
                                                   const xe_thread_group_dimensions_t *pDispatchFuncArgs,
                                                   xe_event_handle_t hEvent));
    MOCK_METHOD3(appendLaunchFunctionIndirect, xe_result_t(xe_function_handle_t hFunction,
                                                           const xe_thread_group_dimensions_t *pDispatchArgumentsBuffer,
                                                           xe_event_handle_t hEvent));
    MOCK_METHOD2(appendLaunchHostFunction, xe_result_t(xe_host_pfn_t pfnHostFunc,
                                                       void *pUserData));
    MOCK_METHOD5(appendLaunchMultipleFunctionsIndirect, xe_result_t(uint32_t numFunctions,
                                                                    const xe_function_handle_t *phFunctions,
                                                                    const size_t *pNumLaunchArguments,
                                                                    const xe_thread_group_dimensions_t *pLaunchArgumentsBuffer,
                                                                    xe_event_handle_t hEvent));
    MOCK_METHOD1(appendEventReset, xe_result_t(xe_event_handle_t hEvent));
    MOCK_METHOD0(appendExecutionBarrier, xe_result_t());
    MOCK_METHOD3(appendImageCopyFromMemory, xe_result_t(xe_image_handle_t hDstImage,
                                                        xe_image_region_t *pDstRegion,
                                                        const void *srcptr));
    MOCK_METHOD3(appendImageCopyToMemory, xe_result_t(void *dstptr,
                                                      xe_image_handle_t hSrcImage,
                                                      xe_image_region_t *pSrcRegion));
    MOCK_METHOD4(appendImageCopyRegion, xe_result_t(xe_image_handle_t hDstImage,
                                                    xe_image_region_t *pDstRegion,
                                                    xe_image_handle_t hSrcImage,
                                                    xe_image_region_t *pSrcRegion));
    MOCK_METHOD2(appendImageCopy, xe_result_t(xe_image_handle_t hDstImage,
                                              xe_image_handle_t hSrcImage));
    MOCK_METHOD4(appendMemAdvise, xe_result_t(xe_device_handle_t hDevice,
                                              const void *ptr,
                                              size_t size,
                                              xe_memory_advice_t advice));
    MOCK_METHOD3(appendMemoryCopy, xe_result_t(void *dstptr,
                                               const void *srcptr,
                                               size_t size));
    MOCK_METHOD2(appendMemoryPrefetch, xe_result_t(const void *ptr,
                                                   size_t count));
    MOCK_METHOD3(appendMemorySet, xe_result_t(void *ptr,
                                              int value,
                                              size_t size));
    MOCK_METHOD1(appendSignalEvent, xe_result_t(xe_event_handle_t hEvent));
    MOCK_METHOD1(appendWaitOnEvent, xe_result_t(xe_event_handle_t hEvent));
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
