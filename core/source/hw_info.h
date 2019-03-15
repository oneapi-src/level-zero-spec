#pragma once
#include "igfxfmid.h"
#include "runtime/helpers/hw_info.h"

namespace L0 {

// Utility conversion
template <PRODUCT_FAMILY productFamily>
struct ToGfxCoreFamily {
    static const GFXCORE_FAMILY gfxCoreFamily = static_cast<GFXCORE_FAMILY>(OCLRT::HwMapper<productFamily>::gfxFamily);
    static constexpr GFXCORE_FAMILY get() {
        return gfxCoreFamily;
    }
};

} // namespace L0
