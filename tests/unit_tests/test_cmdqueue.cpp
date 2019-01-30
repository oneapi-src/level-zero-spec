#include "xe_cmdqueue.h"
#include "gtest/gtest.h"

TEST(xeDeviceCreateCommandQueue, returnsSuccess) {
    xe_device_handle_t device = {};
    xe_command_queue_handle_t commandQueue = {};
    xe_command_queue_desc_t desc = {};
    auto result = xeDeviceCreateCommandQueue(device,
                                             &desc,
                                             &commandQueue);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(xeCommandQueueDestroy, returnsSuccess) {
    xe_command_queue_handle_t commandQueue = {};
    auto result = xeCommandQueueDestroy(commandQueue);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(xeCommandQueueEnqueueCommandList, returnsSuccess) {
    xe_command_queue_handle_t hCommandQueue = {};
    xe_command_list_handle_t hCommandList = {};
    xe_fence_handle_t hFence = {};

    auto result = xeCommandQueueEnqueueCommandLists(hCommandQueue,
                                                    1,
                                                    &hCommandList,
                                                    hFence);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}
