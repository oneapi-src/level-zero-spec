#include "runtime/gen8/hw_cmds.h"
#include "runtime/gen8/hw_info.h"
#include "cmd_list_hw.inl"
#include "igfxfmid.h"

namespace xe {

static CommandListPopulateFactory<IGFX_BROADWELL, CommandListHw<IGFX_GEN8_CORE>> populateSKL;

} // namespace xe
