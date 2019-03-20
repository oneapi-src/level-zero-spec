#pragma once
#include <cstring>
#include <cstdint>

namespace OCLRT {
class GraphicsAllocation;
}

namespace L0 {

struct GraphicsAllocation {
    GraphicsAllocation(const GraphicsAllocation &) = delete;
    GraphicsAllocation &operator=(GraphicsAllocation const &) = delete;

    GraphicsAllocation(OCLRT::GraphicsAllocation *allocationRT);
    GraphicsAllocation(void *buffer, size_t size);

    uint64_t getGpuAddress() const;
    uint64_t getGpuAddressOffsetFromHeapBase() const;
    void *getHostAddress() const;
    size_t getSize() const;
    void setAllocatedFromFault(bool val) {
        this->allocatedFromFault = val;
    }

    bool getAllocatedFromFault(){
        return this->allocatedFromFault;
    }

    bool allocatedFromFault = false;
    OCLRT::GraphicsAllocation *allocationRT = nullptr;
};

} // namespace L0
