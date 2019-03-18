#include "encode_l3state.h"
#include "fixture_cmd_parse.h"

namespace L0 {
namespace ult {

using EncodeL3State = CmdParseFixture;
HWTEST2_F(EncodeL3State, appendsASetMMIO, MatchAny) {
    ::L0::EncodeL3State<productFamily>::append(*commandList, false);

    parseCommandBuffer<FamilyType>();

    using MI_LOAD_REGISTER_IMM = typename FamilyType::MI_LOAD_REGISTER_IMM;
    auto itorLRI = find<MI_LOAD_REGISTER_IMM *>(commands.begin(), commands.end());
    ASSERT_NE(itorLRI, commands.end());
}

HWTEST2_F(EncodeL3State, appendsAFlushBeforeSetMMIO, MatchAny) {
    ::L0::EncodeL3State<productFamily>::append(*commandList, false);

    parseCommandBuffer<FamilyType>();

    using PIPE_CONTROL = typename FamilyType::PIPE_CONTROL;
    auto itorPC = find<PIPE_CONTROL *>(commands.begin(), commands.end());
    ASSERT_NE(itorPC, commands.end());

    using MI_LOAD_REGISTER_IMM = typename FamilyType::MI_LOAD_REGISTER_IMM;
    auto itorLRI = find<MI_LOAD_REGISTER_IMM *>(itorPC, commands.end());
    ASSERT_NE(itorLRI, commands.end());
}

HWTEST2_F(EncodeL3State, givenNoSLMSetCorrectMMIO, IsGen9) {
    ::L0::EncodeL3State<productFamily>::append(*commandList, false);

    parseCommandBuffer<FamilyType>();

    using MI_LOAD_REGISTER_IMM = typename FamilyType::MI_LOAD_REGISTER_IMM;
    auto itorLRI = find<MI_LOAD_REGISTER_IMM *>(commands.begin(), commands.end());
    ASSERT_NE(itorLRI, commands.end());
    auto cmd = genCmdCast<MI_LOAD_REGISTER_IMM *>(*itorLRI);
    EXPECT_EQ(cmd->getRegisterOffset(), 0x7034);
    EXPECT_EQ(cmd->getDataDword(), 0x80000140u);
}

HWTEST2_F(EncodeL3State, givenSLMSetCorrectMMIO, IsGen9) {
    ::L0::EncodeL3State<productFamily>::append(*commandList, true);

    parseCommandBuffer<FamilyType>();

    using MI_LOAD_REGISTER_IMM = typename FamilyType::MI_LOAD_REGISTER_IMM;
    auto itorLRI = find<MI_LOAD_REGISTER_IMM *>(commands.begin(), commands.end());
    ASSERT_NE(itorLRI, commands.end());
    auto cmd = genCmdCast<MI_LOAD_REGISTER_IMM *>(*itorLRI);
    EXPECT_EQ(cmd->getRegisterOffset(), 0x7034);
    EXPECT_EQ(cmd->getDataDword(), 0x60000121u);
}

using IsAtLeastGen12LP = IsAtLeastProduct<IGFX_TIGERLAKE_LP>;
HWTEST2_F(EncodeL3State, setCorrectMMIO, IsAtLeastGen12LP) {
    ::L0::EncodeL3State<productFamily>::append(*commandList, false);

    parseCommandBuffer<FamilyType>();

    using MI_LOAD_REGISTER_IMM = typename FamilyType::MI_LOAD_REGISTER_IMM;
    auto itorLRI = find<MI_LOAD_REGISTER_IMM *>(commands.begin(), commands.end());
    ASSERT_NE(itorLRI, commands.end());
    auto cmd = genCmdCast<MI_LOAD_REGISTER_IMM *>(*itorLRI);
    EXPECT_EQ(cmd->getRegisterOffset(), 0xB134);
    EXPECT_EQ(cmd->getDataDword(), 0xD0000020u);
}

} // namespace ult
} // namespace L0
