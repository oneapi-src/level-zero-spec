#include "graphics_allocation.h"
#include "runtime/memory_manager/graphics_allocation.h"
#include <cassert>

namespace L0 {

GraphicsAllocation::GraphicsAllocation(NEO::GraphicsAllocation *allocationRT)
    : allocationRT(allocationRT) {}

GraphicsAllocation::GraphicsAllocation(void *buffer, size_t size) {
    allocationRT = new NEO::GraphicsAllocation(NEO::GraphicsAllocation::AllocationType::INTERNAL_HOST_MEMORY,
                                               buffer, reinterpret_cast<uint64_t>(buffer), 0, size,
                                               MemoryPool::System4KBPages, true);
}

uint64_t GraphicsAllocation::getGpuAddress() const {
    assert(allocationRT);
    return allocationRT->getGpuAddress();
}

uint64_t GraphicsAllocation::getGpuAddressOffsetFromHeapBase() const {
    assert(allocationRT);
    return allocationRT->getGpuAddressToPatch();
}

void *GraphicsAllocation::getHostAddress() const {
    assert(allocationRT);
    return allocationRT->getUnderlyingBuffer();
}

size_t GraphicsAllocation::getSize() const {
    assert(allocationRT);
    return allocationRT->getUnderlyingBufferSize();
}

} // namespace L0
