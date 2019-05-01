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

xe_result_t EventImp::reset() {
    auto hostAddress = static_cast<uint64_t *>(allocation->getHostAddress());
    *(hostAddress) = Event::STATE_INITIAL;

    // Flush cache line at all levels containing the value
    _mm_clflush(hostAddress);

    return XE_RESULT_SUCCESS;
}

struct EventPoolImp : public EventPool {
    EventPoolImp(Device *device, uint32_t count): device(device), count(count) {
        pool = std::vector<Event *>(this->count, nullptr);
        for (uint32_t i = 0; i < count; i++) {
            auto event = Event::create(this->device);
            assert(event);
            pool[i] = event;
        }
    }

    xe_result_t destroy() override;

    xe_result_t createEvent(const xe_event_desc_t* desc,
            xe_event_handle_t* phEvent) override;

    size_t getPoolSize() override {
        return this->pool.size();
    }

    Event *getEvent(uint32_t index) override {
        return this->pool[index];
    }

    xe_result_t getIpcHandle(xe_ipc_event_pool_handle_t* pIpcHandle) override;

    xe_result_t closeIpcHandle() override;

    void destroyPool() {
        for (Event *event: this->pool) {
            event->destroy();
        }
    }

    Device *device;
    uint32_t count;
    std::vector<Event *> pool;
};

xe_result_t EventPoolImp::createEvent(const xe_event_desc_t* desc,
            xe_event_handle_t* phEvent) {
    assert(desc->index >= 0 && desc->index < this->getPoolSize());
    *phEvent = this->getEvent(desc->index);
    return XE_RESULT_SUCCESS;
}

xe_result_t EventPoolImp::getIpcHandle(xe_ipc_event_pool_handle_t* pIpcHandle) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t EventPoolImp::closeIpcHandle() {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t EventPoolImp::destroy() {
    this->destroyPool();

    return XE_RESULT_SUCCESS;
}

EventPool *EventPool::create(Device *device, const xe_event_pool_desc_t *desc) {
    auto eventPool = new EventPoolImp(device, desc->count);
    assert(eventPool);

    return eventPool;
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

xe_result_t eventPoolOpenIpcHandle(xe_device_handle_t hDevice,
        xe_ipc_event_pool_handle_t hIpc, xe_event_pool_handle_t* phEventPool) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t eventCreate(xe_event_pool_handle_t hEventPool, const xe_event_desc_t* desc,
            xe_event_handle_t* phEvent) {
    EventPool *eventPool = EventPool::fromHandle(hEventPool);
    return eventPool->createEvent(desc, phEvent);
}

xe_result_t eventDestroy(xe_event_handle_t hEvent) {
    return Event::fromHandle(hEvent)->destroy();
}

} // namespace L0
