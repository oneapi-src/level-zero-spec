#include "xe_cmdqueue.h"
#include "gtest/gtest.h"

TEST(deviceCreateCommandQueue, returnsSuccess) {
    xe_device_handle_t device = {};
    xe_command_queue_handle_t commandQueue = {};
    xe_command_queue_desc_t desc = {};
    auto result = xeDeviceCreateCommandQueue(device,
                                             &desc,
                                             &commandQueue);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(commandQueueDestroy, returnsSuccess) {
    xe_command_queue_handle_t commandQueue = {};
    auto result = xeCommandQueueDestroy(commandQueue);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(commandQueueEnqueueCommandList, returnsSuccess) {
    xe_command_queue_handle_t commandQueue = {};
    xe_command_list_handle_t commandList = {};

    auto result = xeCommandQueueEnqueueCommandList(commandQueue,
                                                   commandList);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}
