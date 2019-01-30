#pragma once

namespace OCLRT {
class GraphicsAllocation;
}

namespace xe {

struct GraphicsAllocation {
    GraphicsAllocation(OCLRT::GraphicsAllocation *allocationRT);
    GraphicsAllocation(void *buffer, size_t size);

    OCLRT::GraphicsAllocation *allocationRT = nullptr;
};

} // namespace xe
