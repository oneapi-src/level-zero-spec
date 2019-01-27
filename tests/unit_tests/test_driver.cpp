#include "mock_driver.h"
#include "gmock/gmock.h"

TEST(driverInit, returnsSuccess) {
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
