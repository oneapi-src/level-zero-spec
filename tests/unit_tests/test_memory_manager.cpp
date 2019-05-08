#include "device.h"
#include "memory_manager.h"
#include "graphics_allocation.h"
#include "runtime/platform/platform.h"
#include "gmock/gmock.h"
#include "global_fixture.h"

namespace L0 {
namespace ult {

struct MemoryManagerAllocateHostMemory : public GlobalFixtureTest {};

TEST_F(MemoryManagerAllocateHostMemory, returnsHostBuffer) {
    auto platform = NEO::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    void *ptr = globalMemoryManager->allocateHostMemory(16u, 16u);
    EXPECT_NE(nullptr, ptr);

    globalMemoryManager->freeMemory(ptr);
}

struct MemoryManagerAllocateDeviceMemory : public GlobalFixtureTest {};

TEST_F(MemoryManagerAllocateDeviceMemory, returnsGraphicsAllocation) {
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

struct MemoryManagerGetAddressRange : public GlobalFixtureTest {};

TEST_F(MemoryManagerGetAddressRange, returnsRange) {
    auto platform = NEO::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    auto deviceRT = platform->getDevice(0);
    ASSERT_NE(nullptr, deviceRT);
    auto device = Device::create(deviceRT);

    auto allocation = globalMemoryManager->allocateDeviceMemory(device, 16u, 16u);
    EXPECT_NE(nullptr, allocation);

    void *base;
    size_t size;
    void *allocAddress = allocation->getHostAddress();
    xe_result_t res =
        globalMemoryManager->getAddressRange(allocAddress, &base, &size);
    ASSERT_EQ(base, allocAddress);
    ASSERT_EQ(size, 16u);

    globalMemoryManager->freeMemory(allocation);

    delete device;
}
} // namespace ult
} // namespace L0
