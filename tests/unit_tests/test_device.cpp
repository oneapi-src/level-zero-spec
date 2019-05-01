#include "cmdlist.h"
#include "image.h"
#include "mock_device.h"
#include "mock_event.h"
#include "memory_manager.h"
#include "xe_cmdlist.h"
#include "xe_event.h"
#include "gmock/gmock.h"
#include "runtime/platform/platform.h"
#include "runtime/device/device.h"
#include "global_fixture.h"

using ::testing::Return;

namespace L0 {
namespace ult {

TEST(xeDeviceCreateCommandList, redirectsToObject) {
    Mock<Device> device;
    xe_command_list_desc_t desc = {};
    xe_command_list_handle_t commandList = {};

    EXPECT_CALL(device, createCommandList(&desc, &commandList))
        .Times(1)
        .WillRepeatedly(Return(XE_RESULT_SUCCESS));

    auto result = xeCommandListCreate(device.toHandle(),
                                            &desc,
                                            &commandList);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(xeDeviceCreateCommandQueue, redirectsToObject) {
    Mock<Device> device;
    xe_command_queue_handle_t commandQueue = {};
    xe_command_queue_desc_t desc = {};

    EXPECT_CALL(device, createCommandQueue(&desc, &commandQueue))
        .Times(1)
        .WillRepeatedly(Return(XE_RESULT_SUCCESS));

    auto result = xeCommandQueueCreate(device.toHandle(),
                                             &desc,
                                             &commandQueue);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(xeDeviceCreatePoolEvent, redirectsToObject) {
    Mock<Device> device;
    xe_event_pool_handle_t eventPool = {};
    xe_event_pool_desc_t desc = {};
    desc.count = 2;

    EXPECT_CALL(device, createEventPool(&desc, &eventPool))
        .Times(1)
        .WillRepeatedly(Return(XE_RESULT_SUCCESS));

    auto result = xeEventPoolCreate(device.toHandle(),
                                      &desc,
                                      &eventPool);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(xeDeviceCreateEvent, redirectsToObject) {
    Mock<EventPool> eventPool;
    xe_event_handle_t event = {};
    const xe_event_desc_t desc = {XE_EVENT_DESC_VERSION_CURRENT, 0,
        XE_EVENT_SCOPE_FLAG_NONE, XE_EVENT_SCOPE_FLAG_NONE};

    EXPECT_CALL(eventPool, createEvent(&desc, &event))
        .Times(1)
        .WillRepeatedly(Return(XE_RESULT_SUCCESS));

    auto result = xeEventCreate(eventPool.toHandle(),
                                      &desc,
                                      &event);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);
}

class DeviceCreateImage : public GlobalFixtureTest {
};

TEST_F(DeviceCreateImage, returnsSuccess) {
    auto platform = NEO::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    auto deviceRT = platform->getDevice(0);
    ASSERT_NE(nullptr, deviceRT);
    auto device = Device::create(deviceRT);
    assert(globalMemoryManager);

    xe_image_handle_t image = {};
    xe_image_desc_t desc = {};

    auto result = device->createImage(&desc,
                                      &image);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
    EXPECT_NE(nullptr, image);

    Image::fromHandle(image)->destroy();
    delete device;
}

TEST(MaxHwTrheads, getMaxHwThreads) {
    auto platform = NEO::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    auto deviceRT = platform->getDevice(0);
    ASSERT_NE(nullptr, deviceRT);
    auto device = Device::create(deviceRT);

    auto hwInfo = deviceRT->getHardwareInfo();

    uint32_t threadsPerEU = (hwInfo.pSysInfo->ThreadCount / hwInfo.pSysInfo->EUCount) + hwInfo.capabilityTable.extraQuantityThreadsPerEU;
    uint32_t value = device->getMaxNumHwThreads();

    uint32_t expected = hwInfo.pSysInfo->EUCount * threadsPerEU;
    EXPECT_EQ(expected, value);
}

class DeviceCreateCommandList : public GlobalFixtureTest {
};

TEST_F(DeviceCreateCommandList, returnsSuccess) {
    auto platform = NEO::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    auto deviceRT = platform->getDevice(0);
    ASSERT_NE(nullptr, deviceRT);
    auto device = Device::create(deviceRT);

    xe_command_list_handle_t commandList = {};
    xe_command_list_desc_t desc = {};

    auto result = device->createCommandList(&desc,
                                            &commandList);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
    EXPECT_NE(nullptr, commandList);

    CommandList::fromHandle(commandList)->destroy();
    delete device;
}

class DeviceCreateCommandQueue : public GlobalFixtureTest {
};

TEST_F(DeviceCreateCommandQueue, returnsSuccess) {
    auto platform = NEO::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    auto deviceRT = platform->getDevice(0);
    ASSERT_NE(nullptr, deviceRT);
    auto device = Device::create(deviceRT);

    xe_command_queue_handle_t commandQueue = {};
    xe_command_queue_desc_t desc = {};

    auto result = device->createCommandQueue(&desc,
                                             &commandQueue);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
    EXPECT_NE(nullptr, commandQueue);

    delete device;
}

class DeviceCreatePoolEvent : public GlobalFixtureTest {
};

TEST_F(DeviceCreatePoolEvent, returnsSuccess) {
    auto platform = NEO::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    auto deviceRT = platform->getDevice(0);
    ASSERT_NE(nullptr, deviceRT);
    auto device = Device::create(deviceRT);

    xe_event_pool_handle_t eventPool = {};
    xe_event_pool_desc_t desc = {};
    desc.count = 1;

    auto result = device->createEventPool(&desc,
                                      &eventPool);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
    EXPECT_NE(nullptr, eventPool);

    delete device;
}

class DeviceGetMemoryManager : public GlobalFixtureTest {
};

TEST_F(DeviceGetMemoryManager, returnsPointer) {
    auto platform = NEO::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    auto deviceRT = platform->getDevice(0);
    ASSERT_NE(nullptr, deviceRT);
    auto device = Device::create(deviceRT);

    auto memoryManager = globalMemoryManager;
    EXPECT_NE(nullptr, memoryManager);

    delete device;
}

} // namespace ult
} // namespace L0
