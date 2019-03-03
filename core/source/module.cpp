#include "module.h"

namespace L0 {

xe_result_t moduleBuildLogDestroy(xe_module_build_log_handle_t hModuleBuildLog) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t moduleBuildLogGetString(xe_module_build_log_handle_t hModuleBuildLog,
                                    uint32_t *pSize,
                                    char **pBuildLog) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

} // namespace L0
