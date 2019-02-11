#include "runtime/gen12hp/hw_cmds.h"
#include "runtime/gen12hp/hw_info.h"
#include "cmdlist_hw.inl"
#include "igfxfmid.h"

namespace xe {

static CommandListPopulateFactory<IGFX_TIGERLAKE_HP, CommandListHw<IGFX_GEN12_CORE>> populateTGLHP;

} // namespace xe
