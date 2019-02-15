#pragma once
#include "xe_cmdlist.h"
#include "xe_cmdqueue.h"
#include "xe_device.h"
#include "xe_event.h"
#include "xe_module.h"

struct _xe_device_handle_t {
};

namespace xe {
struct MemoryManager;

struct Device : _xe_device_handle_t {
    virtual xe_result_t createCommandList(const xe_command_list_desc_t *desc,
                                          xe_command_list_handle_t *commandList) = 0;

    virtual xe_result_t createCommandQueue(const xe_command_queue_desc_t *desc,
                                           xe_command_queue_handle_t *commandQueue) = 0;

    virtual xe_result_t createEvent(const xe_event_desc_t *desc,
                                    xe_event_handle_t *event) = 0;

    virtual xe_result_t createModule(const xe_module_desc_t *desc, 
                                     xe_module_handle_t *module,
                                     xe_module_build_log_handle_t *buildLog) = 0;

    virtual MemoryManager *getMemoryManager() = 0;

    static Device *fromHandle(xe_device_handle_t handle) {
        return static_cast<Device *>(handle);
    }

    inline xe_device_handle_t toHandle() {
        return this;
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

xe_result_t __xecall
xeDeviceCreateModule(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_module_desc_t* desc,                   ///< [in] pointer to module descriptor
    xe_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
    xe_module_build_log_handle_t* phBuildLog        ///< [out][optional] pointer to handle of module's build log.
);

} // namespace xe
