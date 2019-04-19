#include "mock_memory_manager.h"
#include "graphics_allocation.h"
#include "runtime/helpers/aligned_memory.h"

namespace L0 {
namespace ult {

using ::testing::An;
using ::testing::AnyNumber;
using ::testing::Invoke;

static GraphicsAllocation *createGraphicsAllocation(size_t size, size_t alignment) {
    auto buffer = alignedMalloc(size, alignment);
    return new GraphicsAllocation(buffer, size);
}

static PtrOwn<GraphicsAllocation> createGraphicsAllocationForIsa(PtrRef<const void> isaHostMem,
                                                                 size_t size) {
    auto buffer = alignedMalloc(size, 64);
    return PtrOwn<GraphicsAllocation>(new GraphicsAllocation(buffer, size));
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
    EXPECT_CALL(*this, allocateDeviceMemory)
            .WillRepeatedly(Invoke(createGraphicsAllocation));

    EXPECT_CALL(*this, allocateGraphicsMemoryForIsa)
        .WillRepeatedly(Invoke(createGraphicsAllocationForIsa));

    EXPECT_CALL(*this, allocateManagedMemory).
            WillRepeatedly(Invoke(createGraphicsAllocation));

    EXPECT_CALL(*this, freeMemory(An<GraphicsAllocation *>()))
        .WillRepeatedly(Invoke(freeGraphicsAllocation));

    EXPECT_CALL(*this, freeMemory(An<const void *>()))
        .WillRepeatedly(Invoke(freePtr));

    EXPECT_CALL(*this, getIsaHeapGpuAddress).Times(AnyNumber());
}

Mock<MemoryManager>::~Mock() {}

} // namespace ult
} // namespace L0
