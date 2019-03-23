#include "runtime/gen9/hw_cmds.h"
#include "runtime/gen9/hw_info.h"
#include "cmdlist_hw.inl"
#include "encode_l3state.h"
#include "igfxfmid.h"

namespace L0 {

template <>
struct CommandListProductFamily<IGFX_SKYLAKE> : public CommandListCoreFamily<IGFX_GEN9_CORE> {
    using CommandListCoreFamily::CommandListCoreFamily;

    void programL3(bool isSLMused) override {
        EncodeL3State<IGFX_SKYLAKE>::encode(*this, isSLMused);
    }
};

static CommandListPopulateFactory<IGFX_SKYLAKE, CommandListProductFamily<IGFX_SKYLAKE>> populateSKL;

} // namespace L0
