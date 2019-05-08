#pragma once
#include "mock_cmdlist.h"
#include "mock_device.h"
#include "runtime/command_stream/linear_stream.h"
#include "unit_tests/gen_common/gen_cmd_parse.h"
#include "test.h"
#include "global_fixture.h"

extern PRODUCT_FAMILY productFamily;

namespace L0 {
namespace ult {

struct CmdParseFixture : public GlobalFixtureTest {
    void SetUp() override {
        GlobalFixtureTest::SetUp();
        commandList = whitebox_cast(CommandList::create(::productFamily, &device));
        ASSERT_NE(commandList, nullptr);

        commandStream = &commandList->getCommandStream();
        usedSpaceBefore = commandStream->getUsed();
    }

    void TearDown() override {
        delete commandList;
        GlobalFixtureTest::TearDown();
    }

    template <typename FamilyType> void parseCommandBuffer() {
        usedSpaceAfter = commandStream->getUsed();
        ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

        ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(
            commands, ptrOffset(commandStream->getCpuBase(), usedSpaceBefore),
            usedSpaceAfter - usedSpaceBefore));
    }

    Mock<Device> device;
    CommandList *commandList = nullptr;
    NEO::LinearStream *commandStream = nullptr;

    size_t usedSpaceBefore = 0;
    size_t usedSpaceAfter = 0;
    GenCmdList commands;
};

} // namespace ult
} // namespace L0
