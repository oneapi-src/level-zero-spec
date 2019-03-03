#pragma once
#include "module.h"

#include "white_box.h"
#include "mock.h"

namespace L0 {
namespace ult {

template <>
struct Mock<Module> : public Module {
    Mock() = default;
    virtual ~Mock() = default;

    MOCK_METHOD2(createFunction, xe_result_t(const xe_function_desc_t *desc, xe_function_handle_t *phFunction));
    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD2(getFunctionPointer, xe_result_t(const char *pFunctionName,
                                                 void **pfnFunction));
    MOCK_METHOD2(getNativeBinary, xe_result_t(uint32_t *pSize,
                                              char **pModuleNativeBinary));

    MOCK_CONST_METHOD0(getDevice, Device *());
};

} // namespace ult
} // namespace L0
