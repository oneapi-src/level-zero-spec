#include "encode_set_mmio.h"
#include "fixture_cmd_parse.h"

namespace L0 {
namespace ult {

using EncodeSetMMIO = CmdParseFixture;
HWTEST2_F(EncodeSetMMIO, encodesAMI_LOAD_REGISTER_IMM, MatchAny) {
    ::L0::EncodeSetMMIO<gfxCoreFamily>::encode(*commandList, 0xf00, 0xbaa);

    parseCommandBuffer<FamilyType>();

    using MI_LOAD_REGISTER_IMM = typename FamilyType::MI_LOAD_REGISTER_IMM;
    auto itorLRI = find<MI_LOAD_REGISTER_IMM *>(commands.begin(), commands.end());
    ASSERT_NE(itorLRI, commands.end());
    {
        auto cmd = genCmdCast<MI_LOAD_REGISTER_IMM *>(*itorLRI);
        EXPECT_EQ(cmd->getRegisterOffset(), 0xf00);
        EXPECT_EQ(cmd->getDataDword(), 0xbaa);
    }
}

} // namespace ult
} // namespace L0
