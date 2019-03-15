#include "mock_module.h"

using ::testing::Return;

namespace L0 {
namespace ult {

Mock<Module>::Mock() {
    EXPECT_CALL(*this, getMaxGroupSize)
        .WillRepeatedly(Return(256u));
}

} // namespace ult
} // namespace L0