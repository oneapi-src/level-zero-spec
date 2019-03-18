#pragma once
#include "cmdlist.h"
#include "hw_info.h"
#include "runtime/command_stream/linear_stream.h"

namespace L0 {

template <GFXCORE_FAMILY gfxCoreFamily>
struct EncodeFlush {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using PIPE_CONTROL = typename GfxFamily::PIPE_CONTROL;

    static const size_t size = sizeof(PIPE_CONTROL);
    static void append(CommandContainer &container) {
        PIPE_CONTROL cmd = GfxFamily::cmdInitPipeControl;
        cmd.setCommandStreamerStallEnable(true);
        cmd.setDcFlushEnable(true);
        auto buffer = container.getCommandStream().getSpace(sizeof(cmd));
        *(PIPE_CONTROL *)buffer = cmd;
    }
};

} // namespace L0
