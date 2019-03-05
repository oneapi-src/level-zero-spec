#include "runtime/gen11/hw_cmds.h"
#include "runtime/gen11/hw_info.h"
#include "image_hw.inl"

namespace L0 {

template <>
struct ImageProductFamily<IGFX_ICELAKE_LP> : public ImageCoreFamily<IGFX_GEN11_CORE> {
    using ImageCoreFamily::ImageCoreFamily;
};

static ImagePopulateFactory<IGFX_ICELAKE_LP, ImageProductFamily<IGFX_ICELAKE_LP>> populateICLLP;

} //namespace L0
