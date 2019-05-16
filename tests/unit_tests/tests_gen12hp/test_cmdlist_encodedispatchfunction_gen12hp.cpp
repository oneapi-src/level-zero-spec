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

ATSTEST_F(CommandListAppendLaunchFunction, addsWalkerToCommandStream) {
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
        EXPECT_NE(idd.getNumberOfThreadsInGpgpuThreadGroup(), 0u);
        EXPECT_EQ(idd.getSharedLocalMemorySize(),
                  INTERFACE_DESCRIPTOR_DATA::SHARED_LOCAL_MEMORY_SIZE_ENCODES_0K);
        EXPECT_EQ(idd.getBarrierEnable(), 0u);
        EXPECT_EQ(idd.getThreadGroupDispatchSize(), 0u);
    }
}

ATSTEST_F(CommandListAppendLaunchFunction, withBarrierAndSLMSetsIDDBarrierEnableAndSLMSize) {
    createFunction("SlmBarrier");
    auto result = commandList->appendLaunchFunction(
        function->toHandle(), &dispatchFunctionArguments, nullptr, 0, nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(
        cmdList, ptrOffset(commandList->commandStream->getCpuBase(), 0), usedSpaceAfter));
    using COMPUTE_WALKER = typename FamilyType::COMPUTE_WALKER;
    using INTERFACE_DESCRIPTOR_DATA = typename FamilyType::INTERFACE_DESCRIPTOR_DATA;

    auto itor = find<COMPUTE_WALKER *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    {
        auto cmd = genCmdCast<COMPUTE_WALKER *>(*itor);
        auto &idd = cmd->getInterfaceDescriptor();
        EXPECT_EQ(idd.getBarrierEnable(), 1u);
        EXPECT_EQ(INTERFACE_DESCRIPTOR_DATA::SHARED_LOCAL_MEMORY_SIZE_ENCODES_64K,
                  idd.getSharedLocalMemorySize());
    }
}

ATSTEST_F(CommandListAppendLaunchFunction, withEventSetsPostSyncOp) {
    createFunction("MemcpyBytes");

    auto usedSpaceBefore = commandList->commandStream->getUsed();
    auto event = whitebox_cast(Event::create(&device));

    auto result = commandList->appendLaunchFunction(
        function->toHandle(), &dispatchFunctionArguments, event->toHandle(), 0, nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(
        cmdList, ptrOffset(commandList->commandStream->getCpuBase(), 0), usedSpaceAfter));
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

    // Make sure event is part of the CL residencyContainer
    {
        auto itorEvent = std::find(std::begin(commandList->residencyContainer),
                                   std::end(commandList->residencyContainer),
                                   event->getAllocation().allocationRT);
        EXPECT_NE(itorEvent, std::end(commandList->residencyContainer));
    }
}

ATSTEST_F(CommandListAppendLaunchFunction, copiesThreadDataToGeneralStateHeap) {
    createFunction("MemcpyBytes");

    using COMPUTE_WALKER = typename FamilyType::COMPUTE_WALKER;
    using INTERFACE_DESCRIPTOR_DATA = typename FamilyType::INTERFACE_DESCRIPTOR_DATA;

    auto heap = commandList->indirectHeaps[CommandList::GENERAL_STATE];
    heap->getSpace(COMPUTE_WALKER::INDIRECTDATASTARTADDRESS_ALIGN_SIZE -
                   1); // this will check if cmdlist takes care of heap allignment

    auto result = commandList->appendLaunchFunction(
        function->toHandle(), &dispatchFunctionArguments, nullptr, 0, nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(
        cmdList, ptrOffset(commandList->commandStream->getCpuBase(), 0), usedSpaceAfter));

    auto itor = find<COMPUTE_WALKER *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    {
        auto cmd = genCmdCast<COMPUTE_WALKER *>(*itor);

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

ATSTEST_F(CommandListAppendLaunchFunction, growsGeneralStateHeapIfNeeded) {
    createFunction("MemcpyBytes");

    using COMPUTE_WALKER = typename FamilyType::COMPUTE_WALKER;
    using INTERFACE_DESCRIPTOR_DATA = typename FamilyType::INTERFACE_DESCRIPTOR_DATA;

    auto heap = commandList->indirectHeaps[CommandList::GENERAL_STATE];
    ASSERT_EQ(0U, heap->getUsed());
    heap->overrideMaxSize(COMPUTE_WALKER::INDIRECTDATASTARTADDRESS_ALIGN_SIZE);

    auto result = commandList->appendLaunchFunction(
        function->toHandle(), &dispatchFunctionArguments, nullptr, 0, nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(
        cmdList, ptrOffset(commandList->commandStream->getCpuBase(), 0), usedSpaceAfter));

    auto itor = find<COMPUTE_WALKER *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    {
        auto cmd = genCmdCast<COMPUTE_WALKER *>(*itor);

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

ATSTEST_F(CommandListAppendLaunchFunction, storesImageSampler) {
    using COMPUTE_WALKER = typename FamilyType::COMPUTE_WALKER;
    using INTERFACE_DESCRIPTOR_DATA = typename FamilyType::INTERFACE_DESCRIPTOR_DATA;
    using SAMPLER_STATE = typename FamilyType::SAMPLER_STATE;

    createFunction("ImageCopy");

    auto fnDynamicStateHeap = function->getDynamicStateHeapData();
    const auto &signature = function->getImmutableData()->getSignature();
    ASSERT_NE(0U, function->getDynamicStateHeapDataSize());
    ASSERT_NE(nullptr, fnDynamicStateHeap.get());
    ASSERT_NE(Undefined, signature.samplerTable.tableOffset);

    auto result = commandList->appendLaunchFunction(
        function->toHandle(), &dispatchFunctionArguments, nullptr, 0, nullptr);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(
        cmdList, ptrOffset(commandList->commandStream->getCpuBase(), 0), usedSpaceAfter));

    auto itor = find<COMPUTE_WALKER *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    auto cmd = genCmdCast<COMPUTE_WALKER *>(*itor);
    auto &idd = cmd->getInterfaceDescriptor();
    auto dsh = commandList->indirectHeaps[CommandList::DYNAMIC_STATE];

    auto samplerCount = signature.samplerTable.numSamplers;
    ASSERT_LE(samplerCount, static_cast<uint32_t>(idd.getSamplerCount() * 4));

    auto sizeSamplerState = sizeof(SAMPLER_STATE) * samplerCount;
    auto fnSamplerState = reinterpret_cast<const SAMPLER_STATE *>(
        ptrOffset(fnDynamicStateHeap.get(), signature.samplerTable.tableOffset));
    auto samplerState = reinterpret_cast<const SAMPLER_STATE *>(
        ptrOffset(dsh->getCpuBase(), idd.getSamplerStatePointer()));

    EXPECT_EQ(memcmp(fnSamplerState, samplerState, sizeSamplerState), 0u);
}

ATSTEST_F(CommandListAppendLaunchFunction, storesBindingTableAndSurfaceStates) {
    using COMPUTE_WALKER = typename FamilyType::COMPUTE_WALKER;
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

    auto itor = find<COMPUTE_WALKER *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    auto cmd = genCmdCast<COMPUTE_WALKER *>(*itor);
    auto &idd = cmd->getInterfaceDescriptor();
    auto fnSsh = function->getSurfaceStateHeapData();
    auto ssh = commandList->indirectHeaps[CommandList::SURFACE_STATE];
    ASSERT_NE(fnSsh.get(), nullptr);
    ASSERT_NE(ssh, nullptr);

    ASSERT_EQ(ssh->getUsed(), function->getSurfaceStateHeapDataSize());

    auto fnBindingTableOffset =
        function->getImmutableData()->getSignature().bindingTable.tableOffset;
    auto bindingTableOffset = idd.getBindingTablePointer();
    auto bindingTableOffsetDiff = bindingTableOffset - fnBindingTableOffset;

    auto fnBindingTable =
        reinterpret_cast<const BINDING_TABLE_STATE *>(ptrOffset(fnSsh.get(), fnBindingTableOffset));
    auto bindingTable = reinterpret_cast<const BINDING_TABLE_STATE *>(
        ptrOffset(ssh->getCpuBase(), bindingTableOffset));

    auto bindingTableStateCount =
        function->getImmutableData()->getSignature().bindingTable.numSurfaceStates;
    ASSERT_GT(bindingTableStateCount, 0u);

    // TODO optimization currently disabled
    // ASSERT_EQ(bindingTableStateCount, idd.getBindingTableEntryCount());

    for (uint32_t i = 0; i < bindingTableStateCount; i++) {
        ASSERT_EQ(fnBindingTable[i].getSurfaceStatePointer() + bindingTableOffsetDiff,
                  bindingTable[i].getSurfaceStatePointer());
    }
}

ATSTEST_F(CommandListAppendLaunchFunction, usesIsaFromInstructionHeap) {
    createFunction("MemcpyBytes");
    auto result = commandList->appendLaunchFunction(
        function->toHandle(), &dispatchFunctionArguments, nullptr, 0, nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(
        cmdList, ptrOffset(commandList->commandStream->getCpuBase(), 0), usedSpaceAfter));
    using COMPUTE_WALKER = typename FamilyType::COMPUTE_WALKER;
    using INTERFACE_DESCRIPTOR_DATA = typename FamilyType::INTERFACE_DESCRIPTOR_DATA;

    COMPUTE_WALKER addressValidator{};
    addressValidator.getInterfaceDescriptor().setKernelStartPointer(
        function->getImmutableData()
            ->getIsaGraphicsAllocation()
            ->getGpuAddressOffsetFromHeapBase());

    auto itor = find<COMPUTE_WALKER *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    {
        auto cmd = genCmdCast<COMPUTE_WALKER *>(*itor);
        auto &idd = cmd->getInterfaceDescriptor();

        EXPECT_EQ(addressValidator.getInterfaceDescriptor().getKernelStartPointer(),
                  idd.getKernelStartPointer());
    }
}

} // namespace ult
} // namespace L0
