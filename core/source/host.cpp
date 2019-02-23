#include "host.h"
#include <cassert>

namespace xe {

xe_result_t Host::signalEvent(xe_event_handle_t hEvent) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t Host::signalMultipleEvents(uint32_t numEvents,
                                       xe_event_handle_t *phEvents) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t Host::waitOnEvent(xe_event_handle_t hEvent,
                              xe_synchronization_mode_t mode,
                              uint32_t delay,
                              uint32_t interval,
                              uint32_t timeout) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t Host::waitOnFence(xe_fence_handle_t hFence,
                              xe_synchronization_mode_t mode,
                              uint32_t delay,
                              uint32_t interval,
                              uint32_t timeout) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t Host::waitOnMultipleEvents(uint32_t numEvents,
                                       xe_event_handle_t *phEvents,
                                       xe_synchronization_mode_t mode,
                                       uint32_t delay,
                                       uint32_t interval,
                                       uint32_t timeout) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t Host::waitOnMultipleFences(uint32_t numFences,
                                       xe_fence_handle_t *phFences,
                                       xe_synchronization_mode_t mode,
                                       uint32_t delay,
                                       uint32_t interval,
                                       uint32_t timeout) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

static Host hostImp;
Host *Host::host = &hostImp;

} // namespace xe
