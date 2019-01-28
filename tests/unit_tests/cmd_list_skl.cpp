#include "cmd_list_gfxcore_family.inl"
#include "igfxfmid.h"

namespace xe {

static CommandListProductFamilyPopulateFactory<IGFX_SKYLAKE, CommandListGfxCoreFamily<IGFX_GEN9_CORE>> populateSKL;

} // namespace xe
