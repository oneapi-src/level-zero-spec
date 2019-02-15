#include "mock_device.h"
#include "runtime/device/device.h"
#include "runtime/platform/platform.h"
#include "unit_tests/mocks/mock_csr.h"
#include "gmock/gmock.h"

namespace xe {
namespace ult {

Mock<Device>::Mock() {
    auto ordinal = 0u;
    auto platform = OCLRT::constructPlatform();
    auto success = platform->initialize();
    assert(success);
    auto deviceRT = platform->getDevice(ordinal);
    this->deviceRT = deviceRT;
    assert(deviceRT);
    auto executionEnvironment = deviceRT->getExecutionEnvironment();
    assert(executionEnvironment);

    csrRT = new MockCommandStreamReceiver(*executionEnvironment);
}

Mock<Device>::~Mock() {
    delete static_cast<MockCommandStreamReceiver *>(csrRT);
}

} // namespace ult
} // namespace xe
