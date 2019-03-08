#include "mock_image.h"
#include "igfxfmid.h"

namespace L0 {
namespace ult {

TEST(xeImageDestroy, redirectsToObject) {
    Mock<Image> image;
    EXPECT_CALL(image, destroy()).Times(1);

    auto result = xeImageDestroy(image.toHandle());
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

using ImageCreate = ::testing::TestWithParam<uint32_t>;

TEST_P(ImageCreate, returnsImageOnSuccess) {
    xe_image_desc_t desc = {};

    auto image = whitebox_cast(Image::create(GetParam(), &desc));
    ASSERT_NE(nullptr, image);

    image->destroy();
}

static uint32_t supportedProductFamilyTable[] = {
    IGFX_KABYLAKE,
    IGFX_SKYLAKE,
};

INSTANTIATE_TEST_CASE_P(,
                        ImageCreate,
                        ::testing::ValuesIn(supportedProductFamilyTable));

using ImageCreateFail = ::testing::TestWithParam<uint32_t>;

TEST_P(ImageCreateFail, returnsNullPointerOnFailure) {
    xe_image_desc_t desc = {};

    auto image = whitebox_cast(Image::create(GetParam(), &desc));
    ASSERT_EQ(nullptr, image);
}

static uint32_t unsupportedProductFamilyTable[] = {
    IGFX_HASWELL,
    IGFX_CANNONLAKE,
    IGFX_MAX_PRODUCT,
};

INSTANTIATE_TEST_CASE_P(,
                        ImageCreateFail,
                        ::testing::ValuesIn(unsupportedProductFamilyTable));

} // namespace ult
} // namespace L0
