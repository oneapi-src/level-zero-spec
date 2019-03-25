#pragma once
#include "module.h"

#include "white_box.h"
#include "mock.h"

namespace L0 {
namespace ult {

template <>
struct Mock<Module> : public Module {
    Mock();
    virtual ~Mock() = default;

    MOCK_METHOD2(createFunction, xe_result_t(const xe_function_desc_t *desc, xe_function_handle_t *phFunction));
    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD2(getFunctionPointer, xe_result_t(const char *pFunctionName,
                                                 void **pfnFunction));
    MOCK_METHOD2(getNativeBinary, xe_result_t(size_t *pSize,
                                              uint8_t *pModuleNativeBinary));
    MOCK_CONST_METHOD1(getImmutableFunctionInfo, PtrRef<ImmutableFunctionInfo>(CStringRef functionName));
    MOCK_CONST_METHOD0(getMaxGroupSize, uint32_t());

    MOCK_CONST_METHOD0(getDevice, Device *());
};

} // namespace ult
} // namespace L0
