#pragma once
#include "cmdqueue_imp.h"
#include "white_box.h"
#include "mock.h"

namespace xe {
namespace ult {

template <>
struct WhiteBox<::xe::CommandQueue> : public ::xe::CommandQueueImp {
    using BaseClass = ::xe::CommandQueueImp;
    using BaseClass::allocation;
    using BaseClass::commandStream;
    using BaseClass::csrRT;
    using BaseClass::device;

    WhiteBox(Device *device, void *csrRT);
    virtual ~WhiteBox();
};

using CommandQueue = WhiteBox<::xe::CommandQueue>;

template <>
struct Mock<CommandQueue> : public CommandQueue {
    Mock(Device *device = nullptr, void *csrRT = nullptr);
    virtual ~Mock();

    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD3(enqueueCommandLists, xe_result_t(uint32_t numCommandLists,
                                                  xe_command_list_handle_t *phCommandLists,
                                                  xe_fence_handle_t hFence));
};

} // namespace ult
} // namespace xe
