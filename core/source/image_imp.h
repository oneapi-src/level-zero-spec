#pragma once
#ifndef IMAGE_INTERNAL
#error "Don't #include this file directly."
#endif //CMD_LIST_INTERNAL

#include "image.h"
#include "memory_manager.h"

namespace L0 {

const int XE_IMAGE_FORMAT_MAX = XE_IMAGE_FORMAT_FLOAT32;
const int XE_NUMCHANNELS_MAX = 4;
const int XE_NUMCHANNELS_MIN = 1;

struct ImageImp : public Image {

    xe_result_t destroy() override;

    virtual bool initialize(Device *device, const xe_image_desc_t *desc);

	//Sizes of xe_image_format_t image formats
    size_t format_size[XE_IMAGE_FORMAT_MAX + 1] = {
			sizeof(uint8_t), sizeof(uint16_t), sizeof(uint32_t),
            sizeof(int8_t), sizeof(int16_t), sizeof(int32_t),
            sizeof(uint16_t), sizeof(float) };
    ImageImp() : imageDesc({0}), allocation(nullptr) {

    }

protected:
    xe_image_desc_t imageDesc;
	GraphicsAllocation *allocation;
};

} //namespace L0
