#pragma once
#include "fence.h"
#include "graphics_allocation.h"
#include "cmdqueue.h"
#include "cmdqueue_imp.h"
#include "mock.h"
#include "white_box.h"

namespace L0 {
namespace ult {

template <> struct WhiteBox<::L0::Fence> : public ::L0::Fence {
    using BaseClass = ::L0::Fence;
    using BaseClass::allocation;
};

using Fence = WhiteBox<::L0::Fence>;

template <> struct Mock<Fence> : public Fence {
    Mock();
    virtual ~Mock();

    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD1(hostSynchronize, xe_result_t(uint32_t timeout));
    MOCK_METHOD2(queryElapsedTime, xe_result_t(xe_event_handle_t hFenceEnd, double *pTime));
    MOCK_METHOD0(queryStatus, xe_result_t());
    MOCK_METHOD0(reset, xe_result_t());

    // Fake an allocation for event memory
    alignas(16) uint32_t memory = -1;
    GraphicsAllocation mockAllocation;

    using Fence::allocation;
};

} // namespace ult
} // namespace L0
