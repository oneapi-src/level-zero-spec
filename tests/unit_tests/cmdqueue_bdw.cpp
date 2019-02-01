#include "runtime/gen8/hw_cmds.h"
#include "runtime/gen8/hw_info.h"
#include "cmdqueue_hw.inl"
#include "igfxfmid.h"

namespace xe {

static CommandQueuePopulateFactory<IGFX_BROADWELL, CommandQueueHw<IGFX_GEN8_CORE>> populateBDW;

} // namespace xe
