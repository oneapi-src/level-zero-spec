#pragma once

#include <cstdint>

#include "ptr.h"

namespace NEO {
class GmmHelper;
}

namespace L0 {

struct MOCSMapper {
    MOCSMapper(PtrRef<NEO::GmmHelper> gmmHelper)
        : gmmHelper(gmmHelper) {
    }

    virtual uint32_t getUncachedMOCS() const;
    virtual uint32_t getFullyCachedMOCS() const;
    virtual uint32_t getCachedInstructionHeapMOCS() const;
    virtual uint32_t getCachedStateHeapMOCS() const;

  protected:
    PtrRef<NEO::GmmHelper> gmmHelper = nullptr;
};

} // namespace L0
