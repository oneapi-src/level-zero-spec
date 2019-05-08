#pragma once
#include "cmdlist.h"
#include "hw_info.h"
#include "runtime/command_stream/linear_stream.h"

namespace L0 {

template <GFXCORE_FAMILY gfxCoreFamily> struct EncodeFlush {
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using PIPE_CONTROL = typename GfxFamily::PIPE_CONTROL;
    using POST_SYNC_OPERATION = typename PIPE_CONTROL::POST_SYNC_OPERATION;

    static const size_t size = sizeof(PIPE_CONTROL);
    static void encode(CommandContainer &container) {
        PIPE_CONTROL cmd = GfxFamily::cmdInitPipeControl;
        cmd.setCommandStreamerStallEnable(true);
        cmd.setDcFlushEnable(true);
        auto buffer = container.getCommandStream().getSpace(sizeof(cmd));
        *(PIPE_CONTROL *)buffer = cmd;
    }

    static void encodeWithQwordWrite(CommandContainer &container, uint64_t gpuAddress,
                                     uint64_t value) {
        PIPE_CONTROL cmd = GfxFamily::cmdInitPipeControl;
        cmd.setPostSyncOperation(POST_SYNC_OPERATION::POST_SYNC_OPERATION_WRITE_IMMEDIATE_DATA);
        cmd.setImmediateData(value);
        cmd.setCommandStreamerStallEnable(true);
        cmd.setDcFlushEnable(true);
        cmd.setAddressHigh(gpuAddress >> 32u);
        cmd.setAddress(uint32_t(gpuAddress));

        auto buffer = container.getCommandStream().getSpace(sizeof(cmd));
        *(PIPE_CONTROL *)buffer = cmd;
    }
};

} // namespace L0
