#include "device.h"
#include "graphics_allocation.h"

#include "mock_compiler.h"
#include "mock_device.h"
#include "mock_function.h"
#include "mock_module.h"

#include "runtime/device/device.h"
#include "runtime/gmm_helper/gmm_helper.h"
#include "runtime/helpers/aligned_memory.h"
#include "runtime/helpers/file_io.h"
#include "runtime/platform/platform.h"

#include "gtest/gtest.h"
#include "test.h"

#include <fstream>
#include "global_fixture.h"

namespace L0 {
namespace ult {

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

class FunctionPrintfTest : public GlobalFixtureTest {
  public:
    void SetUp() override {
        GlobalFixtureTest::SetUp();
        device.reset(new Mock<Device>);
        module.reset(new Mock<Module>);
        kernelInfo.rebind(new NEO::KernelInfo{});
        funcInfo.kernelInfoRT = kernelInfo.weakRefReinterpret<void>();

        function.reset(new ::testing::NiceMock<Mock<Function>>);
        function->module = module.get();

        function->immFuncInfo.rebind(&funcInfo);
        printfSurfaceToken.DataParamOffset = -1;
        printfSurfaceToken.DataParamSize = 0;

        ON_CALL(*function, hasPrintfOutput).WillByDefault(Invoke(function.get(), &Mock<Function>::mock_forwardToBase_hasPrintfOutput));
    }

    void TearDown() override {
        delete function.release();
        kernelInfo.deleteOwned();
        GlobalFixtureTest::TearDown();
    }

    NEO::SPatchAllocateStatelessPrintfSurface printfSurfaceToken;
    PtrOwn<NEO::KernelInfo> kernelInfo = nullptr;
    ImmutableFunctionInfo funcInfo = {};
    std::unique_ptr<Mock<Function>> function;
    std::unique_ptr<Mock<Module>> module;
    std::unique_ptr<Mock<Device>> device;
};

class FunctionPrintfFromSpirvTest : public GlobalFixtureTest {
  public:
    void SetUp() override {
        GlobalFixtureTest::SetUp();
        platform = NEO::constructPlatform();
        auto success = platform->initialize();
        ASSERT_TRUE(success);

        auto deviceRT = platform->getDevice(0);

        // do not call GMM cachePolicyGetMemoryObject, gmm is not loaded
        deviceRT->getExecutionEnvironment()->getGmmHelper()->setSimplifiedMocsTableUsage(true);

        ASSERT_NE(nullptr, deviceRT);
        device.reset(Device::create(deviceRT));

        void *spirvData = nullptr;

        size_t spvModuleSize = loadDataFromFile(
            "test_files/spv_modules/printf_kernel.spv",
            spirvData);

        ASSERT_NE(0U, spvModuleSize);

        xe_module_desc_t modDesc = {};
        modDesc.version = XE_MODULE_DESC_VERSION_CURRENT;
        modDesc.format = XE_MODULE_FORMAT_IL_SPIRV;
        modDesc.inputSize = static_cast<uint32_t>(spvModuleSize);
        modDesc.pInputModule = reinterpret_cast<const uint8_t *>(spirvData);

        UserRealCompilerGuard realCompilerGuard;

        module.reset(whitebox_cast(Module::create(device.get(), &modDesc, deviceRT, nullptr)));
        ASSERT_NE(nullptr, module);

        deleteDataReadFromFile(spirvData);
        spirvData = nullptr;

        funDesc.version = XE_FUNCTION_DESC_VERSION_CURRENT;
        funDesc.pFunctionName = "test_printf";
    }

    void TearDown() override {
        GlobalFixtureTest::TearDown();
    }

    xe_function_desc_t funDesc = {};
    NEO::Platform *platform = nullptr;
    std::unique_ptr<Module> module;
    std::unique_ptr<L0::Device> device;
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
    funDesc.version = XE_FUNCTION_DESC_VERSION_CURRENT;
    funDesc.pFunctionName = "mock";

    function->createPrintfBuffer();

    EXPECT_NE(nullptr, function->getPrintfBufferAllocation());
}

TEST_F(FunctionPrintfTest, createPrintfBufferAddsAllocationToResidencyContainer) {
    kernelInfo->patchInfo.pAllocateStatelessPrintfSurface = &printfSurfaceToken;

    EXPECT_TRUE(function->hasPrintfOutput());
    EXPECT_CALL(*module, getDevice).WillRepeatedly(Return(device.get()));

    xe_function_desc_t funDesc = {};
    funDesc.version = XE_FUNCTION_DESC_VERSION_CURRENT;
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
    funDesc.version = XE_FUNCTION_DESC_VERSION_CURRENT;
    funDesc.pFunctionName = "mock";

    function->createPrintfBuffer();

    EXPECT_EQ(nullptr, function->getPrintfBufferAllocation());
}

TEST_F(FunctionPrintfTest, createPrintfBufferPatchesCrossThreadData) {
    ON_CALL(*module, getDevice).WillByDefault(Return(device.get()));
    EXPECT_CALL(*module, getDevice).Times(1);

    uint32_t *crossThreadData = new uint32_t[4];
    printfSurfaceToken.DataParamOffset = 0;
    printfSurfaceToken.DataParamSize = sizeof(uintptr_t);
    kernelInfo->patchInfo.pAllocateStatelessPrintfSurface = &printfSurfaceToken;

    function->crossThreadData = reinterpret_cast<char *>(crossThreadData);

    function->createPrintfBuffer();

    auto printfBufferAllocation = function->getPrintfBufferAllocation();
    EXPECT_NE(nullptr, printfBufferAllocation);

    auto printfBufferAddressPatched = *reinterpret_cast<uintptr_t *>(crossThreadData);
    auto printfBufferGpuAddressOffset = static_cast<uintptr_t>(printfBufferAllocation->getGpuAddressOffsetFromHeapBase());

    EXPECT_EQ(printfBufferGpuAddressOffset, printfBufferAddressPatched);

    function->crossThreadData = nullptr;
    delete crossThreadData;
}

TEST_F(FunctionPrintfFromSpirvTest, initializePutsPrintfBufferAllocationAfterArgsInResidencyContainer) {
    auto function = std::make_unique<::testing::NiceMock<Mock<Function>>>();
    ASSERT_NE(nullptr, function);

    ON_CALL(*function, hasPrintfOutput).WillByDefault(Invoke(function.get(), &Mock<Function>::mock_forwardToBase_hasPrintfOutput));

    function->module = module.get();
    function->initialize(&funDesc);

    ASSERT_EQ(3u, function->residencyContainer.size());
    EXPECT_EQ(function->residencyContainer[2], function->getPrintfBufferAllocation());
}

} // namespace ult
} // namespace L0
