#include "cmd_list_gfxcore_family.inl"
#include "cmd_list_product_family.h"
#include "igfxfmid.h"

namespace xe {

static CommandListProductFamilyPopulateFactory<IGFX_KABYLAKE, CommandListGfxCoreFamily<IGFX_GEN9_CORE>> populateSKL;

} // namespace xe
