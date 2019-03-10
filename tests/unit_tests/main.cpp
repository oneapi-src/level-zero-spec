#include "igfxfmid.h"
#include "runtime/helpers/hw_info.h"

#include "gmock/gmock.h"

TEST(Should, pass) {
    EXPECT_TRUE(true);
}

namespace L0 {
namespace ult {
::testing::Environment *environment = nullptr;
}
} // namespace L0

using namespace L0::ult;
extern PRODUCT_FAMILY productFamily;

int main(int argc, char **argv) {
    testing::InitGoogleMock(&argc, argv);

    for (int i = 1; i < argc; ++i) {
        if (!strcmp("--product", argv[i])) {
            ++i;
            if (i < argc) {
                if (::isdigit(argv[i][0])) {
                    int productValue = atoi(argv[i]);
                    if (productValue > 0 && productValue < IGFX_MAX_PRODUCT && OCLRT::hardwarePrefix[productValue] != nullptr) {
                        ::productFamily = static_cast<PRODUCT_FAMILY>(productValue);
                    } else {
                        ::productFamily = IGFX_UNKNOWN;
                    }
                } else {
                    ::productFamily = IGFX_UNKNOWN;
                    for (int j = 0; j < IGFX_MAX_PRODUCT; j++) {
                        if (OCLRT::hardwarePrefix[j] == nullptr)
                            continue;
                        if (strcmp(OCLRT::hardwarePrefix[j], argv[i]) == 0) {
                            ::productFamily = static_cast<PRODUCT_FAMILY>(j);
                            break;
                        }
                    }
                }
                if (::productFamily == IGFX_UNKNOWN) {
                    std::cout << "unknown or unsupported product family has been set: " << argv[i] << std::endl;
                    return -1;
                } else {
                    std::cout << "product family: " << OCLRT::hardwarePrefix[::productFamily] << " (" << ::productFamily << ")" << std::endl;
                }
            }
        }
    }

    if (environment) {
        ::testing::AddGlobalTestEnvironment(environment);
    }

    return RUN_ALL_TESTS();
}
