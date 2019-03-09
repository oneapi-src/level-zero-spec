#pragma once
#ifndef MODULE_INTERNAL
#error "Don't #include this file directly."
#endif //MODULE_INTERNAL

#include "module.h"

#include "device.h"

#include <cassert>
#include <memory>

namespace OCLRT_temporary {
struct LightweightOclProgram;
} // namespace OCLRT_temporary

namespace L0 {

struct ModuleImp : public Module {
    ModuleImp(Device *device, void *deviceRT);

    virtual ~ModuleImp();

    xe_result_t destroy() override {
        delete this;
        return XE_RESULT_SUCCESS;
    }

    xe_result_t createFunction(const xe_function_desc_t *desc, xe_function_handle_t *phFunction) override;

    xe_result_t getNativeBinary(uint32_t *pSize,
                                char **pModuleNativeBinary) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t getFunctionPointer(const char *pFunctionName,
                                   void **pfnFunction) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    ImmutableFunctionInfo *getImmutableFunctionInfo(const char *functionName) const override;

    Device *getDevice() const override {
        return device;
    }

    bool initialize(const xe_module_desc_t *desc);

    void *getProgramRT() const {
        return progRT;
    }

  protected:
    Device *device = nullptr;
    OCLRT_temporary::LightweightOclProgram *progRT = nullptr;
    std::vector<ImmutableFunctionInfo *> immFuncInfos;
};

} // namespace L0
