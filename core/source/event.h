#pragma once
#include "xe_event.h"
#include "cmdlist.h"
#include "device.h"

struct _xe_event_handle_t {
};

namespace L0 {
struct GraphicsAllocation;

struct Event : public _xe_event_handle_t {
    virtual xe_result_t destroy();
    virtual xe_result_t hostSignal() = 0;
    virtual xe_result_t hostSynchronize(uint32_t timeout) = 0;
    virtual xe_result_t queryElapsedTime(xe_event_handle_t hEventEnd,
                                         double *pTime) = 0;
    virtual xe_result_t queryMetricsData(xe_event_handle_t hEventEnd,
                                         size_t reportSize,
                                         uint32_t *pReportData) = 0;
    virtual xe_result_t queryStatus() = 0;
    virtual xe_result_t reset() = 0;

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
