#pragma once
#include "image.h"
#include "image_hw.h"
#include "white_box.h"
#include "mock.h"

namespace L0 {

namespace ult {

template <uint32_t xgfxCoreFamily>
struct WhiteBox<::L0::ImageCoreFamily<xgfxCoreFamily>> : public ::L0::ImageCoreFamily<xgfxCoreFamily> {
    WhiteBox() : ::L0::ImageCoreFamily<xgfxCoreFamily>() {
    }

    virtual ~WhiteBox() {
    }

	RENDER_SURFACE_STATE *getSurfaceState() {
        return &surfaceState;
    }
};

template <uint32_t ygfxCoreFamily>
using ImageCoreFamily = WhiteBox<::L0::ImageCoreFamily<ygfxCoreFamily>>;

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
