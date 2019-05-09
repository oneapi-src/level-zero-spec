#pragma once

#include "builtin_functions_lib.h"

#include "ptr.h"

namespace NEO {
class BuiltIns;
}

namespace L0 {

struct BuiltinFunctionsLibImpl : BuiltinFunctionsLib {
    BuiltinFunctionsLibImpl(PtrRef<Device> device, PtrRef<void> builtinsRT)
        : device(device), builtinsRT(builtinsRT.weakRef<NEO::BuiltIns>()) {
        initAllToNullptr(builtins);
    }
    ~BuiltinFunctionsLibImpl() { deleteAllOwned(builtins); }

    PtrRef<Function> getFunction(Builtin func) override;
    void initFunctions() override;

  protected:
    struct BuiltinData;
    PtrOwn<BuiltinData> builtins[static_cast<uint32_t>(Builtin::COUNT)];

    PtrRef<Device> device;
    PtrRef<NEO::BuiltIns> builtinsRT;
};

} // namespace L0
