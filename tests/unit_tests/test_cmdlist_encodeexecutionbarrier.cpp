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

TEST(xeCommandListEncodeExecutionBarrier, redirectsToObject) {
    Mock<CommandList> commandList;

    EXPECT_CALL(commandList, encodeExecutionBarrier()).Times(1);

    auto result = xeCommandListEncodeExecutionBarrier(commandList.toHandle());
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

using CommandListEncodeExecutionBarrier = ::testing::Test;

HWTEST_F(CommandListEncodeExecutionBarrier, addPipeControlToCommandStream) {
    Mock<Device> device;

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList->commandStream);
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    Mock<Event> event;
    auto result = commandList->encodeExecutionBarrier();
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandList->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));

    // Find a PC w/ CS stall and DCFlush
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

        if (!cmd->getDcFlushEnable()) {
            itor++;
            continue;
        }

        break;
    }
    ASSERT_NE(itor, cmdList.end());
}

} // namespace ult
} // namespace L0
