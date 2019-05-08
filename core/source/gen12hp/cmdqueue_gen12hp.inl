
#include "cmdqueue_hw.inl"
#include "runtime/gen12hp/hw_cmds.h"
#include "runtime/gen12hp/hw_info.h"
#include "igfxfmid.h"

namespace L0 {

template <> void CommandQueueHw<IGFX_GEN12_CORE>::dispatchTaskCountWrite(bool flushDataCache) {
    constexpr auto gfxCoreFamily = IGFX_GEN12_CORE;
    auto commandStreamReceiver = static_cast<CommandStreamReceiver *>(csrRT);
    assert(commandStreamReceiver);
    auto taskCountToWrite = commandStreamReceiver->peekTaskCount();

    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;

    using PIPELINE_SELECT = typename GfxFamily::PIPELINE_SELECT;
    using PIPE_CONTROL = typename GfxFamily::PIPE_CONTROL;
    using POST_SYNC_OPERATION = typename PIPE_CONTROL::POST_SYNC_OPERATION;
    using MI_BATCH_BUFFER_END = typename GfxFamily::MI_BATCH_BUFFER_END;

    size_t sizeEstimate =
        sizeof(PIPELINE_SELECT) + sizeof(PIPE_CONTROL) + sizeof(MI_BATCH_BUFFER_END);
    Substream substream = getCmdSubstream(sizeEstimate);

    PIPELINE_SELECT ps = GfxFamily::cmdInitPipelineSelect;
    ps.setPipelineSelection(PIPELINE_SELECT::PIPELINE_SELECTION_GPGPU);
    ps.setMaskBits(3u); // TODO:  Add support for DOP clock gating

    PIPE_CONTROL pc = GfxFamily::cmdInitPipeControl;
    pc.setPostSyncOperation(POST_SYNC_OPERATION::POST_SYNC_OPERATION_WRITE_IMMEDIATE_DATA);
    pc.setImmediateData(taskCountToWrite);
    pc.setCommandStreamerStallEnable(true);
    pc.setDcFlushEnable(flushDataCache);
    auto gpuAddress =
        static_cast<uint64_t>(commandStreamReceiver->getTagAllocation()->getGpuAddress());
    pc.setAddressHigh(gpuAddress >> 32u);
    pc.setAddress(uint32_t(gpuAddress));

    MI_BATCH_BUFFER_END cmdEnd = GfxFamily::cmdInitBatchBufferEnd;

    *substream.getSpaceForCmd<PIPELINE_SELECT>() = ps;
    *substream.getSpaceForCmd<PIPE_CONTROL>() = pc;
    *substream.getSpaceForCmd<MI_BATCH_BUFFER_END>() = cmdEnd;

    NEO::BatchBuffer batchBuffer(allocation->allocationRT, substream.getBaseOffsetInParent(), 0u,
                                 nullptr, false, false, NEO::QueueThrottle::HIGH,
                                 substream.getParent().getUsed(), &substream.getParent());
    NEO::ResidencyContainer residencyContainer;
    residencyContainer.push_back(commandStreamReceiver->getTagAllocation());
    commandStreamReceiver->latestFlushedTaskCount = taskCountToWrite;
    commandStreamReceiver->setLatestSentTaskCount(taskCountToWrite);
    commandStreamReceiver->flush(batchBuffer, residencyContainer);
    commandStreamReceiver->makeSurfacePackNonResident(residencyContainer);
    commandStreamReceiver->makeCoherent(*commandStreamReceiver->getTagAllocation());
    return;
}

} // namespace L0
