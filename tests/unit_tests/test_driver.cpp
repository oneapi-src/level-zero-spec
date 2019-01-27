#include "mock_driver.h"
#include "gmock/gmock.h"

using ::testing::Return;

TEST(driverInit, redirectsToDriverObject) {
    xe::MockDriver driver;
    auto oldDriver = xe::driver;
    xe::driver = &driver;

    EXPECT_CALL(driver, initialize(XE_INIT_FLAG_NONE)).Times(1);

    auto result = xe::DriverInit(
        XE_INIT_FLAG_NONE ///< [in] initialization flags
    );
    EXPECT_EQ(XE_RESULT_SUCCESS, result);

    xe::driver = oldDriver;
}

TEST(driverImpinitialize, returnsSucess) {
    auto result = xe::DriverInit(
        XE_INIT_FLAG_NONE ///< [in] initialization flags
    );
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(driverGetDevice, redirectsToDriverObject) {
    xe::MockDriver driver;
    auto oldDriver = xe::driver;
    xe::driver = &driver;

    xe_device_handle_t deviceHandle = {};
    uint32_t ordinal = 0;

    EXPECT_CALL(driver, getDevice(ordinal, &deviceHandle))
        .Times(1)
        .WillRepeatedly(Return(XE_RESULT_SUCCESS));

    auto result = xe::DriverGetDevice(
        ordinal,
        &deviceHandle
    );
    EXPECT_EQ(XE_RESULT_SUCCESS, result);

    xe::driver = oldDriver;
}

TEST(driverImpgetDevice, returnsSuccess) {
    xe_device_handle_t deviceHandle = {};
    uint32_t ordinal = 0;
    auto result = xe::DriverGetDevice(
        ordinal,
        &deviceHandle
    );
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
    EXPECT_NE(nullptr, deviceHandle.pDriverData);
}
