#pragma once
#define CMD_LIST_INTERNAL
#include "cmdlist_imp.h"
#undef CMD_LIST_INTERNAL
#include "white_box.h"
#include "gmock/gmock.h"

namespace xe {

template <>
struct WhiteBox<CommandList> : public CommandListImp {
    WhiteBox(Device *device);
    virtual ~WhiteBox();

    using CommandListImp::allocation;
    using CommandListImp::commandStream;
    using CommandListImp::device;
};

struct MockCommandList : public WhiteBox<CommandList> {
    MockCommandList(Device *device = nullptr);
    virtual ~MockCommandList();

    MOCK_METHOD0(close, xe_result_t());
    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD1(encodeWaitOnEvent, xe_result_t(xe_event_handle_t hEvent));
};

} // namespace xe
