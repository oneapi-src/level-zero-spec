#include "device.h"
#include "event.h"
#include "graphics_allocation.h"
#include "memory_manager.h"
#include <cassert>

namespace xe {

struct EventImp : public Event {
    EventImp(Device *device) : device(device) {}

    bool initialize();

    Device *device;
};

Event *Event::create(Device *device) {
    auto event = new EventImp(device);

    event->initialize();
    return event;
}

uint64_t Event::getGpuAddress() {
    assert(allocation);
    return allocation->getGpuAddress();
}

bool EventImp::initialize() {
    auto memoryManager = device->getMemoryManager();
    assert(memoryManager);
    allocation = memoryManager->allocateDeviceMemory(64u, 64u);
    assert(allocation);

    return true;
}

xe_result_t Event::destroy() {
    delete this;
    return XE_RESULT_SUCCESS;
}

xe_result_t __xecall
xeEventDestroy(
    xe_event_handle_t hEvent                        ///< [in] handle of event object to destroy
) {
    return Event::fromHandle(hEvent)->destroy();
}

} // namespace xe
