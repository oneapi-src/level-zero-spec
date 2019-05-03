#include "device.h"
#include "event.h"
#include "graphics_allocation.h"
#include "memory_manager.h"
#include "os_interface/os_context.h"
#include "runtime/device/device.h"
#include "runtime/execution_environment/execution_environment.h"

#include <cassert>
#include <vector>

namespace L0 {

struct EventImp : public Event {
    EventImp(Device *device) : device(device) {}

    xe_result_t hostSignal() override;

    xe_result_t hostSynchronize(uint32_t timeout) override;

    xe_result_t queryElapsedTime(xe_event_handle_t hEventEnd,
                                 double *pTime) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t queryMetricsData(xe_event_handle_t hEventEnd,
                                 size_t reportSize,
                                 uint32_t *pReportData) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t queryStatus() override {
        auto hostAddress = static_cast<uint64_t *>(allocation->getHostAddress());

        return *hostAddress == Event::STATE_CLEARED
                   ? XE_RESULT_NOT_READY
                   : XE_RESULT_SUCCESS;
    }

    xe_result_t reset() override;

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
    assert(globalMemoryManager);
    allocation = globalMemoryManager->allocateDeviceMemory(device, 64u, 64u);
    assert(allocation);

    reset();

    return true;
}

xe_result_t Event::destroy() {
    delete this;
    return XE_RESULT_SUCCESS;
}

xe_result_t EventImp::hostSignal() {
    auto hostAddress = static_cast<uint64_t *>(allocation->getHostAddress());
    *(hostAddress) = Event::STATE_SIGNALED;

    // Flush cache line at all levels containing the value
    _mm_clflush(hostAddress);

    return XE_RESULT_SUCCESS;
}

xe_result_t EventImp::hostSynchronize(uint32_t timeout) {
    if (timeout != std::numeric_limits<uint32_t>::max()) {
        return XE_RESULT_ERROR_INVALID_PARAMETER;
    }

    auto execEnvironment = static_cast<NEO::ExecutionEnvironment *>(device->getExecEnvironment());
    OsContext::create(execEnvironment);

    // Fake Flush Stamp value for now
    flushStampToWait = 1;
    bool ret = waitForFlushStamp(flushStampToWait);

    if (!ret) {
        return XE_RESULT_NOT_READY;
    }

    return XE_RESULT_SUCCESS;
}

xe_result_t eventQueryElapsedTime(xe_event_handle_t hEventStart,
                                  xe_event_handle_t hEventEnd,
                                  double *pTime) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t eventQueryMetricsData(xe_event_handle_t hEventStart,
                                  xe_event_handle_t hEventEnd,
                                  size_t reportSize,
                                  uint32_t *pReportData) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t EventImp::reset() {
    auto hostAddress = static_cast<uint64_t *>(allocation->getHostAddress());
    *(hostAddress) = Event::STATE_INITIAL;

    // Flush cache line at all levels containing the value
    _mm_clflush(hostAddress);

    return XE_RESULT_SUCCESS;
}

struct EventPoolImp : public EventPool {
    EventPoolImp(Device *device) : device(device) {}

    bool initialize(uint32_t count);

    Device *device;
};

bool EventPoolImp::initialize(uint32_t count) {
    this->count = count;
    pool = std::vector<Event *>(this->count, nullptr);
    for (uint32_t i = 0; i < count; i++) {
        auto event = Event::create(this->device);
        assert(event);
        pool[i] = event;
    }
    return true;
}

EventPool *EventPool::create(Device *device, const xe_event_pool_desc_t *desc) {
    auto eventPool = new EventPoolImp(device);
    bool ret = eventPool->initialize(desc->count);
    assert(ret);
    return eventPool;
}

xe_result_t EventPool::destroy() {
    for (Event *event: pool) {
        event->destroy();
    }
    return XE_RESULT_SUCCESS;
}

xe_result_t EventPool::createEvent(uint32_t index, xe_event_handle_t* phEvent) {
    assert(index < pool.size());
    *phEvent = this->pool[index];
    return XE_RESULT_SUCCESS;
}

xe_result_t  EventPool::getIpcHandle(xe_ipc_event_pool_handle_t* pIpcHandle) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t eventPoolOpenIpcHandle(xe_device_handle_t hDevice,
        xe_ipc_event_pool_handle_t hIpc, xe_event_pool_handle_t* phEventPool) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t  EventPool::closeIpcHandle() {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

} // namespace L0
