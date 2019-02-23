#pragma once
#include "cmdqueue.h"
#include "host.h"
#include "xe_fence.h"

struct _xe_fence_handle_t {
};

namespace xe {

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

} // namespace xe
