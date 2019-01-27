#include "mock_cmd_list.h"
#include "event.h"
#include "gtest/gtest.h"

TEST(commandListDestroy, redirectsToCmdListObject) {
    xe::MockCommandList cmdList;
    xe_command_list_handle_t commandList = cmdList.toHandle();

    EXPECT_CALL(cmdList, destroy()).Times(1);

    auto result = xe::xeCommandListDestroy(commandList);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(commandListClose, redirectsToCmdListObject) {
    xe::MockCommandList cmdList;
    xe_command_list_handle_t commandList = cmdList.toHandle();

    EXPECT_CALL(cmdList, close()).Times(1);

    auto result = xe::xeCommandListClose(commandList);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(commandListEncodeWaitOnEvent, redirectsToCmdListObject) {
    xe::MockCommandList cmdList;
    xe_command_list_handle_t commandList = cmdList.toHandle();
    xe_event_handle_t event = {};

    EXPECT_CALL(cmdList, encodeWaitOnEvent(event)).Times(1);

    auto result = xe::xeCommandListEncodeWaitOnEvent(commandList,
                                                     event);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}
