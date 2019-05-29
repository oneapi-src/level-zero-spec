#include "device.h"
#include "memory_manager.h"
#include "graphics_allocation.h"
#include "runtime/platform/platform.h"
#include "gmock/gmock.h"
#include "global_fixture.h"

namespace L0 {
namespace ult {

struct MemoryManagerAllocateMemory : public GlobalFixtureTest {};

TEST_F(MemoryManagerAllocateMemory, returnsHostBuffer) {
    auto platform = NEO::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    void *ptr = globalMemoryManager->allocateHostMemory(16u, 16u);
    EXPECT_NE(nullptr, ptr);

    globalMemoryManager->freeMemory(ptr);
}

TEST_F(MemoryManagerAllocateMemory, returnsGraphicsAllocation) {
    auto platform = NEO::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    auto deviceRT = platform->getDevice(0);
    ASSERT_NE(nullptr, deviceRT);
    auto device = Device::create(deviceRT);

    auto allocation = globalMemoryManager->allocateDeviceMemory(device, 16u, 16u);
    EXPECT_NE(nullptr, allocation);

    globalMemoryManager->freeGraphicsAllocation(allocation);

    delete device;
}

TEST_F(MemoryManagerAllocateMemory, returnsRange) {
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
    globalMemoryManager->getAddressRange(allocAddress, &base, &size);
    ASSERT_EQ(base, allocAddress);
    ASSERT_EQ(size, 16u);

    globalMemoryManager->freeGraphicsAllocation(allocation);

    delete device;
}

TEST_F(MemoryManagerAllocateMemory, lookForAllocationForAddressOtherThanBase) {
    auto platform = NEO::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    auto deviceRT = platform->getDevice(0);
    ASSERT_NE(nullptr, deviceRT);
    auto device = Device::create(deviceRT);

    size_t bufferSize = 4096u;
    auto allocation = globalMemoryManager->allocateDeviceMemory(device, bufferSize, 16u);
    EXPECT_NE(nullptr, allocation);

    uint64_t allocAddress = reinterpret_cast<uint64_t>(allocation->getHostAddress());

    void *testAddress = reinterpret_cast<void *>(allocAddress + bufferSize / 2);
    auto alloc = globalMemoryManager->findGraphicsAllocation(testAddress);
    ASSERT_NE(alloc, nullptr);

    testAddress = reinterpret_cast<void *>(allocAddress + bufferSize * 2);
    alloc = globalMemoryManager->findGraphicsAllocation(testAddress);
    ASSERT_EQ(alloc, nullptr);

    globalMemoryManager->freeGraphicsAllocation(allocation);

    delete device;
}

} // namespace ult
} // namespace L0
