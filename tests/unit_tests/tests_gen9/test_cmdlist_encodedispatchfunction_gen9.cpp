#include "runtime/command_stream/linear_stream.h"
#include "runtime/helpers/string.h"
#include "runtime/indirect_heap/indirect_heap.h"
#include "unit_tests/gen_common/gen_cmd_parse.h"

#include "encode_l3state.h"
#include "gmock/gmock.h"
#include "graphics_allocation.h"
#include "igfxfmid.h"
#include "tests/unit_tests/mock_cmdlist.h"
#include "tests/unit_tests/mock_device.h"
#include "tests/unit_tests/mock_event.h"
#include "tests/unit_tests/mock_function.h"
#include "tests/unit_tests/mock_memory_manager.h"
#include "tests/unit_tests/mock_module.h"
#include "tests/unit_tests/mock_module_precompiled.h"
#include "tests/unit_tests/test.h"
#include "xe_api.h"
#include "tests/unit_tests/global_fixture.h"

namespace L0 {

struct Function;
struct FunctionArguments;

namespace ult {

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Return;

struct CommandListAppendLaunchFunction : public GlobalFixtureTest {

    CommandListAppendLaunchFunction() {}

    void SetUp() override {
        GlobalFixtureTest::SetUp();
        auto memoryManager = globalMemoryManager;
        ASSERT_NE(memoryManager, nullptr);
        buffer1 = memoryManager->allocateDeviceMemory(&device, 16384u, 4096u);
        buffer2 = memoryManager->allocateDeviceMemory(&device, 16384u, 4096u);

        commandList = whitebox_cast(CommandList::create(productFamily, &device));
        ASSERT_NE(commandList->commandStream, nullptr);

        dispatchFunctionArguments.groupCountX = 1u;
        dispatchFunctionArguments.groupCountY = 2u;
        dispatchFunctionArguments.groupCountZ = 3u;
    }

    void TearDown() override {
        delete function;

        auto memoryManager = globalMemoryManager;
        ASSERT_NE(memoryManager, nullptr);
        memoryManager->freeGraphicsAllocation(buffer1);
        memoryManager->freeGraphicsAllocation(buffer2);
        GlobalFixtureTest::TearDown();
    }

    void createFunction(const std::string &functionName) {
        std::string deviceName = "Gen12HPcore";
        function = new PrecompiledFunctionMock(functionName, deviceName, {&buffer1, &buffer2});
        function->expectAnyMockFunctionCall();
    }

    Mock<Device> device;
    WhiteBox<::L0::CommandList> *commandList = nullptr;

    PrecompiledFunctionMock *function = nullptr;
    xe_thread_group_dimensions_t dispatchFunctionArguments;

    GraphicsAllocation *buffer1 = nullptr;
    GraphicsAllocation *buffer2 = nullptr;
};

using CommandListAppendLaunchFunctionGEN9 = CommandListAppendLaunchFunction;

using IsSKLOrKBL = IsWithinProducts<IGFX_SKYLAKE, IGFX_KABYLAKE>;

SKLTEST_F(CommandListAppendLaunchFunctionGEN9, copiesThreadDataToIndirectStateHeap) {
    createFunction("MemcpyBytes");

    using GPGPU_WALKER = typename FamilyType::GPGPU_WALKER;
    using INTERFACE_DESCRIPTOR_DATA = typename FamilyType::INTERFACE_DESCRIPTOR_DATA;

    auto heap = commandList->indirectHeaps[CommandList::INDIRECT_OBJECT];
    heap->getSpace(GPGPU_WALKER::INDIRECTDATASTARTADDRESS_ALIGN_SIZE -
                   1); // this will check if cmdlist takes care of heap allignment

    auto result = commandList->appendLaunchFunction(
        function->toHandle(), &dispatchFunctionArguments, nullptr, 0, nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(
        cmdList, ptrOffset(commandList->commandStream->getCpuBase(), 0), usedSpaceAfter));

    auto itor = find<GPGPU_WALKER *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    {
        auto cmd = genCmdCast<GPGPU_WALKER *>(*itor);

        auto indirectDataLength = function->getPerThreadDataSizeForWholeThreadGroup() +
                                  function->getCrossThreadDataSize();
        EXPECT_GE(cmd->getIndirectDataLength(), 0u);
        EXPECT_LE(cmd->getIndirectDataLength(), indirectDataLength);

        auto ptrHeap = ptrOffset(heap->getCpuBase(), cmd->getIndirectDataStartAddress());
        EXPECT_EQ(memcmp(ptrHeap, function->getCrossThreadData().get(),
                         function->getCrossThreadDataSize()),
                  0u);
        ptrHeap = ptrOffset(ptrHeap, function->getCrossThreadDataSize());
        EXPECT_EQ(memcmp(ptrHeap, function->getPerThreadData().get(),
                         function->getPerThreadDataSizeForWholeThreadGroup()),
                  0u);
        ptrHeap = ptrOffset(ptrHeap, function->getPerThreadDataSizeForWholeThreadGroup());
    }
}

GEN9TEST_F(CommandListAppendLaunchFunctionGEN9, addsWalkerToCommandStream) {
    createFunction("MemcpyBytes");
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    auto result = commandList->appendLaunchFunction(
        function->toHandle(), &dispatchFunctionArguments, nullptr, 0, nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(
        cmdList, ptrOffset(commandList->commandStream->getCpuBase(), 0), usedSpaceAfter));
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
        EXPECT_LE(cmd->getInterfaceDescriptorDataStartAddress() +
                      cmd->getInterfaceDescriptorTotalLength(),
                  dsh->getUsed());
        idd = static_cast<INTERFACE_DESCRIPTOR_DATA *>(
            ptrOffset(dsh->getCpuBase(), cmd->getInterfaceDescriptorDataStartAddress()));
    }

    {
        auto cmd = genCmdCast<GPGPU_WALKER *>(*itorWalker);
        ASSERT_NE(cmd, nullptr);

        EXPECT_EQ(function->getThreadsPerThreadGroup(), cmd->getThreadWidthCounterMaximum());
        EXPECT_EQ(1U, cmd->getThreadHeightCounterMaximum());
        EXPECT_EQ(0U, cmd->getThreadDepthCounterMaximum());

        EXPECT_EQ(dispatchFunctionArguments.groupCountX, cmd->getThreadGroupIdXDimension());
        EXPECT_EQ(dispatchFunctionArguments.groupCountY, cmd->getThreadGroupIdYDimension());
        EXPECT_EQ(dispatchFunctionArguments.groupCountZ, cmd->getThreadGroupIdZDimension());
        EXPECT_NE(0u, cmd->getRightExecutionMask());
        EXPECT_EQ(0xffffffffu, cmd->getBottomExecutionMask());
        EXPECT_EQ(GPGPU_WALKER::SIMD_SIZE_SIMD32, cmd->getSimdSize());

        // Index into MIDL table.  Should always be 0
        EXPECT_EQ(0u, cmd->getInterfaceDescriptorOffset());

        // Relative to IndirectObjectBaseAddress
        auto indirectDataLength = function->getPerThreadDataSizeForWholeThreadGroup() +
                                  function->getCrossThreadDataSize();
        EXPECT_EQ(cmd->getIndirectDataLength() % GPGPU_WALKER::INDIRECTDATASTARTADDRESS_ALIGN_SIZE,
                  0u);
        EXPECT_GE(cmd->getIndirectDataLength(), indirectDataLength);

        auto heap = commandList->indirectHeaps[CommandList::INDIRECT_OBJECT];

        auto ptrHeap = ptrOffset(heap->getCpuBase(), cmd->getIndirectDataStartAddress());
        EXPECT_EQ(memcmp(ptrHeap, function->getCrossThreadData().get(),
                         function->getCrossThreadDataSize()),
                  0u);
        ptrHeap = ptrOffset(ptrHeap, function->getCrossThreadDataSize());
        EXPECT_EQ(memcmp(ptrHeap, function->getPerThreadData().get(),
                         function->getPerThreadDataSizeForWholeThreadGroup()),
                  0u);
        ptrHeap = ptrOffset(ptrHeap, function->getPerThreadDataSizeForWholeThreadGroup());

        EXPECT_EQ(INTERFACE_DESCRIPTOR_DATA::SAMPLER_COUNT_NO_SAMPLERS_USED,
                  idd->getSamplerCount());
        EXPECT_EQ(0u, idd->getSamplerStatePointer());
        EXPECT_EQ(0u, idd->getBindingTableEntryCount());
        EXPECT_EQ(function->getThreadsPerThreadGroup(),
                  idd->getNumberOfThreadsInGpgpuThreadGroup());
        EXPECT_EQ(INTERFACE_DESCRIPTOR_DATA::SHARED_LOCAL_MEMORY_SIZE_ENCODES_0K,
                  idd->getSharedLocalMemorySize());
        EXPECT_EQ(0u, idd->getBarrierEnable());

        EXPECT_EQ(function->getCrossThreadDataSize() / sizeof(float[8]),
                  idd->getCrossThreadConstantDataReadLength());
        EXPECT_EQ(function->getPerThreadDataSize() / sizeof(float[8]),
                  idd->getConstantIndirectUrbEntryReadLength());
    }
}

GEN9TEST_F(CommandListAppendLaunchFunction, usesProperInterfaceDescriptorOffsets) {
    createFunction("MemcpyBytes");

    using INTERFACE_DESCRIPTOR_DATA = typename FamilyType::INTERFACE_DESCRIPTOR_DATA;
    using MEDIA_INTERFACE_DESCRIPTOR_LOAD = typename FamilyType::MEDIA_INTERFACE_DESCRIPTOR_LOAD;
    using MEDIA_STATE_FLUSH = typename FamilyType::MEDIA_STATE_FLUSH;
    using GPGPU_WALKER = typename FamilyType::GPGPU_WALKER;

    constexpr uint32_t expectedIDDOffset = 4;
    // -1 to check that driver does the required 64-byte alignment (note : sizeof(IDD) is just
    // 32-bytes)
    commandList->indirectHeaps[CommandList::DYNAMIC_STATE]->getSpace(
        (expectedIDDOffset - 1) * sizeof(INTERFACE_DESCRIPTOR_DATA));

    auto result = commandList->appendLaunchFunction(
        function->toHandle(), &dispatchFunctionArguments, nullptr, 0, nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);
    auto usedSpaceAfter = commandList->commandStream->getUsed();

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(
        cmdList, ptrOffset(commandList->commandStream->getCpuBase(), 0), usedSpaceAfter));

    auto itorMIDL = find<MEDIA_INTERFACE_DESCRIPTOR_LOAD *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itorMIDL);
    {
        auto cmd = genCmdCast<MEDIA_INTERFACE_DESCRIPTOR_LOAD *>(*itorMIDL);
        EXPECT_EQ(expectedIDDOffset * sizeof(INTERFACE_DESCRIPTOR_DATA),
                  cmd->getInterfaceDescriptorDataStartAddress());
    }

    auto itorMSF = find<MEDIA_STATE_FLUSH *>(cmdList.begin(), itorMIDL); // expected before MIDL
    EXPECT_NE(itorMIDL, itorMSF);

    auto itorWalker = find<GPGPU_WALKER *>(itorMIDL, cmdList.end());
    ASSERT_NE(cmdList.end(), itorWalker);
    {
        auto cmd = genCmdCast<GPGPU_WALKER *>(*itorWalker);
        EXPECT_EQ(0U,
                  cmd->getInterfaceDescriptorOffset()); // single IDD per
                                                        // MEDIA_INTERFACE_DESCRIPTOR_LOAD for now
    }

    itorMSF = find<MEDIA_STATE_FLUSH *>(itorWalker, cmdList.end()); // expected after Walker
    EXPECT_NE(cmdList.end(), itorMSF);
}

GEN9TEST_F(CommandListAppendLaunchFunctionGEN9, programsL3InBatchBuffer) {
    createFunction("MemcpyBytes");

    Mock<Device> device;

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList->commandStream);
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    auto result = commandList->appendLaunchFunction(
        function->toHandle(), &dispatchFunctionArguments, nullptr, 0, nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(
        cmdList, ptrOffset(commandList->commandStream->getCpuBase(), 0), usedSpaceAfter));
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

    auto result = commandList->appendLaunchFunction(
        function->toHandle(), &dispatchFunctionArguments, nullptr, 0, nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(
        cmdList, ptrOffset(commandList->commandStream->getCpuBase(), 0), usedSpaceAfter));
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
        EXPECT_LE(cmd->getInterfaceDescriptorDataStartAddress() +
                      cmd->getInterfaceDescriptorTotalLength(),
                  dsh->getUsed());
        idd = static_cast<INTERFACE_DESCRIPTOR_DATA *>(
            ptrOffset(dsh->getCpuBase(), cmd->getInterfaceDescriptorDataStartAddress()));
    }

    EXPECT_EQ(idd->getBarrierEnable(), 1u);
    EXPECT_NE(INTERFACE_DESCRIPTOR_DATA::SHARED_LOCAL_MEMORY_SIZE_ENCODES_0K,
              idd->getSharedLocalMemorySize());
}

GEN9TEST_F(CommandListAppendLaunchFunctionGEN9, storesImageSampler) {
    using GPGPU_WALKER = typename FamilyType::GPGPU_WALKER;
    using MEDIA_INTERFACE_DESCRIPTOR_LOAD = typename FamilyType::MEDIA_INTERFACE_DESCRIPTOR_LOAD;
    using INTERFACE_DESCRIPTOR_DATA = typename FamilyType::INTERFACE_DESCRIPTOR_DATA;
    using SAMPLER_STATE = typename FamilyType::SAMPLER_STATE;

    createFunction("ImageCopy");
    const auto &signature = function->getImmutableData()->getSignature();

    auto fnDynamicStateHeap = function->getDynamicStateHeapData();
    ASSERT_NE(nullptr, fnDynamicStateHeap.get());
    ASSERT_NE(0, function->getDynamicStateHeapDataSize());
    ASSERT_NE(Undefined, signature.samplerTable.tableOffset);

    auto result = commandList->appendLaunchFunction(
        function->toHandle(), &dispatchFunctionArguments, nullptr, 0, nullptr);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(
        cmdList, ptrOffset(commandList->commandStream->getCpuBase(), 0), usedSpaceAfter));

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
        EXPECT_LE(cmd->getInterfaceDescriptorDataStartAddress() +
                      cmd->getInterfaceDescriptorTotalLength(),
                  dsh->getUsed());
        idd = static_cast<INTERFACE_DESCRIPTOR_DATA *>(
            ptrOffset(dsh->getCpuBase(), cmd->getInterfaceDescriptorDataStartAddress()));
    }

    auto dsh = commandList->indirectHeaps[CommandList::DYNAMIC_STATE];
    auto samplerCount = signature.samplerTable.numSamplers;
    ASSERT_LE(samplerCount, static_cast<uint32_t>(idd->getSamplerCount() * 4));

    auto sizeSamplerState = sizeof(SAMPLER_STATE) * samplerCount;
    auto fnSamplerState = reinterpret_cast<const SAMPLER_STATE *>(
        ptrOffset(fnDynamicStateHeap.get(), signature.samplerTable.tableOffset));
    auto samplerState = reinterpret_cast<const SAMPLER_STATE *>(
        ptrOffset(dsh->getCpuBase(), idd->getSamplerStatePointer()));

    ASSERT_EQ(memcmp(fnSamplerState, samplerState, sizeSamplerState), 0u);
}

GEN9TEST_F(CommandListAppendLaunchFunctionGEN9, storesBindingTableAndSurfaceStates) {
    using GPGPU_WALKER = typename FamilyType::GPGPU_WALKER;
    using MEDIA_INTERFACE_DESCRIPTOR_LOAD = typename FamilyType::MEDIA_INTERFACE_DESCRIPTOR_LOAD;
    using INTERFACE_DESCRIPTOR_DATA = typename FamilyType::INTERFACE_DESCRIPTOR_DATA;
    using BINDING_TABLE_STATE = typename FamilyType::BINDING_TABLE_STATE;

    createFunction("ImageCopy");

    auto fnSurfaceStateHeap = function->getSurfaceStateHeapData();
    ASSERT_NE(fnSurfaceStateHeap.get(), nullptr);

    auto result = commandList->appendLaunchFunction(
        function->toHandle(), &dispatchFunctionArguments, nullptr, 0, nullptr);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(
        cmdList, ptrOffset(commandList->commandStream->getCpuBase(), 0), usedSpaceAfter));

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
        EXPECT_LE(cmd->getInterfaceDescriptorDataStartAddress() +
                      cmd->getInterfaceDescriptorTotalLength(),
                  dsh->getUsed());
        idd = static_cast<INTERFACE_DESCRIPTOR_DATA *>(
            ptrOffset(dsh->getCpuBase(), cmd->getInterfaceDescriptorDataStartAddress()));
    }

    auto fnSsh = function->getSurfaceStateHeapData();
    auto ssh = commandList->indirectHeaps[CommandList::SURFACE_STATE];
    ASSERT_NE(fnSsh.get(), nullptr);
    ASSERT_NE(ssh, nullptr);

    ASSERT_EQ(ssh->getUsed(), function->getSurfaceStateHeapDataSize());

    auto fnBindingTableOffset =
        function->getImmutableData()->getSignature().bindingTable.tableOffset;
    auto bindingTableOffset = idd->getBindingTablePointer();
    auto bindingTableOffsetDiff = bindingTableOffset - fnBindingTableOffset;

    auto fnBindingTable =
        reinterpret_cast<const BINDING_TABLE_STATE *>(ptrOffset(fnSsh.get(), fnBindingTableOffset));
    auto bindingTable = reinterpret_cast<const BINDING_TABLE_STATE *>(
        ptrOffset(ssh->getCpuBase(), bindingTableOffset));

    auto bindingTableStateCount =
        function->getImmutableData()->getSignature().bindingTable.numSurfaceStates;
    ASSERT_GT(bindingTableStateCount, 0u);

    // TODO optimization currently disabled
    // ASSERT_EQ(bindingTableStateCount, idd->getBindingTableEntryCount());

    for (uint32_t i = 0; i < bindingTableStateCount; i++) {
        ASSERT_EQ(fnBindingTable[i].getSurfaceStatePointer() + bindingTableOffsetDiff,
                  bindingTable[i].getSurfaceStatePointer());
    }
}

} // namespace ult
} // namespace L0
