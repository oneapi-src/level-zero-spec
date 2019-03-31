#include "mocs_mapper.h"

#include "runtime/gmm_helper/gmm_helper.h"

namespace L0 {

uint32_t MOCSMapper::getUncachedMOCS() const {
    return gmmHelper->getMOCS(GMM_RESOURCE_USAGE_OCL_BUFFER_CACHELINE_MISALIGNED);
}

uint32_t MOCSMapper::getFullyCachedMOCS() const {
    return gmmHelper->getMOCS(GMM_RESOURCE_USAGE_OCL_BUFFER);
}

uint32_t MOCSMapper::getCachedInstructionHeapMOCS() const {
    return gmmHelper->getMOCS(GMM_RESOURCE_USAGE_OCL_STATE_HEAP_BUFFER);
}

uint32_t MOCSMapper::getCachedStateHeapMOCS() const {
    return gmmHelper->getMOCS(GMM_RESOURCE_USAGE_OCL_STATE_HEAP_BUFFER);
}

} // namespace L0
