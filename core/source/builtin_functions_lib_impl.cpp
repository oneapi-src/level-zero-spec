#include "builtin_functions_lib_impl.h"

#include "builtins.h"
#include "device.h"
#include "module.h"

#include "runtime/built_ins/built_ins.h"

namespace L0 {

PtrOwn<BuiltinFunctionsLib> BuiltinFunctionsLib::create(PtrRef<Device> device, PtrRef<void> builtinsRT) {
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

PtrRef<Function> BuiltinFunctionsLibImpl::getFunction(Builtin func) {
    // TODO : Thread safety!
    auto builtId = static_cast<uint32_t>(func);
    if (builtins[builtId] != nullptr) {
        return builtins[builtId]->func.weakRef();
    }

    const char *inputModuleSpirV = nullptr;
    uint32_t inputModuleSize = 0;
    const char *builtinName = nullptr;

    switch (func) {
    default:
        break;
    case Builtin::CopyBufferBytes:
        inputModuleSpirV = compileCopyBufferToBufferBin.getModule();
        inputModuleSize = compileCopyBufferToBufferBin.getSize();
        builtinName = compileCopyBufferToBufferBin.getFunctionName();
        break;
    };

    PtrOwn<Module> module = nullptr;
    {
        xe_module_handle_t moduleHandle;
        xe_module_desc_t moduleDesc = {XE_MODULE_DESC_VERSION_CURRENT};
        moduleDesc.format = XE_MODULE_FORMAT_IL_SPIRV;
        moduleDesc.pInputModule = reinterpret_cast<const uint8_t*>(inputModuleSpirV);
        moduleDesc.inputSize = inputModuleSize;
        auto res = device->createModule(&moduleDesc, &moduleHandle, nullptr);
        assert(res == XE_RESULT_SUCCESS);
        module.rebind(Module::fromHandle(moduleHandle));
    }

    PtrOwn<Function> function = nullptr;
    {
        xe_function_handle_t functionHandle;
        xe_function_desc_t functionDesc = {XE_FUNCTION_DESC_VERSION_CURRENT};
        functionDesc.pFunctionName = builtinName;
        auto res = module->createFunction(&functionDesc, &functionHandle);
        assert(res == XE_RESULT_SUCCESS);
        function.rebind(Function::fromHandle(functionHandle));
    }

    builtins[builtId].rebind(new BuiltinData{std::move(module), std::move(function)});
    return builtins[builtId]->func.weakRef();
}

} // namespace L0
