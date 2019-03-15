#include "image_hw.h"

namespace L0 {
template <GFXCORE_FAMILY gfxCoreFamily>
bool ImageCoreFamily<gfxCoreFamily>::initialize(Device *device, const xe_image_desc_t *desc) {

    if (desc->numChannels < XE_NUMCHANNELS_MIN || desc->numChannels > XE_NUMCHANNELS_MAX) {
        return false;
    }

    if (desc->format > XE_IMAGE_FORMAT_MAX) {
        return false;
    }

    if (!BaseClass::initialize(device, desc)) {
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

    switch (desc->type) {
    case XE_IMAGE_TYPE_3D:
        surfaceState.setDepth(static_cast<uint32_t>(desc->depth));
        //Fall through on purpose
    case XE_IMAGE_TYPE_2D:
    case XE_IMAGE_TYPE_2DARRAY:
        surfaceState.setHeight(static_cast<uint32_t>(desc->height));
        //Fall through on purpose
    default: // 1D
        surfaceState.setWidth(static_cast<uint32_t>(desc->width));
    }

    surfaceState.setSurfaceFormat(format_table[desc->format][desc->numChannels - XE_NUMCHANNELS_MIN]);

    return true;
}
} //namespace L0
