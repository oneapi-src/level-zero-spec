#pragma once
#include "driver.h"
#include "mock.h"
#include "white_box.h"

namespace xe {
namespace ult {

template <>
struct WhiteBox<::xe::Driver> : public ::xe::Driver {
};

using Driver = WhiteBox<::xe::Driver>;

template <>
struct Mock<Driver> : public Driver {
    Mock();
    virtual ~Mock();

    MOCK_METHOD1(initialize, xe_result_t(xe_init_flags_t));

    MOCK_METHOD2(getDevice, xe_result_t(uint32_t ordinal,
                                        xe_device_handle_t *phDevice));

    Driver *previousDriver = nullptr;
};

} // namespace ult
} // namespace xe
