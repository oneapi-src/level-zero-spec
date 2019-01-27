#include "driver.h"
#include "runtime/platform/platform.h"

namespace xe {

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
