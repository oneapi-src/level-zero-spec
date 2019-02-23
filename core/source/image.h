#pragma once
#include "device.h"
#include "xe_image.h"

struct _xe_image_handle_t {
};

namespace xe {

struct Image : public _xe_image_handle_t {
    virtual xe_result_t destroy() = 0;

    static Image *fromHandle(xe_image_handle_t handle) {
        return static_cast<Image *>(handle);
    }

    inline xe_image_handle_t toHandle() {
        return this;
    }
};

} // namespace xe
