#pragma once
#include "event.h"
#include "graphics_allocation.h"
#include "mock.h"
#include "white_box.h"

namespace L0 {
namespace ult {

template <>
struct WhiteBox<::L0::Event> : public ::L0::Event {
    using BaseClass = ::L0::Event;
    using BaseClass::allocation;
};

using Event = WhiteBox<::L0::Event>;

template <>
struct Mock<Event> : public Event {
    Mock();
    virtual ~Mock();

    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD2(queryElapsedTime, xe_result_t(xe_event_handle_t hEventEnd,
                                               double_t *pTime));
    MOCK_METHOD3(queryMetricsData, xe_result_t(xe_event_handle_t hEventEnd,
                                               size_t reportSize,
                                               uint32_t *pReportData));
    MOCK_METHOD0(queryStatus, xe_result_t());
    MOCK_METHOD0(reset, xe_result_t ());

    // Fake an allocation for event memory
    alignas(16) uint32_t memory = -1;
    GraphicsAllocation mockAllocation;

    using Event::allocation;
};

} // namespace ult
} // namespace L0
