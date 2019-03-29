#include "graphics_allocation.h"
#include "mock_compiler.h"
#include "mock_device.h"
#include "mock_function.h"
#include "mock_image.h"
#include "mock_memory_manager.h"
#include "mock_module.h"
#include "mock_module_precompiled.h"
#include "module.h"

#include "runtime/compiler_interface/compiler_interface.h"
#include "runtime/device/device.h"
#include "runtime/gmm_helper/gmm_helper.h"
#include "runtime/helpers/aligned_memory.h"
#include "runtime/platform/platform.h"

#include "gtest/gtest.h"
#include "test.h"

#include <fstream>
#include <vector>

namespace L0 {
namespace ult {

using ::testing::Return;

// Reason for DISABLED :
// Requires special version of IGC + EnableFunctionPointer regkey
// Works only with SKL (due to current IGC limitations)
TEST(FunctionPointers, DISABLED_compileToDeviceBinary) {
    UserRealCompilerGuard realCompilerGuard;

    std::string filename = "test_files/llvm_modules/function_pointers.ll";
    std::string functionName;
    std::string moduleName;

    auto platform = NEO::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    auto deviceRT = platform->getDevice(0);
    ASSERT_NE(nullptr, deviceRT);
    auto device = Device::create(deviceRT);

    size_t llvmModuleSize = 0;
    auto llvmModuleRaw = readBinaryTestFile(filename, llvmModuleSize);
    std::string llvmModuleTxt{llvmModuleRaw.get(), llvmModuleSize};
    ASSERT_FALSE(llvmModuleTxt.empty());

    xe_module_desc_t modDesc = {};
    modDesc.version = XE_MODULE_DESC_VERSION_CURRENT;
    modDesc.format = static_cast<xe_module_format_t>(-1); // -1 for unofficial llvm IR support
    modDesc.inputSize = llvmModuleTxt.size() + 1;
    modDesc.pInputModule = reinterpret_cast<const uint8_t *>(llvmModuleTxt.data());

    auto module = whitebox_cast(Module::create(device, &modDesc, deviceRT, nullptr));
    ASSERT_NE(nullptr, module);

    xe_function_desc_t funDesc = {};
    funDesc.version = XE_FUNCTION_DESC_VERSION_CURRENT;
    funDesc.pFunctionName = "testStackCallMain";
    auto function =
            whitebox_cast(Function::create(deviceRT->getHardwareInfo().pPlatform->eProductFamily,
                     module, &funDesc));
    ASSERT_NE(nullptr, function);

    function->destroy();
    module->destroy();
}

} // namespace ult
} // namespace L0
