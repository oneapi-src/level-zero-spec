#include "xe_all.h"
#include "mock_cmd_list.h"
#include "gmock/gmock.h"

TEST(xeCommandListEncodeWaitOnEvent, redirectsToCmdListObject) {
    xe::MockCommandList commandList;
    xe_event_handle_t event = {};

    EXPECT_CALL(commandList, encodeWaitOnEvent(event)).Times(1);

    auto result = xe::xeCommandListEncodeWaitOnEvent(commandList.toHandle(),
                                                     event);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}
