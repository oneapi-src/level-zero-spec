#pragma once
#include "xe_driver.h "

namespace xe {

struct Driver {
    virtual xe_result_t initialize(xe_init_flags_t) = 0;

    virtual xe_result_t getDevice(uint32_t ordinal,
                                  xe_device_handle_t *phDevice) = 0;
};

extern Driver *driver;

xe_result_t DriverInit(xe_init_flags_t flags);

xe_result_t DriverGetDevice(uint32_t ordinal,
                      xe_device_handle_t *phDevice);
} // namespace xe
