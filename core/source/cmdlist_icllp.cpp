#include "runtime/gen11/hw_cmds.h"
#include "runtime/gen11/hw_info.h"
#include "cmdlist_hw.inl"
#include "igfxfmid.h"

namespace xe {

template <>
struct CommandListProductFamily<IGFX_ICELAKE_LP> : public CommandListCoreFamily<IGFX_GEN11_CORE> {
    using CommandListCoreFamily::CommandListCoreFamily;
};

static CommandListPopulateFactory<IGFX_ICELAKE_LP, CommandListProductFamily<IGFX_ICELAKE_LP>> populateICLLP;

} // namespace xe
