#include "mock_cmd_list.h"

namespace xe {

WhiteBox<CommandList>::WhiteBox(Device *device) : CommandListImp(device) {
}

WhiteBox<CommandList>::~WhiteBox() {
}

MockCommandList::MockCommandList(Device *device) : WhiteBox<CommandList>(device) {
}

MockCommandList::~MockCommandList() {
}

} // namespace xe
