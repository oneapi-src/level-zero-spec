#include "device.h"
#include "driver.h"
#include "runtime/platform/platform.h"

namespace xe {

struct DriverImp : public Driver {
    xe_result_t initialize(xe_init_flags_t) override {
        auto platform = OCLRT::constructPlatform();
        auto success = platform->initialize();

        return XE_RESULT_SUCCESS;
    }

    xe_result_t getDevice(uint32_t ordinal,
                          xe_device_handle_t *phDevice) override {
        auto platform = OCLRT::constructPlatform();
        auto device = Device::create(platform->getDevice(ordinal));
        phDevice->pDriverData = device;

        return XE_RESULT_SUCCESS;
    }
};

static DriverImp driverImp;
Driver *driver = &driverImp;

xe_result_t xeDriverInit(xe_init_flags_t flags) {
    return driver->initialize(flags);
}

xe_result_t __xecall xeDriverGetDevice(
    uint32_t ordinal,
    xe_device_handle_t *phDevice) {
    return driver->getDevice(ordinal, phDevice);
}

} // namespace xe
