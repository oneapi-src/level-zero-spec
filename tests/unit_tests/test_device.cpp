#include "mock_device.h"
#include "gmock/gmock.h"
#include "runtime/platform/platform.h"

using ::testing::Return;

TEST(deviceCreateCommandQueue, redirectsToDeviceObject) {
    xe::MockDevice device;
    xe_device_handle_t deviceHandle = {};
    deviceHandle.pDriverData = static_cast<xe::Device *>(&device);

    xe_command_queue_handle_t commandQueue = {};
    xe_command_queue_desc_t desc = {};

    EXPECT_CALL(device, createCommandQueue(&desc, &commandQueue))
        .Times(1)
        .WillRepeatedly(Return(XE_RESULT_SUCCESS));

    auto result = xe::deviceCreateCommandQueue(
        deviceHandle,
        &desc,
        &commandQueue);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

TEST(deviceImpcreateCommandQueue, returnsSuccess) {
    auto platform = OCLRT::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    auto deviceRT = platform->getDevice(0);
    ASSERT_NE(nullptr, deviceRT);
    auto device = xe::Device::create(deviceRT);

    xe_command_queue_handle_t commandQueue = {};
    xe_command_queue_desc_t desc = {};

    auto result = device->createCommandQueue(
        &desc,
        &commandQueue);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
    EXPECT_NE(nullptr, commandQueue.pDriverData);
}
