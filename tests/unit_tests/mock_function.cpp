#include "mock_function.h"
using ::testing::Invoke;

using ::testing::Return;

namespace L0 {
namespace ult {

Mock<Function>::Mock() {
    ON_CALL(*this, getThreadExecutionMask)
        .WillByDefault(Return(0xfffffffful));
    ON_CALL(*this, getPerThreadDataSize)
        .WillByDefault(Invoke([this]() { return getPerThreadDataSizeForWholeThreadGroup() / getThreadsPerThreadGroup(); }));
}

} // namespace ult
} // namespace L0