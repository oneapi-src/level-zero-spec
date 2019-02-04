#include "mock_cmdlist.h"

namespace xe {
namespace ult {

WhiteBox<::xe::CommandList>::WhiteBox(Device *device) : CommandListImp(device) {
}

WhiteBox<::xe::CommandList>::~WhiteBox() {
}

MockCommandList::MockCommandList(Device *device) : WhiteBox<::xe::CommandList>(device) {
}

MockCommandList::~MockCommandList() {
}

} // namespace ult
} // namespace xe
