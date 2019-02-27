#pragma once
#include "cmdqueue.h"
#include "xe_fence.h"

struct _xe_fence_handle_t {
};

namespace L0 {

struct Fence : public _xe_fence_handle_t {
    virtual xe_result_t destroy() = 0;

    virtual xe_result_t queryElapsedTime(xe_fence_handle_t hFenceEnd,
                                         double_t *pTime) = 0;
    virtual xe_result_t queryStatus() = 0;
    virtual xe_result_t queryValue() = 0;
    virtual xe_result_t reset() = 0;

    static Fence *fromHandle(xe_fence_handle_t handle) {
        return static_cast<Fence *>(handle);
    }

    inline xe_fence_handle_t toHandle() {
        return this;
    }
};

xe_result_t fenceQueryElapsedTime(xe_fence_handle_t hFenceStart,
                                  xe_fence_handle_t hFenceEnd,
                                  double_t *pTime);

xe_result_t hostWaitOnFence(xe_fence_handle_t hFence,
                            xe_synchronization_mode_t mode,
                            uint32_t delay,
                            uint32_t interval,
                            uint32_t timeout);

xe_result_t hostWaitOnMultipleFences(uint32_t numFences,
                                     xe_fence_handle_t *phFences,
                                     xe_synchronization_mode_t mode,
                                     uint32_t delay,
                                     uint32_t interval,
                                     uint32_t timeout);

} // namespace L0
