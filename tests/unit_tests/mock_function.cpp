#include "mock_function.h"
using ::testing::Invoke;

using ::testing::Return;

namespace L0 {
namespace ult {

Mock<Function>::Mock() {
    ON_CALL(*this, getThreadExecutionMask)
        .WillByDefault(Return(0xfffffffful));
    EXPECT_CALL(*this, getPerThreadDataSize)
        .WillRepeatedly(Invoke([this]() { return getPerThreadDataSizeForWholeThreadGroup() / getThreadsPerThreadGroup(); }));
}

} // namespace ult
} // namespace L0