#include "mock_cmdlist.h"
#include "mock_device.h"
#include "mock_memory_manager.h"
#include "event.h"
#include "graphics_allocation.h"
#include "igfxfmid.h"
#include "runtime/command_stream/linear_stream.h"
#include "gtest/gtest.h"

namespace xe {
namespace ult {

TEST(xeCommandListDestroy, redirectsToCmdListObject) {
    MockCommandList cmdList;
    xe_command_list_handle_t commandList = cmdList.toHandle();

    EXPECT_CALL(cmdList, destroy()).Times(1);

    auto result = xe::xeCommandListDestroy(commandList);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

using ::testing::Return;
using CommandListCreate = ::testing::TestWithParam<uint32_t>;

TEST_P(CommandListCreate, returnsCommandListOnSuccess) {
    MockDevice device;
    MockMemoryManager manager;
    uint8_t buffer[1024];
    auto allocation = new GraphicsAllocation(buffer, sizeof(buffer));

    EXPECT_CALL(device, getMemoryManager()).WillRepeatedly(Return(&manager));
    EXPECT_CALL(manager, allocateDeviceMemory()).WillRepeatedly(Return(allocation));
    EXPECT_CALL(manager, freeMemory(allocation)).WillRepeatedly(Return());

    auto commandList = CommandList::create(GetParam(), &device);
    ASSERT_NE(nullptr, commandList);

    auto commandListAlias = whitebox_cast(commandList);
    EXPECT_EQ(&device, commandListAlias->device);
    EXPECT_EQ(allocation, commandListAlias->allocation);
    ASSERT_NE(nullptr, commandListAlias->commandStream);
    EXPECT_LT(0u, commandListAlias->commandStream->getAvailableSpace());
    commandList->destroy();
}

static uint32_t supportedProductFamilyTable[] = {
    IGFX_BROADWELL,
    IGFX_KABYLAKE,
    IGFX_SKYLAKE,
};

INSTANTIATE_TEST_CASE_P(,
                        CommandListCreate,
                        ::testing::ValuesIn(supportedProductFamilyTable));

using CommandListCreateFail = ::testing::TestWithParam<uint32_t>;

TEST_P(CommandListCreateFail, returnsNullPointerOnFailure) {
    MockDevice device;
    auto commandList = CommandList::create(GetParam(), &device);
    EXPECT_EQ(nullptr, commandList);
}

static uint32_t unsupportedProductFamilyTable[] = {
    IGFX_HASWELL,
    IGFX_CANNONLAKE,
    IGFX_MAX_PRODUCT,
};

INSTANTIATE_TEST_CASE_P(,
                        CommandListCreateFail,
                        ::testing::ValuesIn(unsupportedProductFamilyTable));

} // namespace ult
} // namespace xe
