#include "mock_cmdqueue.h"
#include "runtime/device/device.h"
#include "runtime/platform/platform.h"
#include "unit_tests/mocks/mock_csr.h"

namespace L0 {
namespace ult {

WhiteBox<::L0::CommandQueue>::WhiteBox(Device *device, void *csrRT)
    : ::L0::CommandQueueImp(device, csrRT) {
}

WhiteBox<::L0::CommandQueue>::~WhiteBox() {
}

Mock<CommandQueue>::Mock(Device *device, void *csrRT)
    : WhiteBox<::L0::CommandQueue>(device, csrRT) {
    auto ordinal = 0u;
    auto platform = NEO::constructPlatform();
    auto deviceRT = platform->getDevice(ordinal);
    auto executionEnvironment = deviceRT->getExecutionEnvironment();

    this->csrRT = new MockCommandStreamReceiver(*executionEnvironment);
}

Mock<CommandQueue>::~Mock() {
    delete static_cast<MockCommandStreamReceiver *>(csrRT);
}

} // namespace ult
} // namespace L0
