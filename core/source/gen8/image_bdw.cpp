#include "runtime/gen8/hw_cmds.h"
#include "runtime/gen8/hw_info.h"
#include "image_hw.inl"

namespace L0 {

template <>
struct ImageProductFamily<IGFX_BROADWELL> : public ImageCoreFamily<IGFX_GEN8_CORE> {
    using ImageCoreFamily::ImageCoreFamily;
};

static ImagePopulateFactory<IGFX_BROADWELL, ImageProductFamily<IGFX_BROADWELL>> populateBDW;

} //namespace L0
