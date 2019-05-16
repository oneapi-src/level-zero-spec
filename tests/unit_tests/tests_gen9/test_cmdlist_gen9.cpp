#include "tests/unit_tests/mock_cmdlist.h"
#include "tests/unit_tests/mock_device.h"
#include "tests/unit_tests/mock_memory_manager.h"
#include "tests/unit_tests/mock_mocs_mapper.h"
#include "event.h"
#include "graphics_allocation.h"
#include "igfxfmid.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/indirect_heap/indirect_heap.h"
#include "tests/unit_tests/test.h"
#include "unit_tests/gen_common/gen_cmd_parse.h"
#include "tests/unit_tests/global_fixture.h"

namespace L0 {
namespace ult {

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Return;

class CommandListCreate : public GlobalFixtureTest {};

GEN9TEST_F(CommandListCreate, addsPipelineSelectBeforeVfeStateToBatchBuffer) {
    Mock<Device> device;

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList->commandStream);
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    auto result = commandList->close();
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(
        cmdList, ptrOffset(commandList->commandStream->getCpuBase(), 0), usedSpaceAfter));
    using MEDIA_VFE_STATE = typename FamilyType::MEDIA_VFE_STATE;
    auto itorVFE = find<MEDIA_VFE_STATE *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(itorVFE, cmdList.end());

    // Should have a PS before a VFE
    using PIPELINE_SELECT = typename FamilyType::PIPELINE_SELECT;
    auto itorPS = find<PIPELINE_SELECT *>(cmdList.begin(), itorVFE);
    ASSERT_NE(itorPS, itorVFE);

    {
        auto cmd = genCmdCast<PIPELINE_SELECT *>(*itorPS);
        EXPECT_EQ(cmd->getMaskBits() & 3u, 3u);
        EXPECT_EQ(cmd->getPipelineSelection(), PIPELINE_SELECT::PIPELINE_SELECTION_GPGPU);
    }
}

GEN9TEST_F(CommandListCreate, programsThreadGroupPreemption) {
    Mock<Device> device;

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList->commandStream);
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    auto result = commandList->close();
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(
        cmdList, ptrOffset(commandList->commandStream->getCpuBase(), 0), usedSpaceAfter));

    using MI_LOAD_REGISTER_IMM = typename FamilyType::MI_LOAD_REGISTER_IMM;
    auto itor = find<MI_LOAD_REGISTER_IMM *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(itor, cmdList.end());

    constexpr uint32_t mmioAddress = 0x2580;
    constexpr uint32_t maskVal = (1 << 1) | (1 << 2);
    constexpr uint32_t maskShift = 16;
    constexpr uint32_t mask = maskVal << maskShift;
    constexpr uint32_t threadGroupVal = (1 << 1);
    constexpr uint32_t regVal = threadGroupVal | mask;
    auto lri = genCmdCast<MI_LOAD_REGISTER_IMM *>(*itor);
    EXPECT_EQ(mmioAddress, lri->getRegisterOffset());
    EXPECT_EQ(regVal, lri->getDataDword());
}

GEN9TEST_F(CommandListCreate, addsVfeStateToBatchBuffer) {
    Mock<Device> device;

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList->commandStream);
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    auto result = commandList->close();
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(
        cmdList, ptrOffset(commandList->commandStream->getCpuBase(), 0), usedSpaceAfter));
    using MEDIA_VFE_STATE = typename FamilyType::MEDIA_VFE_STATE;
    auto itor = find<MEDIA_VFE_STATE *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    {
        auto cmd = genCmdCast<MEDIA_VFE_STATE *>(*itor);
        EXPECT_EQ(cmd->getNumberOfUrbEntries(), 1u);
        EXPECT_GT(cmd->getUrbEntryAllocationSize(), 0u);
        EXPECT_GT(cmd->getMaximumNumberOfThreads(), 0u);

        EXPECT_EQ(cmd->getPerThreadScratchSpace(), 0u);
        EXPECT_EQ(cmd->getStackSize(), 0u);
        uint64_t scratchAddress = cmd->getScratchSpaceBasePointerHigh();
        scratchAddress <<= 32u;
        scratchAddress |= cmd->getScratchSpaceBasePointer();
        EXPECT_EQ(scratchAddress, 0u);
    }
}

} // namespace ult
} // namespace L0
