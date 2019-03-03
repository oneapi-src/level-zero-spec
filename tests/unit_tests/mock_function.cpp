#include "mock_function.h"

using ::testing::Return;

namespace L0 {
namespace ult {

Mock<Function>::Mock() {
    ON_CALL(*this, getThreadExecutionMask)
        .WillByDefault(Return(0xfffffffful));
}

} // namespace ult
} // namespace L0