#include "os_interface/windows/os_context_windows.h"
#include "os_interface/windows/wddm_event.h"

namespace L0 {

OsContext *OsContext::create(void *execEnvRT) {
    auto wddm = new WddmEvent(execEnvRT);

    return new OsContextWindows(execEnvRT);
}

} //namespace L0
