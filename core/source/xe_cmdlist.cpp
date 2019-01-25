#include <cmath>
#include <cstdint>
#include "xe_cmdlist.h"

xe_result_t __xecall
xeDeviceCreateCommandList(
    xe_device_handle_t hDevice,             ///< [in] handle of the device object
    const xe_command_list_desc_t *desc,     ///< [in] pointer to command list descriptor
    xe_command_list_handle_t *phCommandList ///< [out] pointer to handle of command list object created
) {
    return XE_RESULT_SUCCESS;
}

xe_result_t __xecall
xeCommandListClose(
    xe_command_list_handle_t hCommandList ///< [in] handle of command list object to close
) {
    return XE_RESULT_SUCCESS;
}

xe_result_t __xecall
xeCommandListDestroy(
    xe_command_list_handle_t hCommandList ///< [in] handle of command list object to destroy
) {
    return XE_RESULT_SUCCESS;
}
