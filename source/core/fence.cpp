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

    xe_result_t hostSynchronize(uint32_t timeout) override { return XE_RESULT_ERROR_UNSUPPORTED; }

    xe_result_t queryElapsedTime(xe_fence_handle_t hFenceEnd, double *pTime) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t queryStatus() override {
        auto hostAddr = static_cast<uint64_t *>(allocation->getHostAddress());
        return *hostAddr == Fence::STATE_CLEARED ? XE_RESULT_NOT_READY : XE_RESULT_SUCCESS;
    }

    xe_result_t queryValue() override { return XE_RESULT_ERROR_UNSUPPORTED; }

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

    return true;
}

xe_result_t FenceImp::reset() {
    auto hostAddress = static_cast<uint64_t *>(allocation->getHostAddress());
    *(hostAddress) = Fence::STATE_CLEARED;

    // Flush cache line at all levels containing the value
    _mm_clflush(hostAddress);

    return XE_RESULT_SUCCESS;
}

xe_result_t fenceQueryElapsedTime(xe_fence_handle_t hFenceStart, xe_fence_handle_t hFenceEnd,
                                  double *pTime) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t fenceDestroy(xe_fence_handle_t phFence) {
    return Fence::fromHandle(phFence)->destroy();
}

} // namespace L0
