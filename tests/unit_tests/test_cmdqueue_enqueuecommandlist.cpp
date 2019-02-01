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
    MockCommandList commandList2;
    auto hCommandList = commandList.toHandle();
    auto hCommandList2 = commandList2.toHandle();
    xe_command_list_handle_t commandLists[] = {
        hCommandList,
        hCommandList2
    };
    uint32_t numCommandLists = sizeof(commandLists) / sizeof(commandLists[0]);
    auto result = commandQueue->enqueueCommandLists(numCommandLists,
                                                    commandLists,
                                                    nullptr);

    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandQueueAlias->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandQueueAlias->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));
    using MI_BATCH_BUFFER_START = typename FamilyType::MI_BATCH_BUFFER_START;
    auto itorCurrent = cmdList.begin();
        
    for (auto i = 0u; i < numCommandLists; i++) {
        itorCurrent = find<MI_BATCH_BUFFER_START *>(itorCurrent, cmdList.end());
        ASSERT_NE(cmdList.end(), itorCurrent);

        auto bbs = genCmdCast<MI_BATCH_BUFFER_START *>(*itorCurrent);
        ASSERT_NE(nullptr, bbs);
        EXPECT_EQ(MI_BATCH_BUFFER_START::SECOND_LEVEL_BATCH_BUFFER_SECOND_LEVEL_BATCH, bbs->getSecondLevelBatchBuffer());
    }

    using MI_BATCH_BUFFER_END = typename FamilyType::MI_BATCH_BUFFER_END;
    auto itorBBE = find<MI_BATCH_BUFFER_END *>(itorCurrent, cmdList.end());
    EXPECT_NE(cmdList.end(), itorBBE);
}

} // namespace xe
