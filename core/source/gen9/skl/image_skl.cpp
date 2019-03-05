#include "runtime/gen9/hw_cmds.h"
#include "runtime/gen9/hw_info.h"
#include "image_hw.inl"

namespace L0 {

template <>
struct ImageProductFamily<IGFX_SKYLAKE> : public ImageCoreFamily<IGFX_GEN9_CORE> {
    using ImageCoreFamily::ImageCoreFamily;
};

static ImagePopulateFactory<IGFX_SKYLAKE, ImageProductFamily<IGFX_SKYLAKE>> populateSKL;

} //namespace L0
