#include "runtime/gen11/hw_cmds.h"
#include "runtime/gen11/hw_info.h"
#include "cmdlist_hw.inl"
#include "igfxfmid.h"

namespace xe {

static CommandListPopulateFactory<IGFX_ICELAKE_LP, CommandListHw<IGFX_GEN11_CORE>> populateICLLP;

} // namespace xe
