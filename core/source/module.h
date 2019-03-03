#pragma once
#include "cmdgraph.h"
#include "cmdlist.h"
#include "function.h"
#include "xe_common.h"
#include "xe_module.h"

#include <vector>

struct _xe_module_handle_t {
};

namespace L0 {
struct Device;
struct GraphicsAllocation;

struct Module : public _xe_module_handle_t {
    static Module *create(Device *device, const xe_module_desc_t *desc, void *deiceRT);
    virtual Device *getDevice() const = 0;

    virtual xe_result_t createFunction(const xe_function_desc_t *desc, xe_function_handle_t *phFunction) = 0;
    virtual xe_result_t destroy() = 0;
    virtual xe_result_t getNativeBinary(uint32_t *pSize,
                                        char **pModuleNativeBinary) = 0;
    virtual xe_result_t getFunctionPointer(const char *pFunctionName,
                                           void **pfnFunction) = 0;

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

xe_result_t moduleBuildLogDestroy(xe_module_build_log_handle_t hModuleBuildLog);

xe_result_t moduleBuildLogGetString(xe_module_build_log_handle_t hModuleBuildLog,
                                    uint32_t *pSize,
                                    char **pBuildLog);

} // namespace L0
