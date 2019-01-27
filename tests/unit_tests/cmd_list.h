#pragma once
#include "xe_cmdlist.h"

namespace xe {

struct CommandList {
    static CommandList *create();

    static CommandList *fromHandle(xe_command_list_handle_t handle) {
        return static_cast<CommandList *>(handle.pDriverData);
    }

    inline xe_command_list_handle_t toHandle() const {
        xe_command_list_handle_t handle;
        handle.pDriverData = const_cast<CommandList *>(this);
        return handle;
    }
};

} // namespace xe
