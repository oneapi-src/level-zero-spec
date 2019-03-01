#include "mock_image.h"

namespace L0 {
namespace ult {

WhiteBox<::L0::Image>::WhiteBox(const xe_image_desc_t *desc) {
    if (desc)
        imageDesc = *desc;
}

WhiteBox<::L0::Image>::~WhiteBox() {
}

Mock<Image>::Mock(const xe_image_desc_t *desc) : WhiteBox<::L0::Image>(desc) {
}

Mock<Image>::~Mock() {
}

} // namespace ult
} // namespace L0
