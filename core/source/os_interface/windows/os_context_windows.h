#include "os_interface/os_context.h"

namespace L0 {

class OsContextWindows : public OsContext {
  public:
    OsContextWindows(void *execEnvRT) : execEnvRT(execEnvRT) {}

  protected:
    void *execEnvRT;
};

} // namespace L0
