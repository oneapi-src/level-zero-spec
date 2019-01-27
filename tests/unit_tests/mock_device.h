#pragma once
#include "device.h"
#include "gmock/gmock.h"

namespace xe {

struct MockDevice : public Device {
    MOCK_METHOD2(createCommandQueue, xe_result_t(const xe_command_queue_desc_t *desc,
                                                 xe_command_queue_handle_t *commandQueue));
};

} // namespace xe
