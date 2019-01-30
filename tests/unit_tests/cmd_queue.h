#pragma once
#include "xe_common.h"

struct _xe_command_queue_handle_t {
};

namespace xe {

struct CommandQueue : public _xe_command_queue_handle_t{
    static CommandQueue *fromHandle(xe_command_queue_handle_t handle) {
        return static_cast<CommandQueue *>(handle);
    }

    inline xe_command_queue_handle_t toHandle() {
        return this;
    }
};

} // namespace xe
