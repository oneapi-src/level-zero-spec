#include "os_interface/os_event.h"
#include "graphics_allocation.h"

namespace L0 {

class WddmEvent : public OsEvent{
  public:
    WddmEvent(void *execEnvRT) : OsEvent(execEnvRT) {}
    bool hostSynchronize(NEO::GraphicsAllocation* allocation, uint32_t timeout) override;
};

} // namespace L0
