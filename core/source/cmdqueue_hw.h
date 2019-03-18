#pragma once
#include "cmdqueue_imp.h"

namespace L0 {

template <GFXCORE_FAMILY gfxCoreFamily>
struct CommandQueueHw : public CommandQueueImp {
    using CommandQueueImp::CommandQueueImp;

    xe_result_t createFence(const xe_fence_desc_t *desc,
                            xe_fence_handle_t *phFence) override;
    xe_result_t destroy() override;
    xe_result_t executeCommandLists(uint32_t numCommandLists,
                                    xe_command_list_handle_t *phCommandLists,
                                    xe_fence_handle_t hFence) override;

    void dispatchTaskCountWrite(bool flushDataCache) override;
};

} // namespace L0
