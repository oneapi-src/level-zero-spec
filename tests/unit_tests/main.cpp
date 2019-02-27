#include "gmock/gmock.h"

TEST(Should, pass) {
    EXPECT_TRUE(true);
}

namespace L0 {
namespace ult {
::testing::Environment *environment = nullptr;
}
}

using namespace L0::ult;

int main(int argc, char **argv) {
    testing::InitGoogleMock(&argc, argv);

    if (environment) {
        ::testing::AddGlobalTestEnvironment(environment);    
    }

    return RUN_ALL_TESTS();
}
