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

namespace xe {
namespace ult {

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Return;

TEST(xeCommandListEncodeWaitOnEvent, redirectsToCmdListObject) {
    Mock<CommandList> commandList;
    xe_event_handle_t event = {};

    EXPECT_CALL(commandList, encodeWaitOnEvent(event)).Times(1);

    auto result = xe::xeCommandListEncodeWaitOnEvent(commandList.toHandle(),
                                                     event);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

using CommandListEncodeWaitOnEvent = ::testing::Test;

HWTEST_F(CommandListEncodeWaitOnEvent, addsSemaphoreToCommandStream) {
    Mock<Device> device;
    Mock<MemoryManager> memoryManager;
    EXPECT_CALL(device, getMemoryManager())
        .WillRepeatedly(Return(&memoryManager));
    EXPECT_CALL(memoryManager, allocateDeviceMemory(_)).Times(AnyNumber());
    EXPECT_CALL(memoryManager, freeMemory(_)).Times(AnyNumber());

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList->commandStream);
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    Mock<Event> event;
    auto result = commandList->encodeWaitOnEvent(event.toHandle());
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

HWTEST_F(CommandListEncodeWaitOnEvent, addsEventGraphicsAllocationToResidencyContainer) {
    Mock<Device> device;
    Mock<MemoryManager> memoryManager;
    EXPECT_CALL(device, getMemoryManager())
        .WillRepeatedly(Return(&memoryManager));
    EXPECT_CALL(memoryManager, allocateDeviceMemory(_)).Times(AnyNumber());
    EXPECT_CALL(memoryManager, freeMemory(_)).Times(AnyNumber());

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList->commandStream);
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    Mock<Event> event;
    auto result = commandList->encodeWaitOnEvent(event.toHandle());
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto &residencyContainer = commandList->residencyContainer;
    auto allocationRT = static_cast<OCLRT::GraphicsAllocation *>(event.allocation->allocationRT);
    auto itor = std::find(std::begin(residencyContainer), std::end(residencyContainer), allocationRT); 
    EXPECT_NE(itor, std::end(residencyContainer));
}

} // namespace ult
} // namespace xe
