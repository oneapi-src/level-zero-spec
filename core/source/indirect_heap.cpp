#include "indirect_heap.h"

namespace L0 {

IndirectHeap::IndirectHeap(GraphicsAllocation *gfxAllocation) :
        BaseClass(gfxAllocation) {
}

IndirectHeap::IndirectHeap(GraphicsAllocation *gfxAllocation, bool canBeUtilizedAs4GbHeap) :
        BaseClass(gfxAllocation), canBeUtilizedAs4GbHeap(canBeUtilizedAs4GbHeap) {
}

IndirectHeap::IndirectHeap(void *buffer, size_t bufferSize) :
        BaseClass(buffer, bufferSize) {
}

} // namespace L0
