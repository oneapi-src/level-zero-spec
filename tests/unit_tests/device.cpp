#include "cmd_list.h"
#include "device.h"
#include "event.h"
#include "runtime/device/device.h"

namespace xe {

struct DeviceImp : public Device {
    xe_result_t createCommandList(const xe_command_list_desc_t *desc,
                                  xe_command_list_handle_t *commandList) override {
        commandList->pDriverData = CommandList::create();

        return XE_RESULT_SUCCESS;
    }

    xe_result_t createCommandQueue(const xe_command_queue_desc_t *desc,
                                   xe_command_queue_handle_t *commandQueue) override {
        auto engineControl = device->getDefaultEngine();
        commandQueue->pDriverData = engineControl.commandStreamReceiver;

        return XE_RESULT_SUCCESS;
    }

    xe_result_t createEvent(const xe_event_desc_t *desc,
                            xe_event_handle_t *event) override {
        event->pDriverData = Event::create();
        return XE_RESULT_SUCCESS;
    }

    OCLRT::Device *device = nullptr;
};

Device *Device::create(void *device) {
    auto deviceImp = new DeviceImp;
    deviceImp->device = static_cast<OCLRT::Device *>(device);

    return deviceImp;
}

xe_result_t __xecall
deviceCreateCommandList(
    xe_device_handle_t hDevice,
    const xe_command_list_desc_t *desc,
    xe_command_list_handle_t *phCommandList) {

    auto device = Device::fromHandle(hDevice);
    return device->createCommandList(desc,
                                     phCommandList);
}

xe_result_t __xecall
deviceCreateCommandQueue(
    xe_device_handle_t hDevice,
    const xe_command_queue_desc_t *desc,
    xe_command_queue_handle_t *phCommandQueue) {

    auto device = Device::fromHandle(hDevice);
    return device->createCommandQueue(desc,
                                      phCommandQueue);
}

xe_result_t __xecall
deviceCreateEvent(
    xe_device_handle_t hDevice,
    const xe_event_desc_t *desc,
    xe_event_handle_t *phEvent) {

    auto device = Device::fromHandle(hDevice);
    return device->createEvent(desc,
                               phEvent);
}
} // namespace xe
