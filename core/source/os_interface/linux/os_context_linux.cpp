#include "os_interface/linux/os_context_linux.h"
#include "os_interface/linux/drm_event.h"

namespace L0 {

OsContext *OsContext::create(void *execEnvRT) {
    auto drm = new DrmEvent(execEnvRT);

    return new OsContextLinux(execEnvRT);
}

} // namespace L0
