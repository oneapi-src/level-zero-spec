#include "mock_cmdqueue.h"
#include "mock_cmdlist.h"
#include "xe_all.h"
#include "gtest/gtest.h"

namespace xe {

TEST(xeCommandQueueEnqueueCommandQueue, redirectsToCmdQueueObject) {
    MockCommandList cmdList;
    auto hCommandList = cmdList.toHandle();
    MockCommandQueue cmdQueue;
    xe_fence_handle_t hFence = {};

    EXPECT_CALL(cmdQueue, enqueueCommandLists(1,
                                              &hCommandList,
                                              hFence))
        .Times(1);

    auto result = xe::xeCommandQueueEnqueueCommandLists(cmdQueue.toHandle(),
                                                        1,
                                                        &hCommandList,
                                                        hFence);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

} // namespace xe
