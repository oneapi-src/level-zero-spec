#include "mock_cmdlist.h"
#include "graphics_allocation.h"

namespace L0 {
namespace ult {

WhiteBox<::L0::CommandList>::WhiteBox(Device *device) {
}

WhiteBox<::L0::CommandList>::~WhiteBox() {
}

Mock<CommandList>::Mock(Device *device) : WhiteBox<::L0::CommandList>(device) {
    size_t batchBufferSize = 65536u;
    batchBuffer = new uint8_t[batchBufferSize];
    mockAllocation = new GraphicsAllocation(batchBuffer, batchBufferSize);
    allocation = mockAllocation;
}

Mock<CommandList>::~Mock() {
    allocation = nullptr;
    delete mockAllocation;
    delete[] batchBuffer;
}

} // namespace ult
} // namespace L0
