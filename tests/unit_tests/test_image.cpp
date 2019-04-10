#include "mock_image.h"
#include "mock_device.h"
#include "mock_module_precompiled.h"
#include "igfxfmid.h"
#include "test.h"
#include "unit_tests/gen_common/gen_cmd_parse.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/helpers/hw_info.h"
#include "runtime/indirect_heap/indirect_heap.h"
#include "runtime/platform/platform.h"

namespace L0 {
namespace ult {

using ::testing::AnyNumber;

TEST(xeImageDestroy, redirectsToObject) {

    Mock<Device> device;
    EXPECT_CALL(device, getMemoryManager).Times(AnyNumber());

    xe_image_desc_t desc = {};

    auto image = whitebox_cast(Image::create(productFamily, &device, &desc));
    ASSERT_NE(nullptr, image);

    auto result = xeImageDestroy(image->toHandle());
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

using ImageCreate = ::testing::Test;

TEST_F(ImageCreate, returnsImageOnSuccess) {
    Mock<Device> device;
    EXPECT_CALL(device, getMemoryManager).Times(AnyNumber());

    xe_image_desc_t desc = {};

    auto image = whitebox_cast(Image::create(productFamily, &device, &desc));
    ASSERT_NE(nullptr, image);

    image->destroy();
}

TEST_F(ImageCreate, givenInvalidProductFamilyReturnsNullPointer) {
    Mock<Device> device;
    xe_image_desc_t desc = {};

    auto image = whitebox_cast(Image::create(IGFX_UNKNOWN, &device, &desc));
    ASSERT_EQ(nullptr, image);
}

TEST_F(ImageCreate, descMatchesAllocation) {
    auto platform = NEO::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    auto deviceRT = platform->getDevice(0);
    ASSERT_NE(nullptr, deviceRT);
    auto device = Device::create(deviceRT);

    xe_image_desc_t desc = {};

    desc.type = XE_IMAGE_TYPE_3D;
    desc.format.layout = XE_IMAGE_FORMAT_LAYOUT_8_8_8_8;
    desc.format.type = XE_IMAGE_FORMAT_TYPE_UINT;
    desc.format.x = desc.format.y = desc.format.z = desc.format.w = XE_IMAGE_FORMAT_SWIZZLE_R;
    desc.width = 10;
    desc.height = 10;
    desc.depth = 10;

    auto image = whitebox_cast(Image::create(productFamily, device, &desc));
    ASSERT_NE(nullptr, image);
    auto alloc = image->getAllocation();
    ASSERT_NE(nullptr, alloc);

    ASSERT_EQ(alloc->getSize(),
              4 * desc.width * desc.height * desc.depth * sizeof(uint8_t));
    ASSERT_EQ(image->getSizeInBytes(),
              4 * desc.width * desc.height * desc.depth * sizeof(uint8_t));

    delete device;
}

HWTEST2_F(ImageCreate, descBadParamsFail, MatchAny) {
    using RENDER_SURFACE_STATE = typename FamilyType::RENDER_SURFACE_STATE;

    Mock<Device> device;

    auto imageCore = new ImageCoreFamily<gfxCoreFamily>();

    xe_image_desc_t desc, default_desc;
    bool ret;

    default_desc.type = XE_IMAGE_TYPE_2D;
    default_desc.format.layout = XE_IMAGE_FORMAT_LAYOUT_32;
    default_desc.format.type = XE_IMAGE_FORMAT_TYPE_UINT;
    default_desc.format.x = XE_IMAGE_FORMAT_SWIZZLE_R;
    default_desc.width = 10;
    default_desc.height = 10;
    default_desc.depth = 1;
    default_desc.arraylevels = 1;
    default_desc.miplevels = 1;

    desc = default_desc;
    desc.type = static_cast<xe_image_type_t>(XE_IMAGE_TYPE_3D + 100);

    ret = imageCore->initialize(&device, &desc);
    ASSERT_FALSE(ret);

    desc = default_desc;
    desc.format.layout = static_cast<xe_image_format_layout_t>(XE_IMAGE_FORMAT_LAYOUT_P416 + 100);
    ret = imageCore->initialize(&device, &desc);
    ASSERT_FALSE(ret);

    desc = default_desc;
    desc.format.type = static_cast<xe_image_format_type_t>(XE_IMAGE_FORMAT_TYPE_FLOAT + 100);
    ret = imageCore->initialize(&device, &desc);
    ASSERT_FALSE(ret);

    desc = default_desc;
    desc.format.x = static_cast<xe_image_format_swizzle_t>(XE_IMAGE_FORMAT_SWIZZLE_X + 100);
    ret = imageCore->initialize(&device, &desc);
    ASSERT_FALSE(ret);

    desc = default_desc;
    desc.format.y = static_cast<xe_image_format_swizzle_t>(XE_IMAGE_FORMAT_SWIZZLE_X + 100);
    ret = imageCore->initialize(&device, &desc);
    ASSERT_FALSE(ret);

    desc = default_desc;
    desc.format.z = static_cast<xe_image_format_swizzle_t>(XE_IMAGE_FORMAT_SWIZZLE_X + 100);
    ret = imageCore->initialize(&device, &desc);
    ASSERT_FALSE(ret);

    desc = default_desc;
    desc.format.w = static_cast<xe_image_format_swizzle_t>(XE_IMAGE_FORMAT_SWIZZLE_X + 100);
    ret = imageCore->initialize(&device, &desc);
    ASSERT_FALSE(ret);
}

using ImageSurfaceState = ::testing::Test;

HWTEST2_F(ImageSurfaceState, descMatchesSurface, MatchAny) {
    using RENDER_SURFACE_STATE = typename FamilyType::RENDER_SURFACE_STATE;
    Mock<Device> device;

    xe_image_desc_t desc = {};

    desc.type = XE_IMAGE_TYPE_3D;
    desc.format.layout = XE_IMAGE_FORMAT_LAYOUT_8_8_8_8;
    desc.format.type = XE_IMAGE_FORMAT_TYPE_UINT;
    desc.format.x = XE_IMAGE_FORMAT_SWIZZLE_R;
    desc.format.y = XE_IMAGE_FORMAT_SWIZZLE_G;
    desc.format.z = XE_IMAGE_FORMAT_SWIZZLE_B;
    desc.format.w = XE_IMAGE_FORMAT_SWIZZLE_A;
    desc.width = 11;
    desc.height = 13;
    desc.depth = 17;

    auto imageCore = new ImageCoreFamily<gfxCoreFamily>();
    bool ret = imageCore->initialize(&device, &desc);
    ASSERT_TRUE(ret);

    auto surfaceState = &imageCore->surfaceState;

    ASSERT_EQ(surfaceState->getSurfaceType(), RENDER_SURFACE_STATE::SURFACE_TYPE_SURFTYPE_3D);
    ASSERT_EQ(surfaceState->getSurfaceFormat(), RENDER_SURFACE_STATE::SURFACE_FORMAT_R8G8B8A8_UINT);
    ASSERT_EQ(surfaceState->getWidth(), 11);
    ASSERT_EQ(surfaceState->getHeight(), 13);
    ASSERT_EQ(surfaceState->getDepth(), 17);
    ASSERT_EQ(surfaceState->getShaderChannelSelectRed(), RENDER_SURFACE_STATE::SHADER_CHANNEL_SELECT_RED_RED);
    ASSERT_EQ(surfaceState->getShaderChannelSelectGreen(), RENDER_SURFACE_STATE::SHADER_CHANNEL_SELECT_GREEN_GREEN);
    ASSERT_EQ(surfaceState->getShaderChannelSelectBlue(), RENDER_SURFACE_STATE::SHADER_CHANNEL_SELECT_BLUE_BLUE);
    ASSERT_EQ(surfaceState->getShaderChannelSelectAlpha(), RENDER_SURFACE_STATE::SHADER_CHANNEL_SELECT_ALPHA_ALPHA);
    ASSERT_EQ(surfaceState->getSurfacePitch(), sizeof(uint8_t) * desc.width * 4);
}

HWTEST2_F(ImageSurfaceState, descSwizzlesMatchSurface, MatchAny) {
    using RENDER_SURFACE_STATE = typename FamilyType::RENDER_SURFACE_STATE;
    Mock<Device> device;

    xe_image_desc_t desc = {};

    desc.type = XE_IMAGE_TYPE_3D;
    desc.format.layout = XE_IMAGE_FORMAT_LAYOUT_8_8_8_8;
    desc.format.type = XE_IMAGE_FORMAT_TYPE_UINT;
    desc.width = 11;
    desc.height = 13;
    desc.depth = 17;

    desc.format.x = XE_IMAGE_FORMAT_SWIZZLE_A;
    desc.format.y = XE_IMAGE_FORMAT_SWIZZLE_0;
    desc.format.z = XE_IMAGE_FORMAT_SWIZZLE_1;
    desc.format.w = XE_IMAGE_FORMAT_SWIZZLE_X;

    auto imageCore = new ImageCoreFamily<gfxCoreFamily>();
    bool ret = imageCore->initialize(&device, &desc);
    ASSERT_TRUE(ret);

    auto surfaceState = &imageCore->surfaceState;

    ASSERT_EQ(surfaceState->getShaderChannelSelectRed(), RENDER_SURFACE_STATE::SHADER_CHANNEL_SELECT_RED_ALPHA);
    ASSERT_EQ(surfaceState->getShaderChannelSelectGreen(), RENDER_SURFACE_STATE::SHADER_CHANNEL_SELECT_GREEN_ZERO);
    ASSERT_EQ(surfaceState->getShaderChannelSelectBlue(), RENDER_SURFACE_STATE::SHADER_CHANNEL_SELECT_BLUE_ONE);
    ASSERT_EQ(surfaceState->getShaderChannelSelectAlpha(), RENDER_SURFACE_STATE::SHADER_CHANNEL_SELECT_ALPHA_ZERO);
}

HWTEST2_F(ImageSurfaceState, descMatchesSurfaceFormats, MatchAny) {
    using RENDER_SURFACE_STATE = typename FamilyType::RENDER_SURFACE_STATE;
    using SURFACE_FORMAT = typename RENDER_SURFACE_STATE::SURFACE_FORMAT;
    Mock<Device> device;

    xe_image_desc_t desc = {};
    desc.type = XE_IMAGE_TYPE_3D;
    desc.width = 11;
    desc.height = 13;
    desc.depth = 17;

    struct FormatInfo {
        size_t elemSize;
        xe_image_format_layout_t formatLayout;
        xe_image_format_type_t formatType;
        SURFACE_FORMAT ssFormat;
    };
    struct FormatInfo testFormats[] = {
        {sizeof(uint8_t), XE_IMAGE_FORMAT_LAYOUT_8, XE_IMAGE_FORMAT_TYPE_UINT,
                RENDER_SURFACE_STATE::SURFACE_FORMAT_R8_UINT},
        {sizeof(uint32_t) * 4, XE_IMAGE_FORMAT_LAYOUT_32_32_32_32, XE_IMAGE_FORMAT_TYPE_UINT,
                RENDER_SURFACE_STATE::SURFACE_FORMAT_R32G32B32A32_UINT},
        {sizeof(uint8_t) * 4, XE_IMAGE_FORMAT_LAYOUT_8_8_8_8, XE_IMAGE_FORMAT_TYPE_UNORM,
                RENDER_SURFACE_STATE::SURFACE_FORMAT_R8G8B8A8_UNORM},
        {sizeof(int16_t), XE_IMAGE_FORMAT_LAYOUT_16, XE_IMAGE_FORMAT_TYPE_SNORM,
                RENDER_SURFACE_STATE::SURFACE_FORMAT_R16_SNORM},
        {sizeof(float) * 4, XE_IMAGE_FORMAT_LAYOUT_32_32_32_32, XE_IMAGE_FORMAT_TYPE_FLOAT,
                RENDER_SURFACE_STATE::SURFACE_FORMAT_R32G32B32A32_FLOAT},
    };
    size_t numFormats = sizeof(testFormats) / sizeof(struct FormatInfo);

    for (size_t i = 0; i < numFormats; i++) {
        desc.format.layout = testFormats[i].formatLayout;
        desc.format.type = testFormats[i].formatType;

        auto imageCore = new ImageCoreFamily<gfxCoreFamily>();
        bool ret = imageCore->initialize(&device, &desc);
        ASSERT_TRUE(ret);

        auto surfaceState = &imageCore->surfaceState;
        ASSERT_EQ(surfaceState->getSurfaceFormat(), testFormats[i].ssFormat);

        ASSERT_EQ(imageCore->getSizeInBytes(),
                  testFormats[i].elemSize * desc.width * desc.height * desc.depth);

        delete imageCore;
    }
}

HWTEST2_F(ImageSurfaceState, copyToSSH, MatchAny) {
    using RENDER_SURFACE_STATE = typename FamilyType::RENDER_SURFACE_STATE;
    using BINDING_TABLE_STATE = typename FamilyType::BINDING_TABLE_STATE;
    Mock<Device> device;
    uint8_t mockSSH[sizeof(RENDER_SURFACE_STATE) * 4] = {0};
    const uint32_t bindingTableOffset = sizeof(RENDER_SURFACE_STATE) * 2;

    xe_image_desc_t desc = {};

    desc.type = XE_IMAGE_TYPE_2D;
    desc.format.layout = XE_IMAGE_FORMAT_LAYOUT_8_8_8_8;
    desc.format.type = XE_IMAGE_FORMAT_TYPE_UINT;
    desc.format.x = desc.format.y = desc.format.z = desc.format.w = XE_IMAGE_FORMAT_SWIZZLE_R;
    desc.width = 11;
    desc.height = 13;
    desc.depth = 1;

    auto imageA = new ImageCoreFamily<gfxCoreFamily>();
    bool ret = imageA->initialize(&device, &desc);
    ASSERT_TRUE(ret);

    desc.format.layout = XE_IMAGE_FORMAT_LAYOUT_32_32;
    desc.format.type = XE_IMAGE_FORMAT_TYPE_UINT;
    desc.format.x = desc.format.y = desc.format.z = desc.format.w = XE_IMAGE_FORMAT_SWIZZLE_R;
    desc.width = 10;
    desc.height = 10;

    auto imageB = new ImageCoreFamily<gfxCoreFamily>();
    ret = imageB->initialize(&device, &desc);
    ASSERT_TRUE(ret);

    imageA->copySurfaceStateToSSH(mockSSH, 0);
    imageB->copySurfaceStateToSSH(mockSSH, sizeof(RENDER_SURFACE_STATE));

    auto surfaceStateA = reinterpret_cast<RENDER_SURFACE_STATE *>(mockSSH);
    ASSERT_EQ(surfaceStateA->getSurfaceType(), RENDER_SURFACE_STATE::SURFACE_TYPE_SURFTYPE_2D);
    ASSERT_EQ(surfaceStateA->getSurfaceFormat(), RENDER_SURFACE_STATE::SURFACE_FORMAT_R8G8B8A8_UINT);
    ASSERT_EQ(surfaceStateA->getWidth(), 11);
    ASSERT_EQ(surfaceStateA->getHeight(), 13);

    auto surfaceStateB = reinterpret_cast<RENDER_SURFACE_STATE *>(ptrOffset(mockSSH, sizeof(RENDER_SURFACE_STATE)));
    ASSERT_EQ(surfaceStateB->getSurfaceType(), RENDER_SURFACE_STATE::SURFACE_TYPE_SURFTYPE_2D);
    ASSERT_EQ(surfaceStateB->getSurfaceFormat(), RENDER_SURFACE_STATE::SURFACE_FORMAT_R32G32_UINT);
    ASSERT_EQ(surfaceStateB->getWidth(), 10);
    ASSERT_EQ(surfaceStateB->getHeight(), 10);
}

} // namespace ult
} // namespace L0
