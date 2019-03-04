#pragma once
#include "device.h"
#include "xe_image.h"

struct _xe_image_handle_t {
};

namespace L0 {

struct Image : public _xe_image_handle_t {
    template <typename Type>
    struct Allocator {
        static Image *allocate(const xe_image_desc_t *desc) {
            return new Type(desc);
        }
    };

    virtual xe_result_t destroy() = 0;

    static Image *create(uint32_t productFamily, const xe_image_desc_t *desc);

    static Image *fromHandle(xe_image_handle_t handle) {
        return static_cast<Image *>(handle);
    }

    inline xe_image_handle_t toHandle() {
        return this;
    }
};

using ImageAllocatorFn = Image *(*)(const xe_image_desc_t *);
extern ImageAllocatorFn imageFactory[];

template <uint32_t productFamily, typename ImageType>
struct ImagePopulateFactory {
    ImagePopulateFactory() {
	    imageFactory[productFamily] = Image::Allocator<ImageType>::allocate;
    }
};

} // namespace L0
