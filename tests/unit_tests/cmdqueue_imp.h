#pragma once
#include "cmdqueue.h"

namespace OCLRT {
class LinearStream;
}

namespace xe {
struct GraphicsAllocation;

struct CommandQueueImp : public CommandQueue {
    CommandQueueImp(Device *device)
        : device(device),
        allocation(nullptr),
        commandStream(nullptr) {
    }

    xe_result_t destroy() override;
    xe_result_t enqueueCommandLists(uint32_t numCommandLists,
                                    xe_command_list_handle_t *phCommandLists,
                                    xe_fence_handle_t hFence) override;

    void initialize();

  protected:
    Device *device;
    GraphicsAllocation *allocation;
    OCLRT::LinearStream *commandStream;
};

} // namespace xe
