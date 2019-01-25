#include <cmath>
#include <cstdint>
#include "xe_device.h"

xe_result_t __xecall
xeDriverGetDevice(
    uint32_t ordinal,            ///< [in] ordinal of device to retrieve
    xe_device_handle_t *phDevice ///< [out] pointer to handle of device object created
) {
    return XE_RESULT_SUCCESS;
}
