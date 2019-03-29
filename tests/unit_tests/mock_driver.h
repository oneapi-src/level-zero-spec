#pragma once
#include "driver_imp.h"
#include "mock.h"
#include "white_box.h"
#include <atomic>

namespace L0 {
namespace ult {

template <>
struct WhiteBox<::L0::DriverImp> : public ::L0::DriverImp {
};

using Driver = WhiteBox<::L0::DriverImp>;

template <>
struct Mock<Driver> : public DriverImp {
    Mock();
    virtual ~Mock();

    MOCK_METHOD1(initialize, void(bool *result));
    MOCK_METHOD1(init, xe_result_t(xe_init_flag_t));
    MOCK_METHOD2(getDevice, xe_result_t(uint32_t ordinal,
                                        xe_device_handle_t *phDevice));
    MOCK_METHOD1(getDeviceCount, xe_result_t(uint32_t *count));
    MOCK_METHOD1(getVersion, xe_result_t(uint32_t *version));

    xe_result_t mockInit(xe_init_flag_t) {
        return this->DriverImp::init(XE_INIT_FLAG_NONE);
    }

    Driver *previousDriver = nullptr;
};

} // namespace ult
} // namespace L0
