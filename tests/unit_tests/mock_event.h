#pragma once
#include "event.h"
#include "graphics_allocation.h"
#include "mock.h"
#include "white_box.h"
#include "os_interface/os_context.h"

#include <vector>

namespace L0 {
namespace ult {

template <> struct WhiteBox<::L0::Event> : public ::L0::Event {
    using BaseClass = ::L0::Event;
    using BaseClass::allocation;
};

using Event = WhiteBox<::L0::Event>;

template <> struct WhiteBox<::L0::EventPool> : public ::L0::EventPool {
    using BaseClass = ::L0::EventPool;
};

using EventPool = WhiteBox<::L0::EventPool>;

template <> struct Mock<Event> : public Event {
    Mock();
    virtual ~Mock();

    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD0(hostSignal, xe_result_t());
    MOCK_METHOD1(hostSynchronize, xe_result_t(uint32_t timeout));
    MOCK_METHOD2(queryElapsedTime, xe_result_t(xe_event_handle_t hEventEnd, double *pTime));
    MOCK_METHOD3(queryMetricsData, xe_result_t(xe_event_handle_t hEventEnd, size_t reportSize,
                                               uint32_t *pReportData));
    MOCK_METHOD0(queryStatus, xe_result_t());
    MOCK_METHOD0(reset, xe_result_t());
    MOCK_METHOD1(waitForFlushStamp, bool(FlushStamp &flushStamp));

    // Fake an allocation for event memory
    alignas(16) uint32_t memory = -1;
    GraphicsAllocation mockAllocation;
    FlushStamp mockflushStampToWait;

    using Event::allocation;
};

template <> struct Mock<EventPool> : public EventPool {
    Mock();
    virtual ~Mock();

    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD2(createEvent, xe_result_t(const xe_event_desc_t *desc, xe_event_handle_t *phEvent));
    MOCK_METHOD0(getPoolSize, size_t());
    MOCK_METHOD1(getEvent, Event *(uint32_t index));
    MOCK_METHOD1(getIpcHandle, xe_result_t(xe_ipc_event_pool_handle_t *pIpcHandle));
    MOCK_METHOD0(closeIpcHandle, xe_result_t());

    std::vector<Event *> pool;
};

} // namespace ult
} // namespace L0