#include "test.h"
#include "xe_all.h"
#include "encode_l3state.h"
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
#include "global_fixture.h"

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

struct CommandListAppendLaunchFunction : public GlobalFixtureTest {

    CommandListAppendLaunchFunction() {
    }

    void SetUp() override {
        GlobalFixtureTest::SetUp();
        auto memoryManager = globalMemoryManager;
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

        auto memoryManager = globalMemoryManager;
        ASSERT_NE(memoryManager, nullptr);
        memoryManager->freeMemory(buffer1);
        memoryManager->freeMemory(buffer2);
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

TEST_F(CommandListAppendLaunchFunction, storesFunctionWhenPrintfUsedByFunction) {
    createFunction("Printf");

    auto result = commandList->appendLaunchFunction(function->toHandle(),
                                                    &dispatchFunctionArguments,
                                                    nullptr);

    EXPECT_EQ(1u, commandList->printfFunctionContainer.size());
    EXPECT_EQ(function, commandList->printfFunctionContainer[0]);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST_F(CommandListAppendLaunchFunction, storesFunctionOnceWhenAppendingFunctionMultipleTimes) {
    createFunction("Printf");

    auto result = commandList->appendLaunchFunction(function->toHandle(),
                                                    &dispatchFunctionArguments,
                                                    nullptr);

    EXPECT_EQ(1u, commandList->printfFunctionContainer.size());
    EXPECT_EQ(function, commandList->printfFunctionContainer[0]);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);

    result = commandList->appendLaunchFunction(function->toHandle(),
                                               &dispatchFunctionArguments,
                                               nullptr);

    EXPECT_EQ(1u, commandList->printfFunctionContainer.size());
}

TEST_F(CommandListAppendLaunchFunction, resetCommandListResetsAfterClose) {
    Mock<Device> device;
    createFunction("SlmBarrier");

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList);
    ASSERT_NE(nullptr, commandList->commandStream);

    auto commandListControl = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandListControl);
    ASSERT_NE(nullptr, commandListControl->commandStream);

    auto result = commandList->appendLaunchFunction(function->toHandle(),
                                                    &dispatchFunctionArguments,
                                                    nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = commandList->close();
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = commandList->reset();
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    ASSERT_EQ(&device, commandList->device);
    ASSERT_NE(nullptr, commandList->commandStream);
    ASSERT_EQ(commandListControl->allocation->getSize(),
            commandList->allocation->getSize());
    ASSERT_EQ(commandListControl->residencyContainer.size(),
            commandList->residencyContainer.size());
    ASSERT_EQ(commandListControl->deallocationContainer.size(),
            commandList->deallocationContainer.size());
    ASSERT_EQ(commandListControl->printfFunctionContainer.size(),
            commandList->printfFunctionContainer.size());
    ASSERT_EQ(commandListControl->commandStream->getUsed(),
            commandList->commandStream->getUsed());
    ASSERT_EQ(commandListControl->dirtyHeaps, commandList->dirtyHeaps);
    ASSERT_EQ(commandListControl->slmSize, commandList->slmSize);

    for (int i = 0; i < CommandContainer::NUM_HEAPS; i++) {
        ASSERT_NE(nullptr, commandListControl->allocationIndirectHeaps[i]);
        ASSERT_NE(nullptr, commandList->allocationIndirectHeaps[i]);
        ASSERT_EQ(commandListControl->allocationIndirectHeaps[i]->getSize(),
                commandList->allocationIndirectHeaps[i]->getSize());

        ASSERT_NE(nullptr, commandListControl->indirectHeaps[i]);
        ASSERT_NE(nullptr, commandList->indirectHeaps[i]);
        ASSERT_EQ(commandListControl->indirectHeaps[i]->getUsed(),
                commandList->indirectHeaps[i]->getUsed());
    }
}

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

HWTEST2_F(CommandListAppendLaunchFunction, withEventAddsPostSyncFlush, IsGen9) {
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
    using GPGPU_WALKER = typename FamilyType::GPGPU_WALKER;
    using PIPE_CONTROL = typename FamilyType::PIPE_CONTROL;
    using POST_SYNC_OPERATION = typename PIPE_CONTROL::POST_SYNC_OPERATION;

    auto itor = find<GPGPU_WALKER *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);
    auto itorPC = find<PIPE_CONTROL *>(itor, cmdList.end());
    ASSERT_NE(cmdList.end(), itorPC);

    {
        auto cmd = genCmdCast<PIPE_CONTROL *>(*itorPC);
        ASSERT_NE(cmd, nullptr);

        EXPECT_EQ(cmd->getPostSyncOperation(), POST_SYNC_OPERATION::POST_SYNC_OPERATION_WRITE_IMMEDIATE_DATA);
        EXPECT_EQ(cmd->getImmediateData(), Event::STATE_SIGNALED);
        EXPECT_TRUE(cmd->getCommandStreamerStallEnable());
        EXPECT_TRUE(cmd->getDcFlushEnable());
        auto gpuAddress = event->getGpuAddress();
        EXPECT_EQ(cmd->getAddressHigh(), gpuAddress >> 32u);
        EXPECT_EQ(cmd->getAddress(), uint32_t(gpuAddress));
    }

    // Make sure event is part of the CL residencyContainer
    {
        auto itorEvent = std::find(std::begin(commandList->residencyContainer),
                                   std::end(commandList->residencyContainer),
                                   event->getAllocation().allocationRT);
        EXPECT_NE(itorEvent, std::end(commandList->residencyContainer));
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

        auto indirectDataLength = function->getPerThreadDataSizeForWholeThreadGroup() +
                                  function->getCrossThreadDataSize();
        EXPECT_GE(cmd->getIndirectDataLength(), 0u);
        EXPECT_LE(cmd->getIndirectDataLength(), indirectDataLength);

        auto ptrHeap = ptrOffset(heap->getCpuBase(), cmd->getIndirectDataStartAddress());
        EXPECT_EQ(memcmp(ptrHeap, function->getCrossThreadDataHostMem(), function->getCrossThreadDataSize()), 0u);
        ptrHeap = ptrOffset(ptrHeap, function->getCrossThreadDataSize());
        EXPECT_EQ(memcmp(ptrHeap, function->getPerThreadDataHostMem(), function->getPerThreadDataSizeForWholeThreadGroup()), 0u);
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

        auto indirectDataLength = function->getPerThreadDataSizeForWholeThreadGroup() +
                                  function->getCrossThreadDataSize();
        EXPECT_GE(cmd->getIndirectDataLength(), 0u);
        EXPECT_LE(cmd->getIndirectDataLength(), indirectDataLength);

        auto ptrHeap = ptrOffset(heap->getCpuBase(), cmd->getIndirectDataStartAddress());
        EXPECT_EQ(memcmp(ptrHeap, function->getCrossThreadDataHostMem(), function->getCrossThreadDataSize()), 0u);
        ptrHeap = ptrOffset(ptrHeap, function->getCrossThreadDataSize());
        EXPECT_EQ(memcmp(ptrHeap, function->getPerThreadDataHostMem(), function->getPerThreadDataSizeForWholeThreadGroup()), 0u);
        ptrHeap = ptrOffset(ptrHeap, function->getPerThreadDataSizeForWholeThreadGroup());
    }
}

ATSTEST_F(CommandListAppendLaunchFunction, storesImageSampler) {
    using COMPUTE_WALKER = typename FamilyType::COMPUTE_WALKER;
    using INTERFACE_DESCRIPTOR_DATA = typename FamilyType::INTERFACE_DESCRIPTOR_DATA;
    using SAMPLER_STATE = typename FamilyType::SAMPLER_STATE;

    createFunction("ImageCopy");

    auto fnDynamicStateHeap = function->getDynamicStateHeap();
    auto fnSamplerStateArray = function->getSamplerStateArray();
    ASSERT_NE(fnDynamicStateHeap, nullptr);
    ASSERT_NE(function->getDynamicStateHeapSize(), 0);
    ASSERT_NE(fnSamplerStateArray, nullptr);

    auto result = commandList->appendLaunchFunction(function->toHandle(),
                                                    &dispatchFunctionArguments,
                                                    nullptr);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandList->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));

    auto itor = find<COMPUTE_WALKER *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    auto cmd = genCmdCast<COMPUTE_WALKER *>(*itor);
    auto &idd = cmd->getInterfaceDescriptor();
    auto dsh = commandList->indirectHeaps[CommandList::DYNAMIC_STATE];

    auto samplerCount = fnSamplerStateArray->Count;
    ASSERT_LE(samplerCount, static_cast<uint32_t>(idd.getSamplerCount() * 4));

    auto sizeSamplerState = sizeof(SAMPLER_STATE) * samplerCount;
    auto fnSamplerState = static_cast<const SAMPLER_STATE *>(ptrOffset(fnDynamicStateHeap, fnSamplerStateArray->Offset));
    auto samplerState = static_cast<const SAMPLER_STATE *>(ptrOffset(dsh->getCpuBase(), idd.getSamplerStatePointer()));

    ASSERT_EQ(memcmp(fnSamplerState, samplerState, sizeSamplerState), 0u);
}

ATSTEST_F(CommandListAppendLaunchFunction, storesBindingTableAndSurfaceStates) {
    using COMPUTE_WALKER = typename FamilyType::COMPUTE_WALKER;
    using INTERFACE_DESCRIPTOR_DATA = typename FamilyType::INTERFACE_DESCRIPTOR_DATA;
    using BINDING_TABLE_STATE = typename FamilyType::BINDING_TABLE_STATE;

    createFunction("ImageCopy");

    auto fnSurfaceStateHeap = function->getSurfaceStateHeap();
    ASSERT_NE(fnSurfaceStateHeap, nullptr);

    auto result = commandList->appendLaunchFunction(function->toHandle(),
                                                    &dispatchFunctionArguments,
                                                    nullptr);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandList->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));

    auto itor = find<COMPUTE_WALKER *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    auto cmd = genCmdCast<COMPUTE_WALKER *>(*itor);
    auto &idd = cmd->getInterfaceDescriptor();
    auto fnSsh = function->getSurfaceStateHeap();
    auto ssh = commandList->indirectHeaps[CommandList::SURFACE_STATE];
    ASSERT_NE(fnSsh, nullptr);
    ASSERT_NE(ssh, nullptr);

    ASSERT_EQ(ssh->getUsed(), function->getSurfaceStateHeapSize());

    auto fnBindingTableOffset = function->getBindingTableOffset();
    auto bindingTableOffset = idd.getBindingTablePointer();
    auto bindingTableOffsetDiff = bindingTableOffset - fnBindingTableOffset;

    auto fnBindingTable = static_cast<const BINDING_TABLE_STATE *>(ptrOffset(fnSsh, fnBindingTableOffset));
    auto bindingTable = static_cast<const BINDING_TABLE_STATE *>(ptrOffset(ssh->getCpuBase(), bindingTableOffset));

    auto bindingTableStateCount = function->getBindingTableStateCount();
    ASSERT_GT(bindingTableStateCount, 0u);

    //TODO optimization currently disabled
    //ASSERT_EQ(bindingTableStateCount, idd.getBindingTableEntryCount());

    for (uint32_t i = 0; i < bindingTableStateCount; i++) {
        ASSERT_EQ(fnBindingTable[i].getSurfaceStatePointer() + bindingTableOffsetDiff,
                  bindingTable[i].getSurfaceStatePointer());
    }
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

        auto indirectDataLength = function->getPerThreadDataSizeForWholeThreadGroup() +
                                  function->getCrossThreadDataSize();
        EXPECT_GE(cmd->getIndirectDataLength(), 0u);
        EXPECT_LE(cmd->getIndirectDataLength(), indirectDataLength);

        auto ptrHeap = ptrOffset(heap->getCpuBase(), cmd->getIndirectDataStartAddress());
        EXPECT_EQ(memcmp(ptrHeap, function->getCrossThreadDataHostMem(), function->getCrossThreadDataSize()), 0u);
        ptrHeap = ptrOffset(ptrHeap, function->getCrossThreadDataSize());
        EXPECT_EQ(memcmp(ptrHeap, function->getPerThreadDataHostMem(), function->getPerThreadDataSizeForWholeThreadGroup()), 0u);
        ptrHeap = ptrOffset(ptrHeap, function->getPerThreadDataSizeForWholeThreadGroup());
    }
}

using IsSKLOrKBL = IsWithinProducts<IGFX_SKYLAKE, IGFX_KABYLAKE>;

HWTEST2_F(CommandListAppendLaunchFunctionGEN9, withSLMProgramsL3WithSLMValue, IsSKLOrKBL) {
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
    using MI_LOAD_REGISTER_IMM = typename FamilyType::MI_LOAD_REGISTER_IMM;

    bool foundL3 = false;
    for (auto it = cmdList.begin(); it != cmdList.end(); it++) {
        auto lri = genCmdCast<MI_LOAD_REGISTER_IMM *>(*it);
        if (lri) {
            if (lri->getRegisterOffset() == EncodeL3State<productFamily>::offset) {
                auto value = lri->getDataDword();
                EXPECT_EQ(EncodeL3State<productFamily>::dataSLM, value);
                foundL3 = true;
                break;
            }
        }
    }

    EXPECT_TRUE(foundL3);
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
        EXPECT_EQ(cmd->getIndirectDataLength() % GPGPU_WALKER::INDIRECTDATASTARTADDRESS_ALIGN_SIZE, 0u);
        EXPECT_GE(cmd->getIndirectDataLength(), indirectDataLength);

        auto heap = commandList->indirectHeaps[CommandList::INDIRECT_OBJECT];

        auto ptrHeap = ptrOffset(heap->getCpuBase(), cmd->getIndirectDataStartAddress());
        EXPECT_EQ(memcmp(ptrHeap, function->getCrossThreadDataHostMem(), function->getCrossThreadDataSize()), 0u);
        ptrHeap = ptrOffset(ptrHeap, function->getCrossThreadDataSize());
        EXPECT_EQ(memcmp(ptrHeap, function->getPerThreadDataHostMem(), function->getPerThreadDataSizeForWholeThreadGroup()), 0u);
        ptrHeap = ptrOffset(ptrHeap, function->getPerThreadDataSizeForWholeThreadGroup());

        EXPECT_EQ(INTERFACE_DESCRIPTOR_DATA::SAMPLER_COUNT_NO_SAMPLERS_USED, idd->getSamplerCount());
        EXPECT_EQ(0u, idd->getSamplerStatePointer());
        EXPECT_EQ(0u, idd->getBindingTableEntryCount());
        EXPECT_EQ(function->getThreadsPerThreadGroup(), idd->getNumberOfThreadsInGpgpuThreadGroup());
        EXPECT_EQ(INTERFACE_DESCRIPTOR_DATA::SHARED_LOCAL_MEMORY_SIZE_ENCODES_0K, idd->getSharedLocalMemorySize());
        EXPECT_EQ(0u, idd->getBarrierEnable());

        EXPECT_EQ(function->getCrossThreadDataSize() / sizeof(float[8]), idd->getCrossThreadConstantDataReadLength());
        EXPECT_EQ(function->getPerThreadDataSize() / sizeof(float[8]), idd->getConstantIndirectUrbEntryReadLength());
    }
}

GEN9TEST_F(CommandListAppendLaunchFunction, usesProperInterfaceDescriptorOffsets) {
    createFunction("MemcpyBytes");

    using INTERFACE_DESCRIPTOR_DATA = typename FamilyType::INTERFACE_DESCRIPTOR_DATA;
    using MEDIA_INTERFACE_DESCRIPTOR_LOAD = typename FamilyType::MEDIA_INTERFACE_DESCRIPTOR_LOAD;
    using MEDIA_STATE_FLUSH = typename FamilyType::MEDIA_STATE_FLUSH;
    using GPGPU_WALKER = typename FamilyType::GPGPU_WALKER;

    constexpr uint32_t expectedIDDOffset = 4;
    // -1 to check that driver does the required 64-byte alignment (note : sizeof(IDD) is just 32-bytes)
    commandList->indirectHeaps[CommandList::DYNAMIC_STATE]->getSpace((expectedIDDOffset - 1) * sizeof(INTERFACE_DESCRIPTOR_DATA));

    auto result = commandList->appendLaunchFunction(function->toHandle(),
                                                    &dispatchFunctionArguments,
                                                    nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);
    auto usedSpaceAfter = commandList->commandStream->getUsed();

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandList->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));

    auto itorMIDL = find<MEDIA_INTERFACE_DESCRIPTOR_LOAD *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itorMIDL);
    {
        auto cmd = genCmdCast<MEDIA_INTERFACE_DESCRIPTOR_LOAD *>(*itorMIDL);
        EXPECT_EQ(expectedIDDOffset * sizeof(INTERFACE_DESCRIPTOR_DATA), cmd->getInterfaceDescriptorDataStartAddress());
    }

    auto itorMSF = find<MEDIA_STATE_FLUSH *>(cmdList.begin(), itorMIDL); // expected before MIDL
    EXPECT_NE(itorMIDL, itorMSF);

    auto itorWalker = find<GPGPU_WALKER *>(itorMIDL, cmdList.end());
    ASSERT_NE(cmdList.end(), itorWalker);
    {
        auto cmd = genCmdCast<GPGPU_WALKER *>(*itorWalker);
        EXPECT_EQ(0U, cmd->getInterfaceDescriptorOffset()); // single IDD per MEDIA_INTERFACE_DESCRIPTOR_LOAD for now
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
    EXPECT_NE(INTERFACE_DESCRIPTOR_DATA::SHARED_LOCAL_MEMORY_SIZE_ENCODES_0K, idd->getSharedLocalMemorySize());
}

HWTEST_F(CommandListAppendLaunchFunction, setsGroupCountBeforeAccessingCrossThreadData) {
    createFunction("MemcpyBytes");

    int res = 0;
    ON_CALL(*this->function, setGroupCount)
        .WillByDefault(::testing::Invoke([&](uint32_t x, uint32_t y, uint32_t z) { res += 1; }));

    ON_CALL(*this->function, getCrossThreadDataHostMem)
        .WillByDefault(::testing::Invoke([&]() { res *= 2; return function->crossThreadData.data(); }));

    auto result = commandList->appendLaunchFunction(function->toHandle(), &dispatchFunctionArguments, nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    EXPECT_EQ(2, res);
}

HWTEST_F(CommandListAppendLaunchFunction, residencyContainerDoesNotContainDuplicates) {
    createFunction("MemcpyBytes");

    Mock<Device> device;

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));

    for (int i = 0; i < 4; ++i) {
        auto result = commandList->appendLaunchFunction(function->toHandle(),
                                                        &dispatchFunctionArguments,
                                                        nullptr);
        ASSERT_EQ(XE_RESULT_SUCCESS, result);
    }

    uint32_t it = 0;
    const auto &residencyCont = commandList->residencyContainer;
    for (auto alloc : residencyCont) {
        auto occurences = std::count(residencyCont.begin(), residencyCont.end(), alloc);
        EXPECT_EQ(1U, static_cast<uint32_t>(occurences)) << it;
        ++it;
    }

    delete commandList;
}

GEN9TEST_F(CommandListAppendLaunchFunctionGEN9, storesImageSampler) {
    using GPGPU_WALKER = typename FamilyType::GPGPU_WALKER;
    using MEDIA_INTERFACE_DESCRIPTOR_LOAD = typename FamilyType::MEDIA_INTERFACE_DESCRIPTOR_LOAD;
    using INTERFACE_DESCRIPTOR_DATA = typename FamilyType::INTERFACE_DESCRIPTOR_DATA;
    using SAMPLER_STATE = typename FamilyType::SAMPLER_STATE;

    createFunction("ImageCopy");

    auto fnDynamicStateHeap = function->getDynamicStateHeap();
    auto fnSamplerStateArray = function->getSamplerStateArray();
    ASSERT_NE(fnDynamicStateHeap, nullptr);
    ASSERT_NE(function->getDynamicStateHeapSize(), 0);
    ASSERT_NE(fnSamplerStateArray, nullptr);

    auto result = commandList->appendLaunchFunction(function->toHandle(),
                                                    &dispatchFunctionArguments,
                                                    nullptr);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandList->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));

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

    auto dsh = commandList->indirectHeaps[CommandList::DYNAMIC_STATE];
    auto samplerCount = fnSamplerStateArray->Count;
    ASSERT_LE(samplerCount, static_cast<uint32_t>(idd->getSamplerCount() * 4));

    auto sizeSamplerState = sizeof(SAMPLER_STATE) * samplerCount;
    auto fnSamplerState = static_cast<const SAMPLER_STATE *>(ptrOffset(fnDynamicStateHeap, fnSamplerStateArray->Offset));
    auto samplerState = static_cast<const SAMPLER_STATE *>(ptrOffset(dsh->getCpuBase(), idd->getSamplerStatePointer()));

    ASSERT_EQ(memcmp(fnSamplerState, samplerState, sizeSamplerState), 0u);
}

GEN9TEST_F(CommandListAppendLaunchFunctionGEN9, storesBindingTableAndSurfaceStates) {
    using GPGPU_WALKER = typename FamilyType::GPGPU_WALKER;
    using MEDIA_INTERFACE_DESCRIPTOR_LOAD = typename FamilyType::MEDIA_INTERFACE_DESCRIPTOR_LOAD;
    using INTERFACE_DESCRIPTOR_DATA = typename FamilyType::INTERFACE_DESCRIPTOR_DATA;
    using BINDING_TABLE_STATE = typename FamilyType::BINDING_TABLE_STATE;

    createFunction("ImageCopy");

    auto fnSurfaceStateHeap = function->getSurfaceStateHeap();
    ASSERT_NE(fnSurfaceStateHeap, nullptr);

    auto result = commandList->appendLaunchFunction(function->toHandle(),
                                                    &dispatchFunctionArguments,
                                                    nullptr);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(cmdList,
                                                      ptrOffset(commandList->commandStream->getCpuBase(), 0),
                                                      usedSpaceAfter));

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

    auto fnSsh = function->getSurfaceStateHeap();
    auto ssh = commandList->indirectHeaps[CommandList::SURFACE_STATE];
    ASSERT_NE(fnSsh, nullptr);
    ASSERT_NE(ssh, nullptr);

    ASSERT_EQ(ssh->getUsed(), function->getSurfaceStateHeapSize());

    auto fnBindingTableOffset = function->getBindingTableOffset();
    auto bindingTableOffset = idd->getBindingTablePointer();
    auto bindingTableOffsetDiff = bindingTableOffset - fnBindingTableOffset;

    auto fnBindingTable = static_cast<const BINDING_TABLE_STATE *>(ptrOffset(fnSsh, fnBindingTableOffset));
    auto bindingTable = static_cast<const BINDING_TABLE_STATE *>(ptrOffset(ssh->getCpuBase(), bindingTableOffset));

    auto bindingTableStateCount = function->getBindingTableStateCount();
    ASSERT_GT(bindingTableStateCount, 0u);

    //TODO optimization currently disabled
    //ASSERT_EQ(bindingTableStateCount, idd->getBindingTableEntryCount());

    for (uint32_t i = 0; i < bindingTableStateCount; i++) {
        ASSERT_EQ(fnBindingTable[i].getSurfaceStatePointer() + bindingTableOffsetDiff,
                  bindingTable[i].getSurfaceStatePointer());
    }
}

} // namespace ult
} // namespace L0
