#include "mock_driver.h"
#include "gmock/gmock.h"
#include "runtime/os_interface/debug_settings_manager.h"

using ::testing::Return;

namespace L0 {
namespace ult {

TEST(xeDriverInit, redirectsToObject) {
    Mock<Driver> driver;
    EXPECT_CALL(driver, init(XE_INIT_FLAG_NONE)).Times(1);

    auto result = xeDriverInit(XE_INIT_FLAG_NONE);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(xeDriverInit, returnsSucess) {
    auto result = xeDriverInit(XE_INIT_FLAG_NONE);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(xeDriverGetDevice, redirectsToObject) {
    Mock<Driver> driver;
    xe_device_handle_t deviceHandle = {};
    xe_device_uuid_t uniqueId = {};

    EXPECT_CALL(driver, getDevice(&uniqueId, &deviceHandle))
        .Times(1)
        .WillRepeatedly(Return(XE_RESULT_SUCCESS));

    auto result = xeDriverGetDevice(&uniqueId,
                                    &deviceHandle);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(xeDriverGetDevice, returnsSuccess) {
    xe_device_handle_t deviceHandle = {};
    xe_device_uuid_t uniqueId = {};
    auto result = xeDriverGetDevice(&uniqueId,
                                    &deviceHandle);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
    EXPECT_NE(nullptr, deviceHandle);
}

TEST(xeDriverGetDeviceCount, DefaultDeviceCount) {
    uint32_t count = 0;
    auto ret = xeDriverGetDeviceCount(&count);

    EXPECT_EQ(XE_RESULT_SUCCESS, ret);
    EXPECT_EQ(1, count);
}

TEST(xeDriverGetDeviceUniqueIds, DefaultDeviceUniqueIds) {
    uint32_t count = 0;
    auto ret = xeDriverGetDeviceCount(&count);

    EXPECT_EQ(XE_RESULT_SUCCESS, ret);
    EXPECT_EQ(1, count);

    xe_device_uuid_t *uniqueIds = new xe_device_uuid_t[count]();
    xeDriverGetDeviceUniqueIds(count, uniqueIds);
    for (uint32_t i = 0; i < count; i++) {
        EXPECT_EQ(i, uniqueIds[i].id[0]);
    }
}

} // namespace ult
} // namespace L0
