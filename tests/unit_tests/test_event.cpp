#include "mock_event.h"
#include "mock_device.h"
#include "gtest/gtest.h"

namespace L0 {
namespace ult {

TEST(xeEventDestroy, redirectsToObject) {
    Mock<Event> event;
    EXPECT_CALL(event, destroy);

    auto result = xeEventDestroy(event.toHandle());
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(xeHostWaitOnEvent, redirectsToObject) {
    Mock<Event> event;
    EXPECT_CALL(event, hostWaitOnEvent);

    // Placeholder for expanding on HostWaitonEvent tests
    // Possible cases: 1. non-zero timeout, 2. zero timeout
    // Note: Latest spec update only retains timeout param.
    //       Other args will eventually go away
    auto result = xeHostWaitOnEvent(event.toHandle(),
                                    XE_SYNCHRONIZATION_MODE_SLEEP,
                                    0, 0, 0);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(Event_create, allocationContainsAtLeast64Bytes) {
    Mock<Device> device;

    auto event = whitebox_cast(Event::create(&device));
    ASSERT_NE(event, nullptr);
    EXPECT_GE(event->allocation->getSize(), 64u);
    
    delete event;
}

} // namespace ult
} // namespace L0
