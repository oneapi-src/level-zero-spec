#pragma once
#ifndef IMAGE_INTERNAL
#error "Don't #include this file directly."
#endif // CMD_LIST_INTERNAL

#include "image.h"
#include "memory_manager.h"

namespace L0 {

const int XE_IMAGE_FORMAT_LAYOUT_MAX = XE_IMAGE_FORMAT_LAYOUT_P416;
const int XE_IMAGE_FORMAT_TYPE_MAX = XE_IMAGE_FORMAT_TYPE_FLOAT;
const int XE_IMAGE_FORMAT_SWIZZLE_MAX = XE_IMAGE_FORMAT_SWIZZLE_X;

struct ImageImp : public Image {

    xe_result_t destroy() override;

    virtual bool initialize(Device *device, const xe_image_desc_t *desc);

    // Sizes of xe_image_format_t image formats
    const size_t formatLayoutSize[XE_IMAGE_FORMAT_LAYOUT_MAX] = {
        1,  // XE_IMAGE_FORMAT_LAYOUT_8
        2,  // XE_IMAGE_FORMAT_LAYOUT_16
        4,  // XE_IMAGE_FORMAT_LAYOUT_32
        2,  // XE_IMAGE_FORMAT_LAYOUT_8_8
        4,  // XE_IMAGE_FORMAT_LAYOUT_8_8_8_8
        4,  // XE_IMAGE_FORMAT_LAYOUT_16_16
        8,  // XE_IMAGE_FORMAT_LAYOUT_16_16_16_16
        8,  // XE_IMAGE_FORMAT_LAYOUT_32_32
        16, // XE_IMAGE_FORMAT_LAYOUT_32_32_32_32
        4,  // XE_IMAGE_FORMAT_LAYOUT_10_10_10_2
        4,  // XE_IMAGE_FORMAT_LAYOUT_11_11_10
        2,  // XE_IMAGE_FORMAT_LAYOUT_5_6_5
        2,  // XE_IMAGE_FORMAT_LAYOUT_5_5_5_1
        2,  // XE_IMAGE_FORMAT_LAYOUT_4_4_4_4
        // XE_IMAGE_FORMAT_LAYOUT_Y8
        // XE_IMAGE_FORMAT_LAYOUT_NV12
        // XE_IMAGE_FORMAT_LAYOUT_YUYV
        // XE_IMAGE_FORMAT_LAYOUT_VYUY
        // XE_IMAGE_FORMAT_LAYOUT_YVYU
        // XE_IMAGE_FORMAT_LAYOUT_UYVY
        // XE_IMAGE_FORMAT_LAYOUT_AYUV
        // XE_IMAGE_FORMAT_LAYOUT_YUAV
        // XE_IMAGE_FORMAT_LAYOUT_P010
        // XE_IMAGE_FORMAT_LAYOUT_Y410
        // XE_IMAGE_FORMAT_LAYOUT_P012
        // XE_IMAGE_FORMAT_LAYOUT_Y16
        // XE_IMAGE_FORMAT_LAYOUT_P016
        // XE_IMAGE_FORMAT_LAYOUT_Y216
        // XE_IMAGE_FORMAT_LAYOUT_P216
        // XE_IMAGE_FORMAT_LAYOUT_P416
    };

    ImageImp() : allocation(nullptr) {}

    GraphicsAllocation *getAllocation() override { return allocation; }

    size_t getSizeInBytes() override { return sizeBytes; }

  protected:
    Device *device = nullptr;
    xe_image_desc_t imageDesc;
    GraphicsAllocation *allocation;
    size_t sizeBytes;
};

} // namespace L0
