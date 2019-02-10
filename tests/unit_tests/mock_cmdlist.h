#pragma once
#define CMD_LIST_INTERNAL
#include "cmdlist_imp.h"
#undef CMD_LIST_INTERNAL
#include "white_box.h"
#include "gmock/gmock.h"

namespace xe {
struct GraphicsAllocation;

namespace ult {

template <>
struct WhiteBox<::xe::CommandList> : public ::xe::CommandListImp {
    using BaseClass = ::xe::CommandListImp;
    using BaseClass::allocation;
    using BaseClass::commandStream;
    using BaseClass::device;

    WhiteBox(Device *device);
    virtual ~WhiteBox();
};

struct MockCommandList : public WhiteBox<::xe::CommandList> {
    MockCommandList(Device *device = nullptr);
    virtual ~MockCommandList();

    MOCK_METHOD0(close, xe_result_t());
    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD1(encodeWaitOnEvent, xe_result_t(xe_event_handle_t hEvent));

    void *batchBuffer = nullptr;
    GraphicsAllocation *mockAllocation = nullptr;
};

using CommandList = WhiteBox<::xe::CommandList>;

} // namespace ult
} // namespace xe
