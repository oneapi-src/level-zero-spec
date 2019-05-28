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

} // namespace ult
} // namespace L0
