#include "mock_event.h"
#include "gtest/gtest.h"

namespace xe {
namespace ult {

TEST(xeEventDestroy, redirectsToObject) {
    Mock<Event> event;
    EXPECT_CALL(event, destroy);

    auto result = ::xe::xeEventDestroy(event.toHandle());
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

} // namespace ult
} // namespace xe
