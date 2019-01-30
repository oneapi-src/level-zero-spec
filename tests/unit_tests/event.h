#pragma once
#include "xe_event.h"

struct _xe_event_handle_t {
};

namespace xe {

struct Event : public _xe_event_handle_t {
    static Event *create();

    static Event *fromHandle(xe_event_handle_t handle) {
        return static_cast<Event *>(handle);
    }

    inline xe_event_handle_t toHandle() {
        return this;
    }
};

} // namespace xe
