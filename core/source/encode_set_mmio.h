#pragma once
#include "cmdlist.h"
#include "hw_info.h"
#include "runtime/command_stream/linear_stream.h"

namespace L0 {

template <GFXCORE_FAMILY gfxCoreFamily>
struct EncodeSetMMIO {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using MI_LOAD_REGISTER_IMM = typename GfxFamily::MI_LOAD_REGISTER_IMM;

    static const size_t size = sizeof(MI_LOAD_REGISTER_IMM);

    static void append(CommandContainer &container, uint32_t offset, uint32_t data) {
        MI_LOAD_REGISTER_IMM cmd = GfxFamily::cmdInitLoadRegisterImm;
        cmd.setRegisterOffset(offset);
        cmd.setDataDword(data);
        auto buffer = container.getCommandStream().getSpace(sizeof(cmd));
        *(MI_LOAD_REGISTER_IMM *)buffer = cmd;
    }
};

} // namespace L0
