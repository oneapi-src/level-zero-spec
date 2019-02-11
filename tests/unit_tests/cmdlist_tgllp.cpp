#include "runtime/gen12lp/hw_cmds.h"
#include "runtime/gen12lp/hw_info.h"
#include "cmdlist_hw.inl"
#include "igfxfmid.h"

namespace xe {

static CommandListPopulateFactory<IGFX_TIGERLAKE_LP, CommandListHw<IGFX_GEN12LP_CORE>> populateTGLLP;

} // namespace xe
