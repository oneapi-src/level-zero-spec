#pragma once
#define FUNCTION_INTERNAL
#include "function_imp.h"
#undef FUNCTION_INTERNAL

#include "white_box.h"
#include "mock.h"

#include <type_traits>

namespace L0 {
namespace ult {

template <>
struct WhiteBox<::L0::Function> : public ::L0::FunctionImp {
    using BaseClass = ::L0::FunctionImp;
    using ::L0::FunctionImp::crossThreadData;
    using ::L0::FunctionImp::crossThreadDataSize;
    using ::L0::FunctionImp::groupSizeX;
    using ::L0::FunctionImp::groupSizeY;
    using ::L0::FunctionImp::groupSizeZ;
    using ::L0::FunctionImp::immFuncInfo;

    WhiteBox() : ::L0::FunctionImp(nullptr) {}
    virtual ~WhiteBox() = default;
};

using Function = WhiteBox<::L0::Function>;

template <>
struct Mock<Function> : public Function {
    Mock();
    virtual ~Mock() = default;

    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD2(setAttribute, xe_result_t(xe_function_set_attribute_t attr,
                                           uint32_t pValue));
    MOCK_METHOD2(getAttribute, xe_result_t(xe_function_get_attribute_t attr,
                                           uint32_t *pValue));
    MOCK_METHOD3(setArgumentValue, xe_result_t(uint32_t argIndex,
                                               size_t argSize,
                                               const void *pArgValue));
    MOCK_METHOD3(setGroupCount, void(uint32_t groupCountX,
                                     uint32_t groupCountY,
                                     uint32_t groupCountZ));
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
    MOCK_CONST_METHOD0(getIsaGraphicsAllocation, PtrRef<GraphicsAllocation>());
    MOCK_CONST_METHOD0(getModule, Module *());
    MOCK_CONST_METHOD0(getPerThreadDataHostMem, const void *());
    MOCK_CONST_METHOD0(getPerThreadDataSize, size_t());
    MOCK_CONST_METHOD0(getSimdSize, uint32_t());
    MOCK_CONST_METHOD0(getThreadsPerThreadGroup, uint32_t());
    MOCK_CONST_METHOD0(getThreadExecutionMask, uint32_t());
    MOCK_CONST_METHOD0(getCrossThreadDataHostMem, const void *());
    MOCK_CONST_METHOD0(getCrossThreadDataSize, size_t());
    MOCK_CONST_METHOD0(getResidencyContainer, const std::vector<GraphicsAllocation *> &());
    MOCK_CONST_METHOD0(getHasBarriers, bool());
    MOCK_CONST_METHOD0(getSlmSize, uint32_t());

    // TODO : automate generation of such forwarders (e.g. extend GMOCK macros)
    void mock_forwardToBase_getGroupSize(uint32_t &outGroupSizeX, uint32_t &outGroupSizeY, uint32_t &outGroupSizeZ) {
        this->BaseClass::getGroupSize(outGroupSizeX, outGroupSizeY, outGroupSizeZ);
    }
};

} // namespace ult
} // namespace L0
