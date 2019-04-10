#include "mock_memory_manager.h"
#include "graphics_allocation.h"
#include "runtime/helpers/aligned_memory.h"

namespace L0 {
namespace ult {

using ::testing::AnyNumber;
using ::testing::Invoke;
using ::testing::An;

static GraphicsAllocation *createGraphicsAllocation(size_t size, size_t alignment) {
    auto buffer = alignedMalloc(size, alignment);
    return new GraphicsAllocation(buffer, size);
}

static void freeGraphicsAllocation(GraphicsAllocation *allocation) {
    assert(allocation);
    auto buffer = reinterpret_cast<uint8_t *>(allocation->getGpuAddress());
    alignedFree(buffer);
}

static void freePtr(const void *ptr) {
    assert(ptr);
    alignedFree(const_cast<void *>(ptr));
}

Mock<MemoryManager>::Mock() {
    using MockMemoryManager = Mock<::L0::MemoryManager>;
    ON_CALL(*this, allocateDeviceMemory)
        .WillByDefault(Invoke(createGraphicsAllocation));

    EXPECT_CALL(*this, allocateManagedMemory)
        .WillRepeatedly(Invoke(createGraphicsAllocation));

    EXPECT_CALL(*this, freeMemory(An<GraphicsAllocation *>()))
        .WillRepeatedly(Invoke(freeGraphicsAllocation));

    EXPECT_CALL(*this, freeMemory(An<const void *>()))
        .WillRepeatedly(Invoke(freePtr));
}

Mock<MemoryManager>::~Mock() {
}

} // namespace ult
} // namespace L0
