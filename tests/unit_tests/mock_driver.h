#include "driver.h"
#include "gmock/gmock.h"

namespace xe {

struct MockDriver : public Driver {
    MOCK_METHOD1(initialize, xe_result_t(xe_init_flags_t));

    MOCK_METHOD2(getDevice, xe_result_t(uint32_t ordinal,
                                        xe_device_handle_t *phDevice));
};

} // namespace xe
