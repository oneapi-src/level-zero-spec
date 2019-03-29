#include "device.h"
#include "driver.h"
#include "driver_imp.h"
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
}

xe_result_t DriverImp::init(xe_init_flag_t) {
    bool result = false;
    std::call_once(initDriverOnce, [this, &result]() { this->initialize(&result); });
    MemoryManager::createGlobalMemoryManager();

    return XE_RESULT_SUCCESS;
}

xe_result_t DriverImp::getDevice(uint32_t ordinal, xe_device_handle_t *phDevice) {
    auto platform = NEO::constructPlatform();
    auto device = Device::create(platform->getDevice(static_cast<size_t>(ordinal)));
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

xe_result_t DriverImp::getVersion(uint32_t *version) {
    assert(version != nullptr);
    *version = 0U; // TODO : Take this from build system once one is in place
    return XE_RESULT_SUCCESS;
}

static DriverImp driverImp;
Driver *Driver::driver = &driverImp;

} // namespace L0
