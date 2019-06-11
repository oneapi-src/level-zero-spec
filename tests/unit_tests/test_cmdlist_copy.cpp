#include "test.h"
#include "xe_api.h"
#include "graphics_allocation.h"
#include "mock_cmdlist.h"
#include "mock_device.h"
#include "mock_memory_manager.h"
#include "global_fixture.h"

namespace L0 {
namespace ult {

using namespace testing;

struct CommandListAppendCopy : public GlobalFixtureTest {};

TEST_F(CommandListAppendCopy, checksMemoryCopyFromHostSrcToHostDstHappens) {
    Mock<Device> device;
    Mock<CommandList> commandList;
    size_t bufferSize = 4096u;
    void *dst = globalMemoryManager->allocateHostMemory(bufferSize, 64);
    ASSERT_NE(nullptr, dst);
    const void *src = globalMemoryManager->allocateHostMemory(bufferSize, 64);
    ASSERT_NE(nullptr, src);

    EXPECT_CALL(commandList, appendMemoryCopy(_, _, _, _, _, _)).Times(1);

    auto res =
        xeCommandListAppendMemoryCopy(&commandList, dst, src, bufferSize, nullptr, 0, nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, res);

    globalMemoryManager->freeMemory(dst);
    globalMemoryManager->freeMemory(src);
}

TEST_F(CommandListAppendCopy, checksMemoryCopyFromHeapToHostDstHappens) {
    Mock<Device> device;
    Mock<CommandList> commandList;
    size_t bufferSize = 4096u;
    void *dst = globalMemoryManager->allocateHostMemory(bufferSize, 64);
    ASSERT_NE(nullptr, dst);
    uint8_t *src = new uint8_t[bufferSize];
    ASSERT_NE(nullptr, src);

    EXPECT_CALL(commandList, appendMemoryCopy(_, _, _, _, _, _)).Times(1);

    auto res =
        xeCommandListAppendMemoryCopy(&commandList, dst, src, bufferSize, nullptr, 0, nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, res);

    globalMemoryManager->freeMemory(dst);
    delete[] src;
}

TEST_F(CommandListAppendCopy, checksMemoryCopyForMemoryFromDifferentDevicesHappens) {
    Mock<Device> device0;
    Mock<Device> device1;
    Mock<CommandList> commandList;
    size_t bufferSize = 4096u;
    auto dstAlloc = globalMemoryManager->allocateDeviceMemory(&device0, bufferSize, 64);
    ASSERT_NE(nullptr, dstAlloc);
    void *dst = reinterpret_cast<void *>(dstAlloc->getGpuAddress());
    auto srcAlloc = globalMemoryManager->allocateDeviceMemory(&device1, bufferSize, 64);
    ASSERT_NE(nullptr, srcAlloc);
    void *src = reinterpret_cast<void *>(srcAlloc->getGpuAddress());

    EXPECT_CALL(commandList, appendMemoryCopy(_, _, _, _, _, _)).Times(1);

    auto res =
        xeCommandListAppendMemoryCopy(&commandList, dst, src, bufferSize, nullptr, 0, nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, res);

    globalMemoryManager->freeGraphicsAllocation(dstAlloc);
    globalMemoryManager->freeGraphicsAllocation(srcAlloc);
}

struct CommandListAppendSet : public GlobalFixtureTest {};

TEST_F(CommandListAppendCopy, checksMemorySetHappens) {
    Mock<Device> device;
    Mock<CommandList> commandList;
    size_t bufferSize = 4096u;
    auto dstAlloc = globalMemoryManager->allocateDeviceMemory(&device, bufferSize, 64);
    ASSERT_NE(nullptr, dstAlloc);
	void *dst = reinterpret_cast<void *>(dstAlloc->getGpuAddress());

    EXPECT_CALL(commandList, appendMemorySet(dst, _, bufferSize, _, _, _)).Times(1);

    auto res =
        xeCommandListAppendMemorySet(&commandList, dst, 0, bufferSize, nullptr, 0, nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, res);

    globalMemoryManager->freeGraphicsAllocation(dstAlloc);
}

} // namespace ult
} // namespace L0
