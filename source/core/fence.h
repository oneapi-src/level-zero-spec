#pragma once
#include "cmdqueue.h"
#include "cmdqueue_imp.h"
#include "xe_fence.h"
#include "graphics_allocation.h"

struct _xe_fence_handle_t {};

namespace L0 {

struct Fence : public _xe_fence_handle_t {
    static Fence *create(CommandQueueImp *cmdQueue, const xe_fence_desc_t *desc);
    virtual xe_result_t destroy() = 0;
    virtual xe_result_t hostSynchronize(uint32_t timeout) = 0;
    virtual xe_result_t queryElapsedTime(xe_fence_handle_t hFenceEnd, double *pTime) {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }
    virtual xe_result_t queryStatus() = 0;
    virtual xe_result_t queryValue() { return XE_RESULT_ERROR_UNSUPPORTED; }
    virtual xe_result_t reset() = 0;

    static Fence *fromHandle(xe_fence_handle_t handle) { return static_cast<Fence *>(handle); }

    inline xe_fence_handle_t toHandle() { return this; }

    enum State : uint32_t {
        STATE_SIGNALED = 0u,
        STATE_CLEARED = static_cast<uint32_t>(-1),
        STATE_INITIAL = STATE_CLEARED
    };

  protected:
    GraphicsAllocation *allocation = nullptr;
};

xe_result_t fenceQueryElapsedTime(xe_fence_handle_t hFenceStart, xe_fence_handle_t hFenceEnd,
                                  double *pTime);

xe_result_t fenceDestroy(xe_fence_handle_t *phFence);

} // namespace L0
