#include "cmdqueue_hw.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/helpers/hw_info.h"

namespace xe {

template <uint32_t gfxCoreFamily>
xe_result_t CommandQueueHw<gfxCoreFamily>::enqueueCommandLists(uint32_t numCommandLists,
                                                               xe_command_list_handle_t *phCommandLists,
                                                               xe_fence_handle_t hFence) {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(gfxCoreFamily)>::GfxFamily;

    void *buffer;
    for (auto i = 0u; i < numCommandLists; ++i) {
        using MI_BATCH_BUFFER_START = typename GfxFamily::MI_BATCH_BUFFER_START;
        MI_BATCH_BUFFER_START cmd = GfxFamily::cmdInitBatchBufferStart;
        buffer = commandStream->getSpace(sizeof(cmd));

        cmd.setSecondLevelBatchBuffer(MI_BATCH_BUFFER_START::SECOND_LEVEL_BATCH_BUFFER_SECOND_LEVEL_BATCH);
        *(MI_BATCH_BUFFER_START *)buffer = cmd;
    }

    {
        using MI_BATCH_BUFFER_END = typename GfxFamily::MI_BATCH_BUFFER_END;
        MI_BATCH_BUFFER_END cmd = GfxFamily::cmdInitBatchBufferEnd;
        buffer = commandStream->getSpace(sizeof(cmd));

        *(MI_BATCH_BUFFER_END *)buffer = cmd;
    }

    return XE_RESULT_SUCCESS;
}

} // namespace xe
