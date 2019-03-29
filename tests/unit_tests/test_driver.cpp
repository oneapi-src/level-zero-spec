#include "mock_driver.h"
#include "gmock/gmock.h"
#include "runtime/os_interface/debug_settings_manager.h"
#include <array>
#include <thread>

using ::testing::Return;

namespace L0 {
namespace ult {

TEST(xeDriverInit, redirectsToObject) {
    Mock<Driver> driver;
    EXPECT_CALL(driver, init(XE_INIT_FLAG_NONE)).Times(1);

    auto result = xeDriverInit(XE_INIT_FLAG_NONE);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(xeDriverInit, runDriverInitMultipleTimesInLoopAndCheckThatOnceInitializationOccurs) {
    constexpr uint32_t iterations = 10u;
    ::testing::StrictMock<Mock<Driver>> driver;
    ON_CALL(driver, init).WillByDefault(::testing::Invoke(&driver, &Mock<Driver>::mockInit));
    EXPECT_CALL(driver, initialize(::testing::_)).Times(1);
    EXPECT_CALL(driver, init(XE_INIT_FLAG_NONE)).Times(iterations);

    for (uint32_t i = 0; i < iterations; ++i) {
        auto result = xeDriverInit(XE_INIT_FLAG_NONE);
        EXPECT_EQ(XE_RESULT_SUCCESS, result);
    }
}

TEST(xeDriverInit, runDriverInitOnCoupleThreadsAndCheckThatOnceInitializationOccurs) {
    constexpr uint32_t threads = 10u;
    ::testing::StrictMock<Mock<Driver>> driver;
    std::array<std::thread, threads> initThreads;
    std::atomic<uint32_t> atomic(0u);

    ON_CALL(driver, init).WillByDefault(::testing::Invoke(&driver, &Mock<Driver>::mockInit));
    EXPECT_CALL(driver, initialize(::testing::_)).Times(1);
    EXPECT_CALL(driver, init(XE_INIT_FLAG_NONE)).Times(threads);

    for (uint32_t i = 0; i < threads; ++i) {
        initThreads[i] = std::thread(
            [&](std::atomic<uint32_t> &atomic) {
                while (atomic == 0)
                    ;

                auto result = xeDriverInit(XE_INIT_FLAG_NONE);
                EXPECT_EQ(XE_RESULT_SUCCESS, result);
            },
            std::ref(atomic));
    }

    atomic = 1u;

    for (uint32_t i = 0; i < threads; ++i) {
        initThreads[i].join();
    }
}

TEST(xeDriverGetDevice, redirectsToObject) {
    Mock<Driver> driver;
    xe_device_handle_t deviceHandle = {};

    EXPECT_CALL(driver, getDevice(0, &deviceHandle))
        .Times(1)
        .WillRepeatedly(Return(XE_RESULT_SUCCESS));

    auto result = xeDriverGetDevice(0, &deviceHandle);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(xeDriverGetDevice, returnsSuccess) {
    xe_device_handle_t deviceHandle = {};
    auto result = xeDriverGetDevice(0, &deviceHandle);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
    EXPECT_NE(nullptr, deviceHandle);
}

TEST(xeDriverGetDeviceCount, DefaultDeviceCount) {
    uint32_t count = 0;
    auto ret = xeDriverGetDeviceCount(&count);

    EXPECT_EQ(XE_RESULT_SUCCESS, ret);
    EXPECT_EQ(1, count);
}

} // namespace ult
} // namespace L0
