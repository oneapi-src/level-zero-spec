#include "fence.h"

namespace L0 {

struct FenceImp : public Fence {
    xe_result_t destroy() override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t hostSynchronize(uint32_t timeout) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t queryElapsedTime(xe_fence_handle_t hFenceEnd,
                                 double *pTime) override {
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
                                  double *pTime) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

} // namespace L0
