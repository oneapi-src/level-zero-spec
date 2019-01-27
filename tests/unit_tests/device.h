#pragma once
#include "xe_cmdlist.h"
#include "xe_cmdqueue.h"
#include "xe_device.h"
#include "xe_event.h"

namespace xe {

struct Device {
    virtual xe_result_t createCommandList(const xe_command_list_desc_t *desc,
                                          xe_command_list_handle_t *commandList) = 0;

    virtual xe_result_t createCommandQueue(const xe_command_queue_desc_t *desc,
                                           xe_command_queue_handle_t *commandQueue) = 0;

    virtual xe_result_t createEvent(const xe_event_desc_t *desc,
                                    xe_event_handle_t *event) = 0;

    static Device *fromHandle(xe_device_handle_t handle) {
        return static_cast<Device *>(handle.pDriverData);
    }

    inline xe_device_handle_t toHandle() const {
        xe_device_handle_t handle;
        handle.pDriverData = const_cast<Device *>(this);
        return handle;
    }

    static Device *create(void *device);
};

xe_result_t __xecall
xeDeviceCreateCommandList(
    xe_device_handle_t hDevice,             ///< [in] handle of the device object
    const xe_command_list_desc_t *desc,     ///< [in] pointer to command list descriptor
    xe_command_list_handle_t *phCommandList ///< [out] pointer to handle of command list object created
);

xe_result_t __xecall
xeDeviceCreateCommandQueue(
    xe_device_handle_t hDevice,               ///< [in] handle of the device object
    const xe_command_queue_desc_t *desc,      ///< [in] pointer to command queue descriptor
    xe_command_queue_handle_t *phCommandQueue ///< [out] pointer to handle of command queue object created
);

xe_result_t __xecall
xeDeviceCreateEvent(
    xe_device_handle_t hDevice,  ///< [in] handle of the device
    const xe_event_desc_t *desc, ///< [in] pointer to event descriptor
    xe_event_handle_t *phEvent   ///< [out] pointer to handle of event object created
);

} // namespace xe
