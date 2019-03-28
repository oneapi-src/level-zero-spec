#include "image_hw.h"
#include "runtime/gmm_helper/gmm.h"

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

    switch(desc->numChannels) {
    case 4:
        surfaceState.setShaderChannelSelectAlpha(RENDER_SURFACE_STATE::SHADER_CHANNEL_SELECT_ALPHA_ALPHA);
        //Fall through on purpose
    case 3:
        surfaceState.setShaderChannelSelectBlue(RENDER_SURFACE_STATE::SHADER_CHANNEL_SELECT_BLUE_BLUE);
    case 2:
        surfaceState.setShaderChannelSelectGreen(RENDER_SURFACE_STATE::SHADER_CHANNEL_SELECT_GREEN_GREEN);
    case 1:
        surfaceState.setShaderChannelSelectRed(RENDER_SURFACE_STATE::SHADER_CHANNEL_SELECT_RED_RED);
        break;
    default:
        return false;
    }

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

    auto gmm = this->allocation->allocationRT->gmm;
    if (gmm) {
        surfaceState.setSurfaceHorizontalAlignment(static_cast<typename RENDER_SURFACE_STATE::SURFACE_HORIZONTAL_ALIGNMENT>(gmm->getRenderHAlignment()));
        surfaceState.setSurfaceVerticalAlignment(static_cast<typename RENDER_SURFACE_STATE::SURFACE_VERTICAL_ALIGNMENT>(gmm->getRenderVAlignment()));
    }

    surfaceState.setSurfaceFormat(format_table[desc->format][desc->numChannels - XE_NUMCHANNELS_MIN]);

    size_t elem_size = format_size[imageDesc.format];
    surfaceState.setSurfacePitch(static_cast<uint32_t>(imageDesc.width * elem_size));

    surfaceState.setSurfaceBaseAddress(static_cast<uint64_t>(this->allocation->getGpuAddress()));

    return true;
}

template <GFXCORE_FAMILY gfxCoreFamily>
void ImageCoreFamily<gfxCoreFamily>::copySurfaceStateToSSH(void *surfaceStateHeap, const uint32_t surfaceStateOffset,
        const uint32_t bindingTableOffset, const uint32_t bindingTableIndex) {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using RENDER_SURFACE_STATE = typename GfxFamily::RENDER_SURFACE_STATE;
    using BINDING_TABLE_STATE = typename GfxFamily::BINDING_TABLE_STATE;

    //Copy the image's surface state into position in the provided surface state heap
    auto destSurfaceState = ptrOffset(surfaceStateHeap, surfaceStateOffset);
    memcpy(destSurfaceState, &surfaceState, sizeof(RENDER_SURFACE_STATE));

    //Update the binding table state to point to the copied surface state
    auto bindingTableState = static_cast<BINDING_TABLE_STATE *>(ptrOffset(surfaceStateHeap, bindingTableOffset));
    bindingTableState[bindingTableIndex].setSurfaceStatePointer(surfaceStateOffset);
}

} //namespace L0
