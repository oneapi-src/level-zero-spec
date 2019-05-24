#define MODULE_INTERNAL
#include "module_imp.h"
#undef MODULE_INTERNAL

#include "device.h"
#include "function.h"
#include "graphics_allocation.h"
#include "module_build_log.h"
#include "memory_manager.h"

#include "runtime/compiler_interface/compiler_interface.h"
#include "runtime/program/program.h"

#include <cassert>
#include <memory>
namespace vISA_temporary { // TODO : Remove once unified with IGC

static const uint32_t MAX_SYMBOL_NAME_LENGTH = 256;

/// GenSymType - Specify the symbol's type
enum GenSymType {
    S_NOTYPE = 0,     // The symbol's type is not specified
    S_UNDEF = 1,      // The symbol is undefined in this module
    S_FUNC = 2,       // The symbol is associated with a function
    S_GLOBAL_VAR = 3, // The symbol is associated with a global variable in global address space
    S_GLOBAL_VAR_CONST =
        4 // The symbol is associated with a global variable in constant address space
};

/// GenSymEntry - An symbol table entry
typedef struct {
    uint32_t s_type;   // The symbol's type
    uint32_t s_offset; // The binary offset of this symbol. This field
                       // is ignored if s_type is S_UNDEF
    uint32_t s_size;
    char s_name[MAX_SYMBOL_NAME_LENGTH]; // The symbol's name
} GenSymEntry;

/// GenRelocType - Specify the relocation's type
enum GenRelocType { R_NONE = 0, R_SYM_ADDR = 1 };

/// GenRelocEntry - An relocation table entry
typedef struct {
    uint32_t r_type;                       // The relocation's type
    uint32_t r_offset;                     // The binary offset of the relocated target
    char r_symbol[MAX_SYMBOL_NAME_LENGTH]; // The relocation target symbol's name
} GenRelocEntry;

} // namespace vISA_temporary

namespace NEO_temporary {
struct LightweightOclProgram
    : public NEO::Program { // NEO refactor needed : decouple process gen binary, remove context
    static LightweightOclProgram *create(void *deviceRT) {
        assert(deviceRT != nullptr);
        LightweightOclProgram *prog =
            new LightweightOclProgram(static_cast<NEO::Device *>(deviceRT));
        return prog;
    }

    LightweightOclProgram(NEO::Device *deviceRT)
        : Program(*deviceRT->getExecutionEnvironment(), nullptr, false), deviceRT(deviceRT) {
        setDevice(deviceRT);
    }

    ~LightweightOclProgram() {}

    void buildSpirV(const char *input, uint32_t inputSize) {
        this->isSpirV = true;
        this->programBinaryType = CL_PROGRAM_BINARY_TYPE_INTERMEDIATE;

        NEO::CompilerInterface *compilerInterface =
            this->executionEnvironment.getCompilerInterface();
        assert(compilerInterface != nullptr);

        std::string internalOptions = this->internalOptions + " -cl-intel-has-buffer-offset-arg ";

        NEO::TranslationArgs inputArgs = {};
        inputArgs.pInput = const_cast<char *>(
            input); // this is a broken in the interface, input is considered const in the end
        inputArgs.InputSize = inputSize;
        inputArgs.pOptions = options.c_str();
        inputArgs.OptionsSize = (uint32_t)options.length();
        inputArgs.pInternalOptions = internalOptions.c_str();
        inputArgs.InternalOptionsSize = (uint32_t)internalOptions.length();
        inputArgs.pTracingOptions = nullptr;
        inputArgs.TracingOptionsCount = 0;
        inputArgs.GTPinInput = nullptr;

        cl_int retVal = CL_SUCCESS;
        retVal = compilerInterface->build(*this, inputArgs, false);
        if (retVal != CL_SUCCESS) {
            assert(false);
        }

        retVal = processGenBinary();
        if (retVal != CL_SUCCESS) {
            assert(false);
        }

        buildStatus = CL_BUILD_SUCCESS;
        programBinaryType = CL_PROGRAM_BINARY_TYPE_EXECUTABLE;
    }

    bool tryBuildAsLlvm(const char *input, uint32_t inputSize) {
        bool tryAsOclText = (false == NEO::Program::isValidLlvmBinary(input, inputSize));

        NEO::CompilerInterface *compilerInterface =
            this->executionEnvironment.getCompilerInterface();
        assert(compilerInterface != nullptr);

        std::string internalOptions = this->internalOptions + " -cl-intel-has-buffer-offset-arg ";

        NEO::TranslationArgs inputArgs = {};
        inputArgs.pInput = const_cast<char *>(input);
        inputArgs.InputSize = inputSize;
        inputArgs.pOptions = options.c_str();
        inputArgs.OptionsSize = (uint32_t)options.length();
        inputArgs.pInternalOptions = internalOptions.c_str();
        inputArgs.InternalOptionsSize = (uint32_t)internalOptions.length();
        inputArgs.pTracingOptions = nullptr;
        inputArgs.TracingOptionsCount = 0;
        inputArgs.GTPinInput = nullptr;

        this->isCreatedFromBinary = true;
        this->programBinaryType = CL_PROGRAM_BINARY_TYPE_INTERMEDIATE;

        struct CompileFromLlvmText : NEO::CompilerInterface {
            CompileFromLlvmText(bool useLlvmText)
                : wasUsingLlvmText(NEO::CompilerInterface::useLlvmText) {
                NEO::CompilerInterface::useLlvmText = useLlvmText;
            }
            ~CompileFromLlvmText() { NEO::CompilerInterface::useLlvmText = wasUsingLlvmText; }
            bool wasUsingLlvmText = false;
        } compileFromLlvmTextGuard(tryAsOclText);

        if (tryAsOclText && (inputArgs.InputSize > 0)) {
            // llvm requires llvm text to be null terminated, assert here instead if crashing in IGC
            assert(inputArgs.pInput[inputArgs.InputSize - 1] == '\0');
        }
        cl_int retVal = CL_SUCCESS;
        retVal = compilerInterface->build(*this, inputArgs, false);
        if (retVal != CL_SUCCESS) {
            return false;
        }
        assert(retVal == CL_SUCCESS);

        retVal = processGenBinary();
        assert(retVal == CL_SUCCESS);

        buildStatus = CL_BUILD_SUCCESS;
        programBinaryType = CL_PROGRAM_BINARY_TYPE_EXECUTABLE;
        return true;
    }
    bool createWithNativeBinary(const char *input, size_t inputSize) {
        cl_int retVal = CL_SUCCESS;

        this->storeGenBinary(input, inputSize);
        retVal = this->processGenBinary();
        assert(retVal == CL_SUCCESS);

        buildStatus = CL_BUILD_SUCCESS;
        programBinaryType = CL_PROGRAM_BINARY_TYPE_EXECUTABLE;
        return retVal == CL_SUCCESS;
    }

    NEO::Device *deviceRT;
    using NEO::Program::constantSurface;
    using NEO::Program::globalSurface;
    using NEO::Program::kernelInfoArray;
};

} // namespace NEO_temporary

namespace L0 {

ModuleImp::ModuleImp(Device *device, void *deviceRT, ModuleBuildLog *moduleBuildLog)
    : device(device), progRT(NEO_temporary::LightweightOclProgram::create(deviceRT)),
      moduleBuildLog(moduleBuildLog) {
    productFamily =
        reinterpret_cast<NEO::Device *>(deviceRT)->getHardwareInfo().platform.eProductFamily;
}

ModuleImp::~ModuleImp() {
    if (nullptr != progRT) {
        progRT->release();
    }
    deleteAllOwned(funcImmDatas);
}

bool ModuleImp::initialize(const xe_module_desc_t *desc) {
    // current assumptions - to be relaxed when implementation proceeds further
    assert(desc != nullptr);
    assert(desc->version == XE_API_HEADER_VERSION);
    assert(desc->pInputModule != nullptr);
    assert(desc->inputSize != 0);
    assert(desc->pBuildFlags == nullptr);
    bool success = true;

    if (desc->format == XE_MODULE_FORMAT_NATIVE) {
        success = this->progRT->createWithNativeBinary(
            reinterpret_cast<const char *>(desc->pInputModule), desc->inputSize);
        assert(success == true);
    } else if (desc->format == XE_MODULE_FORMAT_IL_SPIRV) {
        this->progRT->buildSpirV(reinterpret_cast<const char *>(desc->pInputModule),
                                 static_cast<uint32_t>(desc->inputSize));
    } else {
        if (desc->format == static_cast<xe_module_format_t>(-1)) { // unofficial support for llvm
            success =
                this->progRT->tryBuildAsLlvm(reinterpret_cast<const char *>(desc->pInputModule),
                                             static_cast<uint32_t>(desc->inputSize));
        } else {
            assert(0);
            success = false;
        }
    }

    if (success) {
        if (this->progRT->constantSurface != nullptr) {
            globalConstBuffer.rebind(new GraphicsAllocation(this->progRT->constantSurface));
        }

        if (this->progRT->globalSurface != nullptr) {
            globalVarBuffer.rebind(new GraphicsAllocation(this->progRT->globalSurface));
        }

        funcImmDatas.reserve(this->progRT->kernelInfoArray.size());
        for (auto &ki : this->progRT->kernelInfoArray) {
            assert(ki->kernelAllocation != nullptr);
            assert((ki->patchInfo.mediavfestate == nullptr) ||
                   (ki->patchInfo.mediavfestate->PerThreadScratchSpace == 0));
            PtrOwn<FunctionImmutableData> funcImmData{new FunctionImmutableData};
            funcImmData->initialize(
                bindPtrRef(ki).weakRefReinterpret<void>(), *globalMemoryManager,
                &this->progRT->getDevice(0),
                this->progRT->getDevice(0).getDeviceInfo().computeUnitsUsedForScratch,
                globalConstBuffer.weakRef(), globalVarBuffer.weakRef());
            funcImmDatas.push_back(std::move(funcImmData));
        }
        this->maxGroupSize =
            static_cast<uint32_t>(this->progRT->getDevice(0).getDeviceInfo().maxWorkGroupSize);
    }
    return success;
}

PtrRef<FunctionImmutableData> ModuleImp::getFunctionImmutableData(CStringRef functionName) const {
    for (auto &funcImmData : funcImmDatas) {
        if (funcImmData->getSignature().name == functionName.get()) {
            return funcImmData.weakRef();
        }
    }
    return nullptr;
}

void ModuleImp::updateBuildLog(void *deviceRT) {
    const char *buildLog = this->progRT->getBuildLog(static_cast<NEO::Device *>(deviceRT));
    if (this->moduleBuildLog && buildLog)
        moduleBuildLog->appendString(buildLog, strlen(buildLog));
}

xe_result_t ModuleImp::createFunction(const xe_function_desc_t *desc,
                                      xe_function_handle_t *phFunction) {
    *phFunction = Function::create(productFamily, this, desc)->toHandle();
    return XE_RESULT_SUCCESS;
}

xe_result_t ModuleImp::getNativeBinary(size_t *pSize, uint8_t *pModuleNativeBinary) {
    size_t genBinarySize = 0;
    char *genBinary = this->progRT->getGenBinary(genBinarySize);

    *pSize = genBinarySize;
    if (pModuleNativeBinary != nullptr) {
        memcpy(pModuleNativeBinary, genBinary, genBinarySize);
    }
    return XE_RESULT_SUCCESS;
}

Module *Module::create(Device *device, const xe_module_desc_t *desc, void *deviceRT,
                       ModuleBuildLog *moduleBuildLog) {
    auto module = new ModuleImp(device, deviceRT, moduleBuildLog);

    module->initialize(desc);
    module->updateBuildLog(deviceRT);

    return module;
}

} // namespace L0
