#pragma once
#include "image.h"
#include "white_box.h"
#include "mock.h"

namespace L0 {

namespace ult {

template <>
struct WhiteBox<::L0::Image> : public ::L0::Image {
    //using BaseClass = ::L0::ImageImp;

    WhiteBox(const xe_image_desc_t *desc);
    virtual ~WhiteBox();

    xe_image_desc_t imageDesc;
};

using Image = WhiteBox<::L0::Image>;

template <>
struct Mock<Image> : public Image {
    Mock(const xe_image_desc_t *desc = nullptr);
    virtual ~Mock();

    MOCK_METHOD0(destroy, xe_result_t());

};

} // namespace ult
} // namespace L0
