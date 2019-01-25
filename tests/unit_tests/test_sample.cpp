#include <cmath>
#include <cstdint>
#include "xe_all.h"
#include "gtest/gtest.h"

TEST(sample, waitOnEvent) {
    auto result = xeDriverInit(
        XE_INIT_FLAG_NONE ///< [in] initialization flags
    );
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_device_handle_t device = {};
    result = xeDriverGetDevice(
        0,      ///< [in] ordinal of device to retrieve
        &device ///< [out] pointer to handle of device object created
    );
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_command_queue_handle_t commandQueue = {};
    xe_command_queue_desc_t desc = {};
    result = xeDeviceCreateCommandQueue(
        device,       ///< [in] handle of the device
        &desc,        ///< [in] pointer to command queue descriptor
        &commandQueue ///< [out] pointer to handle of command queue object created
    );
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_command_list_desc_t descCommandList = {};
    xe_command_list_handle_t commandList = {};
    result = xeDeviceCreateCommandList(
        device,           ///< [in] handle of the device
        &descCommandList, ///< [in] pointer to command list descriptor
        &commandList      ///< [out] pointer to handle of command list object created
    );
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_event_desc_t descEvent = {};
    xe_event_handle_t event = {};
    result = xeDeviceCreateEvent(
        device,     ///< [in] handle of the device
        &descEvent, ///< [in] pointer to event descriptor
        &event      ///< [out] pointer to handle of event object created
    );
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandListEncodeWaitOnEvent(
        commandList, ///< [in] handle of the command list
        event        ///< [in] handle of the event
    );
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandListClose(
        commandList ///< [in] handle of command list object to close
    );
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandQueueEnqueueCommandList(
        commandQueue, ///< [in] handle of the command queue
        commandList   ///< [in] handle of the command list to execute
    );
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeEventDestroy(
        event ///< [in] handle of event object to destroy
    );
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandListDestroy(
        commandList ///< [in] handle of command list object to destroy
    );
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandQueueDestroy(
        commandQueue ///< [in] handle of command queue object to destroy
    );
    ASSERT_EQ(XE_RESULT_SUCCESS, result);
}
