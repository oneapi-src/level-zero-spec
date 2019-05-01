#include "device.h"
#include "driver.h"
#include "driver_imp.h"
#include "driver_version.h"
#include "memory_manager.h"
#include "runtime/helpers/string.h"
#include "runtime/platform/platform.h"
#include "runtime/os_interface/debug_settings_manager.h"
#include <cassert>
#include <thread>

namespace L0 {

void DriverImp::initialize(bool *result) {
    auto platform = NEO::constructPlatform();
    platform->initialize();
    MemoryManager::createGlobalMemoryManager();
}

xe_result_t DriverImp::driverInit(xe_init_flag_t flag) {
    bool result = false;
    std::call_once(initDriverOnce, [this, &result]() {this->initialize(&result); });

    return XE_RESULT_SUCCESS;
}

xe_result_t DriverImp::driverGetDevice(uint32_t ordinal, xe_device_handle_t *phDevice) {
    auto platform = NEO::constructPlatform();
    auto device = Device::create(platform->getDevice(static_cast<size_t>(ordinal)));
    *phDevice = device;

    return XE_RESULT_SUCCESS;
}

xe_result_t DriverImp::driverGetDeviceCount(uint32_t *count) {
    assert(count);
    *count = 1U;
    if (NEO::DebugManager.flags.CreateMultipleDevices.get() > 0) {
        *count = static_cast<uint32_t>(NEO::DebugManager.flags.CreateMultipleDevices.get());
    }
    return XE_RESULT_SUCCESS;
}

xe_result_t DriverImp::driverGetVersion(uint32_t *version) {
    assert(version != nullptr);
    *version = static_cast<uint32_t>(LOKI_DRIVER_VERSION);
    return XE_RESULT_SUCCESS;
}

xe_result_t getDriverVersion(uint32_t *version) {
    return Driver::get()->driverGetVersion(version);
}

xe_result_t deviceGetCount(uint32_t *count) {
    return Driver::get()->driverGetDeviceCount(count);
}

xe_result_t deviceGet(uint32_t ordinal, xe_device_handle_t *phDevice) {
    return Driver::get()->driverGetDevice(ordinal, phDevice);
}

static DriverImp driverImp;
Driver *Driver::driver = &driverImp;

xe_result_t init(xe_init_flag_t flag) {
    return Driver::get()->driverInit(flag);
}

} // namespace L0
