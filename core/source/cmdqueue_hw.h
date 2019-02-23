#pragma once
#include "cmdqueue_imp.h"

namespace xe {

template <uint32_t gfxCoreFamily>
struct CommandQueueHw : public CommandQueueImp {
    CommandQueueHw(Device *device, void *csrRT) : CommandQueueImp(device, csrRT) {
    }

    xe_result_t createFence(const xe_fence_desc_t *desc,
                            xe_fence_handle_t *phFence) override;
    xe_result_t destroy() override;
    xe_result_t enqueueCommandLists(uint32_t numCommandLists,
                                    xe_command_list_handle_t *phCommandLists,
                                    xe_fence_handle_t hFence) override;
    xe_result_t synchronize(xe_synchronization_mode_t mode,
                            uint32_t delay,
                            uint32_t interval,
                            uint32_t timeout) override;
};

} // namespace xe
