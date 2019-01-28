#pragma once
#include "cmd_list.h"

namespace xe {

template <uint32_t productFamily>
struct CommandListProductFamily : public CommandList {
    xe_result_t close() override;
    xe_result_t destroy() override;
    xe_result_t encodeWaitOnEvent(xe_event_handle_t hEvent) override;
};

} // namespace xe
