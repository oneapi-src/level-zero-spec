#include <cmath>
#include <cstdint>
#include "xe_event.h"

xe_result_t __xecall
xeDeviceCreateEvent(
    xe_device_handle_t hDevice,  ///< [in] handle of the device
    const xe_event_desc_t *desc, ///< [in] pointer to event descriptor
    xe_event_handle_t *phEvent   ///< [out] pointer to handle of event object created
) {
    return XE_RESULT_SUCCESS;
}

xe_result_t __xecall
xeEventDestroy(
    xe_event_handle_t hEvent ///< [in] handle of event object to destroy
) {
    return XE_RESULT_SUCCESS;
}

xe_result_t __xecall
xeCommandListEncodeWaitOnEvent(
    xe_command_list_handle_t hCommandList, ///< [in] handle of the command list
    xe_event_handle_t hEvent               ///< [in] handle of the event
) {
    return XE_RESULT_SUCCESS;
}
