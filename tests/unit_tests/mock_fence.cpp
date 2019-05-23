#include "mock_fence.h"

namespace L0 {
namespace ult {

Mock<Fence>::Mock() : mockAllocation(&memory, sizeof(memory)) { allocation = &mockAllocation; }

Mock<Fence>::~Mock() {}

} // namespace ult
} // namespace L0
