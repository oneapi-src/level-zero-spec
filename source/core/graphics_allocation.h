#pragma once
#include <cstring>
#include <cstdint>

#include "memory_manager.h"

namespace NEO {
class GraphicsAllocation;
}

namespace L0 {

extern MemoryManager *globalMemoryManager;

enum class AllocationType {
    HOST = 0,
    DEVICE,
    SHARED,
};

struct Device;

struct MemAllocation {

    virtual void *getHostAddress() const = 0;
    virtual size_t getSize() const = 0;

    AllocationType allocType;
};

struct HostAllocation : public MemAllocation {
    HostAllocation() : hostBuffer(nullptr) {}

    HostAllocation(void *buffer, size_t size) : hostBuffer(buffer), bufferSize(size) {
        allocType = AllocationType::HOST;
    }

    void *getHostAddress() const override { return hostBuffer; }

    size_t getSize() const override { return bufferSize; }

    void *hostBuffer;
    size_t bufferSize;
};

struct GraphicsAllocation : public MemAllocation {
    virtual ~GraphicsAllocation() = default;
    GraphicsAllocation(const GraphicsAllocation &) = delete;
    GraphicsAllocation &operator=(GraphicsAllocation const &) = delete;

    GraphicsAllocation(NEO::GraphicsAllocation *allocationRT);
    GraphicsAllocation(void *buffer, size_t size);

    uint64_t getGpuAddress() const;
    uint64_t getGpuAddressOffsetFromHeapBase() const;
    void *getHostAddress() const override;
    size_t getSize() const override;
    void setAllocatedFromFault(bool val) { this->allocatedFromFault = val; }

    bool getAllocatedFromFault() { return this->allocatedFromFault; }

    Device *getDevice() { return deviceOwner; }

    void setDevice(Device *device) { deviceOwner = device; }

    bool allocatedFromFault = false;
    NEO::GraphicsAllocation *allocationRT = nullptr;
    Device *deviceOwner;

    // Fields Used for IPC
    size_t alignment;
    std::string shmFileName;
};

} // namespace L0
