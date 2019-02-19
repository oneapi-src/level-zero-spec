#pragma once
#include "xe_event.h"

struct _xe_event_handle_t {
};

namespace xe {
struct Device;
struct GraphicsAllocation;

struct Event : public _xe_event_handle_t {
    static Event *create(Device *device);

    virtual xe_result_t destroy();

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

xe_result_t __xecall
  xeEventDestroy(
    xe_event_handle_t hEvent                        ///< [in] handle of event object to destroy
    );

} // namespace xe
