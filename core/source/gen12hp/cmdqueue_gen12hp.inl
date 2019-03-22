
#include "cmdqueue_hw.inl"
#include "runtime/gen12hp/hw_cmds.h"
#include "runtime/gen12hp/hw_info.h"
#include "igfxfmid.h"

namespace L0 {

template <>
void CommandQueueHw<IGFX_GEN12_CORE>::dispatchTaskCountWrite(bool flushDataCache) {
    constexpr auto gfxCoreFamily = IGFX_GEN12_CORE;
    auto commandStreamReceiver = static_cast<OCLRT::CommandStreamReceiver *>(csrRT);
    assert(commandStreamReceiver);
    auto taskCountToWrite = commandStreamReceiver->peekTaskCount();

    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;

    using PIPELINE_SELECT = typename GfxFamily::PIPELINE_SELECT;
    using PIPE_CONTROL = typename GfxFamily::PIPE_CONTROL;
    using POST_SYNC_OPERATION = typename PIPE_CONTROL::POST_SYNC_OPERATION;
    using MI_BATCH_BUFFER_END = typename GfxFamily::MI_BATCH_BUFFER_END;

    PIPELINE_SELECT ps = GfxFamily::cmdInitPipelineSelect;
    ps.setPipelineSelection(PIPELINE_SELECT::PIPELINE_SELECTION_GPGPU);
    ps.setMaskBits(3u); //TODO:  Add support for DOP clock gating

    PIPE_CONTROL pc = GfxFamily::cmdInitPipeControl;
    pc.setPostSyncOperation(POST_SYNC_OPERATION::POST_SYNC_OPERATION_WRITE_IMMEDIATE_DATA);
    pc.setImmediateData(taskCountToWrite);
    pc.setCommandStreamerStallEnable(true);
    pc.setDcFlushEnable(flushDataCache);
    auto gpuAddress = static_cast<uint64_t>(commandStreamReceiver->getTagAllocation()->getGpuAddress());
    pc.setAddressHigh(gpuAddress >> 32u);
    pc.setAddress(uint32_t(gpuAddress));

    MI_BATCH_BUFFER_END cmdEnd = GfxFamily::cmdInitBatchBufferEnd;

    auto bufferBase = commandStream->getSpace(sizeof(ps) + sizeof(pc) + sizeof(cmdEnd));
    auto cmd = bufferBase;

    *(PIPELINE_SELECT *)cmd = ps;
    cmd = ptrOffset(cmd, sizeof(ps));
    *(PIPE_CONTROL *)cmd = pc;
    cmd = ptrOffset(cmd, sizeof(pc));
    *(MI_BATCH_BUFFER_END *)cmd = cmdEnd;

    OCLRT::BatchBuffer batchBuffer(
        allocation->allocationRT,
        ptrDiff(bufferBase, commandStream->getCpuBase()),
        0u,
        nullptr,
        false,
        false,
        OCLRT::QueueThrottle::HIGH,
        commandStream->getUsed(),
        commandStream);
    OCLRT::ResidencyContainer residencyContainer;
    residencyContainer.push_back(commandStreamReceiver->getTagAllocation());
    commandStreamReceiver->flush(batchBuffer, residencyContainer);
    commandStreamReceiver->makeCoherent(*commandStreamReceiver->getTagAllocation());
    return;
}

} // namespace L0
