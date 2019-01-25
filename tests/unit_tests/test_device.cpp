#include "xe_device.h"
#include "gmock/gmock.h"

TEST(driverGetDevice, returnsSuccess) {
    xe_device_handle_t device = {};
    auto result = xeDriverGetDevice(
        0,      ///< [in] ordinal of device to retrieve
        &device ///< [out] pointer to handle of device object created
    );
    ASSERT_EQ(XE_RESULT_SUCCESS, result);
}
