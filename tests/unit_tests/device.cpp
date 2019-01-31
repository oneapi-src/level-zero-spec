#include "cmd_list.h"
#include "cmd_queue.h"
#include "device.h"
#include "event.h"
#include "memory_manager.h"
#include "runtime/device/device.h"

namespace xe {

struct DeviceImp : public Device {
    xe_result_t createCommandList(const xe_command_list_desc_t *desc,
                                  xe_command_list_handle_t *commandList) override {
        auto productFamily = deviceRT->getHardwareInfo().pPlatform->eProductFamily;
        *commandList = CommandList::create(productFamily, this);

        return XE_RESULT_SUCCESS;
    }

    xe_result_t createCommandQueue(const xe_command_queue_desc_t *desc,
                                   xe_command_queue_handle_t *commandQueue) override {
        *commandQueue = CommandQueue::create(this);

        return XE_RESULT_SUCCESS;
    }

    xe_result_t createEvent(const xe_event_desc_t *desc,
                            xe_event_handle_t *event) override {
        *event = Event::create();
        return XE_RESULT_SUCCESS;
    }

    MemoryManager *getMemoryManager() override {
        return memoryManager;
    }

    OCLRT::Device *deviceRT = nullptr;
    MemoryManager *memoryManager = nullptr;
};

Device *Device::create(void *ptr) {
    auto device = new DeviceImp;

    auto deviceRT = static_cast<OCLRT::Device *>(ptr);
    device->deviceRT = deviceRT;
    device->memoryManager = MemoryManager::create(deviceRT->getMemoryManager());

    return device;
}

xe_result_t __xecall
xeDeviceCreateCommandList(
    xe_device_handle_t hDevice,
    const xe_command_list_desc_t *desc,
    xe_command_list_handle_t *phCommandList) {

    auto device = Device::fromHandle(hDevice);
    return device->createCommandList(desc,
                                     phCommandList);
}

xe_result_t __xecall
xeDeviceCreateCommandQueue(
    xe_device_handle_t hDevice,
    const xe_command_queue_desc_t *desc,
    xe_command_queue_handle_t *phCommandQueue) {

    auto device = Device::fromHandle(hDevice);
    return device->createCommandQueue(desc,
                                      phCommandQueue);
}

xe_result_t __xecall
xeDeviceCreateEvent(
    xe_device_handle_t hDevice,
    const xe_event_desc_t *desc,
    xe_event_handle_t *phEvent) {

    auto device = Device::fromHandle(hDevice);
    return device->createEvent(desc,
                               phEvent);
}
} // namespace xe
