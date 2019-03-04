#pragma once
#include "function.h"

#include "white_box.h"
#include "mock.h"

namespace L0 {
namespace ult {

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
};

} // namespace ult
} // namespace L0
