#include "driver.h"
#include "gmock/gmock.h"

namespace xe {

struct MockDriver : public Driver {
    MOCK_METHOD1(initialize, xe_result_t(xe_init_flags_t));
};

}
