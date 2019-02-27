#include "mock_event.h"

namespace L0 {
namespace ult {

Mock<Event>::Mock() : mockAllocation(&memory, sizeof(memory)) {
    allocation = &mockAllocation;
}

Mock<Event>::~Mock() {
}

} // namespace ult
} // namespace L0
