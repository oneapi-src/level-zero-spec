#include "image_hw.h"

namespace L0 {
template <uint32_t gfxCoreFamily>
bool ImageCoreFamily<gfxCoreFamily>::initialize() {
    if (!BaseClass::initialize()) {
        return false;
    }

    return true;
}
} //namespace L0
