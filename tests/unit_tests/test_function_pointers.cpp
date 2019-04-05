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

std::vector<char> compileLlvmToGenBinary(NEO::CompilerInterface &compilerInterface, NEO::Device *deviceRT,
                                         const char *llvm, uint32_t llvmLen) {
    NEO::TranslationArgs inputArgs = {};
    inputArgs.pInput = const_cast<char *>(llvm);
    inputArgs.InputSize = llvmLen;
    inputArgs.pOptions = "";
    inputArgs.OptionsSize = 0;
    inputArgs.pInternalOptions = "";
    inputArgs.InternalOptionsSize = 0;
    inputArgs.pTracingOptions = nullptr;
    inputArgs.TracingOptionsCount = 0;
    inputArgs.GTPinInput = nullptr;

    struct DummyProgram : NEO::Program {
        DummyProgram(NEO::Device *deviceRT) : Program(*deviceRT->getExecutionEnvironment(), nullptr, false) {
            setDevice(deviceRT);
            this->isCreatedFromBinary = true;
            this->programBinaryType = CL_PROGRAM_BINARY_TYPE_INTERMEDIATE;
        }
    };

    struct CompileFromLlvmText : NEO::CompilerInterface {
        CompileFromLlvmText() : wasUsingLlvmText(NEO::CompilerInterface::useLlvmText) {
            NEO::CompilerInterface::useLlvmText = true;
            // NEO change required : 
            //--- a/runtime/compiler_interface/compiler_interface.cpp
            //+++ b/runtime/compiler_interface/compiler_interface.cpp
            //@@ -51,6 +51,9 @@ cl_int CompilerInterface::build(
            //             intermediateCodeType = IGC::CodeType::spirV;
            //         } else {
            //             intermediateCodeType = IGC::CodeType::llvmBc;
            //+            if (useLlvmText == true) {
            //+                intermediateCodeType = IGC::CodeType::llvmLl;
            //+            }
            //         }
        }
        ~CompileFromLlvmText() {
            NEO::CompilerInterface::useLlvmText = wasUsingLlvmText;
        }
        bool wasUsingLlvmText = false;
    } compileFromLlvmTextGuard;

    if (inputArgs.InputSize > 0) {
        // llvm requires llvm text to be null terminated, assert here instead if crashing in IGC
        assert(inputArgs.pInput[inputArgs.InputSize - 1] == '\0');
    }
    cl_int retVal = CL_SUCCESS;
    DummyProgram program{deviceRT};
    retVal = compilerInterface.build(program, inputArgs, false);
    assert(retVal == CL_SUCCESS);

    size_t binarySize = 0;
    char *binary = program.getGenBinary(binarySize);
    return std::vector<char>(binary, binary + binarySize);
}

// Reason for DISABLED :
// Requires special version of IGC (237a7572207588a5660d906bff2dcde22136f664). 
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

    std::vector<char> genBinary = compileLlvmToGenBinary(*deviceRT->getExecutionEnvironment()->getCompilerInterface(), deviceRT,
                                                         llvmModuleTxt.c_str(), static_cast<uint32_t>(llvmModuleTxt.size() + 1));

    xe_module_desc_t modDesc = {};
    modDesc.version = XE_MODULE_DESC_VERSION_CURRENT;
    modDesc.format = XE_MODULE_FORMAT_NATIVE;
    modDesc.inputSize = static_cast<uint32_t>(genBinary.size());
    modDesc.pInputModule = genBinary.data();

    auto module = whitebox_cast(Module::create(device, &modDesc, deviceRT, nullptr));
    ASSERT_NE(nullptr, module);

    xe_function_desc_t funDesc = {};
    funDesc.version = XE_FUNCTION_DESC_VERSION_CURRENT;
    funDesc.pFunctionName = "testStackCallMain";
    auto function = whitebox_cast(Function::create(deviceRT->getHardwareInfo().pPlatform->eProductFamily, module, &funDesc));
    ASSERT_NE(nullptr, function);

    function->destroy();
    module->destroy();
}

} // namespace ult
} // namespace L0
