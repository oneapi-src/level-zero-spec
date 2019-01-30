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

    xe_command_queue_handle_t hCommandQueue = {};
    xe_command_queue_desc_t desc = {};
    result = xeDeviceCreateCommandQueue(device,
                                        &desc,
                                        &hCommandQueue);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_command_list_desc_t descCommandList = {};
    xe_command_list_handle_t hCommandList = {};
    result = xeDeviceCreateCommandList(device,
                                       &descCommandList,
                                       &hCommandList);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_event_desc_t descEvent = {};
    xe_event_handle_t hEvent = {};
    result = xeDeviceCreateEvent(device,
                                 &descEvent,
                                 &hEvent);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandListEncodeWaitOnEvent(hCommandList,
                                            hEvent);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandListClose(hCommandList);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_fence_handle_t hFence = {};
    result = xeCommandQueueEnqueueCommandLists(hCommandQueue,
                                               1,
                                               &hCommandList,
                                               (xe_fence_handle_t)0);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeEventDestroy(hEvent);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandListDestroy(hCommandList);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandQueueDestroy(hCommandQueue);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);
}
