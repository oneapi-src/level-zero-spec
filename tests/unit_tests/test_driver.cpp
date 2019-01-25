#include "xe_driver.h"
#include "gmock/gmock.h"

TEST(driverInit, returnsSuccess) {
    auto result = xeDriverInit(
        XE_INIT_FLAG_NONE ///< [in] initialization flags
    );
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}
