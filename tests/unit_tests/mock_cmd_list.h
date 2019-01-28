#pragma once
#define CMD_LIST_INTERNAL
#include "cmd_list_imp.h"
#undef CMD_LIST_INTERNAL
#include "gmock/gmock.h"

namespace xe {

struct MockCommandList : public CommandListImp {
    MOCK_METHOD0(close, xe_result_t());
    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD1(encodeWaitOnEvent, xe_result_t(xe_event_handle_t hEvent));
};

} // namespace xe
