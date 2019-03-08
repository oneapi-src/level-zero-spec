#include "mock_function.h"

#include "runtime/helpers/aligned_memory.h"

#include "gtest/gtest.h"
#include "test.h"

namespace L0 {
namespace ult {

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

TEST(FunctionImp, crossThreadDataIsCorrectlyPatchedWithGlobalWorkSize) {
    uint32_t *crossThreadData = reinterpret_cast<uint32_t *>(alignedMalloc(sizeof(uint32_t[3]), 32));

    OCLRT::KernelInfo *kernelInfo = new OCLRT::KernelInfo{};
    kernelInfo->workloadInfo.globalWorkSizeOffsets[0] = 0 * sizeof(uint32_t);
    kernelInfo->workloadInfo.globalWorkSizeOffsets[1] = 1 * sizeof(uint32_t);
    kernelInfo->workloadInfo.globalWorkSizeOffsets[2] = 2 * sizeof(uint32_t);

    Mock<Function> function;
    function.kernelInfo = kernelInfo;
    function.crossThreadData = reinterpret_cast<char *>(crossThreadData);
    ON_CALL(function, getGroupSize(_, _, _))
        .WillByDefault(Invoke(&function, &Mock<Function>::mock_forwardToBase_getGroupSize));
    function.groupSizeX = 2;
    function.groupSizeY = 3;
    function.groupSizeZ = 5;

    function.FunctionImp::setGroupCount(7, 11, 13);
    auto crossThread = function.FunctionImp::getCrossThreadDataHostMem();
    ASSERT_NE(nullptr, crossThread);
    const uint32_t *groupCounts = reinterpret_cast<const uint32_t *>(crossThread);
    EXPECT_EQ(2U * 7U, groupCounts[0]);
    EXPECT_EQ(3U * 11U, groupCounts[1]);
    EXPECT_EQ(5U * 13U, groupCounts[2]);
}

} // namespace ult
} // namespace L0
