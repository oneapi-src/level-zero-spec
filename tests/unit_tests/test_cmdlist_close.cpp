#include "test.h"
#include "mock_cmdlist.h"
#include "fixture_cmd_parse.h"

namespace L0 {
namespace ult {

TEST(xeCommandListClose, redirectsToObject) {
    Mock<CommandList> commands;
    EXPECT_CALL(commands, close());

    auto result = xeCommandListClose(commands.toHandle());
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

using CommandListClose = CmdParseFixture;
HWTEST2_F(CommandListClose, addsBatchBufferEndToCommandStream, MatchAny) {
    auto result = commandList->close();
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    parseCommandBuffer<FamilyType>();

    using MI_BATCH_BUFFER_END = typename FamilyType::MI_BATCH_BUFFER_END;
    auto itor = find<MI_BATCH_BUFFER_END *>(commands.begin(), commands.end());
    EXPECT_NE(commands.end(), itor);
}

} // namespace ult
} // namespace L0
