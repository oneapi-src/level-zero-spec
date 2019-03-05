#include "runtime/gen12lp/hw_cmds.h"
#include "runtime/gen12lp/hw_info.h"
#include "image_hw.inl"

namespace L0 {

template <>
struct ImageProductFamily<IGFX_TIGERLAKE_LP> : public ImageCoreFamily<IGFX_GEN12LP_CORE> {
    using ImageCoreFamily::ImageCoreFamily;
};

static ImagePopulateFactory<IGFX_TIGERLAKE_LP, ImageProductFamily<IGFX_TIGERLAKE_LP>> populateTGLLP;

} //namespace L0
