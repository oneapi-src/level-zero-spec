#include "xe_event.h"
#include "gtest/gtest.h"

TEST(deviceCreateEvent, returnsSuccess) {
    xe_device_handle_t device = {};
    xe_event_desc_t descEvent = {};
    xe_event_handle_t event = {};
    auto result = xeDeviceCreateEvent(
        device,     ///< [in] handle of the device
        &descEvent, ///< [in] pointer to event descriptor
        &event      ///< [out] pointer to handle of event object created
    );
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(eventDestroy, returnsSuccess) {
    xe_event_handle_t event = {};
    auto result = xeEventDestroy(
        event ///< [in] handle of event object to destroy
    );
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}
