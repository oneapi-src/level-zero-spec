#pragma once
#include "xe_driver.h "

namespace xe {

struct Driver {
    virtual xe_result_t initialize(xe_init_flags_t) = 0;
};

extern Driver *driver;

xe_result_t DriverInit(xe_init_flags_t flags);

} // namespace xe
