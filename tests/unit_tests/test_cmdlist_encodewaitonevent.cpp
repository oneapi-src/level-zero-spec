#include "test.h"
#include "xe_all.h"
#include "graphics_allocation.h"
#include "igfxfmid.h"
#include "mock_cmdlist.h"
#include "mock_device.h"
#include "mock_event.h"
#include "mock_memory_manager.h"
#include "runtime/command_stream/linear_stream.h"
#include "unit_tests/gen_common/gen_cmd_parse.h"
#include "gmock/gmock.h"

namespace L0 {
namespace ult {

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Return;

TEST(xeCommandListAppendWaitOnEvent, redirectsToObject) {
    Mock<CommandList> commandList;
    Mock<Event> event;

    EXPECT_CALL(commandList, appendWaitOnEvent(event.toHandle())).Times(1);

    auto result = xeCommandListAppendWaitOnEvent(commandList.toHandle(),
                                                 event.toHandle());
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

using CommandListAppendWaitOnEvent = ::testing::Test;

HWTEST_F(CommandListAppendWaitOnEvent, addsSemaphoreToCommandStream) {
    Mock<Device> device;

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList->commandStream);
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    Mock<Event> event;
    auto result = commandList->appendWaitOnEvent(event.toHandle());
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandList->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));
    using MI_SEMAPHORE_WAIT = typename FamilyType::MI_SEMAPHORE_WAIT;
    auto itor = find<MI_SEMAPHORE_WAIT *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    {
        auto cmd = genCmdCast<MI_SEMAPHORE_WAIT *>(*itor);
        EXPECT_EQ(cmd->getCompareOperation(), MI_SEMAPHORE_WAIT::COMPARE_OPERATION::COMPARE_OPERATION_SAD_NOT_EQUAL_SDD);
        EXPECT_EQ(cmd->getSemaphoreDataDword(), 1u);
        EXPECT_EQ(cmd->getSemaphoreGraphicsAddress(), event.allocation->getGpuAddress());
    }
}

HWTEST_F(CommandListAppendWaitOnEvent, addsEventGraphicsAllocationToResidencyContainer) {
    Mock<Device> device;

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList->commandStream);
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    Mock<Event> event;
    auto result = commandList->appendWaitOnEvent(event.toHandle());
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto &residencyContainer = commandList->residencyContainer;
    auto allocationRT = static_cast<OCLRT::GraphicsAllocation *>(event.allocation->allocationRT);
    auto itor = std::find(std::begin(residencyContainer), std::end(residencyContainer), allocationRT);
    EXPECT_NE(itor, std::end(residencyContainer));
}

} // namespace ult
} // namespace L0
