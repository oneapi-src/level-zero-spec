#include "device.h"
#include "memory_manager.h"
#include "runtime/platform/platform.h"
#include "gmock/gmock.h"

namespace L0 {

TEST(MemoryManagerallocateHostMemory, returnsHostBuffer) {
    auto platform = NEO::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    void *ptr = globalMemoryManager->allocateHostMemory(16u, 16u);
    EXPECT_NE(nullptr, ptr);

    globalMemoryManager->freeMemory(ptr);
}

TEST(MemoryManagerallocateDeviceMemory, returnsGraphicsAllocation) {
    auto platform = NEO::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    auto deviceRT = platform->getDevice(0);
    ASSERT_NE(nullptr, deviceRT);
    auto device = Device::create(deviceRT);

    auto allocation = globalMemoryManager->allocateDeviceMemory(device, 16u, 16u);
    EXPECT_NE(nullptr, allocation);

    globalMemoryManager->freeMemory(allocation);

    delete device;
}

} // namespace L0
