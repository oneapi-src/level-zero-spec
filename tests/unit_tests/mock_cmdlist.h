#pragma once
#define CMD_LIST_INTERNAL
#include "cmdlist_imp.h"
#undef CMD_LIST_INTERNAL
#include "white_box.h"
#include "mock.h"

namespace xe {
struct GraphicsAllocation;

namespace ult {

template <>
struct WhiteBox<::xe::CommandList> : public ::xe::CommandListImp {
    using BaseClass = ::xe::CommandListImp;
    using BaseClass::allocation;
    using BaseClass::allocationIndirectHeaps;
    using BaseClass::commandStream;
    using BaseClass::indirectHeaps;
    using BaseClass::device;
    using BaseClass::residencyContainer;

    WhiteBox(Device *device);
    virtual ~WhiteBox();
};

using CommandList = WhiteBox<::xe::CommandList>;

template <>
struct Mock<CommandList> : public CommandList {
    Mock(Device *device = nullptr);
    virtual ~Mock();

    MOCK_METHOD0(close, xe_result_t());
    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD4(encodeDispatchFunction, xe_result_t(xe_function_handle_t hFunction,
                                                     xe_function_args_handle_t hFunctionArgs,
                                                     xe_dispatch_function_arguments_t *pDispatchFuncArgs,
                                                     xe_event_handle_t hEvent));
    MOCK_METHOD1(encodeSignalEvent, xe_result_t(xe_event_handle_t hEvent));
    MOCK_METHOD1(encodeWaitOnEvent, xe_result_t(xe_event_handle_t hEvent));

    void *batchBuffer = nullptr;
    GraphicsAllocation *mockAllocation = nullptr;
};

} // namespace ult
} // namespace xe
