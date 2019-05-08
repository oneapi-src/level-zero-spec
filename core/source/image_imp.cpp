#define IMAGE_INTERNAL
#include "image_imp.h"
#undef IMAGE_INTERNAL

#include "igfxfmid.h"
#include "memory_manager.h"
#include <cassert>

namespace L0 {

ImageAllocatorFn imageFactory[IGFX_MAX_PRODUCT] = {};

xe_result_t ImageImp::destroy() {
    if (this->allocation) {
        assert(this->device);
        assert(globalMemoryManager);
        globalMemoryManager->freeMemory(this->allocation);
    }

    delete this;
    return XE_RESULT_SUCCESS;
}

Image *Image::create(uint32_t productFamily, Device *device, const xe_image_desc_t *desc) {
    ImageAllocatorFn allocator = nullptr;
    if (productFamily < IGFX_MAX_PRODUCT) {
        allocator = imageFactory[productFamily];
    }

    ImageImp *image = nullptr;
    if (allocator) {
        image = static_cast<ImageImp *>((*allocator)());
        image->initialize(device, desc);
    }

    return image;
}

bool ImageImp::initialize(Device *device, const xe_image_desc_t *desc) {
    assert(device);
    this->device = device;
    assert(globalMemoryManager);

    if (desc == nullptr) {
        return false;
    }

    imageDesc = *desc;

    size_t elem_size = formatLayoutSize[imageDesc.format.layout];
    sizeBytes = elem_size * imageDesc.height * imageDesc.width * imageDesc.depth;

    allocation = globalMemoryManager->allocateManagedMemory(device, sizeBytes, elem_size);
    assert(allocation);
    return true;
}

} // namespace L0
