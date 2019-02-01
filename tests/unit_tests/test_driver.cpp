#include "mock_driver.h"
#include "gmock/gmock.h"

using ::testing::Return;

namespace xe {

TEST(xeDriverInit, redirectsToDriverObject) {
    MockDriver driver;

    EXPECT_CALL(driver, initialize(XE_INIT_FLAG_NONE)).Times(1);

    auto result = xe::xeDriverInit(XE_INIT_FLAG_NONE);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(xeDriverInit, returnsSucess) {
    auto result = xe::xeDriverInit(XE_INIT_FLAG_NONE);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(xeDriverGetDevice, redirectsToDriverObject) {
    MockDriver driver;

    xe_device_handle_t deviceHandle = {};
    uint32_t ordinal = 0;

    EXPECT_CALL(driver, getDevice(ordinal, &deviceHandle))
        .Times(1)
        .WillRepeatedly(Return(XE_RESULT_SUCCESS));

    auto result = xeDriverGetDevice(ordinal,
                                    &deviceHandle);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(xeDriverGetDevice, returnsSuccess) {
    xe_device_handle_t deviceHandle = {};
    uint32_t ordinal = 0;
    auto result = xeDriverGetDevice(ordinal,
                                    &deviceHandle);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
    EXPECT_NE(nullptr, deviceHandle);
}

} // namespace xe
