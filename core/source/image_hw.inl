#include "image_hw.h"
#include "runtime/gmm_helper/gmm.h"

namespace L0 {
template <GFXCORE_FAMILY gfxCoreFamily>
bool ImageCoreFamily<gfxCoreFamily>::initialize(Device *device, const xe_image_desc_t *desc) {
    using RENDER_SURFACE_STATE = typename GfxFamily::RENDER_SURFACE_STATE;

    if (desc == nullptr) {
        return false;
    }

    if (desc->format.layout > XE_IMAGE_FORMAT_LAYOUT_MAX) {
        return false;
    }

    if (desc->format.type > XE_IMAGE_FORMAT_TYPE_MAX) {
        return false;
    }

    if (desc->format.x > XE_IMAGE_FORMAT_SWIZZLE_MAX ||
            desc->format.y > XE_IMAGE_FORMAT_SWIZZLE_MAX ||
            desc->format.z > XE_IMAGE_FORMAT_SWIZZLE_MAX ||
            desc->format.w > XE_IMAGE_FORMAT_SWIZZLE_MAX) {
        return false;
    }

    if (!BaseClass::initialize(device, desc)) {
        return false;
    }

    surfaceState = GfxFamily::cmdInitRenderSurfaceState;

    surfaceState.setShaderChannelSelectRed(
            static_cast<const typename RENDER_SURFACE_STATE::SHADER_CHANNEL_SELECT_RED>(
                shaderChannelSelect[desc->format.x]));
    surfaceState.setShaderChannelSelectGreen(
            static_cast<const typename RENDER_SURFACE_STATE::SHADER_CHANNEL_SELECT_GREEN>(
                shaderChannelSelect[desc->format.y]));
    surfaceState.setShaderChannelSelectBlue(
            static_cast<const typename RENDER_SURFACE_STATE::SHADER_CHANNEL_SELECT_BLUE>(
                shaderChannelSelect[desc->format.z]));
    surfaceState.setShaderChannelSelectAlpha(
            static_cast<const typename RENDER_SURFACE_STATE::SHADER_CHANNEL_SELECT_ALPHA>(
                shaderChannelSelect[desc->format.w]));

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

    auto gmm = this->allocation->allocationRT->getDefaultGmm();
    if (gmm) {
        surfaceState.setSurfaceHorizontalAlignment(static_cast<typename RENDER_SURFACE_STATE::SURFACE_HORIZONTAL_ALIGNMENT>(gmm->getRenderHAlignment()));
        surfaceState.setSurfaceVerticalAlignment(static_cast<typename RENDER_SURFACE_STATE::SURFACE_VERTICAL_ALIGNMENT>(gmm->getRenderVAlignment()));
    }

    surfaceState.setSurfaceFormat(surfaceFormatTable[desc->format.layout][desc->format.type]);

    size_t elem_size = formatLayoutSize[desc->format.layout];
    surfaceState.setSurfacePitch(static_cast<uint32_t>(desc->width * elem_size));

    surfaceState.setSurfaceBaseAddress(static_cast<uint64_t>(this->allocation->getGpuAddress()));

    return true;
}

template <GFXCORE_FAMILY gfxCoreFamily>
void ImageCoreFamily<gfxCoreFamily>::copySurfaceStateToSSH(void *surfaceStateHeap, const uint32_t surfaceStateOffset) {
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using RENDER_SURFACE_STATE = typename GfxFamily::RENDER_SURFACE_STATE;
    using BINDING_TABLE_STATE = typename GfxFamily::BINDING_TABLE_STATE;

    //Copy the image's surface state into position in the provided surface state heap
    auto destSurfaceState = ptrOffset(surfaceStateHeap, surfaceStateOffset);
    memcpy(destSurfaceState, &surfaceState, sizeof(RENDER_SURFACE_STATE));
}

} //namespace L0
