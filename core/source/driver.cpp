#include "device.h"
#include "driver.h"
#include "runtime/platform/platform.h"
#include <cassert>

namespace xe {

struct DriverImp : public Driver {
    xe_result_t init(xe_init_flag_t) override {
        auto platform = OCLRT::constructPlatform();
        auto success = platform->initialize();

        return XE_RESULT_SUCCESS;
    }

    xe_result_t getDevice(uint32_t uniqueId,
                          xe_device_handle_t *phDevice) override {
        auto platform = OCLRT::constructPlatform();
        auto device = Device::create(platform->getDevice(uniqueId));
        *phDevice = device;

        return XE_RESULT_SUCCESS;
    }

    xe_result_t getDeviceCount(uint32_t *count) override {
        assert(count);
        *count = 1u;
        return XE_RESULT_SUCCESS;
    }

    xe_result_t getDeviceUniqueIds(uint32_t count,
                                   uint32_t *pUniqueIds) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t getVersion(uint32_t *version) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }
};

static DriverImp driverImp;
Driver *Driver::driver = &driverImp;

} // namespace xe
