#include "cmdlist.h"
#include "mock_device.h"
#include "xe_cmdlist.h"
#include "xe_event.h"
#include "gmock/gmock.h"
#include "runtime/platform/platform.h"

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

    auto result = xeDeviceCreateCommandList(device.toHandle(),
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

    auto result = xeDeviceCreateCommandQueue(device.toHandle(),
                                             &desc,
                                             &commandQueue);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(xeDeviceCreateEvent, redirectsToObject) {
    Mock<Device> device;
    xe_event_handle_t event = {};
    xe_event_desc_t desc = {};

    EXPECT_CALL(device, createEvent(&desc, &event))
        .Times(1)
        .WillRepeatedly(Return(XE_RESULT_SUCCESS));

    auto result = xeDeviceCreateEvent(device.toHandle(),
                                      &desc,
                                      &event);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(DeviceCreateCommandList, returnsSuccess) {
    auto platform = OCLRT::constructPlatform();
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

TEST(DeviceCreateCommandQueue, returnsSuccess) {
    auto platform = OCLRT::constructPlatform();
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

TEST(DeviceCreateEvent, returnsSuccess) {
    auto platform = OCLRT::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    auto deviceRT = platform->getDevice(0);
    ASSERT_NE(nullptr, deviceRT);
    auto device = Device::create(deviceRT);

    xe_event_handle_t event = {};
    xe_event_desc_t desc = {};

    auto result = device->createEvent(&desc,
                                      &event);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
    EXPECT_NE(nullptr, event);

    delete device;
}

TEST(DeviceGetMemoryManager, returnsPointer) {
    auto platform = OCLRT::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    auto deviceRT = platform->getDevice(0);
    ASSERT_NE(nullptr, deviceRT);
    auto device = Device::create(deviceRT);

    auto memoryManager = device->getMemoryManager();
    EXPECT_NE(nullptr, memoryManager);

    delete device;
}

} // namespace ult
} // namespace L0
