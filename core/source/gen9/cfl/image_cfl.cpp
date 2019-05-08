#include "runtime/gen9/hw_cmds.h"
#include "runtime/gen9/hw_info.h"
#include "image_hw.inl"

namespace L0 {

template <> struct ImageProductFamily<IGFX_COFFEELAKE> : public ImageCoreFamily<IGFX_GEN9_CORE> {
    using ImageCoreFamily::ImageCoreFamily;
};

static ImagePopulateFactory<IGFX_COFFEELAKE, ImageProductFamily<IGFX_COFFEELAKE>> populateCFL;

} // namespace L0
