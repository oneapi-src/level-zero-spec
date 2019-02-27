#include "igfxfmid.h"
#include "mock_cmdqueue.h"
#include "mock_device.h"
#include "mock_memory_manager.h"
#include "graphics_allocation.h"
#include "runtime/command_stream/linear_stream.h"
#include "xe_cmdqueue.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Return;

extern PRODUCT_FAMILY productFamily;

namespace L0 {
namespace ult {

TEST(xeCommandQueueDestroy, redirectsToObject) {
    Mock<CommandQueue> commandQueue;
    EXPECT_CALL(commandQueue, destroy);

    auto result = xeCommandQueueDestroy(commandQueue.toHandle());
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(CommandQueueCreate, returnsCommandQueueOnSuccess) {
    Mock<Device> device;
    EXPECT_CALL(device, getMemoryManager).Times(AnyNumber());

    auto commandQueue = whitebox_cast(CommandQueue::create(productFamily, &device, device.csrRT));
    ASSERT_NE(commandQueue, nullptr);
    EXPECT_EQ(&device, commandQueue->device);
    EXPECT_EQ(commandQueue->csrRT, device.csrRT);
    EXPECT_NE(commandQueue->allocation, nullptr);
    ASSERT_NE(commandQueue->commandStream, nullptr);
    EXPECT_LT(0u, commandQueue->commandStream->getAvailableSpace());
    commandQueue->destroy();
}

} // namespace ult
} // namespace L0
