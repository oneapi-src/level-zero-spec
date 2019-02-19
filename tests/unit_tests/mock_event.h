#pragma once
#include "event.h"
#include "graphics_allocation.h"
#include "mock.h"
#include "white_box.h"

namespace xe {
namespace ult {

template <>
struct WhiteBox<::xe::Event> : public ::xe::Event {
    using BaseClass = ::xe::Event;
    using BaseClass::allocation;
};

using Event = WhiteBox<::xe::Event>;

template<>
struct Mock<Event> : public Event {
    Mock();
    virtual ~Mock();

    MOCK_METHOD0(destroy, xe_result_t ());

    // Fake an allocation for event memory
    alignas(16) uint32_t memory = -1;
    GraphicsAllocation mockAllocation;

    using Event::allocation;
};

} // namespace ult
} // namespace xe
