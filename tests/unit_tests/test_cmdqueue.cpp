#include "igfxfmid.h"
#include "mock_cmdqueue.h"
#include "mock_device.h"
#include "mock_memory_manager.h"
#include "graphics_allocation.h"
#include "runtime/command_stream/linear_stream.h"
#include "xe_cmdqueue.h"
#include "gtest/gtest.h"

using ::testing::Return;

namespace xe {

TEST(xeDeviceCreateCommandQueue, returnsSuccess) {
    xe_device_handle_t device = {};
    xe_command_queue_handle_t commandQueue = {};
    xe_command_queue_desc_t desc = {};
    auto result = ::xeDeviceCreateCommandQueue(device,
                                               &desc,
                                               &commandQueue);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(xeCommandQueueDestroy, returnsSuccess) {
    xe_command_queue_handle_t commandQueue = {};
    auto result = xeCommandQueueDestroy(commandQueue);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(CommandQueueCreate, returnsCommandQueueOnSuccess) {
    MockDevice device;
    MockMemoryManager manager;
    uint8_t buffer[1024];
    auto allocation = new GraphicsAllocation(buffer, sizeof(buffer));

    EXPECT_CALL(device, getMemoryManager()).WillRepeatedly(Return(&manager));
    EXPECT_CALL(manager, allocateDeviceMemory()).WillRepeatedly(Return(allocation));
    EXPECT_CALL(manager, freeMemory(allocation)).WillRepeatedly(Return());

    auto commandQueue = CommandQueue::create(IGFX_SKYLAKE, &device);
    ASSERT_NE(nullptr, commandQueue);

    auto commandQueueAlias = whitebox_cast<CommandQueue>(commandQueue);
    EXPECT_EQ(&device, commandQueueAlias->device);
    EXPECT_EQ(allocation, commandQueueAlias->allocation);
    ASSERT_NE(nullptr, commandQueueAlias->commandStream);
    EXPECT_LT(0u, commandQueueAlias->commandStream->getAvailableSpace());
    commandQueue->destroy();
}

} // namespace xe
