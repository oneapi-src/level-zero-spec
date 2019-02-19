#include "mock_device.h"
#include "mock_memory_manager.h"
#include "runtime/device/device.h"
#include "runtime/platform/platform.h"
#include "unit_tests/mocks/mock_csr.h"
#include "gmock/gmock.h"

namespace xe {
namespace ult {

using ::testing::Return;

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

    static ::testing::NiceMock<Mock<MemoryManager>> memoryManager;
    ON_CALL(*this, getMemoryManager)
        .WillByDefault(Return(&memoryManager));
}

Mock<Device>::~Mock() {
    delete static_cast<MockCommandStreamReceiver *>(csrRT);
}

} // namespace ult
} // namespace xe
