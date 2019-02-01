#include "test.h"
#include "xe_all.h"
#include "graphics_allocation.h"
#include "igfxfmid.h"
#include "mock_cmdlist.h"
#include "mock_device.h"
#include "mock_event.h"
#include "mock_memory_manager.h"
#include "runtime/command_stream/linear_stream.h"
#include "unit_tests/gen_common/gen_cmd_parse.h"
#include "gmock/gmock.h"

using ::testing::Return;

extern PRODUCT_FAMILY productFamily;

TEST(xeCommandListEncodeWaitOnEvent, redirectsToCmdListObject) {
    xe::MockCommandList commandList;
    xe_event_handle_t event = {};

    EXPECT_CALL(commandList, encodeWaitOnEvent(event)).Times(1);

    auto result = xe::xeCommandListEncodeWaitOnEvent(commandList.toHandle(),
                                                     event);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

using CommandListEncodeWaitOnEvent = ::testing::Test;

HWTEST_F(CommandListEncodeWaitOnEvent, addsSemaphoreToCommandStream) {
    xe::MockDevice device;
    xe::MockMemoryManager memoryManager;
    EXPECT_CALL(device, getMemoryManager())
        .WillRepeatedly(Return(&memoryManager));

    int8_t buffer[1024];
    xe::GraphicsAllocation allocation(buffer, sizeof(buffer));
    EXPECT_CALL(memoryManager, allocateDeviceMemory)
        .WillOnce(Return(&allocation));

    auto commandList = xe::CommandList::create(productFamily, &device);
    auto commandListAlias = whitebox_cast<xe::CommandList>(commandList);
    ASSERT_NE(nullptr, commandListAlias->commandStream);
    auto usedSpaceBefore = commandListAlias->commandStream->getUsed();

    xe::MockEvent event;
    auto result = commandList->encodeWaitOnEvent(event.toHandle());
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandListAlias->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandListAlias->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));
    using MI_SEMAPHORE_WAIT = typename FamilyType::MI_SEMAPHORE_WAIT;
    auto itor = find<MI_SEMAPHORE_WAIT *>(cmdList.begin(), cmdList.end());
    EXPECT_NE(cmdList.end(), itor);
}
