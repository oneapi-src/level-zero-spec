#include "runtime/gen8/hw_cmds.h"
#include "runtime/gen8/hw_info.h"
#include "cmd_list_gfxcore_family.inl"
#include "igfxfmid.h"

namespace xe {

static CommandListProductFamilyPopulateFactory<IGFX_BROADWELL, CommandListHw<IGFX_GEN8_CORE>> populateSKL;

} // namespace xe
