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

TEST(xeCommandListAppendReserveSpace, redirectsToObject) {
    Mock<CommandList> commandList;
    size_t sizeToReserveForCommand = 4;
    void *ptrToReservedMemory = nullptr;
    EXPECT_CALL(commandList, reserveSpace(sizeToReserveForCommand, &ptrToReservedMemory)).Times(1);

    auto result = xeCommandListReserveSpace(commandList.toHandle(), sizeToReserveForCommand, &ptrToReservedMemory);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

using CommandList_reserveSpace = ::testing::Test;

HWTEST_F(CommandList_reserveSpace, addsCommandsToBatchBuffer) {
    Mock<Device> device;

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList->commandStream);
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    // Create Testing command to be inserted into the reserved space.
    using MI_NOOP = typename FamilyType::MI_NOOP;
    MI_NOOP cmd = FamilyType::cmdInitNoop;
    uint32_t uniqueIDforTest = 0x12345u;
    cmd.setIdentificationNumber(uniqueIDforTest);

    // reserve space in BatchBuffer
    size_t sizeToReserveForCommand = sizeof(cmd);
    void *ptrToReservedMemory = nullptr;
    auto result = commandList->reserveSpace(sizeToReserveForCommand, &ptrToReservedMemory);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    if (ptrToReservedMemory != nullptr) {
        *(MI_NOOP *)ptrToReservedMemory = cmd;
    }

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandList->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));

    // Find a testing command in batch buffer
    auto itor = cmdList.begin();
    while (itor != cmdList.end()) {
        using MI_NOOP = typename FamilyType::MI_NOOP;
        itor = find<MI_NOOP *>(itor, cmdList.end());
        if (itor == cmdList.end())
            break;

        // make sure we found the correct testing command
        auto cmd = genCmdCast<MI_NOOP *>(*itor);
        if (uniqueIDforTest == cmd->getIdentificationNumber()) {
            break;
        }

        itor++;
    }
    ASSERT_NE(itor, cmdList.end());
}

} // namespace ult
} // namespace L0
