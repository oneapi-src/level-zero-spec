#include "image_gen12hp.inl"

namespace L0 {

template <>
struct ImageProductFamily<IGFX_TIGERLAKE_HP> : public ImageCoreFamily<IGFX_GEN12_CORE> {
    using ImageCoreFamily::ImageCoreFamily;
};

static ImagePopulateFactory<IGFX_TIGERLAKE_HP, ImageProductFamily<IGFX_TIGERLAKE_HP>> populateTGLHP;

} //namespace L0
