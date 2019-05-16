#include "os_interface/windows/os_context_windows.h"

namespace L0 {

OsContext *OsContext::create() { return new OsContextWindows(); }

} // namespace L0
