#pragma once
#include "cmd_queue_imp.h"
#include "white_box.h"
#include "gmock/gmock.h"

namespace xe {

template <>
struct WhiteBox<CommandQueue> : public CommandQueueImp {
    WhiteBox(Device *device);
    virtual ~WhiteBox();

    using CommandQueueImp::allocation;
    using CommandQueueImp::commandStream;
    using CommandQueueImp::device;
};

struct MockCommandQueue : public CommandQueueImp {
    MockCommandQueue(Device *device = nullptr);
    virtual ~MockCommandQueue();

    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD3(enqueueCommandLists, xe_result_t(uint32_t numCommandLists,
                                                  xe_command_list_handle_t *phCommandLists,
                                                  xe_fence_handle_t hFence));
};

} // namespace xe
