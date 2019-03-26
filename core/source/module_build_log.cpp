#include "module.h"

#include <cassert>
#include <memory>

namespace L0 {

struct ModuleBuildLogImp : public ModuleBuildLog {
    ModuleBuildLogImp() {}

    ~ModuleBuildLogImp() {}

    xe_result_t destroy() override {
        delete this;
        return XE_RESULT_SUCCESS;
    }

    xe_result_t getString(size_t *pSize, char *pBuildLog) override {
        const char *buildLog = this->buildLog.c_str();

        if (buildLog != nullptr) {
            auto szLog = this->buildLog.size();

            if (pBuildLog) {
                memcpy(pBuildLog, buildLog, szLog);
                pBuildLog[szLog] = '\0';
            }

            *pSize = szLog + 1;
        } else {
            *pSize = 0;
        }
        return XE_RESULT_SUCCESS;
    }

    void appendString(const char *pBuildLog, size_t size) override {
        if ((pBuildLog == nullptr) || (size == 0) || (pBuildLog[0] == '\0'))
            return;

        if (pBuildLog[size - 1] == '\0')
            --size;

        if (this->buildLog.length() != 0)
            this->buildLog.append("\n");

        this->buildLog.append(pBuildLog, size);
    }

  protected:
    std::string buildLog;
};

ModuleBuildLog *ModuleBuildLog::create() {
    auto moduleBuildLog = new ModuleBuildLogImp();
    assert(moduleBuildLog != nullptr);
    return moduleBuildLog;
}

} // namespace L0
