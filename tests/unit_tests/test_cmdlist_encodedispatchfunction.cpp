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
#include "runtime/helpers/string.h"
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

TEST(xeCommandListAppendLaunchFunction, redirectsToObject) {
    Mock<CommandList> commandList;
    Mock<Event> event;
    Mock<Function> function;
    xe_thread_group_dimensions_t dispatchFunctionArguments;

    EXPECT_CALL(commandList, appendLaunchFunction(
                                 function.toHandle(),
                                 &dispatchFunctionArguments,
                                 event.toHandle()))
        .Times(1);

    auto result = xeCommandListAppendLaunchFunction(commandList.toHandle(),
                                                      function.toHandle(),
                                                      &dispatchFunctionArguments,
                                                      event.toHandle());
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

struct CommandListAppendLaunchFunction : public ::testing::Test {

    CommandListAppendLaunchFunction() {
    }

    void SetUp() override {
        auto memoryManager = device.getMemoryManager();
        ASSERT_NE(memoryManager, nullptr);
        buffer1 = memoryManager->allocateDeviceMemory(16384u, 4096u);
        buffer2 = memoryManager->allocateDeviceMemory(16384u, 4096u);

        commandList = whitebox_cast(CommandList::create(productFamily, &device));
        ASSERT_NE(commandList->commandStream, nullptr);

        dispatchFunctionArguments.groupCountX = 1u;
        dispatchFunctionArguments.groupCountY = 2u;
        dispatchFunctionArguments.groupCountZ = 3u;
    }

    void TearDown() override {
        delete function;

        auto memoryManager = device.getMemoryManager();
        ASSERT_NE(memoryManager, nullptr);
        memoryManager->freeMemory(buffer1);
        memoryManager->freeMemory(buffer2);
    }

    void createFunction(const std::string &functionName) {
        std::string deviceName = "Gen12HPcore";
        function = new PrecompiledFunctionMock(functionName, deviceName, {&buffer1, &buffer2});

        EXPECT_CALL(*function, getThreadExecutionMask()).Times(AnyNumber());
        EXPECT_CALL(*function, setGroupCount(_, _, _)).Times(AnyNumber());
    }

    Mock<Device> device;
    WhiteBox<::L0::CommandList> *commandList = nullptr;

    PrecompiledFunctionMock *function = nullptr;
    xe_thread_group_dimensions_t dispatchFunctionArguments;

    GraphicsAllocation *buffer1 = nullptr;
    GraphicsAllocation *buffer2 = nullptr;
};

ATSTEST_F(CommandListAppendLaunchFunction, addsWalkerToCommandStream) {
    createFunction("MemcpyBytes");

    auto usedSpaceBefore = commandList->commandStream->getUsed();

    auto result = commandList->appendLaunchFunction(function->toHandle(),
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

ATSTEST_F(CommandListAppendLaunchFunction, withBarrierAndSLMSetsIDDBarrierEnableAndSLMSize) {
    createFunction("SlmBarrier");
    auto result = commandList->appendLaunchFunction(function->toHandle(),
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
        EXPECT_EQ(idd.getBarrierEnable(), 1u);
        EXPECT_EQ(INTERFACE_DESCRIPTOR_DATA::SHARED_LOCAL_MEMORY_SIZE_ENCODES_64K, idd.getSharedLocalMemorySize());
    }
}

ATSTEST_F(CommandListAppendLaunchFunction, withEventSetsPostSyncOp) {
    createFunction("MemcpyBytes");

    auto usedSpaceBefore = commandList->commandStream->getUsed();
    auto event = whitebox_cast(Event::create(&device));

    auto result = commandList->appendLaunchFunction(function->toHandle(),
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

ATSTEST_F(CommandListAppendLaunchFunction, copiesThreadDataToGeneralStateHeap) {
    createFunction("MemcpyBytes");

    using COMPUTE_WALKER = typename FamilyType::COMPUTE_WALKER;
    using INTERFACE_DESCRIPTOR_DATA = typename FamilyType::INTERFACE_DESCRIPTOR_DATA;

    auto heap = commandList->indirectHeaps[CommandList::GENERAL_STATE];
    heap->getSpace(COMPUTE_WALKER::INDIRECTDATASTARTADDRESS_ALIGN_SIZE - 1); // this will check if cmdlist takes care of heap allignment

    auto result = commandList->appendLaunchFunction(function->toHandle(),
                                                      &dispatchFunctionArguments,
                                                      nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandList->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));

    auto itor = find<COMPUTE_WALKER *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    {
        auto cmd = genCmdCast<COMPUTE_WALKER *>(*itor);

        auto indirectDataLength = function->getPerThreadDataSize() +
                                  function->getCrossThreadDataSize();
        EXPECT_GE(cmd->getIndirectDataLength(), 0u);
        EXPECT_LE(cmd->getIndirectDataLength(), indirectDataLength);

        auto ptrHeap = ptrOffset(heap->getCpuBase(), cmd->getIndirectDataStartAddress());
        EXPECT_EQ(memcmp(ptrHeap, function->getCrossThreadDataHostMem(), function->getCrossThreadDataSize()), 0u);
        ptrHeap = ptrOffset(ptrHeap, function->getCrossThreadDataSize());
        EXPECT_EQ(memcmp(ptrHeap, function->getPerThreadDataHostMem(), function->getPerThreadDataSize()), 0u);
        ptrHeap = ptrOffset(ptrHeap, function->getPerThreadDataSize());
    }
}

ATSTEST_F(CommandListAppendLaunchFunction, growsGeneralStateHeapIfNeededAndPreservesOldContents) {
    createFunction("MemcpyBytes");

    using COMPUTE_WALKER = typename FamilyType::COMPUTE_WALKER;
    using INTERFACE_DESCRIPTOR_DATA = typename FamilyType::INTERFACE_DESCRIPTOR_DATA;

    auto heap = commandList->indirectHeaps[CommandList::GENERAL_STATE];
    ASSERT_EQ(0U, heap->getUsed());
    heap->overrideMaxSize(COMPUTE_WALKER::INDIRECTDATASTARTADDRESS_ALIGN_SIZE);
    auto preocupiedMemSize = heap->getAvailableSpace() - 1;
    void *preocupiedMem = heap->getSpace(preocupiedMemSize);
    std::vector<char> precopiedMemPattern(preocupiedMemSize, 7);
    memcpy_s(preocupiedMem, preocupiedMemSize, precopiedMemPattern.data(), precopiedMemPattern.size());

    auto result = commandList->appendLaunchFunction(function->toHandle(),
                                                      &dispatchFunctionArguments,
                                                      nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandList->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));

    auto itor = find<COMPUTE_WALKER *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    {
        auto cmd = genCmdCast<COMPUTE_WALKER *>(*itor);

        auto indirectDataLength = function->getPerThreadDataSize() +
                                  function->getCrossThreadDataSize();
        EXPECT_GE(cmd->getIndirectDataLength(), 0u);
        EXPECT_LE(cmd->getIndirectDataLength(), indirectDataLength);

        auto ptrHeap = ptrOffset(heap->getCpuBase(), cmd->getIndirectDataStartAddress());
        EXPECT_EQ(memcmp(ptrHeap, function->getCrossThreadDataHostMem(), function->getCrossThreadDataSize()), 0u);
        ptrHeap = ptrOffset(ptrHeap, function->getCrossThreadDataSize());
        EXPECT_EQ(memcmp(ptrHeap, function->getPerThreadDataHostMem(), function->getPerThreadDataSize()), 0u);
        ptrHeap = ptrOffset(ptrHeap, function->getPerThreadDataSize());
    }

    EXPECT_EQ(0U, memcmp(precopiedMemPattern.data(), heap->getCpuBase(), precopiedMemPattern.size()));
}

using CommandListAppendLaunchFunctionGEN9 = CommandListAppendLaunchFunction;
SKLTEST_F(CommandListAppendLaunchFunctionGEN9, copiesThreadDataToIndirectStateHeap) {
    createFunction("MemcpyBytes");

    using GPGPU_WALKER = typename FamilyType::GPGPU_WALKER;
    using INTERFACE_DESCRIPTOR_DATA = typename FamilyType::INTERFACE_DESCRIPTOR_DATA;

    auto heap = commandList->indirectHeaps[CommandList::INDIRECT_OBJECT];
    heap->getSpace(GPGPU_WALKER::INDIRECTDATASTARTADDRESS_ALIGN_SIZE - 1); // this will check if cmdlist takes care of heap allignment

    auto result = commandList->appendLaunchFunction(function->toHandle(),
                                                      &dispatchFunctionArguments,
                                                      nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandList->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));

    auto itor = find<GPGPU_WALKER *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    {
        auto cmd = genCmdCast<GPGPU_WALKER *>(*itor);

        auto indirectDataLength = function->getPerThreadDataSize() +
                                  function->getCrossThreadDataSize();
        EXPECT_GE(cmd->getIndirectDataLength(), 0u);
        EXPECT_LE(cmd->getIndirectDataLength(), indirectDataLength);

        auto ptrHeap = ptrOffset(heap->getCpuBase(), cmd->getIndirectDataStartAddress());
        EXPECT_EQ(memcmp(ptrHeap, function->getCrossThreadDataHostMem(), function->getCrossThreadDataSize()), 0u);
        ptrHeap = ptrOffset(ptrHeap, function->getCrossThreadDataSize());
        EXPECT_EQ(memcmp(ptrHeap, function->getPerThreadDataHostMem(), function->getPerThreadDataSize()), 0u);
        ptrHeap = ptrOffset(ptrHeap, function->getPerThreadDataSize());
    }
}

ATSTEST_F(CommandListAppendLaunchFunction, usesIsaFromInstructionHeap) {
    createFunction("MemcpyBytes");
    auto result = commandList->appendLaunchFunction(function->toHandle(),
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

    COMPUTE_WALKER addressValidator{};
    addressValidator.getInterfaceDescriptor().setKernelStartPointer(function->getIsaGraphicsAllocation()->getGpuAddressOffsetFromHeapBase());

    auto itor = find<COMPUTE_WALKER *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    {
        auto cmd = genCmdCast<COMPUTE_WALKER *>(*itor);
        auto &idd = cmd->getInterfaceDescriptor();

        EXPECT_EQ(addressValidator.getInterfaceDescriptor().getKernelStartPointer(), idd.getKernelStartPointer());
    }
}

GEN9TEST_F(CommandListAppendLaunchFunctionGEN9, addsWalkerToCommandStream) {
    createFunction("MemcpyBytes");
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    auto result = commandList->appendLaunchFunction(function->toHandle(),
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
        EXPECT_GE(cmd->getIndirectDataLength(), indirectDataLength);

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

GEN9TEST_F(CommandListAppendLaunchFunctionGEN9, programsL3InBatchBuffer) {
    createFunction("MemcpyBytes");

    Mock<Device> device;

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList->commandStream);
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    auto result = commandList->appendLaunchFunction(function->toHandle(),
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

GEN9TEST_F(CommandListAppendLaunchFunctionGEN9, withBarrierAndSLMSetsIDDBarrierEnable) {
    createFunction("SlmBarrier");

    auto result = commandList->appendLaunchFunction(function->toHandle(),
                                                      &dispatchFunctionArguments,
                                                      nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();

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

    EXPECT_EQ(idd->getBarrierEnable(), 1u);
    // Do not set SLM size for now - it requires proper L3 programming
    EXPECT_EQ(INTERFACE_DESCRIPTOR_DATA::SHARED_LOCAL_MEMORY_SIZE_ENCODES_0K, idd->getSharedLocalMemorySize());
}

} // namespace ult
} // namespace L0
