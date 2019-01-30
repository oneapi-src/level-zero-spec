#include "xe_all.h"
#include "graphics_allocation.h"
#include "igfxfmid.h"
#include "mock_cmd_list.h"
#include "mock_device.h"
#include "mock_event.h"
#include "mock_memory_manager.h"
#include "runtime/command_stream/linear_stream.h"
#include "gmock/gmock.h"

using ::testing::Return;

TEST(xeCommandListEncodeWaitOnEvent, redirectsToCmdListObject) {
    xe::MockCommandList commandList;
    xe_event_handle_t event = {};

    EXPECT_CALL(commandList, encodeWaitOnEvent(event)).Times(1);

    auto result = xe::xeCommandListEncodeWaitOnEvent(commandList.toHandle(),
                                                     event);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(CommandListEncodeWaitOnEvent, addsCommandsToCommandStream) {
    xe::MockDevice device;
    xe::MockMemoryManager memoryManager;
    EXPECT_CALL(device, getMemoryManager())
        .WillRepeatedly(Return(&memoryManager));

    int8_t buffer[1024];
    xe::GraphicsAllocation allocation(buffer, sizeof(buffer));
    EXPECT_CALL(memoryManager, allocateDeviceMemory)
        .WillOnce(Return(&allocation));

    auto commandList = xe::CommandList::create(IGFX_SKYLAKE, &device);
    auto commandListAlias = whitebox_cast<xe::CommandList>(commandList);
    ASSERT_NE(nullptr, commandListAlias->commandStream);
    auto usedSpaceBefore = commandListAlias->commandStream->getUsed();

    xe::MockEvent event;
    auto result = commandList->encodeWaitOnEvent(event.toHandle());
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandListAlias->commandStream->getUsed();
    EXPECT_GT(usedSpaceAfter, usedSpaceBefore);
}
