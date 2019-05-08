#pragma once

#include "ptr.h"

namespace L0 {
struct Device;
struct Function;

enum class Builtin { CopyBufferBytes, CopyImageBytes, COUNT };

struct BuiltinFunctionsLib {
    virtual ~BuiltinFunctionsLib() = default;
    static PtrOwn<BuiltinFunctionsLib> create(PtrRef<Device> device, PtrRef<void> builtinsRT);

    virtual PtrRef<Function> getFunction(Builtin func) = 0;
    virtual void initFunctions() = 0;

  protected:
    BuiltinFunctionsLib() = default;
};

} // namespace L0
