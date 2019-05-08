#include "igfxfmid.h"
#include "mock_cmdqueue.h"
#include "mock_device.h"
#include "mock_function.h"
#include "mock_memory_manager.h"
#include "graphics_allocation.h"
#include "runtime/command_stream/linear_stream.h"
#include "unit_tests/mocks/mock_csr.h"
#include "xe_cmdqueue.h"
#include "gtest/gtest.h"
#include "global_fixture.h"

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

class CommandQueueCreate : public GlobalFixtureTest {};

TEST_F(CommandQueueCreate, returnsCommandQueueOnSuccess) {
    Mock<Device> device;

    auto commandQueue = whitebox_cast(CommandQueue::create(productFamily, &device, device.csrRT));
    ASSERT_NE(commandQueue, nullptr);
    EXPECT_EQ(&device, commandQueue->device);
    EXPECT_EQ(commandQueue->csrRT, device.csrRT);
    EXPECT_NE(commandQueue->allocation, nullptr);
    ASSERT_NE(commandQueue->commandStream, nullptr);
    EXPECT_LT(0u, commandQueue->commandStream->getAvailableSpace());
    commandQueue->destroy();
}

TEST(CommandQueue,
     synchronizeByPollingCallsPrintOutputOnPrintfFunctionsStoredAndClearsFunctionContainer) {
    Mock<CommandQueue> commandQueue;

    uint32_t tag = 0;
    static_cast<MockCommandStreamReceiver *>(commandQueue.csrRT)->tagAddress = &tag;

    Mock<Function> function1, function2;

    EXPECT_CALL(function1, printPrintfOutput).Times(1);
    EXPECT_CALL(function2, printPrintfOutput).Times(1);

    commandQueue.printfFunctionContainer.push_back(&function1);
    commandQueue.printfFunctionContainer.push_back(&function2);

    commandQueue.synchronizeByPollingForTaskCount(0);

    EXPECT_EQ(0u, commandQueue.printfFunctionContainer.size());
}

} // namespace ult
} // namespace L0
