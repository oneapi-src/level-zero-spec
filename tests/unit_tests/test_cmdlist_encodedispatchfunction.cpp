#include "test.h"
#include "xe_all.h"
#include "graphics_allocation.h"
#include "igfxfmid.h"
#include "mock_cmdlist.h"
#include "mock_device.h"
#include "mock_event.h"
#include "mock_function.h"
#include "mock_memory_manager.h"
#include "mock_module.h"
#include "mock_module_precompiled.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/indirect_heap/indirect_heap.h"
#include "unit_tests/gen_common/gen_cmd_parse.h"
#include "gmock/gmock.h"

namespace L0 {

struct Function;
struct FunctionArguments;

namespace ult {

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Return;

TEST(xeCommandListEncodeDispatchFunction, redirectsToObject) {
    Mock<CommandList> commandList;
    Mock<Event> event;
    Mock<Function> function;
    xe_dispatch_function_arguments_t dispatchFunctionArguments;

    EXPECT_CALL(commandList, encodeDispatchFunction(
                                 function.toHandle(),
                                 &dispatchFunctionArguments,
                                 event.toHandle()))
        .Times(1);

    auto result = xeCommandListEncodeDispatchFunction(commandList.toHandle(),
                                                      function.toHandle(),
                                                      &dispatchFunctionArguments,
                                                      event.toHandle());
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
        function = new PrecompiledFunctionMock("MemcpyBytes", deviceName, {&buffer1, &buffer2});

        EXPECT_CALL(*function, getThreadExecutionMask()).Times(AnyNumber());
    }

    void TearDown() override {
        delete function;

        auto memoryManager = device.getMemoryManager();
        ASSERT_NE(memoryManager, nullptr);
        memoryManager->freeMemory(buffer1);
        memoryManager->freeMemory(buffer2);
    }

    Mock<Device> device;
    WhiteBox<::L0::CommandList> *commandList = nullptr;

    PrecompiledFunctionMock *function = nullptr;
    xe_dispatch_function_arguments_t dispatchFunctionArguments;

    GraphicsAllocation *buffer1 = nullptr;
    GraphicsAllocation *buffer2 = nullptr;
};

ATSTEST_F(CommandListEncodeDispatchFunction, addsWalkerToCommandStream) {
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    auto result = commandList->encodeDispatchFunction(function->toHandle(),
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
                                  function->getCrossThreadDataSize();
        EXPECT_GE(cmd->getIndirectDataLength(), 0u);
        EXPECT_LE(cmd->getIndirectDataLength(), indirectDataLength);

        auto heap = commandList->indirectHeaps[CommandList::GENERAL_STATE];

        auto ptrHeap = ptrOffset(heap->getCpuBase(), cmd->getIndirectDataStartAddress());
        EXPECT_EQ(memcmp(ptrHeap, function->getCrossThreadDataHostMem(), function->getCrossThreadDataSize()), 0u);
        ptrHeap = ptrOffset(ptrHeap, function->getCrossThreadDataSize());
        EXPECT_EQ(memcmp(ptrHeap, function->getPerThreadDataHostMem(), function->getPerThreadDataSize()), 0u);
        ptrHeap = ptrOffset(ptrHeap, function->getPerThreadDataSize());
    }
}

ATSTEST_F(CommandListEncodeDispatchFunction, copiesKernelIsaToInstructionHeap) {
    auto result = commandList->encodeDispatchFunction(function->toHandle(),
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
        kernelOffset |= idd.getKernelStartPointer();

        auto heap = commandList->indirectHeaps[CommandList::INSTRUCTION];

        auto ptrHeap = ptrOffset(heap->getCpuBase(), kernelOffset);
        EXPECT_EQ(memcmp(ptrHeap, function->getIsaHostMem(), function->getIsaSize()), 0u);
    }
}

using CommandListEncodeDispatchFunctionGEN9 = CommandListEncodeDispatchFunction;
GEN9TEST_F(CommandListEncodeDispatchFunctionGEN9, addsWalkerToCommandStream) {
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    auto result = commandList->encodeDispatchFunction(function->toHandle(),
                                                      &dispatchFunctionArguments,
                                                      nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandList->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));
    using GPGPU_WALKER = typename FamilyType::GPGPU_WALKER;
    using INTERFACE_DESCRIPTOR_DATA = typename FamilyType::INTERFACE_DESCRIPTOR_DATA;
    using MEDIA_INTERFACE_DESCRIPTOR_LOAD = typename FamilyType::MEDIA_INTERFACE_DESCRIPTOR_LOAD;

    auto itorWalker = find<GPGPU_WALKER *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itorWalker);

    auto itorMIDL = find<MEDIA_INTERFACE_DESCRIPTOR_LOAD *>(cmdList.begin(), itorWalker);
    ASSERT_NE(itorMIDL, itorWalker);
    INTERFACE_DESCRIPTOR_DATA *idd = nullptr;
    {
        auto cmd = genCmdCast<MEDIA_INTERFACE_DESCRIPTOR_LOAD *>(*itorMIDL);
        ASSERT_NE(cmd, nullptr);

        EXPECT_EQ(cmd->getInterfaceDescriptorTotalLength(), sizeof(INTERFACE_DESCRIPTOR_DATA));
        auto dsh = commandList->indirectHeaps[CommandList::DYNAMIC_STATE];
        EXPECT_LE(cmd->getInterfaceDescriptorDataStartAddress() + cmd->getInterfaceDescriptorTotalLength(), dsh->getUsed());
        idd = static_cast<INTERFACE_DESCRIPTOR_DATA *>(ptrOffset(dsh->getCpuBase(), cmd->getInterfaceDescriptorDataStartAddress()));
    }

    {
        auto cmd = genCmdCast<GPGPU_WALKER *>(*itorWalker);
        ASSERT_NE(cmd, nullptr);

        EXPECT_EQ(cmd->getThreadGroupIdXDimension(), dispatchFunctionArguments.groupCountX);
        EXPECT_EQ(cmd->getThreadGroupIdYDimension(), dispatchFunctionArguments.groupCountY);
        EXPECT_EQ(cmd->getThreadGroupIdZDimension(), dispatchFunctionArguments.groupCountZ);
        EXPECT_NE(cmd->getRightExecutionMask(), 0u);
        EXPECT_EQ(cmd->getBottomExecutionMask(), 0xffffffffu);
        EXPECT_EQ(cmd->getSimdSize(), GPGPU_WALKER::SIMD_SIZE_SIMD32);

        // Index into MIDL table.  Should always be 0
        EXPECT_EQ(cmd->getInterfaceDescriptorOffset(), 0u);

        // Relative to IndirectObjectBaseAddress
        auto indirectDataLength = function->getPerThreadDataSize() +
                                  function->getCrossThreadDataSize();
        EXPECT_EQ(cmd->getIndirectDataLength() % GPGPU_WALKER::INDIRECTDATASTARTADDRESS_ALIGN_SIZE, 0u);
        EXPECT_GE(cmd->getIndirectDataLength(), 0u);
        EXPECT_LE(cmd->getIndirectDataLength(), indirectDataLength);

        auto heap = commandList->indirectHeaps[CommandList::INDIRECT_OBJECT];

        auto ptrHeap = ptrOffset(heap->getCpuBase(), cmd->getIndirectDataStartAddress());
        EXPECT_EQ(memcmp(ptrHeap, function->getCrossThreadDataHostMem(), function->getCrossThreadDataSize()), 0u);
        ptrHeap = ptrOffset(ptrHeap, function->getCrossThreadDataSize());
        EXPECT_EQ(memcmp(ptrHeap, function->getPerThreadDataHostMem(), function->getPerThreadDataSize()), 0u);
        ptrHeap = ptrOffset(ptrHeap, function->getPerThreadDataSize());

        EXPECT_EQ(idd->getSamplerCount(), INTERFACE_DESCRIPTOR_DATA::SAMPLER_COUNT_NO_SAMPLERS_USED);
        EXPECT_EQ(idd->getSamplerStatePointer(), 0u);
        EXPECT_EQ(idd->getBindingTableEntryCount(), 0u);
        EXPECT_EQ(idd->getBindingTablePointer(), 0u);
        EXPECT_NE(idd->getNumberOfThreadsInGpgpuThreadGroup(), 0u);
        EXPECT_EQ(idd->getSharedLocalMemorySize(), INTERFACE_DESCRIPTOR_DATA::SHARED_LOCAL_MEMORY_SIZE_ENCODES_0K);
        EXPECT_EQ(idd->getBarrierEnable(), 0u);

        EXPECT_NE(idd->getCrossThreadConstantDataReadLength(), 0u);
        EXPECT_NE(idd->getConstantIndirectUrbEntryReadLength(), 0u);
    }
}

GEN9TEST_F(CommandListEncodeDispatchFunctionGEN9, programsL3InBatchBuffer) {
    Mock<Device> device;
    EXPECT_CALL(device, getMemoryManager).Times(AnyNumber());

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList->commandStream);
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    auto result = commandList->encodeDispatchFunction(function->toHandle(),
                                                      &dispatchFunctionArguments,
                                                      nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandList->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));
    using MI_LOAD_REGISTER_IMM = typename FamilyType::MI_LOAD_REGISTER_IMM;
    using PIPE_CONTROL = typename FamilyType::PIPE_CONTROL;

    auto itorPC = find<PIPE_CONTROL *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(itorPC, cmdList.end());
    {
        auto cmd = genCmdCast<PIPE_CONTROL *>(*itorPC);
        EXPECT_TRUE(cmd->getCommandStreamerStallEnable());
        EXPECT_TRUE(cmd->getDcFlushEnable());
    }

    auto itorLRI = find<MI_LOAD_REGISTER_IMM *>(itorPC, cmdList.end());
    ASSERT_NE(itorLRI, cmdList.end());
    {
        auto cmd = genCmdCast<MI_LOAD_REGISTER_IMM *>(*itorLRI);
        EXPECT_NE(cmd->getRegisterOffset(), 0u);
    }
}

} // namespace ult
} // namespace L0
