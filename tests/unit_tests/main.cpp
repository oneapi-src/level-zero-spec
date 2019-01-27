#include "gmock/gmock.h"

TEST(Should, pass) {
    EXPECT_TRUE(true);
}

::testing::Environment *environment = nullptr;

int main(int argc, char **argv) {
    testing::InitGoogleMock(&argc, argv);

    if (environment) {
        ::testing::AddGlobalTestEnvironment(environment);    
    }

    return RUN_ALL_TESTS();
}
