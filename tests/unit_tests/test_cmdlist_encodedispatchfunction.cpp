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

struct Function;
struct FunctionArguments;

namespace ult {

using ::testing::Return;

TEST(xeCommandListEncodeDispatchFunction, redirectsToCmdListObject) {
    Mock<CommandList> commandList;
    xe_event_handle_t event = {};
    xe_function_handle_t function = {};
    xe_function_args_handle_t functionArgs = {};
    xe_dispatch_function_arguments_t dispatchFunctionArguments;

    EXPECT_CALL(commandList, encodeDispatchFunction(
                                 function,
                                 functionArgs,
                                 &dispatchFunctionArguments,
                                 event))
        .Times(1);

    auto result = xe::xeCommandListEncodeDispatchFunction(commandList.toHandle(),
                                                          function,
                                                          functionArgs,
                                                          &dispatchFunctionArguments,
                                                          event);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

using CommandListEncodeDispatchFunction = ::testing::Test;

ATSTEST_F(CommandListEncodeDispatchFunction, addsWalkerToCommandStream) {
    Mock<Device> device;
    Mock<MemoryManager> memoryManager;
    EXPECT_CALL(device, getMemoryManager())
        .WillRepeatedly(Return(&memoryManager));

    int8_t buffer[1024];
    GraphicsAllocation allocation(buffer, sizeof(buffer));
    EXPECT_CALL(memoryManager, allocateDeviceMemory)
        .WillOnce(Return(&allocation));

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList->commandStream);
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    xe_function_handle_t function = {};
    xe_function_args_handle_t functionArgs = {};
    xe_dispatch_function_arguments_t dispatchFunctionArguments = {};

    dispatchFunctionArguments.groupCountX = 1u;
    dispatchFunctionArguments.groupCountY = 2u;
    dispatchFunctionArguments.groupCountZ = 3u;

    auto result = commandList->encodeDispatchFunction(function,
                                                      functionArgs,
                                                      &dispatchFunctionArguments,
                                                      nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandList->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));
    using COMPUTE_WALKER = typename FamilyType::COMPUTE_WALKER;
    auto itor = find<COMPUTE_WALKER *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    {
        auto cmd = genCmdCast<COMPUTE_WALKER *>(*itor);

        EXPECT_EQ(cmd->getThreadGroupIdXDimension(), dispatchFunctionArguments.groupCountX);
        EXPECT_EQ(cmd->getThreadGroupIdYDimension(), dispatchFunctionArguments.groupCountY);
        EXPECT_EQ(cmd->getThreadGroupIdZDimension(), dispatchFunctionArguments.groupCountZ);
        EXPECT_EQ(cmd->getEmitLocalId(), 0u);
        EXPECT_NE(cmd->getExecutionMask(), 0u);
        EXPECT_EQ(cmd->getSimdSize(), COMPUTE_WALKER::SIMD_SIZE_SIMD32);
    }
}

} // namespace ult
} // namespace xe
