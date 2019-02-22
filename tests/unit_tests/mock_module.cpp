#include "mock_module.h"

using ::testing::Return;

namespace xe {
namespace ult {

Mock<Function>::Mock() {
    ON_CALL(*this, getThreadExecutionMask)
        .WillByDefault(Return(0xfffffffful));
}

} // namespace ult
} // namespace xe