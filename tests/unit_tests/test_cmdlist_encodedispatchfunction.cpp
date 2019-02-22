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

TEST(xeCommandListEncodeDispatchFunction, redirectsToObject) {
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
        EXPECT_CALL(device, getMemoryManager).Times(AnyNumber());

        auto memoryManager = device.getMemoryManager();
        ASSERT_NE(memoryManager, nullptr);
        buffer1 = memoryManager->allocateDeviceMemory(16384u, 4096u);
        buffer2 = memoryManager->allocateDeviceMemory(16384u, 4096u);

        commandList = whitebox_cast(CommandList::create(productFamily, &device));
        ASSERT_NE(commandList->commandStream, nullptr);

        dispatchFunctionArguments.version = XE_DISPATCH_FUNCTION_ARGS_VERSION;
        dispatchFunctionArguments.groupCountX = 1u;
        dispatchFunctionArguments.groupCountY = 2u;
        dispatchFunctionArguments.groupCountZ = 3u;

        std::string deviceName = "Gen12HPcore";
        function = new PrecompiledFunctionMock("MemcpyBytes", deviceName);
        functionArgs = new PrecompiledFunctionArgsMock(function, {&buffer1, &buffer2});

        EXPECT_CALL(*function, getThreadExecutionMask()).Times(AnyNumber());
    }

    void TearDown() override {
        delete functionArgs;
        delete function;

        auto memoryManager = device.getMemoryManager();
        ASSERT_NE(memoryManager, nullptr);
        memoryManager->freeMemory(buffer1);
        memoryManager->freeMemory(buffer2);
    }

    Mock<Device> device;
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
    using POSTSYNC_DATA = typename FamilyType::POSTSYNC_DATA;
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

        auto &postSync = cmd->getPostSync();
        EXPECT_EQ(postSync.getDestinationAddress(), 0u);
        EXPECT_EQ(postSync.getOperation(), POSTSYNC_DATA::OPERATION_NO_WRITE);

        auto &idd = cmd->getInterfaceDescriptor();
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

ATSTEST_F(CommandListEncodeDispatchFunction, withEventSetsPostSyncOp) {
    auto usedSpaceBefore = commandList->commandStream->getUsed();
    auto event = whitebox_cast(Event::create(&device));

    auto result = commandList->encodeDispatchFunction(function->toHandle(),
                                                      functionArgs->toHandle(),
                                                      &dispatchFunctionArguments,
                                                      event->toHandle());
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandList->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));
    using COMPUTE_WALKER = typename FamilyType::COMPUTE_WALKER;
    using POSTSYNC_DATA = typename FamilyType::POSTSYNC_DATA;

    auto itor = find<COMPUTE_WALKER *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    {
        auto cmd = genCmdCast<COMPUTE_WALKER *>(*itor);
        auto &postSync = cmd->getPostSync();

        EXPECT_NE(postSync.getDestinationAddress(), 0u);
        EXPECT_EQ(postSync.getOperation(), POSTSYNC_DATA::OPERATION_WRITE_TIMESTAMP);
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

        auto indirectDataLength = function->getPerThreadDataSize() +
                                  functionArgs->getCrossThreadDataSize();
        EXPECT_LE(cmd->getIndirectDataLength(), indirectDataLength);

        cmd->getIndirectDataLength();
        cmd->getIndirectDataStartAddress();
        auto heap = commandList->indirectHeaps[CommandList::GENERAL_STATE];

        auto ptrHeap = ptrOffset(heap->getCpuBase(), cmd->getIndirectDataStartAddress());
        EXPECT_EQ(memcmp(ptrHeap, functionArgs->getCrossThreadDataHostMem(), functionArgs->getCrossThreadDataSize()), 0u);
        ptrHeap = ptrOffset(ptrHeap, functionArgs->getCrossThreadDataSize());
        EXPECT_EQ(memcmp(ptrHeap, function->getPerThreadDataHostMem(), function->getPerThreadDataSize()), 0u);
        ptrHeap = ptrOffset(ptrHeap, function->getPerThreadDataSize());
    }
}

ATSTEST_F(CommandListEncodeDispatchFunction, copiesKernelIsaToInstructionHeap) {
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
        auto &idd = cmd->getInterfaceDescriptor();
        uint64_t kernelOffset = idd.getKernelStartPointerHigh();
        kernelOffset <<= 32u; 
        kernelOffset |= idd.getKernelStartPointerHigh();

        auto heap = commandList->indirectHeaps[CommandList::INSTRUCTION];

        auto ptrHeap = ptrOffset(heap->getCpuBase(), kernelOffset);
        EXPECT_EQ(memcmp(ptrHeap, function->getIsaHostMem(), function->getIsaSize()), 0u);
    }
}

} // namespace ult
} // namespace xe
