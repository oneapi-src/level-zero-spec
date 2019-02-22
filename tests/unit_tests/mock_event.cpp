#include "mock_event.h"

namespace xe {
namespace ult {

Mock<Event>::Mock() : mockAllocation(&memory, sizeof(memory)) {
    allocation = &mockAllocation;
}

Mock<Event>::~Mock() {
}

} // namespace ult
} // namespace xe
