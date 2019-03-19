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

TEST(Event_create, allocationContainsAtLeast64Bytes) {
    Mock<Device> device;

    auto event = whitebox_cast(Event::create(&device));
    ASSERT_NE(event, nullptr);
    EXPECT_GE(event->allocation->getSize(), 64u);
    
    delete event;
}

TEST(hostSynchronize, waitWithMaxTimeout) {
    Mock<Device> device;

    auto event = whitebox_cast(Event::create(&device));
    ASSERT_NE(event, nullptr);

    auto result = event->hostSynchronize(std::numeric_limits<uint32_t>::max());
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(hostSynchronize, waitWithFiniteTimeout) {
    Mock<Device> device;

    auto event = whitebox_cast(Event::create(&device));
    ASSERT_NE(event, nullptr);

    auto result = event->hostSynchronize(40);
    EXPECT_EQ(XE_RESULT_ERROR_INVALID_PARAMETER, result);
}

TEST(hostSignal, signalEvent) {
    Mock<Device> device;

    auto event = whitebox_cast(Event::create(&device));
    ASSERT_NE(event, nullptr);

    auto result = event->hostSignal();
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

} // namespace ult
} // namespace L0
