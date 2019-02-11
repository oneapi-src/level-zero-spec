#pragma once
#include "device.h"
#include "mock.h"
#include "white_box.h"

namespace xe {
namespace ult {

template <>
struct WhiteBox<Device> : public ::xe::Device {
};

using Device = WhiteBox<Device>;

template <>
struct Mock<Device> : public Device {
    Mock();
    virtual ~Mock();

    MOCK_METHOD2(createCommandList, xe_result_t(const xe_command_list_desc_t *desc,
                                                xe_command_list_handle_t *commandList));

    MOCK_METHOD2(createCommandQueue, xe_result_t(const xe_command_queue_desc_t *desc,
                                                 xe_command_queue_handle_t *commandQueue));

    MOCK_METHOD2(createEvent, xe_result_t(const xe_event_desc_t *desc,
                                          xe_event_handle_t *event));

    MOCK_METHOD0(getMemoryManager, MemoryManager *());

    void *csrRT;
};

} // namespace ult
} // namespace xe
