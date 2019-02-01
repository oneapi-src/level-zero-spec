#include "mock_driver.h"

namespace xe {

MockDriver::MockDriver() {
    previousDriver = driver;
    driver = this;
}

MockDriver::~MockDriver() {
    if (driver == this) {
        driver = previousDriver;
    }
}

} // namespace xe
