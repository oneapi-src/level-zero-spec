#include "function.h"

#include "graphics_allocation.h"

namespace L0 {
ImmutableFunctionInfo::~ImmutableFunctionInfo() {
    delete isaGraphicsAllocation;
}
} // namespace L0
