#include "gmock/gmock.h"
#include "runtime/helpers/options.h"
#include "runtime/platform/platform.h"
#include "runtime/helpers/hw_info.h"

TEST(platformInitialize, shouldSucceed) {
    auto platform = OCLRT::constructPlatform();
    ASSERT_NE(nullptr, platform);

    bool ret = platform->initialize();
    ASSERT_TRUE(ret);

    EXPECT_TRUE(platform->isInitialized());
}

TEST(platformGetDevice, returnsDevice) {
    auto platform = OCLRT::constructPlatform();
    ASSERT_NE(nullptr, platform);

    bool ret = platform->initialize();
    ASSERT_TRUE(ret);

    auto device = platform->getDevice(0);
    EXPECT_NE(nullptr, device);
}
