#include "gmock/gmock.h"

TEST(Should, pass) {
    EXPECT_TRUE(true);
}

namespace xe {
namespace ult {
::testing::Environment *environment = nullptr;
}
}

using namespace xe::ult;

int main(int argc, char **argv) {
    testing::InitGoogleMock(&argc, argv);

    if (environment) {
        ::testing::AddGlobalTestEnvironment(environment);    
    }

    return RUN_ALL_TESTS();
}
