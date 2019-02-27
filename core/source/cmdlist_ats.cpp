#include "cmdlist_gen12hp.inl"

namespace L0 {

template <>
struct CommandListProductFamily<IGFX_TIGERLAKE_HP> : public CommandListCoreFamily<IGFX_GEN12_CORE> {
    using CommandListCoreFamily::CommandListCoreFamily;
};

static CommandListPopulateFactory<IGFX_TIGERLAKE_HP, CommandListProductFamily<IGFX_TIGERLAKE_HP>> populateTGLHP;

} // namespace L0
