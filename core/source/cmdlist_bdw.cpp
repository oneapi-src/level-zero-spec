#include "runtime/gen8/hw_cmds.h"
#include "runtime/gen8/hw_info.h"
#include "cmdlist_hw.inl"
#include "igfxfmid.h"

namespace xe {

static CommandListPopulateFactory<IGFX_BROADWELL, CommandListCoreFamily<IGFX_GEN8_CORE>> populateBDW;

} // namespace xe
