#include "graphics_allocation.h"
#include "memory_manager.h"
#include "mock_device.h"
#include "mock_memory_manager.h"
#include "xe_memory.h"
#include "gmock/gmock.h"

namespace xe {

xe_result_t __xecall
xeSharedMemAlloc(
    xe_mem_allocator_handle_t hMemAllocHandle,
    xe_device_handle_t hDevice,
    xe_device_mem_alloc_flag_t device_flags,
    xe_host_mem_alloc_flag_t host_flags,
    size_t size,
    size_t alignment,
    void **ptr) {
    auto device = Device::fromHandle(hDevice);
    assert(device);
    auto memoryManager = device->getMemoryManager();
    assert(memoryManager);

    auto allocation = memoryManager->allocateManagedMemory(size, alignment);
    assert(allocation);
    *ptr = allocation->getHostAddress();

    return XE_RESULT_SUCCESS;
}

namespace ult {

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Return;

TEST(sharedMemAlloc, returnsValidPtr) {
    Mock<Device> device;
    Mock<MemoryManager> memoryManager;
    EXPECT_CALL(device, getMemoryManager())
        .WillRepeatedly(Return(&memoryManager));
    EXPECT_CALL(memoryManager, allocateManagedMemory(_, _)).Times(AnyNumber());
    EXPECT_CALL(memoryManager, freeMemory(_)).Times(AnyNumber());

    xe_mem_allocator_handle_t handleAllocator = {};
    xe_device_mem_alloc_flag_t flagsDevice = {};
    xe_host_mem_alloc_flag_t flagsHost = {};
    size_t size = 65536u;
    size_t alignment = 4096u;
    void *ptr = nullptr;

    auto result = ::xe::xeSharedMemAlloc(
        handleAllocator,
        device.toHandle(),
        flagsDevice,
        flagsHost,
        size,
        alignment,
        &ptr);
    ASSERT_EQ(result, XE_RESULT_SUCCESS);
    memset(ptr, 0xbf, size);
}

} // namespace ult
} // namespace xe