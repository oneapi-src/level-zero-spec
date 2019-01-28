#include "cmd_list_gfxcore_family.h"
#include "runtime/helpers/hw_info.h"

namespace xe {

template <uint32_t gfxCoreFamily>
xe_result_t CommandListGfxCoreFamily<gfxCoreFamily>::close() {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(gfxCoreFamily)>::GfxFamily;
    using MI_BATCH_BUFFER_END = typename GfxFamily::MI_BATCH_BUFFER_END;

    MI_BATCH_BUFFER_END bbe;
    (void)bbe;

    return XE_RESULT_SUCCESS;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListGfxCoreFamily<gfxCoreFamily>::encodeWaitOnEvent(xe_event_handle_t hEvent) {
    return XE_RESULT_SUCCESS;
}

} // namespace xe
