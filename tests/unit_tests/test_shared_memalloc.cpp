#include "memory.h"
#include "mock_device.h"
#include "mock_memory_manager.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Return;

namespace xe {
namespace ult {

TEST(sharedMemAlloc, returnsValidPtr) {
    Mock<Device> device;
    EXPECT_CALL(device, getMemoryManager).Times(AnyNumber());

    xe_mem_allocator_handle_t hMemAllocHandle = {};
    auto result = xeCreateMemAllocator(&hMemAllocHandle);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_device_mem_alloc_flag_t flagsDevice = {};
    xe_host_mem_alloc_flag_t flagsHost = {};
    size_t size = 65536u;
    size_t alignment = 4096u;
    void *ptr = nullptr;

    result = xeSharedMemAlloc(
        hMemAllocHandle,
        device.toHandle(),
        flagsDevice,
        flagsHost,
        size,
        alignment,
        &ptr);
    ASSERT_EQ(result, XE_RESULT_SUCCESS);
    memset(ptr, 0xbf, size);

    result = xeMemFree(hMemAllocHandle, ptr);
    ASSERT_EQ(result, XE_RESULT_SUCCESS);

    result = xeMemAllocatorDestroy(hMemAllocHandle);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);
}

} // namespace ult
} // namespace xe