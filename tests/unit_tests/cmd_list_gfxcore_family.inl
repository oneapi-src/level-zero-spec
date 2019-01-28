#include "cmd_list_gfxcore_family.h"

namespace xe {

template <uint32_t gfxCoreFamily>
xe_result_t CommandListGfxCoreFamily<gfxCoreFamily>::close() {
    return XE_RESULT_SUCCESS;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListGfxCoreFamily<gfxCoreFamily>::destroy() {
    delete this;
    return XE_RESULT_SUCCESS;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListGfxCoreFamily<gfxCoreFamily>::encodeWaitOnEvent(xe_event_handle_t hEvent) {
    return XE_RESULT_SUCCESS;
}

} // namespace xe
