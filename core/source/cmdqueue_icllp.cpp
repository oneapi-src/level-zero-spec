#include "runtime/gen11/hw_cmds.h"
#include "runtime/gen11/hw_info.h"
#include "cmdqueue_hw.inl"
#include "igfxfmid.h"

namespace xe {

static CommandQueuePopulateFactory<IGFX_ICELAKE_LP, CommandQueueHw<IGFX_GEN11_CORE>> populateICLLP;

} // namespace xe
