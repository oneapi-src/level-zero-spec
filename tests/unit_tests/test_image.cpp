#include "mock_image.h"
#include "igfxfmid.h"
#include "test.h"
#include "unit_tests/gen_common/gen_cmd_parse.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/helpers/hw_info.h"
#include "runtime/indirect_heap/indirect_heap.h"

namespace L0 {
namespace ult {

TEST(xeImageDestroy, redirectsToObject) {
    Mock<Image> image;
    EXPECT_CALL(image, destroy()).Times(1);

    auto result = xeImageDestroy(image.toHandle());
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

using ImageCreate = ::testing::Test;

TEST_F(ImageCreate, returnsImageOnSuccess) {
    xe_image_desc_t desc = {};

    auto image = whitebox_cast(Image::create(productFamily, &desc));
    ASSERT_NE(nullptr, image);

    image->destroy();
}


TEST_F(ImageCreate, givenInvalidProductFamilyReturnsNullPointer) {
    xe_image_desc_t desc = {};

    auto image = whitebox_cast(Image::create(IGFX_UNKNOWN, &desc));
    ASSERT_EQ(nullptr, image);
}

HWTEST2_F(ImageCreate, descMatchesSurface, MatchAny) {
    using RENDER_SURFACE_STATE = typename FamilyType::RENDER_SURFACE_STATE;
    xe_image_desc_t desc = {};

    desc.type = XE_IMAGE_TYPE_3D;
    desc.numChannels = 4;
    desc.format = XE_IMAGE_FORMAT_UINT8;
    desc.width = 11;
    desc.height = 13;
    desc.depth = 17;

    auto imageCore = new ImageCoreFamily<gfxCoreFamily>();
    bool ret = imageCore->initialize(&desc);
    ASSERT_TRUE(ret);

    auto surfaceState = imageCore->getSurfaceState();

    ASSERT_EQ(surfaceState->getSurfaceType(), RENDER_SURFACE_STATE::SURFACE_TYPE_SURFTYPE_3D);
    ASSERT_EQ(surfaceState->getSurfaceFormat(), RENDER_SURFACE_STATE::SURFACE_FORMAT_R8G8B8A8_UINT);
    ASSERT_EQ(surfaceState->getWidth(), 11);
    ASSERT_EQ(surfaceState->getHeight(), 13);
    ASSERT_EQ(surfaceState->getDepth(), 17);
}

HWTEST2_F(ImageCreate, descBadParamsFail, MatchAny) {
    using RENDER_SURFACE_STATE = typename FamilyType::RENDER_SURFACE_STATE;

    auto imageCore = new ImageCoreFamily<gfxCoreFamily>();
    xe_image_desc_t desc, default_desc;
    bool ret;

    default_desc.type = XE_IMAGE_TYPE_2D;
    default_desc.numChannels = 1;
    default_desc.format = XE_IMAGE_FORMAT_UINT32;
    default_desc.width = 10;
    default_desc.height = 10;
    default_desc.depth = 1;
    default_desc.arraylevels = 1;
    default_desc.miplevels = 1;

	desc = default_desc;
	desc.type = static_cast<xe_image_type_t>(XE_IMAGE_TYPE_3D + 100);

	ret = imageCore->initialize(&desc);
	ASSERT_FALSE(ret);

	desc = default_desc;
    desc.numChannels = 0;
    ASSERT_FALSE(ret);

	desc = default_desc;
    desc.numChannels = 100;
    ASSERT_FALSE(ret);

	desc = default_desc;
    desc.format = static_cast<xe_image_format_t>(XE_IMAGE_FORMAT_FLOAT32 + 100);
    ASSERT_FALSE(ret);
}

} // namespace ult
} // namespace L0
