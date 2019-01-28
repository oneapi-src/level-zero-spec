#pragma once
#define CMD_LIST_INTERNAL
#include "cmd_list_imp.h"
#undef CMD_LIST_INTERNAL

namespace xe {

template <uint32_t gfxCoreFamily>
struct CommandListHw : public CommandListImp {
    CommandListHw(Device *device) : CommandListImp(device) {
    }

    xe_result_t close() override;
    xe_result_t encodeWaitOnEvent(xe_event_handle_t hEvent) override;
};

} // namespace xe
