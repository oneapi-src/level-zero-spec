#pragma once
#include "xe_device.h"
#include "xe_driver.h"

namespace xe {

struct Driver {
    virtual xe_result_t getDevice(uint32_t uniqueId,
                                  xe_device_handle_t *phDevice) = 0;
    virtual xe_result_t getDeviceCount(uint32_t *count) = 0;
    virtual xe_result_t getDeviceLinkProperties(uint32_t srcOrdinal,
                                                uint32_t dstOrdinal,
                                                xe_device_link_properties_t *pLinkProperties) = 0;
    virtual xe_result_t getDeviceUniqueIds(uint32_t count,
                                           uint32_t *pUniqueIds) = 0;
    virtual xe_result_t getVersion(uint32_t *version) = 0;
    virtual xe_result_t init(_xe_init_flag_t) = 0;

    static Driver *get() {
        return driver;
    }

  protected:
    static Driver *driver;
};

} // namespace xe
