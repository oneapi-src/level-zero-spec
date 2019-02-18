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