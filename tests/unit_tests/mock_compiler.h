#pragma once

#include "igc.opencl.h"

// temporarily to instrument NEO's compiler interface
namespace Os {
extern const char *frontEndDllName;
extern const char *igcDllName;
} // namespace Os

namespace L0 {
namespace ult {

struct UserRealCompilerGuard {
    UserRealCompilerGuard() {
        prevCompilerFcl = Os::frontEndDllName;
        prevCompilerIgc = Os::igcDllName;

        Os::frontEndDllName = FCL_LIBRARY_NAME;
        Os::igcDllName = IGC_LIBRARY_NAME;
    }

    UserRealCompilerGuard(const UserRealCompilerGuard &) = delete;
    UserRealCompilerGuard(UserRealCompilerGuard &&) = delete;
    UserRealCompilerGuard &operator=(const UserRealCompilerGuard &) = delete;
    UserRealCompilerGuard &operator=(UserRealCompilerGuard &&) = delete;

    ~UserRealCompilerGuard() {
        Os::frontEndDllName = prevCompilerFcl;
        Os::igcDllName = prevCompilerIgc;
    }

    const char *prevCompilerFcl = nullptr;
    const char *prevCompilerIgc = nullptr;
};

} // namespace ult
} // namespace L0
