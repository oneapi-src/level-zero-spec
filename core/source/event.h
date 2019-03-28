#pragma once
#include "xe_event.h"
#include "cmdlist.h"
#include "device.h"

struct _xe_event_handle_t {
};

namespace L0 {
struct GraphicsAllocation;
typedef uint64_t FlushStamp;

struct Event : public _xe_event_handle_t {
    virtual xe_result_t destroy();
    virtual xe_result_t hostSignal() {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }
    virtual xe_result_t hostSynchronize(uint32_t timeout) {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }
    virtual xe_result_t queryElapsedTime(xe_event_handle_t hEventEnd,
                                         double *pTime) {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }
    virtual xe_result_t queryMetricsData(xe_event_handle_t hEventEnd,
                                         size_t reportSize,
                                         uint32_t *pReportData) {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }
    virtual xe_result_t queryStatus() {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }
    virtual xe_result_t reset() {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    // NOTE: Only bit 0 determines signaled.
    enum State : uint32_t {
        STATE_SIGNALED = 0u,
        STATE_CLEARED = static_cast<uint32_t>(-1),
        STATE_INITIAL = STATE_CLEARED
    };

    static Event *create(Device *device);

    static Event *fromHandle(xe_event_handle_t handle) {
        return static_cast<Event *>(handle);
    }

    inline xe_event_handle_t toHandle() {
        return this;
    }

    GraphicsAllocation &getAllocation() {
        return *allocation;
    }

    uint64_t getGpuAddress();

    FlushStamp flushStampToWait;
    virtual bool waitForFlushStamp(FlushStamp &flushStamp) { return true; }

  protected:
    GraphicsAllocation *allocation = nullptr;
};

xe_result_t eventQueryElapsedTime(xe_event_handle_t hEventStart,
                                  xe_event_handle_t hEventEnd,
                                  double *pTime);

xe_result_t eventQueryMetricsData(xe_event_handle_t hEventStart,
                                  xe_event_handle_t hEventEnd,
                                  size_t reportSize,
                                  uint32_t *pReportData);

xe_result_t eventHostSignal(xe_event_handle_t hEvent);

xe_result_t eventHostSynchronize(xe_event_handle_t hEvent, uint32_t timeout);

} // namespace L0
