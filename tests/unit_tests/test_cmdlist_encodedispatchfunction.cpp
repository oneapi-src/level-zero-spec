#include "test.h"
#include "xe_all.h"
#include "graphics_allocation.h"
#include "igfxfmid.h"
#include "mock_cmdlist.h"
#include "mock_device.h"
#include "mock_event.h"
#include "mock_memory_manager.h"
#include "mock_module.h"
#include "mock_module_precompiled.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/indirect_heap/indirect_heap.h"
#include "unit_tests/gen_common/gen_cmd_parse.h"
#include "gmock/gmock.h"

namespace xe {

struct Function;
struct FunctionArguments;

namespace ult {

using ::testing::_;
using ::testing::AnyNumber;
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

struct CommandListEncodeDispatchFunction : public ::testing::Test {

    CommandListEncodeDispatchFunction() {
    }

    void SetUp() override {
        EXPECT_CALL(device, getMemoryManager())
            .WillRepeatedly(Return(&memoryManager));
        EXPECT_CALL(memoryManager, allocateDeviceMemory(_, _)).Times(AnyNumber());
        EXPECT_CALL(memoryManager, freeMemory(_)).Times(AnyNumber());

        buffer1 = memoryManager.allocateDeviceMemory(16384u, 4096u);
        buffer2 = memoryManager.allocateDeviceMemory(16384u, 4096u);

        commandList = whitebox_cast(CommandList::create(productFamily, &device));
        ASSERT_NE(nullptr, commandList->commandStream);

        dispatchFunctionArguments.groupCountX = 1u;
        dispatchFunctionArguments.groupCountY = 2u;
        dispatchFunctionArguments.groupCountZ = 3u;

        std::string deviceName = "Gen12HPcore";
        function = new PrecompiledFunctionMock("MemcpyBytes", deviceName);
        functionArgs = new PrecompiledFunctionArgsMock(function, {&buffer1, &buffer2});
    }

    void TearDown() override {
        delete functionArgs;
        delete function;
        memoryManager.freeMemory(buffer1);
        memoryManager.freeMemory(buffer2);
    }

    Mock<Device> device;
    Mock<MemoryManager> memoryManager;
    WhiteBox<::xe::CommandList> *commandList = nullptr;

    PrecompiledFunctionMock *function = nullptr;
    PrecompiledFunctionArgsMock *functionArgs = nullptr;
    xe_dispatch_function_arguments_t dispatchFunctionArguments;

    GraphicsAllocation *buffer1 = nullptr;
    GraphicsAllocation *buffer2 = nullptr;
};

ATSTEST_F(CommandListEncodeDispatchFunction, addsWalkerToCommandStream) {
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    auto result = commandList->encodeDispatchFunction(function->toHandle(),
                                                      functionArgs->toHandle(),
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
    using INTERFACE_DESCRIPTOR_DATA = typename FamilyType::INTERFACE_DESCRIPTOR_DATA;

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

        EXPECT_NE(cmd->getIndirectDataLength(), 0u);

        auto &idd = cmd->getInterfaceDescriptor();
        //TODO: Verify that kernelStartPointer is correct
        //EXPECT_NE(idd.getKernelStartPointer(), 0u);
        //EXPECT_EQ(idd.getKernelStartPointerHigh(), 0u);
        EXPECT_EQ(idd.getSamplerCount(), INTERFACE_DESCRIPTOR_DATA::SAMPLER_COUNT_NO_SAMPLERS_USED);
        EXPECT_EQ(idd.getSamplerStatePointer(), 0u);
        EXPECT_EQ(idd.getBindingTableEntryCount(), 0u);
        EXPECT_EQ(idd.getBindingTablePointer(), 0u);
        EXPECT_NE(idd.getNumberOfThreadsInGpgpuThreadGroup(), 0u);
        EXPECT_EQ(idd.getSharedLocalMemorySize(), INTERFACE_DESCRIPTOR_DATA::SHARED_LOCAL_MEMORY_SIZE_ENCODES_0K);
        EXPECT_EQ(idd.getBarrierEnable(), 0u);
        EXPECT_EQ(idd.getThreadGroupDispatchSize(), 0u);
    }
}

ATSTEST_F(CommandListEncodeDispatchFunction, copiesThreadDataToGeneralStateHeap) {
    auto result = commandList->encodeDispatchFunction(function->toHandle(),
                                                      functionArgs->toHandle(),
                                                      &dispatchFunctionArguments,
                                                      nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandList->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));
    using COMPUTE_WALKER = typename FamilyType::COMPUTE_WALKER;
    using INTERFACE_DESCRIPTOR_DATA = typename FamilyType::INTERFACE_DESCRIPTOR_DATA;

    auto itor = find<COMPUTE_WALKER *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    {
        auto cmd = genCmdCast<COMPUTE_WALKER *>(*itor);

        auto indirectDataLength = functionArgs->getPerThreadDataSize() +
                                  functionArgs->getCrossThreadDataSize();
        EXPECT_LE(cmd->getIndirectDataLength(), indirectDataLength);

        cmd->getIndirectDataLength();
        cmd->getIndirectDataStartAddress();
        auto heap = commandList->indirectHeaps[CommandList::GENERAL_STATE];

        auto ptrHeap = ptrOffset(heap->getCpuBase(), cmd->getIndirectDataStartAddress());
        EXPECT_EQ(memcmp(ptrHeap, functionArgs->getCrossThreadDataHostMem(), functionArgs->getCrossThreadDataSize()), 0u);
        ptrHeap = ptrOffset(ptrHeap, functionArgs->getCrossThreadDataSize());
        EXPECT_EQ(memcmp(ptrHeap, functionArgs->getPerThreadDataHostMem(), functionArgs->getPerThreadDataSize()), 0u);
        ptrHeap = ptrOffset(ptrHeap, functionArgs->getPerThreadDataSize());
    }
}

} // namespace ult
} // namespace xe
