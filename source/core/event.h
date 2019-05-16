#pragma once
#include "xe_event.h"
#include "cmdlist.h"
#include "device.h"
#include "graphics_allocation.h"

struct _xe_event_handle_t {};

struct _xe_event_pool_handle_t {};

namespace L0 {
struct GraphicsAllocation;
typedef uint64_t FlushStamp;

struct Event : public _xe_event_handle_t {
    virtual ~Event() = default;
    virtual xe_result_t destroy();
    virtual xe_result_t hostSignal() { return XE_RESULT_ERROR_UNSUPPORTED; }
    virtual xe_result_t hostSynchronize(uint32_t timeout) { return XE_RESULT_ERROR_UNSUPPORTED; }
    virtual xe_result_t queryElapsedTime(xe_event_handle_t hEventEnd, double *pTime) {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }
    virtual xe_result_t queryMetricsData(xe_event_handle_t hEventEnd, size_t reportSize,
                                         uint32_t *pReportData) {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }
    virtual xe_result_t queryStatus() { return XE_RESULT_ERROR_UNSUPPORTED; }
    virtual xe_result_t reset() { return XE_RESULT_ERROR_UNSUPPORTED; }

    // NOTE: Only bit 0 determines signaled.
    enum State : uint32_t {
        STATE_SIGNALED = 0u,
        STATE_CLEARED = static_cast<uint32_t>(-1),
        STATE_INITIAL = STATE_CLEARED
    };

    static Event *create(Device *device);

    static Event *fromHandle(xe_event_handle_t handle) { return static_cast<Event *>(handle); }

    inline xe_event_handle_t toHandle() { return this; }

    GraphicsAllocation &getAllocation() { return *allocation; }

    uint64_t getGpuAddress();

  protected:
    GraphicsAllocation *allocation = nullptr;
};

struct EventPool : public _xe_event_pool_handle_t {
    static EventPool *create(Device *device, const xe_event_pool_desc_t *desc);

    virtual xe_result_t destroy() = 0;
    virtual xe_result_t createEvent(const xe_event_desc_t *desc, xe_event_handle_t *phEvent) = 0;
    virtual size_t getPoolSize() = 0;
    virtual Event *getEvent(uint32_t index) = 0;
    virtual xe_result_t getIpcHandle(xe_ipc_event_pool_handle_t *pIpcHandle) = 0;
    virtual xe_result_t closeIpcHandle() = 0;

    static EventPool *fromHandle(xe_event_pool_handle_t handle) {
        return static_cast<EventPool *>(handle);
    }

    inline xe_event_pool_handle_t toHandle() { return this; }
};

xe_result_t eventQueryElapsedTime(xe_event_handle_t hEventStart, xe_event_handle_t hEventEnd,
                                  double *pTime);

xe_result_t eventQueryMetricsData(xe_event_handle_t hEventStart, xe_event_handle_t hEventEnd,
                                  size_t reportSize, uint32_t *pReportData);

xe_result_t eventPoolOpenIpcHandle(xe_device_handle_t hDevice, xe_ipc_event_pool_handle_t hIpc,
                                   xe_event_pool_handle_t *phEventPool);

xe_result_t eventCreate(xe_event_pool_handle_t hEventPool, const xe_event_desc_t *desc,
                        xe_event_handle_t *phEvent);

xe_result_t eventDestroy(xe_event_handle_t hEvent);

} // namespace L0
