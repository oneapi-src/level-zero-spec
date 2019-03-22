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
    ModuleImp(Device *device, void *deviceRT, ModuleBuildLog *moduleBuildLog);

    virtual ~ModuleImp();

    xe_result_t destroy() override {
        delete this;
        return XE_RESULT_SUCCESS;
    }

    xe_result_t createFunction(const xe_function_desc_t *desc, xe_function_handle_t *phFunction) override;

    xe_result_t getNativeBinary(size_t *pSize,
                                uint8_t *pModuleNativeBinary) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t getFunctionPointer(const char *pFunctionName,
                                   void **pfnFunction) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    virtual xe_result_t getGlobalPointer(const char *pGlobalName, void **pPtr)
    {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    PtrRef<ImmutableFunctionInfo> getImmutableFunctionInfo(CStringRef functionName) const override;
    uint32_t getMaxGroupSize() const override {
        return maxGroupSize;
    }

    void updateBuildLog(void *deviceRT);

    Device *getDevice() const override {
        return device;
    }

    bool initialize(const xe_module_desc_t *desc);

    void *getProgramRT() const {
        return progRT;
    }

  protected:
    Device *device = nullptr;
    ModuleBuildLog *moduleBuildLog = nullptr;
    OCLRT_temporary::LightweightOclProgram *progRT = nullptr;
    uint32_t maxGroupSize = 0U;
    std::vector<PtrOwn<ImmutableFunctionInfo>> immFuncInfos;
};

} // namespace L0
