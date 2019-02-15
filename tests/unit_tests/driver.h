#pragma once
#include "xe_driver.h"

namespace xe {

struct Driver {
    virtual xe_result_t initialize(_xe_init_flag_t) = 0;

    virtual xe_result_t getDevice(uint32_t ordinal,
                                  xe_device_handle_t *phDevice) = 0;

    static Driver *get() {
        return driver;
    }

  protected:
    static Driver *driver;
};

xe_result_t __xecall xeDriverInit(_xe_init_flag_t flags);

xe_result_t __xecall xeDriverGetDevice(uint32_t ordinal,
                              xe_device_handle_t *phDevice);
} // namespace xe
