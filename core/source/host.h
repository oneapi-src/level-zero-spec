#pragma once
#include "xe_common.h"

namespace xe {

struct Host {
    xe_result_t signalEvent(xe_event_handle_t hEvent);
    xe_result_t signalMultipleEvents(uint32_t numEvents,
                                     xe_event_handle_t *phEvents);
    xe_result_t waitOnEvent(xe_event_handle_t hEvent,
                            xe_synchronization_mode_t mode,
                            uint32_t delay,
                            uint32_t interval,
                            uint32_t timeout);
    xe_result_t waitOnFence(xe_fence_handle_t hFence,
                            xe_synchronization_mode_t mode,
                            uint32_t delay,
                            uint32_t interval,
                            uint32_t timeout);
    xe_result_t waitOnMultipleEvents(uint32_t numEvents,
                                     xe_event_handle_t *phEvents,
                                     xe_synchronization_mode_t mode,
                                     uint32_t delay,
                                     uint32_t interval,
                                     uint32_t timeout);
    xe_result_t waitOnMultipleFences(uint32_t numFences,
                                     xe_fence_handle_t *phFences,
                                     xe_synchronization_mode_t mode,
                                     uint32_t delay,
                                     uint32_t interval,
                                     uint32_t timeout);

    static Host *get() {
        return host;
    }

  protected:
    static Host *host;
};

} // namespace xe