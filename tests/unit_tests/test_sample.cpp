#include <cmath>
#include <cstdint>
#include "xe_all.h"
#include "gtest/gtest.h"

TEST(sample, waitOnEvent) {
    auto result = xeDriverInit(XE_INIT_FLAG_NONE);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_device_handle_t device = {};
    result = xeDriverGetDevice(0,
                               &device);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_command_queue_handle_t commandQueue = {};
    xe_command_queue_desc_t desc = {};
    result = xeDeviceCreateCommandQueue(device,
                                        &desc,
                                        &commandQueue);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_command_list_desc_t descCommandList = {};
    xe_command_list_handle_t commandList = {};
    result = xeDeviceCreateCommandList(device,
                                       &descCommandList,
                                       &commandList);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_event_desc_t descEvent = {};
    xe_event_handle_t event = {};
    result = xeDeviceCreateEvent(device,
                                 &descEvent,
                                 &event);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandListEncodeWaitOnEvent(commandList,
                                            event);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandListClose(commandList);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandQueueEnqueueCommandList(commandQueue,
                                              commandList);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeEventDestroy(event);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandListDestroy(commandList);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandQueueDestroy(commandQueue);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);
}
