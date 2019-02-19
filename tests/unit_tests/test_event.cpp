#include "mock_event.h"
#include "mock_device.h"
#include "gtest/gtest.h"

namespace xe {
namespace ult {

TEST(xeEventDestroy, redirectsToObject) {
    Mock<Event> event;
    EXPECT_CALL(event, destroy);

    auto result = ::xe::xeEventDestroy(event.toHandle());
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(Event_create, allocationContainsAtLeast64Bytes) {
    Mock<Device> device;
    EXPECT_CALL(device, getMemoryManager);

    auto event = whitebox_cast(Event::create(&device));
    ASSERT_NE(event, nullptr);
    EXPECT_GE(event->allocation->getSize(), 64u);
    
    delete event;
}

} // namespace ult
} // namespace xe
