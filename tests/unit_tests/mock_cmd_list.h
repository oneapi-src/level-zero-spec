#pragma once
#include "cmd_list.h"
#include "gmock/gmock.h"

namespace xe {

struct MockCommandList : public CommandList {
    MOCK_METHOD0(close, xe_result_t());
    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD1(encodeWaitOnEvent, xe_result_t(xe_event_handle_t hEvent));
};

} // namespace xe
