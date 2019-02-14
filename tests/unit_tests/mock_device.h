#pragma once
#include "device.h"
#include "mock.h"
#include "white_box.h"

namespace xe {
namespace ult {

template <>
struct WhiteBox<::xe::Device> : public ::xe::Device {
};

using Device = WhiteBox<::xe::Device>;

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

    MOCK_METHOD3(createModule, xe_result_t(const xe_module_desc_t *desc,
                                           xe_module_handle_t *module,
                                           xe_module_build_log_handle_t *buildLog));

    MOCK_METHOD0(getMemoryManager, MemoryManager *());

    void *deviceRT;
    void *csrRT;
};

} // namespace ult
} // namespace xe
