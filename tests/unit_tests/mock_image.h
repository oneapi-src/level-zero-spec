#pragma once
#include "image.h"
#include "image_hw.h"
#include "white_box.h"
#include "mock.h"

namespace L0 {

namespace ult {

template <GFXCORE_FAMILY gfxCoreFamily>
struct WhiteBox<::L0::ImageCoreFamily<gfxCoreFamily>>
    : public ::L0::ImageCoreFamily<gfxCoreFamily> {
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using RENDER_SURFACE_STATE = typename GfxFamily::RENDER_SURFACE_STATE;

    WhiteBox() : ::L0::ImageCoreFamily<gfxCoreFamily>() {}

    virtual ~WhiteBox() {}

    using ::L0::ImageCoreFamily<gfxCoreFamily>::surfaceState;
};

template <GFXCORE_FAMILY gfxCoreFamily>
using ImageCoreFamily = WhiteBox<::L0::ImageCoreFamily<gfxCoreFamily>>;

template <> struct WhiteBox<::L0::Image> : public ::L0::ImageImp {
    WhiteBox();
    virtual ~WhiteBox();

    using ::L0::ImageImp::imageDesc;
};

using Image = WhiteBox<::L0::Image>;

template <> struct Mock<Image> : public Image {
    Mock();
    virtual ~Mock();

    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD0(getAllocation, GraphicsAllocation *());
    MOCK_METHOD2(copySurfaceStateToSSH,
                 void(void *surfaceStateHeap, const uint32_t surfaceStateOffset));
    MOCK_METHOD0(getSizeInBytes, size_t());
};

} // namespace ult
} // namespace L0
