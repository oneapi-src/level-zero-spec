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

using ::testing::Return;

extern PRODUCT_FAMILY productFamily;

namespace xe {
namespace ult {

TEST(xeCommandListClose, redirectsToCmdListObject) {
    MockCommandList cmdList;
    xe_command_list_handle_t commandList = cmdList.toHandle();

    EXPECT_CALL(cmdList, close()).Times(1);

    auto result = xe::xeCommandListClose(commandList);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

using CommandListClose = ::testing::Test;

HWTEST_F(CommandListClose, addsBatchBufferEndToCommandStream) {
    MockDevice device;
    MockMemoryManager memoryManager;
    EXPECT_CALL(device, getMemoryManager())
        .WillRepeatedly(Return(&memoryManager));

    int8_t buffer[1024];
    GraphicsAllocation allocation(buffer, sizeof(buffer));
    EXPECT_CALL(memoryManager, allocateDeviceMemory)
        .WillOnce(Return(&allocation));

    auto commandList = CommandList::create(productFamily, &device);
    auto commandListAlias = whitebox_cast(commandList);
    ASSERT_NE(nullptr, commandListAlias->commandStream);
    auto usedSpaceBefore = commandListAlias->commandStream->getUsed();

    auto result = commandList->close();
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandListAlias->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandListAlias->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));
    using MI_BATCH_BUFFER_END = typename FamilyType::MI_BATCH_BUFFER_END;
    auto itor = find<MI_BATCH_BUFFER_END *>(cmdList.begin(), cmdList.end());
    EXPECT_NE(cmdList.end(), itor);
}

} // namespace ult
} // namespace xe
