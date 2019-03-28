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
    EXPECT_EQ(event->queryStatus(), XE_RESULT_NOT_READY);
    
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

TEST(Event_hostSignal, returnsSuccessFromQueryStatus) {
    Mock<Device> device;

    auto event = whitebox_cast(Event::create(&device));
    ASSERT_NE(event, nullptr);

    auto result = event->hostSignal();
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    EXPECT_EQ(event->queryStatus(), XE_RESULT_SUCCESS);

    delete event;
}

TEST(Event_reset, returnsNotReadyFromQueryStatus) {
    Mock<Device> device;

    auto event = whitebox_cast(Event::create(&device));
    ASSERT_NE(event, nullptr);

    auto result = event->hostSignal();
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = event->reset();
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    EXPECT_EQ(event->queryStatus(), XE_RESULT_NOT_READY);

    delete event;
}

} // namespace ult
} // namespace L0
