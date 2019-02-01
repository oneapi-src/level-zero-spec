#include "graphics_allocation.h"
#include "mock_cmdqueue.h"
#include "mock_cmdlist.h"
#include "mock_device.h"
#include "mock_memory_manager.h"
#include "runtime/command_stream/linear_stream.h"
#include "test.h"
#include "unit_tests/gen_common/gen_cmd_parse.h"
#include "xe_all.h"
#include "gtest/gtest.h"

using ::testing::Return;

namespace xe {

TEST(xeCommandQueueEnqueueCommandQueue, redirectsToCmdQueueObject) {
    MockCommandList cmdList;
    auto hCommandList = cmdList.toHandle();
    MockCommandQueue cmdQueue;
    xe_fence_handle_t hFence = {};

    EXPECT_CALL(cmdQueue, enqueueCommandLists(1,
                                              &hCommandList,
                                              hFence))
        .Times(1);

    auto result = xe::xeCommandQueueEnqueueCommandLists(cmdQueue.toHandle(),
                                                        1,
                                                        &hCommandList,
                                                        hFence);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

using CommandQueueEnqueueCommandQueue = ::testing::Test;

HWTEST_F(CommandQueueEnqueueCommandQueue, addsASecondLevelBatchBufferPerCommandList) {
    MockDevice device;
    MockMemoryManager memoryManager;
    EXPECT_CALL(device, getMemoryManager())
        .WillRepeatedly(Return(&memoryManager));

    int8_t buffer[1024];
    GraphicsAllocation allocation(buffer, sizeof(buffer));
    EXPECT_CALL(memoryManager, allocateDeviceMemory)
        .WillOnce(Return(&allocation));

    auto commandQueue = CommandQueue::create(IGFX_SKYLAKE, &device);
    auto commandQueueAlias = whitebox_cast<CommandQueue>(commandQueue);
    ASSERT_NE(nullptr, commandQueueAlias->commandStream);
    auto usedSpaceBefore = commandQueueAlias->commandStream->getUsed();

    MockCommandList commandList;
    auto hCommandList = commandList.toHandle();
    auto result = commandQueue->enqueueCommandLists(1,
                                                    &hCommandList,
                                                    nullptr);

    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandQueueAlias->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandQueueAlias->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));
    using MI_BATCH_BUFFER_START = typename FamilyType::MI_BATCH_BUFFER_START;
    auto itor = find<MI_BATCH_BUFFER_START *>(cmdList.begin(), cmdList.end());
    EXPECT_NE(cmdList.end(), itor);

    auto bbs = genCmdCast<MI_BATCH_BUFFER_START *>(*itor);
    ASSERT_NE(nullptr, bbs);

    EXPECT_EQ(MI_BATCH_BUFFER_START::SECOND_LEVEL_BATCH_BUFFER_SECOND_LEVEL_BATCH, bbs->getSecondLevelBatchBuffer());
}

} // namespace xe
