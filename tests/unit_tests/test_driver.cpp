#include "xe_driver.h"
#include "runtime/platform/platform.h"
#include "gmock/gmock.h"

namespace xe {

struct Driver {
    virtual xe_result_t initialize(xe_init_flags_t) = 0;
};

struct MockDriver : public Driver {
    MOCK_METHOD1(initialize, xe_result_t(xe_init_flags_t));
};

struct DriverImp : public Driver {
    xe_result_t initialize(xe_init_flags_t) override {
        auto platform = OCLRT::constructPlatform();
        auto success = platform->initialize();

        return XE_RESULT_SUCCESS;
    }
};

static DriverImp driverImp;
Driver *driver = &driverImp;

xe_result_t DriverInit(xe_init_flags_t flags) {
    return driver->initialize(flags);
}

}

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
