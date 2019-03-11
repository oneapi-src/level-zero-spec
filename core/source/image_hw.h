#pragma once
#define IMAGE_INTERNAL
#include "image_imp.h"
#undef IMAGE_INTERNAL
#include "runtime/command_stream/linear_stream.h"
#include "runtime/helpers/hw_info.h"
#include "runtime/indirect_heap/indirect_heap.h"

namespace L0 {

template <uint32_t gfxCoreFamily>
struct ImageCoreFamily : public ImageImp {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(gfxCoreFamily)>::GfxFamily;
    using RENDER_SURFACE_STATE = typename GfxFamily::RENDER_SURFACE_STATE;
    using BaseClass = ImageImp;
    using ImageImp::ImageImp;

    bool initialize(const xe_image_desc_t *desc) override;

  protected:
    RENDER_SURFACE_STATE surfaceState;
};

template <uint32_t gfxProductFamily>
struct ImageProductFamily;

} //namespace L0
