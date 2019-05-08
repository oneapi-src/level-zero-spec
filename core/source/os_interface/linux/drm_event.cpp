#include "os_interface/linux/drm_event.h"
#include "runtime/execution_environment/execution_environment.h"
#include "runtime/os_interface/linux/drm_neo.h"

#include "drm/i915_drm.h"

namespace L0 {

bool DrmEvent::waitForFlushStamp(FlushStamp &flushStamp) {
    drm_i915_gem_wait wait = {};
    wait.bo_handle = static_cast<uint32_t>(flushStamp);
    wait.timeout_ns = -1;
    auto drm = static_cast<NEO::ExecutionEnvironment *>(execEnvRT)->osInterface->get()->getDrm();

    int ret = drm->ioctl(DRM_IOCTL_I915_GEM_WAIT, &wait);

    if (ret != 0) {
        return false;
    }

    return true;
}

} // namespace L0
