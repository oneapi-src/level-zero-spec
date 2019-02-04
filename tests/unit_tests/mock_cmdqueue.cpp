#include "mock_cmdqueue.h"

namespace xe {
namespace ult {

WhiteBox<::xe::CommandQueue>::WhiteBox(Device *device)
    : ::xe::CommandQueueImp(device) {
}

WhiteBox<::xe::CommandQueue>::~WhiteBox() {
}

MockCommandQueue::MockCommandQueue(Device *device)
    : WhiteBox<::xe::CommandQueue>(device) {
}

MockCommandQueue::~MockCommandQueue() {
}

} // ult
} // namespace xe
