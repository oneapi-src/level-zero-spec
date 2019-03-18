#include "encode_flush.h"
#include "fixture_cmd_parse.h"

namespace L0 {
namespace ult {

using EncodeFlush = CmdParseFixture;
HWTEST2_F(EncodeFlush, appendsAPIPE_CONTROL, MatchAny) {
    ::L0::EncodeFlush<gfxCoreFamily>::append(*commandList);

    parseCommandBuffer<FamilyType>();

    using PIPE_CONTROL = typename FamilyType::PIPE_CONTROL;
    auto itorPC = find<PIPE_CONTROL *>(commands.begin(), commands.end());
    ASSERT_NE(itorPC, commands.end());
    {
        auto cmd = genCmdCast<PIPE_CONTROL *>(*itorPC);
        EXPECT_TRUE(cmd->getCommandStreamerStallEnable());
        EXPECT_TRUE(cmd->getDcFlushEnable());
    }
}

} // namespace ult
} // namespace L0
