#define IMAGE_INTERNAL
#include "image_imp.h"
#undef IMAGE_INTERNAL

#include "igfxfmid.h"

namespace L0 {

ImageAllocatorFn imageFactory[IGFX_MAX_PRODUCT] = {};

xe_result_t ImageImp::destroy() {
    delete this;
    return XE_RESULT_SUCCESS;
}

Image *Image::create(uint32_t productFamily, const xe_image_desc_t *desc) {
    ImageAllocatorFn allocator = nullptr;
    if (productFamily < IGFX_MAX_PRODUCT) {
        allocator = imageFactory[productFamily];
    }

    ImageImp *image = nullptr;
    if (allocator) {
        image = static_cast<ImageImp *>((*allocator)(desc));
        image->initialize();
    }

    return image;
}

bool ImageImp::initialize() {
    return true;
}

} //namespace L0
