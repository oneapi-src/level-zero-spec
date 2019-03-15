#include "test.h"
#include "xe_all.h"
#include "graphics_allocation.h"
#include "mock_cmdlist.h"
#include "mock_device.h"
#include "mock_event.h"
#include "mock_memory_manager.h"
#include "runtime/command_stream/linear_stream.h"
#include "unit_tests/gen_common/gen_cmd_parse.h"

namespace L0 {
namespace ult {

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Return;

TEST(xeCommandListEncodeSignalEvent, redirectsToObject) {
    Mock<CommandList> commandList;
    Mock<Event> event;

    EXPECT_CALL(commandList, encodeSignalEvent(event.toHandle())).Times(1);

    auto result = xeCommandListEncodeSignalEvent(commandList.toHandle(),
                                                 event.toHandle());
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

using CommandListEncodeSignalEvent = ::testing::Test;

HWTEST_F(CommandListEncodeSignalEvent, addsPipeControlToCommandStream) {
    Mock<Device> device;

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

    // Find a PC w/ a WriteImmediateData and CS stall
    auto itor = cmdList.begin();
    while (itor != cmdList.end()) {
        using PIPE_CONTROL = typename FamilyType::PIPE_CONTROL;
        itor = find<PIPE_CONTROL *>(itor, cmdList.end());
        if (itor == cmdList.end())
            break;

        auto cmd = genCmdCast<PIPE_CONTROL *>(*itor);
        if (!cmd->getCommandStreamerStallEnable()) {
            itor++;
            continue;
        }

        using POST_SYNC_OPERATION = typename PIPE_CONTROL::POST_SYNC_OPERATION;
        if (cmd->getPostSyncOperation() != POST_SYNC_OPERATION::POST_SYNC_OPERATION_WRITE_IMMEDIATE_DATA) {
            itor++;
            continue;
        }

        if (cmd->getImmediateData() != 0u) {
            itor++;
            continue;
        }

        auto gpuAddress = (uint64_t(cmd->getAddressHigh()) << 32u) | cmd->getAddress();
        if (gpuAddress != event.allocation->getGpuAddress()) {
            itor++;
            continue;
        }

        break;
    }
    ASSERT_NE(itor, cmdList.end());
}

HWTEST_F(CommandListEncodeSignalEvent, addsEventGraphicsAllocationToResidencyContainer) {
    Mock<Device> device;

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
} // namespace L0
