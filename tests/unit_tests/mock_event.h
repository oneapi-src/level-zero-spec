#pragma once
#include "event.h"
#include "graphics_allocation.h"
#include "gmock/gmock.h"

namespace xe {

struct MockEvent : public Event {
    MockEvent();
    virtual ~MockEvent();

    // Fake an allocation for event memory
    alignas(16) uint32_t memory = -1;
    GraphicsAllocation mockAllocation;

    using Event::allocation;
};

} // namespace xe
