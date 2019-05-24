#include "fence.h"
#include "memory_manager.h"

namespace L0 {

struct FenceImp : public Fence {
    FenceImp(CommandQueueImp *cmdQueue) : cmdQueue(cmdQueue) {}

    ~FenceImp() {
        globalMemoryManager->freeGraphicsAllocation(allocation);
        allocation = nullptr;
    }

    xe_result_t destroy() override {
        delete this;
        return XE_RESULT_SUCCESS;
    }

    xe_result_t hostSynchronize(uint32_t timeout) override;

    xe_result_t queryStatus() override {
        if (enqueueState == Fence::ENQUEUE_NOT_READY) {
            return XE_RESULT_ERROR_INVALID_PARAMETER;
        }

        auto hostAddr = static_cast<uint64_t *>(allocation->getHostAddress());
        return *hostAddr == Fence::STATE_CLEARED ? XE_RESULT_NOT_READY : XE_RESULT_SUCCESS;
    }

    xe_result_t reset() override;

    static Fence *fromHandle(xe_fence_handle_t handle) { return static_cast<Fence *>(handle); }

    inline xe_fence_handle_t toHandle() { return this; }

    bool initialize();

  protected:
    CommandQueueImp *cmdQueue;
};

Fence *Fence::create(CommandQueueImp *cmdQueue, const xe_fence_desc_t *desc) {
    auto fence = new FenceImp(cmdQueue);
    assert(fence);

    fence->initialize();

    return fence;
}

bool FenceImp::initialize() {
    assert(globalMemoryManager);
    allocation = globalMemoryManager->allocateManagedMemory(cmdQueue->getDevice(), 64u, 64u);
    assert(allocation);

    reset();

    enqueueState = Fence::ENQUEUE_NOT_READY;

    return true;
}

xe_result_t FenceImp::reset() {
    auto hostAddress = static_cast<uint64_t *>(allocation->getHostAddress());
    *(hostAddress) = Fence::STATE_CLEARED;

    // Flush cache line at all levels containing the value
    _mm_clflush(hostAddress);

    return XE_RESULT_SUCCESS;
}

xe_result_t FenceImp::hostSynchronize(uint32_t timeout) {
    uint32_t timeArg = timeout;
    std::chrono::high_resolution_clock::time_point time1, time2;
    int64_t timeDiff = 0;
    xe_result_t ret = XE_RESULT_NOT_READY;

    if (enqueueState == Fence::ENQUEUE_NOT_READY) {
        return XE_RESULT_ERROR_INVALID_PARAMETER;
    }

    if (timeout == 0) {
        return queryStatus();
    }

    /* Block until timeout. If Event is Signaled, then return immediately */
    time1 = std::chrono::high_resolution_clock::now();
    while (timeDiff < timeout) {
        ret = queryStatus();
        if (ret == XE_RESULT_SUCCESS) {
            return XE_RESULT_SUCCESS;
        }

        std::this_thread::yield();
        _mm_pause();

        time2 = std::chrono::high_resolution_clock::now();
        // TODO: We may need to use nanosecs here. Pending gitlab issue
        // resolution
        timeDiff = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count();
    }

    return ret;
}

xe_result_t fenceDestroy(xe_fence_handle_t phFence) {
    return Fence::fromHandle(phFence)->destroy();
}

} // namespace L0
