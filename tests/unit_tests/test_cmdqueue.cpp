#include "xe_cmdqueue.h"
#include "gtest/gtest.h"

TEST(deviceCreateCommandQueue, returnsSuccess) {
    xe_device_handle_t device = {};
    xe_command_queue_handle_t commandQueue = {};
    xe_command_queue_desc_t desc = {};
    auto result = xeDeviceCreateCommandQueue(
        device,       ///< [in] handle of the device
        &desc,        ///< [in] pointer to command queue descriptor
        &commandQueue ///< [out] pointer to handle of command queue object created
    );
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(commandQueueDestroy, returnsSuccess) {
    xe_command_queue_handle_t commandQueue = {};
    auto result = xeCommandQueueDestroy(
        commandQueue ///< [in] handle of command queue object to destroy
    );
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(commandQueueEnqueueCommandList, returnsSuccess) {
    xe_command_queue_handle_t commandQueue = {};
    xe_command_list_handle_t commandList = {};

    auto result = xeCommandQueueEnqueueCommandList(
        commandQueue, ///< [in] handle of the command queue
        commandList   ///< [in] handle of the command list to execute
    );
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}
