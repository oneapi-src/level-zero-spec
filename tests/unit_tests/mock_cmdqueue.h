#pragma once
#include "cmd_queue_imp.h"
#include "white_box.h"
#include "gmock/gmock.h"

template <>
struct WhiteBox<xe::CommandQueue> : public xe::CommandQueueImp {
    WhiteBox(xe::Device *device) : xe::CommandQueueImp(device) {
    }

    using xe::CommandQueueImp::allocation;
    using xe::CommandQueueImp::commandStream;
    using xe::CommandQueueImp::device;
};

namespace xe {

struct MockCommandQueue : public CommandQueueImp {
    MockCommandQueue(Device *device = nullptr)
        : CommandQueueImp(device) {
    }

    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD3(enqueueCommandLists, xe_result_t(uint32_t numCommandLists,
                                                  xe_command_list_handle_t *phCommandLists,
                                                  xe_fence_handle_t hFence));
};

} // namespace xe
