#include "mock_image.h"

namespace L0 {
namespace ult {

WhiteBox<::L0::Image>::WhiteBox() {

}

WhiteBox<::L0::Image>::~WhiteBox() {
}

Mock<Image>::Mock() : WhiteBox<::L0::Image>() {
}

Mock<Image>::~Mock() {
}

} // namespace ult
} // namespace L0
