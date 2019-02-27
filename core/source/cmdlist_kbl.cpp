#include "runtime/gen9/hw_cmds.h"
#include "runtime/gen9/hw_info.h"
#include "cmdlist_hw.inl"
#include "igfxfmid.h"

namespace xe {

template <>
struct CommandListProductFamily<IGFX_KABYLAKE> : public CommandListCoreFamily<IGFX_GEN9_CORE> {
    using CommandListCoreFamily::CommandListCoreFamily;
};

static CommandListPopulateFactory<IGFX_KABYLAKE, CommandListProductFamily<IGFX_KABYLAKE>> populateKBL;

} // namespace xe
