#include "cmdlist.h"
#include "cmdqueue.h"
#include "device.h"
#include "event.h"
#include "memory_manager.h"
#include "module.h"
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
        auto productFamily = deviceRT->getHardwareInfo().pPlatform->eProductFamily;

        auto executionEnvironment = deviceRT->getExecutionEnvironment();
        auto csrRT = executionEnvironment->commandStreamReceivers[0][0].get();

        *commandQueue = CommandQueue::create(productFamily, this, csrRT);

        return XE_RESULT_SUCCESS;
    }

    xe_result_t createEvent(const xe_event_desc_t *desc,
        xe_event_handle_t *event) override {
        *event = Event::create(this);
        return XE_RESULT_SUCCESS;
    }

    xe_result_t createModule(const xe_module_desc_t *desc,
        xe_module_handle_t *module,
        xe_module_build_log_handle_t *buildLog) override {
        *module = Module::create(this, desc, deviceRT);
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

xe_result_t __xecall
xeDeviceCreateModule(
    xe_device_handle_t hDevice,              
    const xe_module_desc_t* desc,            
    xe_module_handle_t* phModule,            
    xe_module_build_log_handle_t* phBuildLog) {

    auto device = Device::fromHandle(hDevice);
    return device->createModule(desc, phModule, phBuildLog);
}
} // namespace xe
