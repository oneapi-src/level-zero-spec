#pragma once
#define CMD_LIST_INTERNAL
#include "cmd_list_imp.h"
#undef CMD_LIST_INTERNAL
#include "white_box.h"
#include "gmock/gmock.h"

namespace xe {

template <>
struct WhiteBox<CommandList> : public CommandListImp {
    WhiteBox(Device *device) : CommandListImp(device) {
    }

    using CommandListImp::device;
    using CommandListImp::allocation;
};

struct MockCommandList : public WhiteBox<CommandList> {
    MockCommandList(Device *device = nullptr) : WhiteBox<CommandList>(device) {
    }

    MOCK_METHOD0(close, xe_result_t());
    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD1(encodeWaitOnEvent, xe_result_t(xe_event_handle_t hEvent));
};

} // namespace xe
