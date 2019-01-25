#include <cmath>
#include <cstdint>
#include "xe_cmdqueue.h"

xe_result_t __xecall
xeDeviceCreateCommandQueue(
    xe_device_handle_t hDevice,               ///< [in] handle of the device object
    const xe_command_queue_desc_t *desc,      ///< [in] pointer to command queue descriptor
    xe_command_queue_handle_t *phCommandQueue ///< [out] pointer to handle of command queue object created
) {
    return XE_RESULT_SUCCESS;
}

xe_result_t __xecall
xeCommandQueueDestroy(
    xe_command_queue_handle_t hCommandQueue ///< [in] handle of command queue object to destroy
) {
    return XE_RESULT_SUCCESS;
}

xe_result_t __xecall
xeCommandQueueEnqueueCommandList(
    xe_command_queue_handle_t hCommandQueue, ///< [in] handle of the command queue
    xe_command_list_handle_t hCommandList    ///< [in] handle of the command list to execute
) {
    return XE_RESULT_SUCCESS;
}
