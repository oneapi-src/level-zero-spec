#include "mock_cmdqueue.h"
#include "runtime/device/device.h"
#include "runtime/platform/platform.h"
#include "unit_tests/mocks/mock_csr.h"

namespace xe {
namespace ult {

WhiteBox<::xe::CommandQueue>::WhiteBox(Device *device, void *csrRT)
    : ::xe::CommandQueueImp(device, csrRT) {
}

WhiteBox<::xe::CommandQueue>::~WhiteBox() {
}

Mock<CommandQueue>::Mock(Device *device, void *csrRT)
    : WhiteBox<::xe::CommandQueue>(device, csrRT) {
    auto ordinal = 0u;
    auto platform = OCLRT::constructPlatform();
    auto deviceRT = platform->getDevice(ordinal);
    auto executionEnvironment = deviceRT->getExecutionEnvironment();

    csrRT = new MockCommandStreamReceiver(*executionEnvironment);
}

Mock<CommandQueue>::~Mock() {
    delete static_cast<MockCommandStreamReceiver *>(csrRT);
}

} // ult
} // namespace xe
