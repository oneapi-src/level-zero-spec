#include "mock_driver.h"
#include "gmock/gmock.h"
#include "runtime/os_interface/debug_settings_manager.h"

using ::testing::Return;

namespace L0 {
namespace ult {

TEST(MultipleDevicesCount, SetMultipleDevicesAndVerifyDeviceCount) {
    uint32_t count = 0;
    auto requiredDeviceCount = 2u;

    OCLRT::DebugManager.flags.CreateMultipleDevices.set(requiredDeviceCount);

    auto result = xeDriverInit(XE_INIT_FLAG_NONE);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);

    auto ret = xeDriverGetDeviceCount(&count);

    EXPECT_EQ(XE_RESULT_SUCCESS, ret);
    EXPECT_EQ(requiredDeviceCount, count);
}

TEST(MultipleDevicesUniqueIds, SetMultipleDevicesAndVerifyDeviceUniqueIds) {
    uint32_t count = 0;
    auto requiredDeviceCount = 2u;

    OCLRT::DebugManager.flags.CreateMultipleDevices.set(requiredDeviceCount);
    auto result = xeDriverInit(XE_INIT_FLAG_NONE);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);

    auto ret = xeDriverGetDeviceCount(&count);

    EXPECT_EQ(XE_RESULT_SUCCESS, ret);
    EXPECT_EQ(requiredDeviceCount, count);

    xe_device_uuid_t *uniqueIds = new xe_device_uuid_t[count];
    xeDriverGetDeviceUniqueIds(count, uniqueIds);
    for (uint32_t i = 0; i < count; i++) {
        EXPECT_EQ(i, uniqueIds[i].id[0]);
    }
}

} // namespace ult
} // namespace L0
