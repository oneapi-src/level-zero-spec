#include "graphics_allocation.h"
#include "runtime/memory_manager/graphics_allocation.h"
#include "gmock/gmock.h"

namespace L0 {

TEST(GraphicsAllocation, ctor) {
    uint8_t buffer[1024];
    GraphicsAllocation allocation(buffer, sizeof(buffer));

    EXPECT_NE(nullptr, allocation.allocationRT);
}

TEST(GraphicsAllocation, ctorWrapper) {
    uint8_t buffer[1024];
    OCLRT::GraphicsAllocation graphicsAllocation(buffer, sizeof(buffer), 0, 1, false);
    GraphicsAllocation allocation(&graphicsAllocation);

    EXPECT_NE(nullptr, allocation.allocationRT);
}

} // namespace L0
