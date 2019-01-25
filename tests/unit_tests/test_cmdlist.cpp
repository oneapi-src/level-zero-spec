#include "xe_cmdlist.h"
#include "xe_event.h"
#include "gtest/gtest.h"

TEST(deviceCreateCommandList, returnsSuccess) {
    xe_device_handle_t device = {};
    xe_command_list_desc_t descCommandList = {};
    xe_command_list_handle_t commandList = {};
    auto result = xeDeviceCreateCommandList(
        device,           ///< [in] handle of the device
        &descCommandList, ///< [in] pointer to command list descriptor
        &commandList      ///< [out] pointer to handle of command list object created
    );
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(commandListDestroy, returnsSuccess) {
    xe_command_list_handle_t commandList = {};
    auto result = xeCommandListDestroy(
        commandList ///< [in] handle of command list object to destroy
    );
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(commandListClose, returnsSuccess) {
    xe_command_list_handle_t commandList = {};
    auto result = xeCommandListClose(
        commandList ///< [in] handle of command list object to close
    );
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(commandListEncodeWaitOnEvent, returnsSuccess) {
    xe_command_list_handle_t commandList = {};
    xe_event_handle_t event = {};
    auto result = xeCommandListEncodeWaitOnEvent(
        commandList, ///< [in] handle of the command list
        event        ///< [in] handle of the event
    );
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}
