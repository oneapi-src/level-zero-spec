#pragma once

#include "runtime/platform/platform.h"

#include "driver.h"
#include <mutex>

namespace L0 {

class Platform {
  public:
  Platform();

  static Platform *getPlatform() {
    static Platform platform;
    return &platform;
  }
};

class DriverImp : public Driver {
  public:
    xe_result_t driverGetDevice(uint32_t ordinal, xe_device_handle_t *phDevice) override;
    xe_result_t driverGetDeviceCount(uint32_t *count) override;
    xe_result_t driverGetVersion(uint32_t *version) override;
    xe_result_t driverInit(_xe_init_flag_t) override;

    void initialize(bool *result) override;

  protected:
    std::once_flag initDriverOnce;
};
} // namespace L0
