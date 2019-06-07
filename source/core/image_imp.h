#pragma once
#ifndef IMAGE_INTERNAL
#error "Don't #include this file directly."
#endif // CMD_LIST_INTERNAL

#include "image.h"
#include "memory_manager.h"

namespace L0 {

const int XE_IMAGE_FORMAT_COMPONENT_LAYOUT_MAX = XE_IMAGE_FORMAT_LAYOUT_P416;
const int XE_IMAGE_FORMAT_MEDIA_LAYOUT_OFFSET = XE_IMAGE_FORMAT_LAYOUT_Y8;
const int XE_IMAGE_FORMAT_MEDIA_LAYOUT_MAX = XE_IMAGE_FORMAT_LAYOUT_P416;
const int XE_IMAGE_FORMAT_LAYOUT_MAX = XE_IMAGE_FORMAT_MEDIA_LAYOUT_MAX;
const int XE_IMAGE_FORMAT_TYPE_MAX = XE_IMAGE_FORMAT_TYPE_FLOAT;
const int XE_IMAGE_FORMAT_SWIZZLE_MAX = XE_IMAGE_FORMAT_SWIZZLE_X;

struct ImageFormatDescriptor {
    enum formatType {
        COMPONENT,
        MEDIA
    };
    uint32_t channelBytes;
    uint32_t bitsPerPixel;
    enum formatType type;

    ImageFormatDescriptor(enum formatType type, uint32_t cBytes, uint32_t bpp=0)
       : type(type), channelBytes(cBytes) {
        bitsPerPixel = bpp > 0 ? bpp : cBytes * 8;
    }
};

struct ImageImp : public Image {
    using IFD = ImageFormatDescriptor;

    xe_result_t destroy() override;

    virtual bool initialize(Device *device, const xe_image_desc_t *desc);

    const ImageFormatDescriptor formats[XE_IMAGE_FORMAT_LAYOUT_MAX+1] = {
        IFD(IFD::COMPONENT, 1),  // XE_IMAGE_FORMAT_LAYOUT_8
        IFD(IFD::COMPONENT, 2),  // XE_IMAGE_FORMAT_LAYOUT_16
        IFD(IFD::COMPONENT, 4),  // XE_IMAGE_FORMAT_LAYOUT_32
        IFD(IFD::COMPONENT, 2),  // XE_IMAGE_FORMAT_LAYOUT_8_8
        IFD(IFD::COMPONENT, 4),  // XE_IMAGE_FORMAT_LAYOUT_8_8_8_8
        IFD(IFD::COMPONENT, 4),  // XE_IMAGE_FORMAT_LAYOUT_16_16
        IFD(IFD::COMPONENT, 8),  // XE_IMAGE_FORMAT_LAYOUT_16_16_16_16
        IFD(IFD::COMPONENT, 8),  // XE_IMAGE_FORMAT_LAYOUT_32_32
        IFD(IFD::COMPONENT, 16), // XE_IMAGE_FORMAT_LAYOUT_32_32_32_32
        IFD(IFD::COMPONENT, 4),  // XE_IMAGE_FORMAT_LAYOUT_10_10_10_2
        IFD(IFD::COMPONENT, 4),  // XE_IMAGE_FORMAT_LAYOUT_11_11_10
        IFD(IFD::COMPONENT, 2),  // XE_IMAGE_FORMAT_LAYOUT_5_6_5
        IFD(IFD::COMPONENT, 2),  // XE_IMAGE_FORMAT_LAYOUT_5_5_5_1
        IFD(IFD::COMPONENT, 2),  // XE_IMAGE_FORMAT_LAYOUT_4_4_4_4
        IFD(IFD::MEDIA, 1),      // XE_IMAGE_FORMAT_LAYOUT_Y8
        IFD(IFD::MEDIA, 1, 12),  // XE_IMAGE_FORMAT_LAYOUT_NV12
        IFD(IFD::MEDIA, 2),      // XE_IMAGE_FORMAT_LAYOUT_YUYV
        IFD(IFD::MEDIA, 2),      // XE_IMAGE_FORMAT_LAYOUT_VYUY
        IFD(IFD::MEDIA, 2),      // XE_IMAGE_FORMAT_LAYOUT_YVYU
        IFD(IFD::MEDIA, 2),      // XE_IMAGE_FORMAT_LAYOUT_UYVY
        IFD(IFD::MEDIA, 4),      // XE_IMAGE_FORMAT_LAYOUT_AYUV
        IFD(IFD::MEDIA, 0),      // XE_IMAGE_FORMAT_LAYOUT_YUAV (does this exist?)
        IFD(IFD::MEDIA, 2, 24),  // XE_IMAGE_FORMAT_LAYOUT_P010
        IFD(IFD::MEDIA, 4, 32),  // XE_IMAGE_FORMAT_LAYOUT_Y410
        IFD(IFD::MEDIA, 2, 24),  // XE_IMAGE_FORMAT_LAYOUT_P012
        IFD(IFD::MEDIA, 2, 16),  // XE_IMAGE_FORMAT_LAYOUT_Y16
        IFD(IFD::MEDIA, 2, 24),  // XE_IMAGE_FORMAT_LAYOUT_P016
        IFD(IFD::MEDIA, 2, 32),  // XE_IMAGE_FORMAT_LAYOUT_Y216
        IFD(IFD::MEDIA, 2, 32),  // XE_IMAGE_FORMAT_LAYOUT_P216
        IFD(IFD::MEDIA, 2, 64)   // XE_IMAGE_FORMAT_LAYOUT_P416
    };

    ImageImp() : allocation(nullptr) {}

    virtual ~ImageImp() = default;

    GraphicsAllocation *getAllocation() override { return allocation; }

    size_t getSizeInBytes() override { return sizeBytes; }

  protected:
    Device *device = nullptr;
    xe_image_desc_t imageDesc;
    GraphicsAllocation *allocation;
    size_t sizeBytes;
};

} // namespace L0
