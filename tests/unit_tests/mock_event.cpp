#pragma once
#include "mock_event.h"

namespace xe {

MockEvent::MockEvent() :
    mockAllocation(&memory, sizeof(memory)) {
    allocation = &mockAllocation;
}

MockEvent::~MockEvent() {
}

} // namespace xe
