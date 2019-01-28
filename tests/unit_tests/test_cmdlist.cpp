#include "mock_cmd_list.h"
#include "event.h"
#include "igfxfmid.h"
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

using CommandListCreate = ::testing::TestWithParam<uint32_t>;

TEST_P(CommandListCreate, returnsCommandListOnSuccess) {
    auto commandList = xe::CommandList::create(GetParam());
    ASSERT_NE(nullptr, commandList);
    commandList->destroy();
}

static uint32_t supportedProductFamilyTable[] = {
    IGFX_BROADWELL,
    IGFX_KABYLAKE,
    IGFX_SKYLAKE
};

INSTANTIATE_TEST_CASE_P(,
                        CommandListCreate,
                        ::testing::ValuesIn(supportedProductFamilyTable));

TEST(commandListCreate, returnsNullPointerOnFailure) {
    auto commandList = xe::CommandList::create(IGFX_MAX_PRODUCT);
    EXPECT_EQ(nullptr, commandList);
}
