#include "xe_event.h"
#include "gtest/gtest.h"

namespace xe {

TEST(xeDeviceCreateEvent, returnsSuccess) {
    xe_device_handle_t device = {};
    xe_event_desc_t descEvent = {};
    xe_event_handle_t event = {};
    auto result = xeDeviceCreateEvent(device,
                                      &descEvent,
                                      &event);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(xeEventDestroy, returnsSuccess) {
    xe_event_handle_t event = {};
    auto result = xeEventDestroy(event);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

} // namespace xe
