#pragma once
#include "cmd_queue.h"
#include "gmock/gmock.h"

namespace xe {

struct MockCommandQueue : public CommandQueue {
    MOCK_METHOD3(enqueueCommandLists, xe_result_t(uint32_t numCommandLists,
                                                  xe_command_list_handle_t *phCommandLists,
                                                  xe_fence_handle_t hFence));
};

} // namespace xe
