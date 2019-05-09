#pragma once
#include "runtime/os_interface/linux/os_interface.h"

#include "os_interface/os_event.h"
#include "graphics_allocation.h"

namespace L0 {

class DrmEvent : public OsEvent {
  public:
    DrmEvent(void *execEnvRT) : OsEvent(execEnvRT) {}
    bool hostSynchronize(NEO::GraphicsAllocation* allocation, uint32_t timeout) override;
};

} // namespace L0
