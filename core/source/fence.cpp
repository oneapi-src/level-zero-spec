#pragma once
#include "fence.h"

namespace xe {

struct FenceImp : public Fence {
    xe_result_t destroy() override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t queryElapsedTime(xe_fence_handle_t hFenceEnd,
                                         double_t *pTime) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t queryStatus() override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t queryValue() override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t reset() override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    static Fence *fromHandle(xe_fence_handle_t handle) {
        return static_cast<Fence *>(handle);
    }

    inline xe_fence_handle_t toHandle() {
        return this;
    }
};

xe_result_t fenceQueryElapsedTime(xe_fence_handle_t hFenceStart,
                                  xe_fence_handle_t hFenceEnd,
                                  double_t *pTime) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

} // namespace xe
