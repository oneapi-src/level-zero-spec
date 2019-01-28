#include "cmd_list_gfxcore_family.inl"
#include "cmd_list_product_family.h"
#include "igfxfmid.h"

namespace xe {

static CommandListProductFamilyPopulateFactory<IGFX_BROADWELL, CommandListGfxCoreFamily<IGFX_GEN8_CORE>> populateSKL;

} // namespace xe
