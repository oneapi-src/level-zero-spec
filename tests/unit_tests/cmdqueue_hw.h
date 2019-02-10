#pragma once
#include "cmdqueue_imp.h"

namespace xe {

template <uint32_t gfxCoreFamily>
struct CommandQueueHw : public CommandQueueImp {
    CommandQueueHw(Device *device, void *csrRT) : CommandQueueImp(device, csrRT) {
    }

    xe_result_t enqueueCommandLists(uint32_t numCommandLists,
                                    xe_command_list_handle_t *phCommandLists,
                                    xe_fence_handle_t hFence) override;
};

} // namespace xe
