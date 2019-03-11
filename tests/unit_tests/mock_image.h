#pragma once
#include "image.h"
#include "image_hw.h"
#include "white_box.h"
#include "mock.h"

namespace L0 {

namespace ult {

template <uint32_t gfxCoreFamily>
struct WhiteBox<::L0::ImageCoreFamily<gfxCoreFamily>> : public ::L0::ImageCoreFamily<gfxCoreFamily> {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(gfxCoreFamily)>::GfxFamily;
    using RENDER_SURFACE_STATE = typename GfxFamily::RENDER_SURFACE_STATE;

    WhiteBox() : ::L0::ImageCoreFamily<gfxCoreFamily>() {
    }

    virtual ~WhiteBox() {
    }

	RENDER_SURFACE_STATE *getSurfaceState() {
        return &this->surfaceState;
    }
};

template <uint32_t gfxCoreFamily>
using ImageCoreFamily = WhiteBox<::L0::ImageCoreFamily<gfxCoreFamily>>;

template <>
struct WhiteBox<::L0::Image> : public ::L0::Image {
    WhiteBox();
    virtual ~WhiteBox();

    xe_image_desc_t imageDesc;
};

using Image = WhiteBox<::L0::Image>;

template <>
struct Mock<Image> : public Image {
    Mock();
    virtual ~Mock();

    MOCK_METHOD0(destroy, xe_result_t());
};

} // namespace ult
} // namespace L0
