#include "image_hw.h"

namespace L0 {
template <uint32_t gfxCoreFamily>
bool ImageCoreFamily<gfxCoreFamily>::initialize(const xe_image_desc_t *desc) {
    if (!BaseClass::initialize(desc)) {
        return false;
    }

    surfaceState = GfxFamily::cmdInitRenderSurfaceState;

    switch (desc->type) {
    case XE_IMAGE_TYPE_1D:
    case XE_IMAGE_TYPE_1DARRAY:
        surfaceState.setSurfaceType(RENDER_SURFACE_STATE::SURFACE_TYPE_SURFTYPE_1D);
        break;
    case XE_IMAGE_TYPE_2D:
    case XE_IMAGE_TYPE_2DARRAY:
        surfaceState.setSurfaceType(RENDER_SURFACE_STATE::SURFACE_TYPE_SURFTYPE_2D);
        break;
    case XE_IMAGE_TYPE_3D:
        surfaceState.setSurfaceType(RENDER_SURFACE_STATE::SURFACE_TYPE_SURFTYPE_3D);
        break;
    default:
        return false;
    }
    return true;
}
} //namespace L0
