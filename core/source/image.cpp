#include "image.h"

#include <cassert>

namespace L0 {

struct ImageImp : public Image {

    xe_result_t destroy() override {
        delete this;
        return XE_RESULT_SUCCESS;
    }

    ImageImp(const xe_image_desc_t *desc) {
        if (desc)
            imageDesc = *desc;
    }
protected:

    xe_image_desc_t imageDesc;
};

Image *Image::create(const xe_image_desc_t *desc) {
    auto image = new ImageImp(desc);
    assert(image != nullptr);
    return image;
}

} //namespace L0
