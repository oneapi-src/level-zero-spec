#include "mock_event.h"

namespace L0 {
namespace ult {

Mock<Event>::Mock() : mockAllocation(&memory, sizeof(memory)) { allocation = &mockAllocation; }

Mock<Event>::~Mock() {}

Mock<EventPool>::Mock() : pool(1, nullptr) {
    pool[0] = new Event();

    EXPECT_CALL(*this, getPoolSize()).WillRepeatedly(testing::Return(1));
}

Mock<EventPool>::~Mock() { delete (pool[0]); }

} // namespace ult
} // namespace L0
