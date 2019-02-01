#pragma once
#include "event.h"
#include "gmock/gmock.h"

namespace xe {

struct MockEvent : public Event {
    MockEvent();
    virtual ~MockEvent();
};

} // namespace xe
