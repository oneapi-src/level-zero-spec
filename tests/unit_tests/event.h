#pragma once
#include "xe_event.h"

namespace xe {

struct Event {
    static Event *create();

    static Event *fromHandle(xe_event_handle_t handle) {
        return static_cast<Event *>(handle.pDriverData);
    }

    inline xe_event_handle_t toHandle() const {
        xe_event_handle_t handle;
        handle.pDriverData = const_cast<Event *>(this);
        return handle;
    }
};

} // namespace xe
