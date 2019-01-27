#include "cmd_list_product_family.h"
#include "igfxfmid.h"

namespace xe {

template <typename Type>
xe_result_t CommandListHw<Type>::close() {
    return XE_RESULT_SUCCESS;
}

template <typename Type>
xe_result_t CommandListHw<Type>::destroy() {
    delete this;
    return XE_RESULT_SUCCESS;
}

template <typename Type>
xe_result_t CommandListHw<Type>::encodeWaitOnEvent(xe_event_handle_t hEvent) {
    return XE_RESULT_SUCCESS;
}

CommandList *CommandList::create(uint32_t productFamily) {
    return productFamily < IGFX_MAX_PRODUCT
        ? new CommandListHw<void>
        : nullptr;
}

} // namespace xe
