#include "os_interface/os_context.h"

namespace L0 {

class OsContextLinux : public OsContext {
  public:
    OsContextLinux(void *execEnvRT) : execEnvRT(execEnvRT) {}

  protected:
    void *execEnvRT;
};

} // namespace L0
