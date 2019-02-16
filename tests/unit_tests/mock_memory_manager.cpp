#include "mock_memory_manager.h"
#include "graphics_allocation.h"

namespace xe {
namespace ult {

using ::testing::AnyNumber;
using ::testing::Invoke;

static GraphicsAllocation *createGraphicsAllocation(size_t size) {
    auto buffer = new uint8_t[size];
    return new GraphicsAllocation(buffer, size);
}

static void freeGraphicsAllocation(GraphicsAllocation *allocation) {
    assert(allocation);
    auto buffer = reinterpret_cast<uint8_t *>(allocation->getGpuAddress());
    delete[] buffer;
    delete allocation;
}

Mock<MemoryManager>::Mock() {
    using MockMemoryManager = Mock<::xe::MemoryManager>;
    ON_CALL(*this, allocateDeviceMemory)
        .WillByDefault(Invoke(createGraphicsAllocation));

    ON_CALL(*this, freeMemory)
        .WillByDefault(Invoke(freeGraphicsAllocation));
}

Mock<MemoryManager>::~Mock() {
}

} // namespace ult
} // namespace xe
