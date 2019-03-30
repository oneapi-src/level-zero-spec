#include "mock_memory_manager.h"
#include "graphics_allocation.h"
#include "runtime/helpers/aligned_memory.h"

namespace L0 {
namespace ult {

using ::testing::AnyNumber;
using ::testing::Invoke;

static GraphicsAllocation *createGraphicsAllocation(size_t size, size_t alignment) {
    auto buffer = alignedMalloc(size, alignment);
    return new GraphicsAllocation(buffer, size);
}

static void freeGraphicsAllocation(GraphicsAllocation *allocation) {
    assert(allocation);
    auto buffer = reinterpret_cast<uint8_t *>(allocation->getGpuAddress());
    alignedFree(buffer);
}

Mock<MemoryManager>::Mock() {
    using MockMemoryManager = Mock<::L0::MemoryManager>;
    ON_CALL(*this, allocateDeviceMemory)
        .WillByDefault(Invoke(createGraphicsAllocation));

    ON_CALL(*this, allocateManagedMemory)
        .WillByDefault(Invoke(createGraphicsAllocation));

    ON_CALL(*this, freeMemory)
        .WillByDefault(Invoke(freeGraphicsAllocation));
}

Mock<MemoryManager>::~Mock() {
}

} // namespace ult
} // namespace L0
