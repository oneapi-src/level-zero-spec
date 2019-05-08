#include "os_interface/windows/wddm_event.h"
#include "runtime/execution_environment/execution_environment.h"

namespace L0 {

bool WddmEvent::waitForFlushStamp(FlushStamp &flushStamp) { return true; }

} // namespace L0
