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
        device.reset(new Mock<Device>);
        module.reset(new Mock<Module>);
        kernelInfo.rebind(new OCLRT::KernelInfo{});
        funcInfo.kernelInfoRT = kernelInfo.weakRefReinterpret<void>();

        function.reset(new Mock<Function>);
        function->module = module.get();

        function->immFuncInfo.rebind(&funcInfo);
    }

    void TearDown() override {
        delete function.release();
        kernelInfo.deleteOwned();
    }

    OCLRT::SPatchAllocateStatelessPrintfSurface printfSurfaceToken;
    PtrOwn<OCLRT::KernelInfo> kernelInfo = nullptr;
    ImmutableFunctionInfo funcInfo = {};
    std::unique_ptr<Mock<Function>> function;
    std::unique_ptr<Mock<Module>> module;
    std::unique_ptr<Mock<Device>> device;
};

TEST_F(FunctionPrintfTest, hasPrintfOutputReturnsTrueWhenPrintfIsUsed) {
    kernelInfo->patchInfo.pAllocateStatelessPrintfSurface = &printfSurfaceToken;
    EXPECT_TRUE(function->hasPrintfOutput());
}

TEST_F(FunctionPrintfTest, hasPrintfOutputReturnsFalseWhenPrintfNotUsed) {
    kernelInfo->patchInfo.pAllocateStatelessPrintfSurface = nullptr;
    EXPECT_FALSE(function->hasPrintfOutput());
}

TEST_F(FunctionPrintfTest, createPrintfBufferCreatesOnlyWhenUsingPrintf) {
    kernelInfo->patchInfo.pAllocateStatelessPrintfSurface = &printfSurfaceToken;

    EXPECT_TRUE(function->hasPrintfOutput());
    EXPECT_CALL(*module, getDevice).WillRepeatedly(Return(device.get()));

    xe_function_desc_t funDesc = {};
    funDesc.version = XE_API_HEADER_VERSION;
    funDesc.pFunctionName = "mock";

    function->createPrintfBuffer();

    EXPECT_NE(nullptr, function->getPrintfBufferAllocation());
}

TEST_F(FunctionPrintfTest, createPrintfBufferAddsAllocationToResidencyContainer) {
    kernelInfo->patchInfo.pAllocateStatelessPrintfSurface = &printfSurfaceToken;

    EXPECT_TRUE(function->hasPrintfOutput());
    EXPECT_CALL(*module, getDevice).WillRepeatedly(Return(device.get()));

    xe_function_desc_t funDesc = {};
    funDesc.version = XE_API_HEADER_VERSION;
    funDesc.pFunctionName = "mock";

    function->createPrintfBuffer();

    auto printfBufferAllocation = function->getPrintfBufferAllocation();
    EXPECT_NE(nullptr, printfBufferAllocation);

    EXPECT_NE(0u, function->residencyContainer.size());
    EXPECT_EQ(function->residencyContainer[0], printfBufferAllocation);
}

TEST_F(FunctionPrintfTest, createPrintfBufferDoesNotCreateWhenNotUsingPrintf) {
    kernelInfo->patchInfo.pAllocateStatelessPrintfSurface = nullptr;

    EXPECT_FALSE(function->hasPrintfOutput());

    xe_function_desc_t funDesc = {};
    funDesc.version = XE_API_HEADER_VERSION;
    funDesc.pFunctionName = "mock";

    function->createPrintfBuffer();

    EXPECT_EQ(nullptr, function->getPrintfBufferAllocation());
}

} // namespace ult
} // namespace L0
