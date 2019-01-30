#include "graphics_allocation.h"
#include "runtime/memory_manager/graphics_allocation.h"

namespace xe {

GraphicsAllocation::GraphicsAllocation(OCLRT::GraphicsAllocation *allocationRT)
    : allocationRT(allocationRT) {
}

GraphicsAllocation::GraphicsAllocation(void *buffer, size_t size) {
    allocationRT = new OCLRT::GraphicsAllocation(buffer, reinterpret_cast<uint64_t>(buffer), 0, size, 1, false);
}

OCLRT::GraphicsAllocation *allocationRT;

} // namespace xe
