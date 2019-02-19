#include "test.h"
#include "xe_all.h"
#include "graphics_allocation.h"
#include "mock_cmdlist.h"
#include "mock_device.h"
#include "mock_event.h"
#include "mock_memory_manager.h"
#include "runtime/command_stream/linear_stream.h"
#include "unit_tests/gen_common/gen_cmd_parse.h"

namespace xe {
namespace ult {

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Return;

TEST(xeCommandListEncodeSignalEvent, redirectsToCmdListObject) {
    Mock<CommandList> commandList;
    xe_event_handle_t event = {};

    EXPECT_CALL(commandList, encodeSignalEvent(event)).Times(1);

    auto result = xe::xeCommandListEncodeSignalEvent(commandList.toHandle(),
                                                     event);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

using CommandListEncodeSignalEvent = ::testing::Test;

HWTEST_F(CommandListEncodeSignalEvent, addsPipeControlToCommandStream) {
    Mock<Device> device;
    EXPECT_CALL(device, getMemoryManager).Times(AnyNumber());

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList->commandStream);
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    Mock<Event> event;
    auto result = commandList->encodeSignalEvent(event.toHandle());
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandList->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));
    using PIPE_CONTROL = typename FamilyType::PIPE_CONTROL;
    auto itor = find<PIPE_CONTROL *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    {
        auto cmd = genCmdCast<PIPE_CONTROL *>(*itor);
        EXPECT_TRUE(cmd->getCommandStreamerStallEnable());

        using POST_SYNC_OPERATION = typename PIPE_CONTROL::POST_SYNC_OPERATION;
        EXPECT_EQ(cmd->getPostSyncOperation(), POST_SYNC_OPERATION::POST_SYNC_OPERATION_WRITE_IMMEDIATE_DATA);
        EXPECT_EQ(cmd->getImmediateData(), 0u);
        auto gpuAddress = (uint64_t(cmd->getAddressHigh()) << 32u) | cmd->getAddress();
        EXPECT_EQ(gpuAddress, event.allocation->getGpuAddress());
    }
}

HWTEST_F(CommandListEncodeSignalEvent, addsEventGraphicsAllocationToResidencyContainer) {
    Mock<Device> device;
    EXPECT_CALL(device, getMemoryManager).Times(AnyNumber());

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList->commandStream);
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    Mock<Event> event;
    auto result = commandList->encodeSignalEvent(event.toHandle());
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto &residencyContainer = commandList->residencyContainer;
    auto allocationRT = static_cast<OCLRT::GraphicsAllocation *>(event.allocation->allocationRT);
    auto itor = std::find(std::begin(residencyContainer), std::end(residencyContainer), allocationRT); 
    EXPECT_NE(itor, std::end(residencyContainer));
}

} // namespace ult
} // namespace xe
