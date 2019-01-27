#include "device.h"
#include "runtime/device/device.h"

namespace xe {

struct DeviceImp : public Device {
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
deviceCreateCommandQueue(
    xe_device_handle_t hDevice,
    const xe_command_queue_desc_t *desc,
    xe_command_queue_handle_t *phCommandQueue) {

    auto device = static_cast<Device *>(hDevice.pDriverData);
    return device->createCommandQueue(desc, phCommandQueue);
}

} // namespace xe

