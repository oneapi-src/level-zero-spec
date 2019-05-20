#include "builtin_functions_lib_impl.h"

#include "builtins.h"
#include "device.h"
#include "module.h"

#include "runtime/built_ins/built_ins.h"

namespace L0 {

PtrOwn<BuiltinFunctionsLib> BuiltinFunctionsLib::create(PtrRef<Device> device,
                                                        PtrRef<void> builtinsRT) {
    return PtrOwn<BuiltinFunctionsLib>(new BuiltinFunctionsLibImpl(device, builtinsRT));
}

struct BuiltinFunctionsLibImpl::BuiltinData {
    ~BuiltinData() {
        func.deleteOwned();
        module.deleteOwned();
    }

    PtrOwn<Module> module = nullptr;
    PtrOwn<Function> func = nullptr;
};

void BuiltinFunctionsLibImpl::initFunctions() {
    for (uint32_t builtId = 0; builtId < static_cast<uint32_t>(Builtin::COUNT); builtId++) {
        const unsigned char *inputModuleSpirV = nullptr;
        uint32_t inputModuleSize = 0;
        const char *builtinName = nullptr;

        switch (static_cast<Builtin>(builtId)) {
        case Builtin::CopyBufferBytes:
            inputModuleSpirV = compileCopyBufferToBufferBin.getModule();
            inputModuleSize = compileCopyBufferToBufferBin.getSize();
            builtinName = compileCopyBufferToBufferBin.getModuleName();
            break;
        case Builtin::CopyBufferToBufferSide:
            inputModuleSpirV = compileCopyBufferToBufferDecomposedBin.getModule();
            inputModuleSize = compileCopyBufferToBufferDecomposedBin.getSize();
            builtinName = "CopyBufferToBufferSide";
            break;
        case Builtin::CopyBufferToBufferMiddle:
            inputModuleSpirV = compileCopyBufferToBufferDecomposedBin.getModule();
            inputModuleSize = compileCopyBufferToBufferDecomposedBin.getSize();
            builtinName = "CopyBufferToBufferMiddle";
            break;
        default:
            continue;
        };

        xe_result_t res;
        PtrOwn<Module> module = nullptr;
        xe_module_handle_t moduleHandle;
        xe_module_desc_t moduleDesc = {XE_MODULE_DESC_VERSION_CURRENT};
        moduleDesc.format = XE_MODULE_FORMAT_IL_SPIRV;
        moduleDesc.pInputModule = inputModuleSpirV;
        moduleDesc.inputSize = inputModuleSize;
        res = device->createModule(&moduleDesc, &moduleHandle, nullptr);
        if (res != XE_RESULT_SUCCESS) {
            assert(false);
        }
        module.rebind(Module::fromHandle(moduleHandle));

        PtrOwn<Function> function = nullptr;
        xe_function_handle_t functionHandle;
        xe_function_desc_t functionDesc = {XE_FUNCTION_DESC_VERSION_CURRENT};
        functionDesc.pFunctionName = builtinName;
        res = module->createFunction(&functionDesc, &functionHandle);
        if (res != XE_RESULT_SUCCESS) {
            assert(false);
        }
        function.rebind(Function::fromHandle(functionHandle));

        builtins[builtId].rebind(new BuiltinData{std::move(module), std::move(function)});
    }
}

PtrRef<Function> BuiltinFunctionsLibImpl::getFunction(Builtin func) {
    auto builtId = static_cast<uint32_t>(func);
    return builtins[builtId]->func.weakRef();
}

} // namespace L0
