#include "mock_cmdqueue.h"

namespace xe {

WhiteBox<CommandQueue>::WhiteBox(Device *device)
    : CommandQueueImp(device) {
}

WhiteBox<CommandQueue>::~WhiteBox() {
}

MockCommandQueue::MockCommandQueue(Device *device)
    : CommandQueueImp(device) {
}

MockCommandQueue::~MockCommandQueue() {
}

} // namespace xe
