#include "runtime/gen9/hw_cmds.h"
#include "runtime/gen9/hw_info.h"
#include "cmdlist_hw.inl"
#include "igfxfmid.h"

namespace xe {

static CommandListPopulateFactory<IGFX_SKYLAKE, CommandListHw<IGFX_GEN9_CORE>> populateSKL;

} // namespace xe
