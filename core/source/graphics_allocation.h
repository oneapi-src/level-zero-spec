#pragma once
#include <cstring>
#include <cstdint>

namespace NEO {
class GraphicsAllocation;
}

namespace L0 {

struct GraphicsAllocation {
    GraphicsAllocation(const GraphicsAllocation &) = delete;
    GraphicsAllocation &operator=(GraphicsAllocation const &) = delete;

    GraphicsAllocation(NEO::GraphicsAllocation *allocationRT);
    GraphicsAllocation(void *buffer, size_t size);

    uint64_t getGpuAddress() const;
    uint64_t getGpuAddressOffsetFromHeapBase() const;
    void *getHostAddress() const;
    size_t getSize() const;
    void setAllocatedFromFault(bool val) {
        this->allocatedFromFault = val;
    }

    bool getAllocatedFromFault() {
        return this->allocatedFromFault;
    }

    void setAllocatedFromCL(bool val) {
        this->allocatedFromCL = val;
    }

    bool getAllocatedFromCL() {
        return this->allocatedFromCL;
    }

    bool allocatedFromFault = false;
    bool allocatedFromCL = false;
    NEO::GraphicsAllocation *allocationRT = nullptr;
};

} // namespace L0
