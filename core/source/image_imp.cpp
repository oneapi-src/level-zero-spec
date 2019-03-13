#define IMAGE_INTERNAL
#include "image_imp.h"
#undef IMAGE_INTERNAL

#include "igfxfmid.h"
#include "memory_manager.h"
#include <cassert>

namespace L0 {

ImageAllocatorFn imageFactory[IGFX_MAX_PRODUCT] = {};

xe_result_t ImageImp::destroy() {
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
    auto memoryManager = device->getMemoryManager();
    assert(memoryManager);

    if (desc)
        imageDesc = *desc;

	size_t elem_size = format_size[imageDesc.format];
	size_t size = elem_size * imageDesc.height * imageDesc.width * imageDesc.width;

	//TODO should this really be allocating memory?  Should it be done later?
	//TODO free the allocation when image is destroyed
	auto allocation = memoryManager->allocateManagedMemory(size, elem_size);
    assert(allocation);
    return true;
}

} //namespace L0
