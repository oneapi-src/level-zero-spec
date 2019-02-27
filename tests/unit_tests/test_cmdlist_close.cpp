#include "test.h"
#include "xe_all.h"
#include "graphics_allocation.h"
#include "igfxfmid.h"
#include "mock_cmdlist.h"
#include "mock_device.h"
#include "mock_memory_manager.h"
#include "runtime/command_stream/linear_stream.h"
#include "unit_tests/gen_common/gen_cmd_parse.h"
#include "gmock/gmock.h"

namespace L0 {
namespace ult {

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Return;

TEST(xeCommandListClose, redirectsToObject) {
    Mock<CommandList> cmdList;
    EXPECT_CALL(cmdList, close()).Times(1);

    auto result = xeCommandListClose(cmdList.toHandle());
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

using CommandListClose = ::testing::Test;

HWTEST_F(CommandListClose, addsBatchBufferEndToCommandStream) {
    Mock<Device> device;
    EXPECT_CALL(device, getMemoryManager).Times(AnyNumber());

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList->commandStream);
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    auto result = commandList->close();
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandList->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));
    using MI_BATCH_BUFFER_END = typename FamilyType::MI_BATCH_BUFFER_END;
    auto itor = find<MI_BATCH_BUFFER_END *>(cmdList.begin(), cmdList.end());
    EXPECT_NE(cmdList.end(), itor);
}

} // namespace ult
} // namespace L0
