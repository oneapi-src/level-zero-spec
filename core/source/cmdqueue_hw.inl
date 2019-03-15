#include "cmdlist.h"
#include "cmdqueue_hw.h"
#include "graphics_allocation.h"
#include "runtime/command_stream/command_stream_receiver.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/helpers/hw_info.h"
#include <cassert>

namespace L0 {

template <uint32_t gfxCoreFamily>
xe_result_t CommandQueueHw<gfxCoreFamily>::createFence(const xe_fence_desc_t *desc,
                                                       xe_fence_handle_t *phFence) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandQueueHw<gfxCoreFamily>::destroy() {
    delete this;
    return XE_RESULT_SUCCESS;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandQueueHw<gfxCoreFamily>::enqueueCommandLists(uint32_t numCommandLists,
                                                               xe_command_list_handle_t *phCommandLists,
                                                               xe_fence_handle_t hFence) {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(gfxCoreFamily)>::GfxFamily;
    using MI_BATCH_BUFFER_START = typename GfxFamily::MI_BATCH_BUFFER_START;
    using MI_BATCH_BUFFER_END = typename GfxFamily::MI_BATCH_BUFFER_END;

    for (auto i = 0u; i < numCommandLists; ++i) {
        MI_BATCH_BUFFER_START cmd = GfxFamily::cmdInitBatchBufferStart;
        cmd.setSecondLevelBatchBuffer(MI_BATCH_BUFFER_START::SECOND_LEVEL_BATCH_BUFFER_SECOND_LEVEL_BATCH);
        cmd.setAddressSpaceIndicator(MI_BATCH_BUFFER_START::ADDRESS_SPACE_INDICATOR_PPGTT);

        auto commandList = CommandList::fromHandle(phCommandLists[i]);
        auto &allocation = commandList->getAllocation();
        cmd.setBatchBufferStartAddressGraphicsaddress472(allocation.getGpuAddress());

        auto buffer = commandStream->getSpace(sizeof(cmd));
        *(MI_BATCH_BUFFER_START *)buffer = cmd;

        // Add each
        processResidency(commandList);
    }

    {
        MI_BATCH_BUFFER_END cmd = GfxFamily::cmdInitBatchBufferEnd;

        auto buffer = commandStream->getSpace(sizeof(cmd));
        *(MI_BATCH_BUFFER_END *)buffer = cmd;
    }

    // Submit our batch buffer
    submitBatchBuffer();

    // TODO: Enable unified memory.  For now, imply everything gets made consistent
    for (auto i = 0u; i < numCommandLists; ++i) {
        auto commandList = CommandList::fromHandle(phCommandLists[i]);
        processCoherency(commandList);
    }

    return XE_RESULT_SUCCESS;
}

template <uint32_t gfxCoreFamily>
void CommandQueueHw<gfxCoreFamily>::dispatchTaskCountWrite(bool flushDataCache) {
    auto commandStreamReceiver = static_cast<OCLRT::CommandStreamReceiver *>(csrRT);
    assert(commandStreamReceiver);
    auto taskCountToWrite = commandStreamReceiver->peekTaskCount();

    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(gfxCoreFamily)>::GfxFamily;

    using PIPELINE_SELECT = typename GfxFamily::PIPELINE_SELECT;
    using PIPE_CONTROL = typename GfxFamily::PIPE_CONTROL;
    using POST_SYNC_OPERATION = typename PIPE_CONTROL::POST_SYNC_OPERATION;
    using MI_BATCH_BUFFER_END = typename GfxFamily::MI_BATCH_BUFFER_END;

    PIPELINE_SELECT ps = GfxFamily::cmdInitPipelineSelect;
    ps.setPipelineSelection(PIPELINE_SELECT::PIPELINE_SELECTION_GPGPU);

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
