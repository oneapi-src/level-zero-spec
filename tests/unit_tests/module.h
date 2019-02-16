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

    Module() = default;
    Module(const Module&) = delete;
    Module(Module&&) = delete;
    Module &operator=(const Module&) = delete;
    Module &operator=(Module&&) = delete;

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
    virtual Module *getModule() const = 0;
    virtual const void *getIsaHostMem() const = 0;
    virtual size_t getIsaSize() const = 0;
    virtual uint32_t getSimdSize() const = 0;

    Function() = default;
    Function(const Function&) = delete;
    Function(Function&&) = delete;
    Function &operator=(const Function&) = delete;
    Function &operator=(Function&&) = delete;

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
    virtual const void *getPerThreadDataHostMem() const = 0;
    virtual size_t getPerThreadDataSize() const = 0;

    FunctionArgs() = default;
    FunctionArgs(const FunctionArgs&) = delete;
    FunctionArgs(FunctionArgs&&) = delete;
    FunctionArgs &operator=(const FunctionArgs&) = delete;
    FunctionArgs &operator=(FunctionArgs&&) = delete;

    static FunctionArgs *fromHandle(xe_function_args_handle_t handle) {
        return static_cast<FunctionArgs *>(handle);
    }

    inline xe_function_args_handle_t toHandle() {
        return this;
    }
};

} // namespace xe
