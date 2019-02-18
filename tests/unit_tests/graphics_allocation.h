#pragma once
#include <cstring>
#include <cstdint>

namespace OCLRT {
class GraphicsAllocation;
}

namespace xe {

struct GraphicsAllocation {
    GraphicsAllocation(const GraphicsAllocation &) = delete;
    GraphicsAllocation &operator=(GraphicsAllocation const &) = delete;

    GraphicsAllocation(OCLRT::GraphicsAllocation *allocationRT);
    GraphicsAllocation(void *buffer, size_t size);

    uint64_t getGpuAddress() const;
    void *getHostAddress() const;

    OCLRT::GraphicsAllocation *allocationRT = nullptr;
};

} // namespace xe
