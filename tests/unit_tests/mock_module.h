#pragma once
#include "module.h"

#include "white_box.h"
#include "mock.h"

#include "igc.opencl.h" // temporarily to instrument NEO's compiler interface

// temporarily to instrument NEO's compiler interface
namespace Os {
extern const char *frontEndDllName;
extern const char *igcDllName;
} // namespace Os

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

template <>
struct Mock<Function> : public Function {
    Mock();
    virtual ~Mock() = default;

    MOCK_METHOD1(createFunctionArgs, xe_result_t(xe_function_args_handle_t *phFunctionArgs));
    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD2(queryAttribute, xe_result_t(xe_function_attribute_t attr,
                                             uint32_t *pValue));
    MOCK_METHOD3(setGroupSize, xe_result_t(uint32_t groupSizeX,
                                           uint32_t groupSizeY,
                                           uint32_t groupSizeZ));
    MOCK_METHOD6(suggestGroupSize, xe_result_t(uint32_t globalSizeX,
                                               uint32_t globalSizeY,
                                               uint32_t globalSizeZ,
                                               uint32_t *groupSizeX,
                                               uint32_t *groupSizeY,
                                               uint32_t *groupSizeZ));

    MOCK_CONST_METHOD3(getGroupSize, void(uint32_t &outGroupSizeX, uint32_t &outGroupSizeY, uint32_t &outGroupSizeZ));
    MOCK_CONST_METHOD0(getIsaHostMem, const void *());
    MOCK_CONST_METHOD0(getIsaSize, size_t());
    MOCK_CONST_METHOD0(getModule, Module *());
    MOCK_CONST_METHOD0(getPerThreadDataHostMem, const void *());
    MOCK_CONST_METHOD0(getPerThreadDataSize, size_t());
    MOCK_CONST_METHOD0(getSimdSize, uint32_t());
    MOCK_CONST_METHOD0(getThreadsPerThreadGroup, uint32_t());
    MOCK_CONST_METHOD0(getThreadExecutionMask, uint32_t());
};

template <>
struct Mock<FunctionArgs> : public FunctionArgs {
    Mock() = default;
    virtual ~Mock() = default;

    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD2(setAttribute, xe_result_t(xe_function_argument_attribute_t attr,
                                           uint32_t value));
    MOCK_METHOD3(setValue, xe_result_t(uint32_t argIndex, size_t argSize, const void *pArgValue));

    MOCK_CONST_METHOD0(getCrossThreadDataHostMem, const void *());
    MOCK_CONST_METHOD0(getCrossThreadDataSize, size_t());
    MOCK_CONST_METHOD0(getResidencyContainer, const std::vector<GraphicsAllocation *> &());
    MOCK_METHOD3(setGroupCount, void(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ));
};

struct UserRealCompilerGuard {
    UserRealCompilerGuard() {
        prevCompilerFcl = Os::frontEndDllName;
        prevCompilerIgc = Os::igcDllName;

        Os::frontEndDllName = FCL_LIBRARY_NAME;
        Os::igcDllName = IGC_LIBRARY_NAME;
    }

    UserRealCompilerGuard(const UserRealCompilerGuard &) = delete;
    UserRealCompilerGuard(UserRealCompilerGuard &&) = delete;
    UserRealCompilerGuard &operator=(const UserRealCompilerGuard &) = delete;
    UserRealCompilerGuard &operator=(UserRealCompilerGuard &&) = delete;

    ~UserRealCompilerGuard() {
        Os::frontEndDllName = prevCompilerFcl;
        Os::igcDllName = prevCompilerIgc;
    }

    const char *prevCompilerFcl = nullptr;
    const char *prevCompilerIgc = nullptr;
};

} // namespace ult
} // namespace L0
