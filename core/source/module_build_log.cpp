#include "module.h"

#include <cassert>
#include <memory>

namespace L0 {

struct ModuleBuildLogImp : public ModuleBuildLog {
    ModuleBuildLogImp(Module *module) : module(module) {}

    ~ModuleBuildLogImp() {}

    xe_result_t destroy() override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t getString(uint32_t *pSize, char **pBuildLog) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

  protected:
    Module *module = nullptr;
};

ModuleBuildLog *ModuleBuildLog::create(Module *module) {
    auto moduleBuildLog = new ModuleBuildLogImp(module);
    assert(moduleBuildLog != nullptr);
    return moduleBuildLog;
}

} // namespace L0
