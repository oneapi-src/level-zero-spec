#include "os_interface/linux/drm_event.h"
#include "runtime/execution_environment/execution_environment.h"
#include "runtime/os_interface/linux/drm_neo.h"
#include "runtime/os_interface/linux/drm_allocation.h"
#include "runtime/os_interface/linux/drm_buffer_object.h"

#include "drm/i915_drm.h"

namespace L0 {

OsEvent *OsEvent::create(void *execEnvRT) {
    return new DrmEvent(execEnvRT);
}

bool DrmEvent::hostSynchronize(NEO::GraphicsAllocation *allocation,
                               uint32_t timeout) {
    //Note: Can also do getBO()->wait(-1); the wait() call does not take
    //      timeout value into consideration though. So, doing that here.
    auto bo = static_cast<NEO::DrmAllocation *>(allocation)->getBO();
    if (bo == nullptr) {
	return false;
    }
    
    drm_i915_gem_wait wait = {};
    wait.bo_handle = bo->peekHandle();
    wait.timeout_ns = timeout;

    auto drm = static_cast<NEO::ExecutionEnvironment *>(execEnvRT)->osInterface->get()->getDrm();
    int ret = drm->ioctl(DRM_IOCTL_I915_GEM_WAIT, &wait);

    if (ret != 0) {
        return false;
    }

    return true;
}

} // namespace L0
