#pragma once
#include "module_build_log.h"

#include "white_box.h"
#include "mock.h"

namespace L0 {
namespace ult {

template <>
struct Mock<ModuleBuildLog> : public ModuleBuildLog {
    Mock() = default;
    virtual ~Mock() = default;

    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD2(getString, xe_result_t(size_t *pSize,
                                        char **pBuildLog));
    MOCK_METHOD2(appendString, void(const char *pBuildLog,
                                    size_t size));
};

} // namespace ult
} // namespace L0
