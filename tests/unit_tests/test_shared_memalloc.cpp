#include "memory.h"
#include "mock_device.h"
#include "mock_memory_manager.h"
#include "gmock/gmock.h"
#include "global_fixture.h"

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Return;

namespace L0 {
namespace ult {

class SharedMemAllocTest: public GlobalFixtureTest {
};

TEST_F(SharedMemAllocTest, returnsValidPtr) {
    Mock<Device> device;

    xe_device_mem_alloc_flag_t flagsDevice = {};
    xe_host_mem_alloc_flag_t flagsHost = {};
    size_t size = 65536u;
    size_t alignment = 4096u;
    void *ptr = nullptr;

    auto result = xeSharedMemAlloc(
        device.toHandle(),
        flagsDevice,
        flagsHost,
        size,
        alignment,
        &ptr);
    ASSERT_EQ(result, XE_RESULT_SUCCESS);
    memset(ptr, 0xbf, size);

    result = xeMemFree(const_cast<const void *>(ptr));
    ASSERT_EQ(result, XE_RESULT_SUCCESS);
}

} // namespace ult
} // namespace L0