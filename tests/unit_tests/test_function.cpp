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

class FunctionPrintfTest : public ::testing::Test {
  public:
    void SetUp() override {
        kernelInfo.rebind(new OCLRT::KernelInfo{});
        funcInfo.kernelInfoRT = kernelInfo.weakRefReinterpret<void>();
        function.immFuncInfo.rebind(&funcInfo);
    }

    void TearDown() override {
        kernelInfo.deleteOwned();
    }

    OCLRT::SPatchAllocateStatelessPrintfSurface printfSurfaceToken;
    PtrOwn<OCLRT::KernelInfo> kernelInfo = nullptr;
    ImmutableFunctionInfo funcInfo = {};
    Mock<Function> function;
};

TEST(FunctionImp, crossThreadDataIsCorrectlyPatchedWithGlobalWorkSizeAndGroupCount) {
    uint32_t *crossThreadData = reinterpret_cast<uint32_t *>(alignedMalloc(sizeof(uint32_t[6]), 32));

    PtrOwn<OCLRT::KernelInfo> kernelInfo{new OCLRT::KernelInfo{}};
    kernelInfo->workloadInfo.globalWorkSizeOffsets[0] = 0 * sizeof(uint32_t);
    kernelInfo->workloadInfo.globalWorkSizeOffsets[1] = 1 * sizeof(uint32_t);
    kernelInfo->workloadInfo.globalWorkSizeOffsets[2] = 2 * sizeof(uint32_t);
    kernelInfo->workloadInfo.numWorkGroupsOffset[0] = 3 * sizeof(uint32_t);
    kernelInfo->workloadInfo.numWorkGroupsOffset[1] = 4 * sizeof(uint32_t);
    kernelInfo->workloadInfo.numWorkGroupsOffset[2] = 5 * sizeof(uint32_t);
    ImmutableFunctionInfo funcInfo = {};
    funcInfo.kernelInfoRT = kernelInfo.weakRefReinterpret<void>();

    Mock<Function> function;
    function.immFuncInfo.rebind(&funcInfo);
    function.crossThreadData = reinterpret_cast<char *>(crossThreadData);
    EXPECT_CALL(function, getGroupSize(_, _, _))
        .WillRepeatedly(Invoke(&function, &Mock<Function>::mock_forwardToBase_getGroupSize));
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

    kernelInfo.deleteOwned();
}

TEST(FunctionImp, suggestGroupSizeClampsToMaxGroupSize) {
    OCLRT::SPatchExecutionEnvironment execEnv = {};
    PtrOwn<OCLRT::KernelInfo> kernelInfo{new OCLRT::KernelInfo{}};
    kernelInfo->patchInfo.executionEnvironment = &execEnv;
    ImmutableFunctionInfo funcInfo = {};
    funcInfo.kernelInfoRT = kernelInfo.weakRefReinterpret<void>();
    execEnv.LargestCompiledSIMDSize = 16;

    Mock<Module> module;
    EXPECT_CALL(module, getMaxGroupSize)
        .WillRepeatedly(Return(8));

    Mock<Function> function;
    function.immFuncInfo.rebind(&funcInfo);
    function.module = &module;
    uint32_t groupSize[3];
    function.FunctionImp::suggestGroupSize(256, 1, 1, groupSize, groupSize + 1, groupSize + 2);
    EXPECT_EQ(8U, groupSize[0]);
    EXPECT_EQ(1U, groupSize[1]);
    EXPECT_EQ(1U, groupSize[2]);
}

TEST_F(FunctionPrintfTest, hasPrintfOutputReturnsTrueWhenPrintfIsUsed) {
    kernelInfo->patchInfo.pAllocateStatelessPrintfSurface = &printfSurfaceToken;
    EXPECT_TRUE(function.hasPrintfOutput());
}

TEST_F(FunctionPrintfTest, hasPrintfOutputReturnsFalseWhenPrintfNotUsed) {
    kernelInfo->patchInfo.pAllocateStatelessPrintfSurface = nullptr;
    EXPECT_FALSE(function.hasPrintfOutput());
}

TEST_F(FunctionPrintfTest, createPrintfHandlerCreatesOnlyWhenUsingPrintf) {
    kernelInfo->patchInfo.pAllocateStatelessPrintfSurface = &printfSurfaceToken;

    EXPECT_TRUE(function.hasPrintfOutput());
    Mock<Device> device;
    Mock<Module> module;
    EXPECT_CALL(module, getDevice).WillRepeatedly(Return(&device));

    function.module = &module;

    xe_function_desc_t funDesc = {};
    funDesc.version = XE_FUNCTION_DESC_VERSION_CURRENT;
    funDesc.pFunctionName = "mock";

    function.createPrintfHandler();

    EXPECT_NE(nullptr, function.getPrintfHandler());
}

TEST_F(FunctionPrintfTest, createPrintfHandlerDoesNotCreateWhenNotUsingPrintf) {
    kernelInfo->patchInfo.pAllocateStatelessPrintfSurface = nullptr;

    EXPECT_FALSE(function.hasPrintfOutput());

    Mock<Module> module;
    function.module = &module;

    xe_function_desc_t funDesc = {};
    funDesc.version = XE_FUNCTION_DESC_VERSION_CURRENT;
    funDesc.pFunctionName = "mock";

    function.createPrintfHandler();

    EXPECT_EQ(nullptr, function.getPrintfHandler());
}

using FunctionImpSuggestGroupSize = ::testing::TestWithParam<uint32_t>;

INSTANTIATE_TEST_CASE_P(,
                        FunctionImpSuggestGroupSize,
                        ::testing::Values(4, 7, 8, 16, 32, 192, 1024, 4097, 16000));

TEST_P(FunctionImpSuggestGroupSize, suggestGroupChoosesProperGroupSize) {
    OCLRT::SPatchExecutionEnvironment execEnv = {};
    PtrOwn<OCLRT::KernelInfo> kernelInfo{new OCLRT::KernelInfo{}};
    kernelInfo->patchInfo.executionEnvironment = &execEnv;
    ImmutableFunctionInfo funcInfo = {};
    funcInfo.kernelInfoRT = kernelInfo.weakRefReinterpret<void>();
    execEnv.LargestCompiledSIMDSize = 16;

    Mock<Module> module;
    EXPECT_CALL(module, getMaxGroupSize)
        .WillRepeatedly(Return(256));

    uint32_t size = GetParam();

    Mock<Function> function;
    function.immFuncInfo.rebind(&funcInfo);
    function.module = &module;
    uint32_t groupSize[3];
    function.FunctionImp::suggestGroupSize(size, 1, 1, groupSize, groupSize + 1, groupSize + 2);
    EXPECT_EQ(0U, size % groupSize[0]);
    EXPECT_EQ(0U, 1U % groupSize[1]);
    EXPECT_EQ(0U, 1U % groupSize[2]);

    function.FunctionImp::suggestGroupSize(size, size, 1, groupSize, groupSize + 1, groupSize + 2);
    EXPECT_EQ(0U, size % groupSize[0]);
    EXPECT_EQ(0U, size % groupSize[1]);
    EXPECT_EQ(0U, 1U % groupSize[2]);

    function.FunctionImp::suggestGroupSize(size, size, size, groupSize, groupSize + 1, groupSize + 2);
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
}

} // namespace ult
} // namespace L0
