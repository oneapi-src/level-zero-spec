#include "runtime/gen8/hw_cmds.h"
#include "runtime/gen8/hw_info.h"
#include "cmdlist_hw.inl"
#include "igfxfmid.h"

namespace xe {

template <>
struct CommandListProductFamily<IGFX_BROADWELL> : public CommandListCoreFamily<IGFX_GEN8_CORE> {
    using CommandListCoreFamily::CommandListCoreFamily;
};

static CommandListPopulateFactory<IGFX_BROADWELL, CommandListProductFamily<IGFX_BROADWELL>> populateBDW;

} // namespace xe
