#pragma once
#ifndef CMD_LIST_INTERNAL
#error "Don't #include this file directly."
#endif //CMD_LIST_INTERNAL

#include "cmd_list.h"

namespace xe {

struct CommandListImp : public CommandList {
    CommandListImp(Device *device) : device(device) {
    }

    xe_result_t destroy() override;

  protected:
    Device *device;
};

} // namespace xe
