#include "test.h"
#include "mock_fence.h"
#include "mock_cmdqueue.h"
#include "gtest/gtest.h"

namespace L0 {
namespace ult {

TEST(xeFenceDestroy, redirectsToObject) {
    Mock<Fence> fence;
    EXPECT_CALL(fence, destroy);

    auto result = xeFenceDestroy(fence.toHandle());
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(Fence_create, allocationContainsAtLeast64Bytes) {
    Mock<CommandQueue> cmdqueue;
    xe_fence_desc_t desc;
    desc.version = XE_FENCE_DESC_VERSION_CURRENT;

    auto fence = whitebox_cast(Fence::create(&cmdqueue, &desc));
    ASSERT_NE(fence, nullptr);
    EXPECT_GE(fence->allocation->getSize(), 64u);

    delete fence;
}

TEST(Fence_reset, fenceStateIsCleared) {
    Mock<CommandQueue> cmdqueue;
    xe_fence_desc_t desc;
    desc.version = XE_FENCE_DESC_VERSION_CURRENT;

    auto fence = whitebox_cast(Fence::create(&cmdqueue, &desc));
    ASSERT_NE(fence, nullptr);

    auto result = fence->reset();
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    EXPECT_EQ(fence->queryStatus(), XE_RESULT_NOT_READY);
}

} // namespace ult
} // namespace L0
