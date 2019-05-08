#include "mock_device.h"
#include "mock_function.h"
#include "mock_module.h"

#include "runtime/helpers/aligned_memory.h"

#include "gtest/gtest.h"
#include "test.h"

namespace L0 {
namespace ult {

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

TEST(FunctionImp, crossThreadDataIsCorrectlyPatchedWithGlobalWorkSizeAndGroupCount) {
    uint32_t *crossThreadData =
        reinterpret_cast<uint32_t *>(alignedMalloc(sizeof(uint32_t[6]), 32));

    WhiteBox<::L0::FunctionImmutableData> funcInfo = {};
    funcInfo.signature.dispatchMetadata.globalWorkSize[0] = 0 * sizeof(uint32_t);
    funcInfo.signature.dispatchMetadata.globalWorkSize[1] = 1 * sizeof(uint32_t);
    funcInfo.signature.dispatchMetadata.globalWorkSize[2] = 2 * sizeof(uint32_t);
    funcInfo.signature.dispatchMetadata.numWorkGroups[0] = 3 * sizeof(uint32_t);
    funcInfo.signature.dispatchMetadata.numWorkGroups[1] = 4 * sizeof(uint32_t);
    funcInfo.signature.dispatchMetadata.numWorkGroups[2] = 5 * sizeof(uint32_t);

    Mock<Function> function;
    function.funcImmData.rebind(&funcInfo);
    function.crossThreadData.rebind(reinterpret_cast<uint8_t *>(crossThreadData));
    function.crossThreadDataSize = sizeof(uint32_t[6]);
    EXPECT_CALL(function, getGroupSize(_, _, _))
        .WillRepeatedly(Invoke(&function, &Mock<Function>::mock_forwardToBase_getGroupSize));
    function.groupSize[0] = 2;
    function.groupSize[1] = 3;
    function.groupSize[2] = 5;

    function.FunctionImp::setGroupCount(7, 11, 13);
    auto crossThread = function.FunctionImp::getCrossThreadData();
    ASSERT_NE(nullptr, crossThread.get());
    const uint32_t *globalWorkSizes = reinterpret_cast<const uint32_t *>(crossThread.get());
    EXPECT_EQ(2U * 7U, globalWorkSizes[0]);
    EXPECT_EQ(3U * 11U, globalWorkSizes[1]);
    EXPECT_EQ(5U * 13U, globalWorkSizes[2]);

    const uint32_t *numGroups = globalWorkSizes + 3;
    EXPECT_EQ(7U, numGroups[0]);
    EXPECT_EQ(11U, numGroups[1]);
    EXPECT_EQ(13U, numGroups[2]);

    function.crossThreadData.rebind(nullptr);
    alignedFree(crossThreadData);
}

TEST(FunctionImp, suggestGroupSizeClampsToMaxGroupSize) {
    NEO::SPatchExecutionEnvironment execEnv = {};
    PtrOwn<NEO::KernelInfo> kernelInfo{new NEO::KernelInfo{}};
    kernelInfo->patchInfo.executionEnvironment = &execEnv;
    FunctionImmutableData funcInfo = {};
    funcInfo.kernelInfoRT = kernelInfo.weakRefReinterpret<void>();
    execEnv.LargestCompiledSIMDSize = 16;

    Mock<Module> module;
    EXPECT_CALL(module, getMaxGroupSize).WillRepeatedly(Return(8));

    Mock<Function> function;
    function.funcImmData.rebind(&funcInfo);
    function.module.rebind(&module);
    uint32_t groupSize[3];
    function.FunctionImp::suggestGroupSize(256, 1, 1, groupSize, groupSize + 1, groupSize + 2);
    EXPECT_EQ(8U, groupSize[0]);
    EXPECT_EQ(1U, groupSize[1]);
    EXPECT_EQ(1U, groupSize[2]);

    kernelInfo.deleteOwned();
}

using FunctionImpSuggestGroupSize = ::testing::TestWithParam<uint32_t>;

INSTANTIATE_TEST_CASE_P(, FunctionImpSuggestGroupSize,
                        ::testing::Values(4, 7, 8, 16, 32, 192, 1024, 4097, 16000));

TEST_P(FunctionImpSuggestGroupSize, suggestGroupChoosesProperGroupSize) {
    NEO::SPatchExecutionEnvironment execEnv = {};
    PtrOwn<NEO::KernelInfo> kernelInfo{new NEO::KernelInfo{}};
    kernelInfo->patchInfo.executionEnvironment = &execEnv;
    FunctionImmutableData funcInfo = {};
    funcInfo.kernelInfoRT = kernelInfo.weakRefReinterpret<void>();
    execEnv.LargestCompiledSIMDSize = 16;

    Mock<Module> module;
    EXPECT_CALL(module, getMaxGroupSize).WillRepeatedly(Return(256));

    uint32_t size = GetParam();

    Mock<Function> function;
    function.funcImmData.rebind(&funcInfo);
    function.module.rebind(&module);
    uint32_t groupSize[3];
    function.FunctionImp::suggestGroupSize(size, 1, 1, groupSize, groupSize + 1, groupSize + 2);
    EXPECT_EQ(0U, size % groupSize[0]);
    EXPECT_EQ(0U, 1U % groupSize[1]);
    EXPECT_EQ(0U, 1U % groupSize[2]);

    function.FunctionImp::suggestGroupSize(size, size, 1, groupSize, groupSize + 1, groupSize + 2);
    EXPECT_EQ(0U, size % groupSize[0]);
    EXPECT_EQ(0U, size % groupSize[1]);
    EXPECT_EQ(0U, 1U % groupSize[2]);

    function.FunctionImp::suggestGroupSize(size, size, size, groupSize, groupSize + 1,
                                           groupSize + 2);
    EXPECT_EQ(0U, size % groupSize[0]);
    EXPECT_EQ(0U, size % groupSize[1]);
    EXPECT_EQ(0U, size % groupSize[2]);

    function.FunctionImp::suggestGroupSize(size, 1, 1, groupSize, groupSize + 1, groupSize + 2);
    EXPECT_EQ(0U, size % groupSize[0]);
    EXPECT_EQ(0U, 1U % groupSize[1]);
    EXPECT_EQ(0U, 1U % groupSize[2]);

    function.FunctionImp::suggestGroupSize(1, size, 1, groupSize, groupSize + 1, groupSize + 2);
    EXPECT_EQ(0U, 1U % groupSize[0]);
    EXPECT_EQ(0U, size % groupSize[1]);
    EXPECT_EQ(0U, 1U % groupSize[2]);

    function.FunctionImp::suggestGroupSize(1, 1, size, groupSize, groupSize + 1, groupSize + 2);
    EXPECT_EQ(0U, 1U % groupSize[0]);
    EXPECT_EQ(0U, 1U % groupSize[1]);
    EXPECT_EQ(0U, size % groupSize[2]);

    function.FunctionImp::suggestGroupSize(1, size, size, groupSize, groupSize + 1, groupSize + 2);
    EXPECT_EQ(0U, 1U % groupSize[0]);
    EXPECT_EQ(0U, size % groupSize[1]);
    EXPECT_EQ(0U, size % groupSize[2]);

    function.FunctionImp::suggestGroupSize(size, 1, size, groupSize, groupSize + 1, groupSize + 2);
    EXPECT_EQ(0U, size % groupSize[0]);
    EXPECT_EQ(0U, 1U % groupSize[1]);
    EXPECT_EQ(0U, size % groupSize[2]);

    kernelInfo.deleteOwned();
}

TEST(FunctionImp, setGroupSizeGuardsAgainst0SizeDispatch) {
    Mock<Function> function;
    EXPECT_EQ(XE_RESULT_ERROR_INVALID_PARAMETER, function.FunctionImp::setGroupSize(0U, 1U, 1U));
    EXPECT_EQ(XE_RESULT_ERROR_INVALID_PARAMETER, function.FunctionImp::setGroupSize(1U, 0U, 1U));
    EXPECT_EQ(XE_RESULT_ERROR_INVALID_PARAMETER, function.FunctionImp::setGroupSize(1U, 1U, 0U));
}

TEST(FunctionImp, setGroupSizeDoesNotGenerateLocalIdsIfNumChannelsIs0) {
    iOpenCL::SPatchThreadPayload payload{};
    NEO::SPatchExecutionEnvironment execEnv = {};
    PtrOwn<NEO::KernelInfo> kernelInfo{new NEO::KernelInfo{}};
    kernelInfo->patchInfo.executionEnvironment = &execEnv;
    kernelInfo->patchInfo.threadPayload = &payload;
    FunctionImmutableData funcInfo = {};
    funcInfo.kernelInfoRT = kernelInfo.weakRefReinterpret<void>();
    execEnv.LargestCompiledSIMDSize = 32;

    Mock<Module> module;
    Mock<Function> function;
    function.funcImmData.rebind(&funcInfo);
    function.module.rebind(&module);

    function.FunctionImp::setGroupSize(16U, 16U, 1U);
    std::vector<char> memBefore;
    {
        auto perThreadData =
            reinterpret_cast<const char *>(function.FunctionImp::getPerThreadData().get());
        memBefore.assign(perThreadData,
                         perThreadData + function.FunctionImp::getPerThreadDataSize());
    }

    function.FunctionImp::setGroupSize(8U, 32U, 1U);
    std::vector<char> memAfter;
    {
        auto perThreadData =
            reinterpret_cast<const char *>(function.FunctionImp::getPerThreadData().get());
        memAfter.assign(perThreadData,
                        perThreadData + function.FunctionImp::getPerThreadDataSize());
    }

    EXPECT_EQ(memAfter, memBefore);
    kernelInfo.deleteOwned();
}

} // namespace ult
} // namespace L0
