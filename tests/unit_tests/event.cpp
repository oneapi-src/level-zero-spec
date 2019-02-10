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
    allocation = memoryManager->allocateDeviceMemory(16u);
    assert(allocation);

    return true;
}

} // namespace xe
