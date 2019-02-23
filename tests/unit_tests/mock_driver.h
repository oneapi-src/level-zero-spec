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

    MOCK_METHOD1(init, xe_result_t(xe_init_flag_t));
    MOCK_METHOD2(getDevice, xe_result_t(uint32_t ordinal,
                                        xe_device_handle_t *phDevice));
    MOCK_METHOD1(getDeviceCount, xe_result_t(uint32_t *count));
    MOCK_METHOD3(getDeviceLinkProperties, xe_result_t(uint32_t srcOrdinal,
                                                      uint32_t dstOrdinal,
                                                      xe_device_link_properties_t *pLinkProperties));
    MOCK_METHOD2(getDeviceUniqueIds, xe_result_t(uint32_t count,
                                                 uint32_t *pUniqueIds));
    MOCK_METHOD1(getVersion, xe_result_t(uint32_t *version));

    Driver *previousDriver = nullptr;
};

} // namespace ult
} // namespace xe
