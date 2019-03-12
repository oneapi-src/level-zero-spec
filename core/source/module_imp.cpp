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

namespace OCLRT_temporary {
struct LightweightOclProgram : public OCLRT::Program { // NEO refactor needed : decouple process gen binary, remove context
    static LightweightOclProgram *create(void *deviceRT) {
        assert(deviceRT != nullptr);
        LightweightOclProgram *prog = new LightweightOclProgram(static_cast<OCLRT::Device *>(deviceRT));
        return prog;
    }

    LightweightOclProgram(OCLRT::Device *deviceRT) : Program(*deviceRT->getExecutionEnvironment(), nullptr, false), deviceRT(deviceRT) {
        setDevice(deviceRT);
    }

    ~LightweightOclProgram() {
    }

    void buildSpirV(const char *input, uint32_t inputSize) {
        this->isSpirV = true;
        this->programBinaryType = CL_PROGRAM_BINARY_TYPE_INTERMEDIATE;

        OCLRT::CompilerInterface *pCompilerInterface = this->executionEnvironment.getCompilerInterface();
        assert(pCompilerInterface != nullptr);

        std::string internalOptions = this->internalOptions + " -cl-intel-greater-than-4GB-buffer-required"; // Disable surface states for buffers for now

        OCLRT::TranslationArgs inputArgs = {};
        inputArgs.pInput = const_cast<char *>(input); // this is a broken in the interface, input is considered const in the end
        inputArgs.InputSize = inputSize;
        inputArgs.pOptions = options.c_str();
        inputArgs.OptionsSize = (uint32_t)options.length();
        inputArgs.pInternalOptions = internalOptions.c_str();
        inputArgs.InternalOptionsSize = (uint32_t)internalOptions.length();
        inputArgs.pTracingOptions = nullptr;
        inputArgs.TracingOptionsCount = 0;
        inputArgs.GTPinInput = nullptr;

        cl_int retVal = CL_SUCCESS;
        retVal = pCompilerInterface->build(*this, inputArgs, false);
        assert(retVal == CL_SUCCESS);

        retVal = processGenBinary();
        assert(retVal == CL_SUCCESS);

        buildStatus = CL_BUILD_SUCCESS;
        programBinaryType = CL_PROGRAM_BINARY_TYPE_EXECUTABLE;
    }

    OCLRT::Device *deviceRT;
    using OCLRT::Program::kernelInfoArray;
};

} // namespace OCLRT_temporary

namespace L0 {

ModuleImp::ModuleImp(Device *device, void *deviceRT, ModuleBuildLog *moduleBuildLog)
    : device(device),
      progRT(OCLRT_temporary::LightweightOclProgram::create(deviceRT)),
      moduleBuildLog(moduleBuildLog) {}

ModuleImp::~ModuleImp() {
    progRT->release();
    deleteAllOwned(immFuncInfos);
}

bool ModuleImp::initialize(const xe_module_desc_t *desc) {
    // current assumptions - to be relaxed when implementation proceeds further
    assert(desc != nullptr);
    assert(desc->version == XE_API_HEADER_VERSION);
    assert(desc->format == XE_MODULE_FORMAT_IL_SPIRV);
    assert(desc->pInputModule != nullptr);
    assert(desc->inputSize != 0);
    assert(desc->pBuildFlags == nullptr);

    cl_int errorCode = 0;
    this->progRT->buildSpirV(desc->pInputModule, desc->inputSize);
    // allocate graphics memory for ISA upfront to avoid critical sections at function create time
    auto memoryManager = this->device->getMemoryManager();
    immFuncInfos.reserve(this->progRT->kernelInfoArray.size());
    for (auto &ki : this->progRT->kernelInfoArray) {
        auto kernelIsaSize = ki->heapInfo.pKernelHeader->KernelHeapSize;
        auto alloc = memoryManager->allocateGraphicsMemoryForIsa(bindPtrRef(ki->heapInfo.pKernelHeap), kernelIsaSize);
        assert(ki->kernelAllocation != nullptr);
        PtrOwn<ImmutableFunctionInfo> immFuncInfo{new ImmutableFunctionInfo{bindPtrRef(ki).weakRefReinterpret<void>(), std::move(alloc)}};
        immFuncInfos.push_back(std::move(immFuncInfo));
    }

    return true;
}

PtrRef<ImmutableFunctionInfo> ModuleImp::getImmutableFunctionInfo(CStringRef functionName) const {
    for (auto &immFuncInfo : immFuncInfos) {
        auto kernelInfoRT = immFuncInfo->kernelInfoRT.weakRefReinterpret<OCLRT::KernelInfo>();
        if (kernelInfoRT->name == functionName.get()) {
            return immFuncInfo.weakRef();
        }
    }
    return nullptr;
}

void ModuleImp::updateBuildLog(void *deviceRT) {
    const char *buildLog = this->progRT->getBuildLog(static_cast<OCLRT::Device *>(deviceRT));
    if (this->moduleBuildLog && buildLog)
       moduleBuildLog->appendString(buildLog, strlen(buildLog));
}

xe_result_t ModuleImp::createFunction(const xe_function_desc_t *desc, xe_function_handle_t *phFunction) {
    *phFunction = Function::create(this, desc)->toHandle();
    return XE_RESULT_SUCCESS;
}

Module *Module::create(Device *device, const xe_module_desc_t *desc,
                       void *deviceRT, ModuleBuildLog *moduleBuildLog) {
    auto module = new ModuleImp(device, deviceRT, moduleBuildLog);

    module->initialize(desc);
    module->updateBuildLog(deviceRT);

    return module;
}

} // namespace L0
