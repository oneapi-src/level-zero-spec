#include "mock_function.h"

#include "runtime/helpers/aligned_memory.h"

#include "gtest/gtest.h"
#include "test.h"

namespace L0 {
namespace ult {

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

TEST(FunctionImp, crossThreadDataIsCorrectlyPatchedWithGlobalWorkSizeAndGroupCount) {
    uint32_t *crossThreadData = reinterpret_cast<uint32_t *>(alignedMalloc(sizeof(uint32_t[6]), 32));

    OCLRT::KernelInfo *kernelInfo{new OCLRT::KernelInfo{}};
    kernelInfo->workloadInfo.globalWorkSizeOffsets[0] = 0 * sizeof(uint32_t);
    kernelInfo->workloadInfo.globalWorkSizeOffsets[1] = 1 * sizeof(uint32_t);
    kernelInfo->workloadInfo.globalWorkSizeOffsets[2] = 2 * sizeof(uint32_t);
    kernelInfo->workloadInfo.numWorkGroupsOffset[0] = 3 * sizeof(uint32_t);
    kernelInfo->workloadInfo.numWorkGroupsOffset[1] = 4 * sizeof(uint32_t);
    kernelInfo->workloadInfo.numWorkGroupsOffset[2] = 5 * sizeof(uint32_t);
    ImmutableFunctionInfo funcInfo = {};
    funcInfo.kernelInfoRT = reinterpret_cast<void *>(kernelInfo);

    Mock<Function> function;
    function.immFuncInfo = &funcInfo;
    function.crossThreadData = reinterpret_cast<char *>(crossThreadData);
    ON_CALL(function, getGroupSize(_, _, _))
        .WillByDefault(Invoke(&function, &Mock<Function>::mock_forwardToBase_getGroupSize));
    function.groupSizeX = 2;
    function.groupSizeY = 3;
    function.groupSizeZ = 5;

    function.FunctionImp::setGroupCount(7, 11, 13);
    auto crossThread = function.FunctionImp::getCrossThreadDataHostMem();
    ASSERT_NE(nullptr, crossThread);
    const uint32_t *globalWorkSizes = reinterpret_cast<const uint32_t *>(crossThread);
    EXPECT_EQ(2U * 7U, globalWorkSizes[0]);
    EXPECT_EQ(3U * 11U, globalWorkSizes[1]);
    EXPECT_EQ(5U * 13U, globalWorkSizes[2]);

    const uint32_t *numGroups = globalWorkSizes + 3;
    EXPECT_EQ(7U, numGroups[0]);
    EXPECT_EQ(11U, numGroups[1]);
    EXPECT_EQ(13U, numGroups[2]);

    delete kernelInfo;
}

} // namespace ult
} // namespace L0
