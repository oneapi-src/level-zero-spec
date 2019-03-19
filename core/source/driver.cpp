#include "device.h"
#include "driver.h"
#include "runtime/helpers/string.h"
#include "runtime/platform/platform.h"
#include <cassert>

namespace L0 {

constexpr xe_device_uuid_t singleDeviceId{"single_device"}; // replace with really unique ids
                                                            // once multidevice support gets added

struct DriverImp : public Driver {
    xe_result_t init(xe_init_flag_t) override {
        auto platform = OCLRT::constructPlatform();
        auto success = platform->initialize();

        return XE_RESULT_SUCCESS;
    }

    xe_result_t getDevice(xe_device_uuid_t *uniqueId,
                          xe_device_handle_t *phDevice) override {
        auto platform = OCLRT::constructPlatform();
        //TODO: map uniqueId -> deviceOrdinal
        auto device = Device::create(platform->getDevice(0u));
        *phDevice = device;

        return XE_RESULT_SUCCESS;
    }

    xe_result_t getDeviceCount(uint32_t *count) override {
        assert(count);
        *count = 1u;
        return XE_RESULT_SUCCESS;
    }

    xe_result_t getDeviceUniqueIds(uint32_t count,
                                   xe_device_uuid_t *pUniqueIds) override {
        if (count < 1) {
            return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        memcpy_s(&pUniqueIds[0], sizeof(xe_device_uuid_t), &singleDeviceId, sizeof(singleDeviceId));
        return XE_RESULT_SUCCESS;
    }

    xe_result_t getVersion(uint32_t *version) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }
};

static DriverImp driverImp;
Driver *Driver::driver = &driverImp;

} // namespace L0
