#include "device.h"
#include "driver.h"
#include "runtime/helpers/string.h"
#include "runtime/platform/platform.h"
#include "runtime/os_interface/debug_settings_manager.h"
#include <cassert>

namespace L0 {

struct DriverImp : public Driver {
    xe_result_t init(xe_init_flag_t) override {
        auto platform = OCLRT::constructPlatform();
        auto success = platform->initialize();

        return XE_RESULT_SUCCESS;
    }

    xe_result_t getDevice(const xe_device_uuid_t *uniqueId,
                          xe_device_handle_t *phDevice) override {
        auto platform = OCLRT::constructPlatform();
        // Assume for now xe_device_uuid_t id[0] contains ordinalID
        auto device = Device::create(platform->getDevice(static_cast<size_t>(uniqueId->id[0])));
        *phDevice = device;

        return XE_RESULT_SUCCESS;
    }

    xe_result_t getDeviceCount(uint32_t *count) override {
        assert(count);
        *count = OCLRT::DebugManager.flags.CreateMultipleDevices.get();
        return XE_RESULT_SUCCESS;
    }

    xe_result_t getDeviceUniqueIds(uint32_t count,
                                   xe_device_uuid_t *pUniqueIds) override {
        if (count < 1) {
            return XE_RESULT_ERROR_INVALID_PARAMETER;
        }

        for (uint8_t i = 0; i < count; i++) {
            // Assume for now xe_device_uuid_t id[0] contains ordinalID
            pUniqueIds[i].id[0] = i;
        }
        return XE_RESULT_SUCCESS;
    }

    xe_result_t getVersion(uint32_t *version) override {
        assert(version != nullptr);
        *version = 0U; // TODO : Take this from build system once one is in place
        return XE_RESULT_SUCCESS;
    }
};

static DriverImp driverImp;
Driver *Driver::driver = &driverImp;

} // namespace L0
