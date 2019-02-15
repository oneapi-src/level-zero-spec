#include "module.h"

#include "device.h"
#include "memory_manager.h"

#include "runtime/compiler_interface/compiler_interface.h"
#include "runtime/context/context.h"
#include "runtime/kernel/kernel.h"
#include "runtime/program/program.h"

#include <cassert>
#include <memory>

namespace OCLRT_temporary{
    struct LightweightOclProgram : public OCLRT::Program { // NEO refactor needed : decouple process gen binary, remove context
        static LightweightOclProgram *create(void *deviceRT){
            assert(deviceRT != nullptr);
            LightweightOclProgram *prog = new LightweightOclProgram(static_cast<OCLRT::Device*>(deviceRT));
            return prog;
        }

        LightweightOclProgram(OCLRT::Device *deviceRT) : Program(*deviceRT->getExecutionEnvironment(), nullptr, false), deviceRT(deviceRT) {
            setDevice(deviceRT);
        }

        ~LightweightOclProgram() {
        }

        void buildSpirV(const char *input, uint32_t inputSize){
            this->isSpirV = true;
            this->programBinaryType = CL_PROGRAM_BINARY_TYPE_INTERMEDIATE;

            OCLRT::CompilerInterface *pCompilerInterface = this->executionEnvironment.getCompilerInterface();
            assert(pCompilerInterface != nullptr);

            std::string internalOptions = this->internalOptions + " -cl-intel-greater-than-4GB-buffer-required"; // Disable surface states for buffers for now

            OCLRT::TranslationArgs inputArgs = {};
            inputArgs.pInput = const_cast<char*>(input); // this is a broken in the interface, input is considered const in the end
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
    };

    struct LightweightOclKernel : public OCLRT::Kernel {
        LightweightOclKernel(LightweightOclProgram *program, const OCLRT::KernelInfo &kernelInfo)
            : Kernel(program, kernelInfo, program->getDevice(0), false){
        }

        using Kernel::kernelArguments;
        using Kernel::kernelArgHandlers;
        using Kernel::kernelSvmGfxAllocations;

        using Kernel::numberOfBindingTableStates;
        using Kernel::localBindingTableOffset;
        using Kernel::pSshLocal;
        using Kernel::sshLocalSize;

        using Kernel::crossThreadData;
        using Kernel::crossThreadDataSize;

        using Kernel::privateSurface;
        using Kernel::privateSurfaceSize;

        using Kernel::usingSharedObjArgs;
        using Kernel::usingImagesOnly;
        using Kernel::auxTranslationRequired;
        using Kernel::patchedArgumentsNum;
        using Kernel::startOffset;
    };
}


namespace xe {

struct ModuleImp : public Module {
    ModuleImp(Device *device, void *deviceRT) : device(device), progRT(OCLRT_temporary::LightweightOclProgram::create(deviceRT)) {}

    virtual ~ModuleImp() {
        progRT->release();
    }

    xe_result_t destroy() override {
        delete this;
        return XE_RESULT_SUCCESS;
    }

    Device *getDevice() const override {
        return device;
    }

    bool initialize(const xe_module_desc_t *desc) {
        // current assumptions - to be relaxed when implementation proceeds further
        assert(desc != nullptr);
        assert(desc->version == XE_API_HEADER_VERSION);
        assert(desc->format == XE_MODULE_FORMAT_IL_SPIRV);
        assert(desc->pInputModule != nullptr);
        assert(desc->inputSize != 0);
        assert(desc->pBuildFlags == nullptr);

        cl_int errorCode = 0;
        this->progRT->buildSpirV(desc->pInputModule, desc->inputSize);

        return true;
    }

    const OCLRT::KernelInfo *getKernelInfoRT(const char *name) const {
        return progRT->getKernelInfo(name);
    }

    OCLRT_temporary::LightweightOclProgram *getProgramRT() const { // TODO : Decouple "program state shared across kernels" from OCLRT::Program object;
        return progRT;
    }

protected:
    Device *device  = nullptr;
    OCLRT_temporary::LightweightOclProgram *progRT = nullptr;
};

Module *Module::create(Device *device, const xe_module_desc_t *desc, void *deviceRT) {
    auto module = new ModuleImp(device, deviceRT);

    module->initialize(desc);
    return module;
}

struct FunctionImp : Function  {
    FunctionImp(Module *module) : module(module) {}

    virtual ~FunctionImp() {
        kernelRT->release();
    }

    xe_result_t destroy() override {
        delete this;
        return XE_RESULT_SUCCESS;
    }

    Module *getModule() const override {
        return module;
    }

    bool initialize(const xe_function_desc_t *desc) {
        assert(desc->version == XE_API_HEADER_VERSION);
        assert(desc->flags == 0);

        const OCLRT::KernelInfo *kernelInfoRT = static_cast<ModuleImp*>(module)->getKernelInfoRT(desc->pFunctionName);
        assert(kernelInfoRT != nullptr);
        kernelRT = new OCLRT_temporary::LightweightOclKernel(static_cast<ModuleImp*>(module)->getProgramRT(), *kernelInfoRT);
        kernelRT->initialize();

        return true;
    }

    const void *getIsaHostMem() const override {
        return kernelRT->getKernelHeap();
    }
    
    size_t getIsaSize() const override {
        return kernelRT->getKernelHeapSize();
    }

    OCLRT_temporary::LightweightOclKernel *getKernelRT() {
        return kernelRT;
    }
protected:
    OCLRT_temporary::LightweightOclKernel *kernelRT = nullptr;
    Module *module = nullptr;
};

Function *Function::create(Module *module, const xe_function_desc_t *desc) {
    auto function = new FunctionImp(module);
    function->initialize(desc);
    return function;
}

struct FunctionArgsImp : FunctionArgs {
    FunctionArgsImp(Function *function) : function(function) {}

    virtual ~FunctionArgsImp() {
    }

    xe_result_t destroy() override {
        delete this;
        return XE_RESULT_SUCCESS;
    }

    xe_result_t setValue(uint32_t argIndex, size_t argSize, const void *pArgValue) override {
        assert(argIndex < oclInternals.kernelArgHandlers.size());
        (this->*oclInternals.kernelArgHandlers[argIndex])(argIndex, argSize, pArgValue);
        return XE_RESULT_SUCCESS;
    }

    xe_result_t setArgBuffer(uint32_t argIndex, size_t argSize, const void *argVal) {
        const auto &kernelArgInfo = static_cast<FunctionImp*>(function)->getKernelRT()->getKernelInfo().kernelArgInfo[argIndex];
        // patchBufferOffset(kernelArgInfo, nullptr, nullptr); // stateless to stateful buffer offsets disabled

        auto patchLocation = ptrOffset(oclInternals.crossThreadData,
                                       kernelArgInfo.kernelArgPatchInfoVector[0].crossthreadOffset);

        patchWithRequiredSize(patchLocation, kernelArgInfo.kernelArgPatchInfoVector[0].size, *reinterpret_cast<const uintptr_t*>(argVal));

        oclInternals.storeKernelArg(argIndex, OCLRT::Kernel::BUFFER_OBJ, nullptr, argVal, argSize);

        //if (requiresSshForBuffers()) {
        //    auto surfaceState = ptrOffset(getSurfaceStateHeap(), kernelArgInfo.offsetHeap);
        //    Buffer::setSurfaceState(&getDevice(), surfaceState, 0, nullptr);
        //} // no SSH for buffers for now - stateless to stateful disabled

        GraphicsAllocation *alloc = function->getModule()->getDevice()->getMemoryManager()->findAllocation(*reinterpret_cast<void * const *>(argVal));
        assert(alloc != nullptr);
        residencyContainer[argIndex] = alloc;

        return XE_RESULT_SUCCESS;
    }

    const void *getCrossThreadDataHostMem() const override {
        return oclInternals.crossThreadData;
    }
    
    size_t getCrossThreadDataSize() const {
        return oclInternals.crossThreadDataSize;
    }

    const std::vector<GraphicsAllocation *> &getResidencyContainer() const override {
        return residencyContainer;
    }

    bool initialize() {
        OCLRT_temporary::LightweightOclKernel *kernelRT = static_cast<FunctionImp*>(function)->getKernelRT();

        // clone muttables from kernel object - note some may be immutable - fix this later
        this->oclInternals.kernelArguments = kernelRT->kernelArguments;
        for(auto handleRT : kernelRT->kernelArgHandlers){
            if(handleRT == &OCLRT::Kernel::setArgBuffer){
                this->oclInternals.kernelArgHandlers.push_back(&FunctionArgsImp::setArgBuffer);
            }else{
                assert(0); // only setArgBuffer for now
            }          
        }
        this->oclInternals.kernelSvmGfxAllocations = kernelRT->kernelSvmGfxAllocations;

        this->oclInternals.numberOfBindingTableStates = kernelRT->numberOfBindingTableStates;
        this->oclInternals.localBindingTableOffset = kernelRT->localBindingTableOffset;
        if(kernelRT->sshLocalSize != 0){
            this->oclInternals.pSshLocal = std::make_unique<char[]>(kernelRT->sshLocalSize);
            memcpy(this->oclInternals.pSshLocal.get(), kernelRT->pSshLocal.get(), kernelRT->sshLocalSize);
            this->oclInternals.sshLocalSize = kernelRT->sshLocalSize;
        }

        if(kernelRT->crossThreadDataSize != 0){
            this->oclInternals.crossThreadData = new char[kernelRT->crossThreadDataSize];
            memcpy(this->oclInternals.crossThreadData, kernelRT->crossThreadData, kernelRT->crossThreadDataSize);
            this->oclInternals.crossThreadDataSize = kernelRT->crossThreadDataSize;
        }

        this->oclInternals.usingSharedObjArgs = kernelRT->usingSharedObjArgs;
        this->oclInternals.usingImagesOnly = kernelRT->usingImagesOnly;
        this->oclInternals.auxTranslationRequired = kernelRT->auxTranslationRequired;
        this->oclInternals.patchedArgumentsNum = kernelRT->patchedArgumentsNum;
        this->oclInternals.startOffset = kernelRT->startOffset;
        residencyContainer.resize(this->oclInternals.kernelArgHandlers.size(), nullptr); // todo : handle implicit surfaces - printf/private/constant

        return true;
    }
protected:
    Function *function;
    std::vector<GraphicsAllocation *> residencyContainer;

    typedef xe_result_t(FunctionArgsImp::*FunctionArgHandler)(uint32_t argIndex, size_t argSize, const void *argVal);

    struct OCLInternal { // cloned from OCLRT::Kernel - keeping types/names the same for simplicity
        std::vector<OCLRT::Kernel::SimpleKernelArgInfo> kernelArguments;
        std::vector<FunctionArgsImp::FunctionArgHandler> kernelArgHandlers;
        std::vector<OCLRT::GraphicsAllocation *> kernelSvmGfxAllocations;

        void storeKernelArg(uint32_t argIndex, OCLRT::Kernel::kernelArgType argType, void *argObject,
            const void *argValue, size_t argSize,
            OCLRT::GraphicsAllocation *argSvmAlloc = nullptr, cl_mem_flags argSvmFlags = 0) {
            kernelArguments[argIndex].type = argType;
            kernelArguments[argIndex].object = argObject;
            kernelArguments[argIndex].value = argValue;
            kernelArguments[argIndex].size = argSize;
            kernelArguments[argIndex].pSvmAlloc = argSvmAlloc;
            kernelArguments[argIndex].svmFlags = argSvmFlags;
        }

        size_t numberOfBindingTableStates = 0;
        size_t localBindingTableOffset = 0;
        std::unique_ptr<char[]> pSshLocal = nullptr;
        uint32_t sshLocalSize = 0;

        char *crossThreadData = 0;
        uint32_t crossThreadDataSize = 0;

        bool usingSharedObjArgs = false;
        bool usingImagesOnly = false;
        bool auxTranslationRequired = false;
        uint32_t patchedArgumentsNum = 0;
        uint32_t startOffset = 0;
    } oclInternals;
};

FunctionArgs *FunctionArgs::create(Function *function) {
    auto functionArgs = new FunctionArgsImp(function);
    functionArgs->initialize();
    return functionArgs;
}

} // namespace xe
