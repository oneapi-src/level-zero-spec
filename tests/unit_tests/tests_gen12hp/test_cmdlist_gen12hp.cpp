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

ATSTEST_F(CommandListCreate, addsCfeStateToBatchBuffer) {
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
    using CFE_STATE = typename FamilyType::CFE_STATE;
    auto itor = find<CFE_STATE *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);
}

} // namespace ult
} // namespace L0
