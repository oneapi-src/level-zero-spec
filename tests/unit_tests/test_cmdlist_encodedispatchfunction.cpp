#include "test.h"
#include "xe_api.h"
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

    EXPECT_CALL(commandList, appendLaunchFunction(function.toHandle(), &dispatchFunctionArguments,
                                                  event.toHandle(), 0, nullptr))
        .Times(1);

    auto result =
        xeCommandListAppendLaunchFunction(commandList.toHandle(), function.toHandle(),
                                          &dispatchFunctionArguments, event.toHandle(), 0, nullptr);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

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

    auto result = commandList->appendLaunchFunction(
        function->toHandle(), &dispatchFunctionArguments, nullptr, 0, nullptr);

    EXPECT_EQ(1u, commandList->printfFunctionContainer.size());
    EXPECT_EQ(function, commandList->printfFunctionContainer[0]);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST_F(CommandListAppendLaunchFunction, storesFunctionOnceWhenAppendingFunctionMultipleTimes) {
    createFunction("Printf");

    auto result = commandList->appendLaunchFunction(
        function->toHandle(), &dispatchFunctionArguments, nullptr, 0, nullptr);

    EXPECT_EQ(1u, commandList->printfFunctionContainer.size());
    EXPECT_EQ(function, commandList->printfFunctionContainer[0]);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);

    result = commandList->appendLaunchFunction(function->toHandle(), &dispatchFunctionArguments,
                                               nullptr, 0, nullptr);

    EXPECT_EQ(1u, commandList->printfFunctionContainer.size());
}

HWTEST2_F(CommandListAppendLaunchFunction, withEventAddsPostSyncFlush, IsGen9) {
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

        EXPECT_EQ(cmd->getPostSyncOperation(),
                  POST_SYNC_OPERATION::POST_SYNC_OPERATION_WRITE_IMMEDIATE_DATA);
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

using CommandListAppendLaunchFunctionGEN9 = CommandListAppendLaunchFunction;

using IsSKLOrKBL = IsWithinProducts<IGFX_SKYLAKE, IGFX_KABYLAKE>;

HWTEST2_F(CommandListAppendLaunchFunctionGEN9, withSLMProgramsL3WithSLMValue, IsSKLOrKBL) {
    createFunction("SlmBarrier");
    auto result = commandList->appendLaunchFunction(
        function->toHandle(), &dispatchFunctionArguments, nullptr, 0, nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(
        cmdList, ptrOffset(commandList->commandStream->getCpuBase(), 0), usedSpaceAfter));
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

HWTEST_F(CommandListAppendLaunchFunction, setsGroupCountBeforeAccessingCrossThreadData) {
    createFunction("MemcpyBytes");

    int res = 0;
    ON_CALL(*this->function, setGroupCount)
        .WillByDefault(::testing::Invoke([&](uint32_t x, uint32_t y, uint32_t z) { res += 1; }));

    ON_CALL(*this->function, getCrossThreadData).WillByDefault(::testing::Invoke([&]() {
        res *= 2;
        return bindPtrRef<const uint8_t[]>(function->crossThreadData.data());
    }));

    auto result = commandList->appendLaunchFunction(
        function->toHandle(), &dispatchFunctionArguments, nullptr, 0, nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    EXPECT_EQ(2, res);
}

HWTEST_F(CommandListAppendLaunchFunction, residencyContainerDoesNotContainDuplicates) {
    createFunction("MemcpyBytes");

    Mock<Device> device;

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));

    for (int i = 0; i < 4; ++i) {
        auto result = commandList->appendLaunchFunction(
            function->toHandle(), &dispatchFunctionArguments, nullptr, 0, nullptr);
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

class CommandListReset : public CommandListAppendLaunchFunction {};

INSTANTIATE_TEST_CASE_P(, CommandListReset,
                        ::testing::Values("MemcpyBytes", "SlmBarrier", "Printf", "ImageCopy"));

TEST_P(CommandListReset, resetCommandListResetsAfterClose) {
    Mock<Device> device;
    createFunction(GetParam());

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList);
    ASSERT_NE(nullptr, commandList->commandStream);

    auto commandListControl = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandListControl);
    ASSERT_NE(nullptr, commandListControl->commandStream);

    auto result = commandList->appendLaunchFunction(
        function->toHandle(), &dispatchFunctionArguments, nullptr, 0, nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = commandList->close();
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = commandList->reset();
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    ASSERT_EQ(&device, commandList->device);
    ASSERT_NE(nullptr, commandList->commandStream);
    ASSERT_EQ(commandListControl->allocation->getSize(), commandList->allocation->getSize());
    ASSERT_EQ(commandListControl->residencyContainer.size(),
              commandList->residencyContainer.size());
    ASSERT_EQ(commandListControl->deallocationContainer.size(),
              commandList->deallocationContainer.size());
    ASSERT_EQ(commandListControl->printfFunctionContainer.size(),
              commandList->printfFunctionContainer.size());
    ASSERT_EQ(commandListControl->commandStream->getUsed(), commandList->commandStream->getUsed());
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

} // namespace ult
} // namespace L0
