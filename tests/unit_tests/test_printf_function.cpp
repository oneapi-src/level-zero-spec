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

        function.reset(new ::testing::NiceMock<Mock<Function>>);
        function->module.rebind(module.get());

        function->funcImmData.rebind(&funcInfo);
    }

    void TearDown() override {
        function.reset();
        GlobalFixtureTest::TearDown();
    }

    WhiteBox<FunctionImmutableData> funcInfo = {};
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

        size_t spvModuleSize =
            loadDataFromFile("test_files/spv_modules/printf_kernel.spv", spirvData);

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

    void TearDown() override { GlobalFixtureTest::TearDown(); }

    xe_function_desc_t funDesc = {};
    NEO::Platform *platform = nullptr;
    std::unique_ptr<Module> module;
    std::unique_ptr<L0::Device> device;
};

TEST_F(FunctionPrintfTest, createPrintfBufferCreatesOnlyWhenUsingPrintf) {
    funcInfo.signature.attributes.flags.hasPrintf = true;
    funcInfo.signature.implicitArgs.printfSurface.pointerSize = 4;
    EXPECT_TRUE(function->getImmutableData()->getSignature().attributes.flags.hasPrintf);
    EXPECT_CALL(*module, getDevice).WillRepeatedly(Return(device.get()));

    xe_function_desc_t funDesc = {};
    funDesc.version = XE_FUNCTION_DESC_VERSION_CURRENT;
    funDesc.pFunctionName = "mock";

    function->createPrintfBuffer();

    EXPECT_NE(nullptr, function->getPrintfBufferAllocation());
}

TEST_F(FunctionPrintfTest, createPrintfBufferAddsAllocationToResidencyContainer) {
    funcInfo.signature.attributes.flags.hasPrintf = true;
    funcInfo.signature.implicitArgs.printfSurface.pointerSize = 4;

    EXPECT_TRUE(function->getImmutableData()->getSignature().attributes.flags.hasPrintf);
    EXPECT_CALL(*module, getDevice).WillRepeatedly(Return(device.get()));

    xe_function_desc_t funDesc = {};
    funDesc.version = XE_FUNCTION_DESC_VERSION_CURRENT;
    funDesc.pFunctionName = "mock";

    function->createPrintfBuffer();

    auto printfBufferAllocation = function->getPrintfBufferAllocation();
    EXPECT_NE(nullptr, printfBufferAllocation);

    EXPECT_NE(0u, function->residencyContainer.size());
    EXPECT_EQ(function->residencyContainer[0], printfBufferAllocation.get());
}

TEST_F(FunctionPrintfTest, createPrintfBufferDoesNotCreateWhenNotUsingPrintf) {
    funcInfo.signature.attributes.flags.hasPrintf = false;

    EXPECT_FALSE(function->getImmutableData()->getSignature().attributes.flags.hasPrintf);

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
    funcInfo.signature.attributes.flags.hasPrintf = true;
    funcInfo.signature.implicitArgs.printfSurface.stateless = 0;
    funcInfo.signature.implicitArgs.printfSurface.pointerSize = sizeof(uintptr_t);

    function->crossThreadData.rebind(reinterpret_cast<uint8_t *>(crossThreadData));
    function->crossThreadDataSize = 4;

    function->createPrintfBuffer();

    auto printfBufferAllocation = function->getPrintfBufferAllocation();
    EXPECT_NE(nullptr, printfBufferAllocation);

    auto printfBufferAddressPatched = *reinterpret_cast<uintptr_t *>(crossThreadData);
    auto printfBufferGpuAddressOffset =
        static_cast<uintptr_t>(printfBufferAllocation->getGpuAddressOffsetFromHeapBase());

    EXPECT_EQ(printfBufferGpuAddressOffset, printfBufferAddressPatched);

    function->crossThreadData.rebind(nullptr);
    delete crossThreadData;
}

TEST_F(FunctionPrintfFromSpirvTest,
       initializePutsPrintfBufferAllocationAfterArgsInResidencyContainer) {
    auto function = std::make_unique<::testing::NiceMock<Mock<Function>>>();
    ASSERT_NE(nullptr, function);

    function->module.rebind(module.get());
    function->initialize(&funDesc);

    auto &container = function->residencyContainer;
    auto printfPos =
        std::find(container.begin(), container.end(), function->getPrintfBufferAllocation().get());
    EXPECT_NE(container.end(), printfPos);
    bool correctPos =
        printfPos >=
        container.begin() + function->getImmutableData()->getSignature().explicitArgs.args.size();
    EXPECT_TRUE(correctPos) << "Needs to be after explicit kernel args";
}

} // namespace ult
} // namespace L0
