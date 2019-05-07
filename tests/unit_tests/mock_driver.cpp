#include "mock_driver.h"

namespace L0 {
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
} // namespace L0
