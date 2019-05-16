#include "os_interface/linux/os_context_linux.h"

namespace L0 {

OsContext *OsContext::create() {
    return new OsContextLinux();
}

} // namespace L0
