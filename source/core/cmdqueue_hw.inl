#include "cmdlist.h"
#include "cmdqueue_hw.h"
#include "fence.h"
#include "graphics_allocation.h"
#include "runtime/command_stream/command_stream_receiver.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/helpers/hw_info.h"
#include <cassert>

namespace L0 {

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandQueueHw<gfxCoreFamily>::createFence(const xe_fence_desc_t *desc,
                                                       xe_fence_handle_t *phFence) {
    *phFence = Fence::create(this, desc);
    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily> xe_result_t CommandQueueHw<gfxCoreFamily>::destroy() {
    delete this;
    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandQueueHw<gfxCoreFamily>::executeCommandLists(
    uint32_t numCommandLists, xe_command_list_handle_t *phCommandLists, xe_fence_handle_t hFence) {
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using MI_BATCH_BUFFER_START = typename GfxFamily::MI_BATCH_BUFFER_START;
    using MI_BATCH_BUFFER_END = typename GfxFamily::MI_BATCH_BUFFER_END;
    using PIPE_CONTROL = typename GfxFamily::PIPE_CONTROL;
    using POST_SYNC_OPERATION = typename PIPE_CONTROL::POST_SYNC_OPERATION;

    size_t sizeEstimate =
        sizeof(MI_BATCH_BUFFER_END) +
        sizeof(PIPE_CONTROL) + sizeof(POST_SYNC_OPERATION) +
        numCommandLists * sizeof(MI_BATCH_BUFFER_START);
    Substream substream = getCmdSubstream(sizeEstimate);

    NEO::ResidencyContainer residencyContainer;

    // padding if we need for a fence signal
    if (hFence) {
        residencyContainer.reserve((16 * numCommandLists) + 2);
    } else {
        residencyContainer.reserve(16 * numCommandLists);
    }

    for (auto i = 0u; i < numCommandLists; ++i) {
        MI_BATCH_BUFFER_START cmd = GfxFamily::cmdInitBatchBufferStart;
        cmd.setSecondLevelBatchBuffer(
            MI_BATCH_BUFFER_START::SECOND_LEVEL_BATCH_BUFFER_SECOND_LEVEL_BATCH);
        cmd.setAddressSpaceIndicator(MI_BATCH_BUFFER_START::ADDRESS_SPACE_INDICATOR_PPGTT);

        auto commandList = CommandList::fromHandle(phCommandLists[i]);
        auto &allocation = commandList->getAllocation();
        cmd.setBatchBufferStartAddressGraphicsaddress472(allocation.getGpuAddress());

        auto buffer = substream.getSpaceForCmd<MI_BATCH_BUFFER_START>();
        *(MI_BATCH_BUFFER_START *)buffer = cmd;

        // Add each
        printfFunctionContainer.insert(printfFunctionContainer.end(),
                                       commandList->getPrintfFunctionContainer().begin(),
                                       commandList->getPrintfFunctionContainer().end());

        for (auto alloc : commandList->getResidencyContainer()) {
            if (residencyContainer.end() ==
                std::find(residencyContainer.begin(), residencyContainer.end(), alloc)) {
                residencyContainer.push_back(alloc);
            }
        }
    }

    // If validfence handle provided, append a flush with memory write
    if (hFence) {
        auto fence = Fence::fromHandle(hFence);
        assert(fence);

        PIPE_CONTROL cmd = GfxFamily::cmdInitPipeControl;
        uint64_t gpuAddress = fence->getGpuAddress();

        cmd.setPostSyncOperation(POST_SYNC_OPERATION::POST_SYNC_OPERATION_WRITE_IMMEDIATE_DATA);
        cmd.setImmediateData(Fence::STATE_SIGNALED);
        cmd.setCommandStreamerStallEnable(true);
        cmd.setDcFlushEnable(true);
        cmd.setAddressHigh(gpuAddress >> 32u);
        cmd.setAddress(uint32_t(gpuAddress));

        auto buffer = substream.getSpaceForCmd<PIPE_CONTROL>();
        *(PIPE_CONTROL *)buffer = cmd;

        auto fenceAlloc = &fence->getAllocation();
        if (residencyContainer.end() == std::find(residencyContainer.begin(),
                                                  residencyContainer.end(),
                                                  fenceAlloc->allocationRT)) {
            residencyContainer.push_back(fenceAlloc->allocationRT);
        }

        fence->enqueueState = Fence::ENQUEUE_READY;
    }

    {
        MI_BATCH_BUFFER_END cmd = GfxFamily::cmdInitBatchBufferEnd;

        auto buffer = substream.getSpaceForCmd<MI_BATCH_BUFFER_END>();
        *(MI_BATCH_BUFFER_END *)buffer = cmd;
    }

    auto commandStreamReceiver = static_cast<NEO::CommandStreamReceiver *>(csrRT);
    commandStreamReceiver->processResidency(residencyContainer);

    // Submit our batch buffer
    submitBatchBuffer(substream.getBaseOffsetInParent());

    // TODO: Enable unified memory.  For now, imply everything gets made consistent
    for (auto i = 0u; i < numCommandLists; ++i) {
        auto commandList = CommandList::fromHandle(phCommandLists[i]);
        processCoherency(commandList);
    }

    return XE_RESULT_SUCCESS;
}

// FIXME: Remove direct access to taskCount.
// Needed below
struct CommandStreamReceiver : public NEO::CommandStreamReceiver {
    using NEO::CommandStreamReceiver::latestFlushedTaskCount;
    using NEO::CommandStreamReceiver::taskCount;
};

template <GFXCORE_FAMILY gfxCoreFamily>
void CommandQueueHw<gfxCoreFamily>::dispatchTaskCountWrite(bool flushDataCache) {
    auto commandStreamReceiver = static_cast<CommandStreamReceiver *>(csrRT);
    assert(commandStreamReceiver);
    auto taskCountToWrite = commandStreamReceiver->peekTaskCount();

    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;

    using PIPELINE_SELECT = typename GfxFamily::PIPELINE_SELECT;
    using PIPE_CONTROL = typename GfxFamily::PIPE_CONTROL;
    using POST_SYNC_OPERATION = typename PIPE_CONTROL::POST_SYNC_OPERATION;
    using MI_BATCH_BUFFER_END = typename GfxFamily::MI_BATCH_BUFFER_END;

    size_t sizeEstimate = sizeof(PIPELINE_SELECT) + sizeof(PIPE_CONTROL) + sizeof(PIPE_CONTROL) +
                          sizeof(MI_BATCH_BUFFER_END);
    Substream substream = getCmdSubstream(sizeEstimate);

    PIPELINE_SELECT ps = GfxFamily::cmdInitPipelineSelect;
    ps.setPipelineSelection(PIPELINE_SELECT::PIPELINE_SELECTION_GPGPU);
    ps.setMaskBits(3u); // TODO:  Add support for DOP clock gating

    *substream.getSpaceForCmd<PIPELINE_SELECT>() = ps;

    {
        // Add a PIPE_CONTROL w/ CS_stall per Bspec, require prior to any PostSync Operation
        // without this PipeControl may leave to early and cause too early resource destruction
        // which may lead to BSODs Note : this is SKL-specific
        PIPE_CONTROL pc0 = GfxFamily::cmdInitPipeControl;
        pc0.setDcFlushEnable(flushDataCache);
        pc0.setCommandStreamerStallEnable(true);
        *substream.getSpaceForCmd<PIPE_CONTROL>() = pc0;
    }

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
    commandStreamReceiver->waitForTaskCountWithKmdNotifyFallback(0, 0, false, false);
    return;
}

} // namespace L0
