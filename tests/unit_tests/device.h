#pragma once
#include "xe_cmdlist.h"
#include "xe_cmdqueue.h"
#include "xe_device.h"

namespace xe {

struct Device {
    virtual xe_result_t createCommandList(const xe_command_list_desc_t *desc,
                                          xe_command_list_handle_t *commandList) = 0;

    virtual xe_result_t createCommandQueue(const xe_command_queue_desc_t *desc,
                                           xe_command_queue_handle_t *commandQueue) = 0;

    static Device *create(void *device);
};

xe_result_t __xecall
deviceCreateCommandList(
    xe_device_handle_t hDevice,             ///< [in] handle of the device object
    const xe_command_list_desc_t *desc,     ///< [in] pointer to command list descriptor
    xe_command_list_handle_t *phCommandList ///< [out] pointer to handle of command list object created
);

xe_result_t __xecall
deviceCreateCommandQueue(
    xe_device_handle_t hDevice,               ///< [in] handle of the device object
    const xe_command_queue_desc_t *desc,      ///< [in] pointer to command queue descriptor
    xe_command_queue_handle_t *phCommandQueue ///< [out] pointer to handle of command queue object created
);

} // namespace xe