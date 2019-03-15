#include "device.h"
#include "event.h"
#include "graphics_allocation.h"
#include "memory_manager.h"

#include <cassert>

namespace L0 {

struct EventImp : public Event {
    EventImp(Device *device) : device(device) {}

    xe_result_t queryElapsedTime(xe_event_handle_t hEventEnd,
                                 double_t *pTime) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t queryMetricsData(xe_event_handle_t hEventEnd,
                                 size_t reportSize,
                                 uint32_t *pReportData) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t queryStatus() override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t reset() override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

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

xe_result_t hostWaitOnEvent(xe_event_handle_t hEvent, uint32_t timeout) {
    return XE_RESULT_SUCCESS;
}

xe_result_t eventQueryElapsedTime(xe_event_handle_t hEventStart,
                                  xe_event_handle_t hEventEnd,
                                  double_t *pTime) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t eventQueryMetricsData(xe_event_handle_t hEventStart,
                                  xe_event_handle_t hEventEnd,
                                  size_t reportSize,
                                  uint32_t *pReportData) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t hostSignalEvent(xe_event_handle_t hEvent) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t hostSignalMultipleEvents(uint32_t numEvents,
                                       xe_event_handle_t *phEvents) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t hostWaitOnMultipleEvents(uint32_t numEvents,
                                       xe_event_handle_t *phEvents,
                                       xe_synchronization_mode_t mode,
                                       uint32_t delay,
                                       uint32_t interval,
                                       uint32_t timeout) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

} // namespace L0
