#include "function.h"

#include "graphics_allocation.h"

namespace L0 {
ImmutableFunctionInfo::~ImmutableFunctionInfo() {
    isaGraphicsAllocation.deleteOwned();
}
} // namespace L0
