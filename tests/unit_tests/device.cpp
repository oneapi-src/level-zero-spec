#include "device.h"
#include "cmd_list.h"
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

    auto device = static_cast<Device *>(hDevice.pDriverData);
    return device->createCommandList(desc,
                                     phCommandList);
}

xe_result_t __xecall
deviceCreateCommandQueue(
    xe_device_handle_t hDevice,
    const xe_command_queue_desc_t *desc,
    xe_command_queue_handle_t *phCommandQueue) {

    auto device = static_cast<Device *>(hDevice.pDriverData);
    return device->createCommandQueue(desc,
                                      phCommandQueue);
}

} // namespace xe

