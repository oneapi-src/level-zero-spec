#pragma once

#include "driver.h"
#include <mutex>

namespace L0 {
struct DriverImp : public Driver {
    xe_result_t getDevice(const xe_device_uuid_t *uniqueId, xe_device_handle_t *phDevice) override;
    xe_result_t getDeviceCount(uint32_t *count) override;
    xe_result_t getDeviceUniqueIds(uint32_t count, xe_device_uuid_t *pUniqueIds) override;
    xe_result_t getVersion(uint32_t *version) override;
    xe_result_t init(_xe_init_flag_t) override;

    void initialize(bool *result) override;

  protected:
    std::once_flag initDriverOnce;
};
} // namespace L0
