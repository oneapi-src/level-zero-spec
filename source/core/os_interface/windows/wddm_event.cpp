#include "os_interface/windows/wddm_event.h"
#include "runtime/execution_environment/execution_environment.h"

namespace L0 {

OsEvent *OsEvent::create(void *execEnvRT) {
    return new WddmEvent(execEnvRT);
}

bool WddmEvent::hostSynchronize(NEO::GraphicsAllocation *allocation,
                                uint32_t timeout) {
    return true;
}

} // namespace L0
