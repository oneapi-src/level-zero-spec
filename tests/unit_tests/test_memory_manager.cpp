#include "device.h"
#include "memory_manager.h"
#include "runtime/platform/platform.h"
#include "gmock/gmock.h"

namespace xe {

TEST(MemoryManagerallocateDeviceMemory, returnsGraphicsAllocation) {
    auto platform = OCLRT::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    auto deviceRT = platform->getDevice(0);
    ASSERT_NE(nullptr, deviceRT);
    auto device = Device::create(deviceRT);

    auto memoryManager = device->getMemoryManager();
    auto allocation = memoryManager->allocateDeviceMemory();
    EXPECT_NE(nullptr, allocation);

    memoryManager->freeMemory(allocation);

    delete device;
}

} // namespace xe
