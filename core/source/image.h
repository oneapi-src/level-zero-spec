#pragma once
#include "device.h"
#include "graphics_allocation.h"
#include "xe_image.h"

struct _xe_image_handle_t {
};

namespace L0 {

struct Image : public _xe_image_handle_t {
    template <typename Type>
    struct Allocator {
        static Image *allocate() {
            return new Type();
        }
    };

    virtual xe_result_t destroy() = 0;

    static Image *create(uint32_t productFamily, Device *device, const xe_image_desc_t *desc);

    virtual GraphicsAllocation *getAllocation() = 0;
    virtual void copySurfaceStateToSSH(void *surfaceStateHeap, const uint32_t surfaceStateOffset,
            const uint32_t bindingTableOffset, const uint32_t bindingTableIndex) = 0;
    virtual size_t getSizeInBytes() = 0;

    static Image *fromHandle(xe_image_handle_t handle) {
        return static_cast<Image *>(handle);
    }

    inline xe_image_handle_t toHandle() {
        return this;
    }
};

using ImageAllocatorFn = Image *(*)();
extern ImageAllocatorFn imageFactory[];

template <uint32_t productFamily, typename ImageType>
struct ImagePopulateFactory {
    ImagePopulateFactory() {
	    imageFactory[productFamily] = Image::Allocator<ImageType>::allocate;
    }
};

} // namespace L0
