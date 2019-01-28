#include "cmd_list_product_family.h"

namespace xe {

template <uint32_t productFamily>
xe_result_t CommandListProductFamily<productFamily>::close() {
    return XE_RESULT_SUCCESS;
}

template <uint32_t productFamily>
xe_result_t CommandListProductFamily<productFamily>::destroy() {
    delete this;
    return XE_RESULT_SUCCESS;
}

template <uint32_t productFamily>
xe_result_t CommandListProductFamily<productFamily>::encodeWaitOnEvent(xe_event_handle_t hEvent) {
    return XE_RESULT_SUCCESS;
}

} // namespace xe
