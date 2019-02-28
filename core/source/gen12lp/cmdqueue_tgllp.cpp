#include "runtime/gen12lp/hw_cmds.h"
#include "runtime/gen12lp/hw_info.h"
#include "cmdqueue_hw.inl"
#include "igfxfmid.h"

namespace L0 {

static CommandQueuePopulateFactory<IGFX_TIGERLAKE_LP, CommandQueueHw<IGFX_GEN12LP_CORE>> populateTGLLP;

} // namespace L0
