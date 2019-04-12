#include "device.h"
#include "driver.h"
#include "driver_imp.h"
#include "runtime/helpers/string.h"
#include "runtime/platform/platform.h"
#include "runtime/os_interface/debug_settings_manager.h"
#include <cassert>
#include <thread>

namespace L0 {
void DriverImp::initialize(bool *result) {
    auto platform = NEO::constructPlatform();
    platform->initialize();
}

xe_result_t DriverImp::init(xe_init_flag_t) {
    bool result = false;
    std::call_once(initDriverOnce, [this, &result]() { this->initialize(&result); });

    return XE_RESULT_SUCCESS;
}

xe_result_t DriverImp::getDevice(const xe_device_uuid_t *uniqueId, xe_device_handle_t *phDevice) {
    auto platform = NEO::constructPlatform();
    // Assume for now xe_device_uuid_t id[0] contains ordinalID
    auto device = Device::create(platform->getDevice(static_cast<size_t>(uniqueId->id[0])));
    *phDevice = device;

    return XE_RESULT_SUCCESS;
}

xe_result_t DriverImp::getDeviceCount(uint32_t *count) {
    assert(count);
    *count = 1U;
    if (NEO::DebugManager.flags.CreateMultipleDevices.get() > 0) {
        *count = static_cast<uint32_t>(NEO::DebugManager.flags.CreateMultipleDevices.get());
    }
    return XE_RESULT_SUCCESS;
}

xe_result_t DriverImp::getDeviceUniqueIds(uint32_t count, xe_device_uuid_t *pUniqueIds) {
    if (count < 1) {
        return XE_RESULT_ERROR_INVALID_PARAMETER;
    }

    for (uint8_t i = 0; i < count; i++) {
        // Assume for now xe_device_uuid_t id[0] contains ordinalID
        pUniqueIds[i].id[0] = i;
    }
    return XE_RESULT_SUCCESS;
}

xe_result_t DriverImp::getVersion(uint32_t *version) {
    assert(version != nullptr);
    *version = 0U; // TODO : Take this from build system once one is in place
    return XE_RESULT_SUCCESS;
}

static DriverImp driverImp;
Driver *Driver::driver = &driverImp;

} // namespace L0
