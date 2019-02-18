#pragma once
#include "xe_module.h"

#include <vector>

struct _xe_module_handle_t {
};

struct _xe_function_handle_t {
};

struct _xe_function_args_handle_t {
};

namespace xe {
struct Device;
struct GraphicsAllocation;

struct Module : public _xe_module_handle_t {
    static Module *create(Device *device, const xe_module_desc_t *desc, void *deiceRT);
    virtual xe_result_t destroy() = 0;
    virtual Device *getDevice() const = 0;

    virtual xe_result_t createFunction(const xe_function_desc_t *desc, xe_function_handle_t *phFunction) = 0;

    Module() = default;
    Module(const Module &) = delete;
    Module(Module &&) = delete;
    Module &operator=(const Module &) = delete;
    Module &operator=(Module &&) = delete;

    static Module *fromHandle(xe_module_handle_t handle) {
        return static_cast<Module *>(handle);
    }

    inline xe_module_handle_t toHandle() {
        return this;
    }
};

// TODO : Decompose to function.h ?
struct Function : public _xe_function_handle_t {
    static Function *create(Module *module, const xe_function_desc_t *desc);
    virtual xe_result_t destroy() = 0;
    virtual xe_result_t createFunctionArgs(xe_function_args_handle_t *phFunctionArgs) = 0;

    virtual Module *getModule() const = 0;
    virtual const void *getIsaHostMem() const = 0;
    virtual size_t getIsaSize() const = 0;
    virtual uint32_t getSimdSize() const = 0;

    Function() = default;
    Function(const Function &) = delete;
    Function(Function &&) = delete;
    Function &operator=(const Function &) = delete;
    Function &operator=(Function &&) = delete;

    static Function *fromHandle(xe_function_handle_t handle) {
        return static_cast<Function *>(handle);
    }

    inline xe_function_handle_t toHandle() {
        return this;
    }
};

// TODO : Decompose to function_args.h ?
struct FunctionArgs : public _xe_function_args_handle_t {
    static FunctionArgs *create(Function *function);
    virtual xe_result_t destroy() = 0;
    virtual xe_result_t setValue(uint32_t argIndex, size_t argSize, const void *pArgValue) = 0;

    virtual const void *getCrossThreadDataHostMem() const = 0;
    virtual size_t getCrossThreadDataSize() const = 0;
    virtual const std::vector<GraphicsAllocation *> &getResidencyContainer() const = 0;
    virtual void setGroupSize(uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ) = 0;
    virtual void getGroupSize(uint32_t &outGroupSizeX, uint32_t &outGroupSizeY, uint32_t &outGroupSizeZ) const = 0;
    virtual uint32_t getThreadsPerThreadGroup() const = 0;
    virtual const void *getPerThreadDataHostMem() const = 0;
    virtual size_t getPerThreadDataSize() const = 0;

    FunctionArgs() = default;
    FunctionArgs(const FunctionArgs &) = delete;
    FunctionArgs(FunctionArgs &&) = delete;
    FunctionArgs &operator=(const FunctionArgs &) = delete;
    FunctionArgs &operator=(FunctionArgs &&) = delete;

    static FunctionArgs *fromHandle(xe_function_args_handle_t handle) {
        return static_cast<FunctionArgs *>(handle);
    }

    inline xe_function_args_handle_t toHandle() {
        return this;
    }
};

xe_result_t __xecall
xeModuleCreateFunction(
    xe_module_handle_t hModule,      ///< [in] handle of the module
    const xe_function_desc_t *desc,  ///< [in] pointer to function descriptor
    xe_function_handle_t *phFunction ///< [out] handle of the Function object
);

xe_result_t __xecall
xeFunctionDestroy(
    xe_function_handle_t phFunction
);

xe_result_t __xecall
xeFunctionCreateFunctionArgs(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function
    xe_function_args_handle_t* phFunctionArgs       ///< [out] handle of the Function arguments object
);

xe_result_t __xecall
xeFunctionArgsDestroy(
    xe_function_args_handle_t hFunctionArgs         ///< [in] handle of the function arguments buffer object
);

xe_result_t __xecall
xeFunctionArgsSetValue(
    xe_function_args_handle_t hFunctionArgs,        ///< [in/out] handle of the function args object.
    uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
    size_t argSize,                                 ///< [in] size of argument type
    const void* pArgValue                           ///< [in] argument value represented as matching arg type
);

} // namespace xe
