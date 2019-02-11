#include "mock_driver.h"

namespace xe {
namespace ult {

Mock<Driver>::Mock() {
    previousDriver = driver;
    driver = this;
}

Mock<Driver>::~Mock() {
    if (driver == this) {
        driver = previousDriver;
    }
}

} // namespace ult
} // namespace xe
