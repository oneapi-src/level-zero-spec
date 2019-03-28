#include "device.h"
#include "event.h"
#include "graphics_allocation.h"
#include "memory_manager.h"
#include "os_interface/os_context.h"
#include "runtime/device/device.h"
#include "runtime/execution_environment/execution_environment.h"

#include <cassert>

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
    auto memoryManager = device->getMemoryManager();
    assert(memoryManager);
    allocation = memoryManager->allocateDeviceMemory(64u, 64u);
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

    auto execEnvironment = static_cast<OCLRT::ExecutionEnvironment *>(device->getExecEnvironment());
    auto osContext = OsContext::create(execEnvironment);

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

} // namespace L0
