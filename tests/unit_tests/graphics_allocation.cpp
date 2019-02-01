#include "graphics_allocation.h"
#include "runtime/memory_manager/graphics_allocation.h"
#include <cassert>

namespace xe {

GraphicsAllocation::GraphicsAllocation(OCLRT::GraphicsAllocation *allocationRT)
    : allocationRT(allocationRT) {
}

GraphicsAllocation::GraphicsAllocation(void *buffer, size_t size) {
    allocationRT = new OCLRT::GraphicsAllocation(buffer, reinterpret_cast<uint64_t>(buffer), 0, size, 1, false);
}

uint64_t GraphicsAllocation::getGpuAddress() const {
    assert(allocationRT);
    return allocationRT->getGpuAddress();
}

} // namespace xe
