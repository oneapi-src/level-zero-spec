#include "mock_device.h"
#include "runtime/device/device.h"
#include "runtime/platform/platform.h"
#include "unit_tests/mocks/mock_csr.h"
#include "gmock/gmock.h"

namespace xe {

MockDevice::MockDevice() {
    auto ordinal = 0u;
    auto platform = OCLRT::constructPlatform();
    auto success = platform->initialize();
    assert(success);
    auto deviceRT = platform->getDevice(ordinal);
    assert(deviceRT);
    auto executionEnvironment = deviceRT->getExecutionEnvironment();
    assert(executionEnvironment);

    csrRT = new MockCommandStreamReceiver(*executionEnvironment);
}

MockDevice::~MockDevice() {
    delete csrRT;
}

} // namespace xe
