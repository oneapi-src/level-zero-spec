#include "function.h"

#include "graphics_allocation.h"

#include "igfxfmid.h"

namespace L0 {
ImmutableFunctionInfo::~ImmutableFunctionInfo() {
    isaGraphicsAllocation.deleteOwned();
}

FunctionAllocatorFn functionFactory[IGFX_MAX_PRODUCT] = {};

} // namespace L0
