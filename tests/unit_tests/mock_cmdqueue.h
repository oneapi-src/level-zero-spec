#pragma once
#include "cmdqueue_imp.h"
#include "white_box.h"
#include "mock.h"

namespace L0 {
namespace ult {

template <>
struct WhiteBox<::L0::CommandQueue> : public ::L0::CommandQueueImp {
    using BaseClass = ::L0::CommandQueueImp;
    using BaseClass::allocation;
    using BaseClass::commandStream;
    using BaseClass::csrRT;
    using BaseClass::device;

    WhiteBox(Device *device, void *csrRT);
    virtual ~WhiteBox();
};

using CommandQueue = WhiteBox<::L0::CommandQueue>;

template <>
struct Mock<CommandQueue> : public CommandQueue {
    Mock(Device *device = nullptr, void *csrRT = nullptr);
    virtual ~Mock();

    MOCK_METHOD2(createFence, xe_result_t(const xe_fence_desc_t *desc,
                                          xe_fence_handle_t *phFence));
    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD3(enqueueCommandLists, xe_result_t(uint32_t numCommandLists,
                                                  xe_command_list_handle_t *phCommandLists,
                                                  xe_fence_handle_t hFence));
    MOCK_METHOD4(synchronize, xe_result_t(xe_synchronization_mode_t mode,
                                          uint32_t delay,
                                          uint32_t interval,
                                          uint32_t timeout));

    MOCK_METHOD1(dispatchTaskCountWrite, void(bool flushDataCache));
};

} // namespace ult
} // namespace L0
