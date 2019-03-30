#include "device.h"
#include "memory_manager.h"
#include "runtime/platform/platform.h"
#include "gmock/gmock.h"

namespace L0 {

TEST(MemoryManagerallocateDeviceMemory, returnsGraphicsAllocation) {
    auto platform = OCLRT::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    auto deviceRT = platform->getDevice(0);
    ASSERT_NE(nullptr, deviceRT);
    auto device = Device::create(deviceRT);

    auto memoryManager = device->getMemoryManager();
    auto allocation = memoryManager->allocateDeviceMemory(16u, 16u);
    EXPECT_NE(nullptr, allocation);

    memoryManager->freeMemory(allocation);

    delete device;
}

} // namespace L0
