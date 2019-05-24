#pragma once
#include "cmdqueue_imp.h"
#include "runtime/command_stream/tbx_command_stream_receiver_hw.h"
#include "runtime/memory_manager/graphics_allocation.h"
#include "runtime/memory_manager/page_table.h"
#include "runtime/memory_manager/memory_constants.h"
#include "runtime/command_stream/submissions_aggregator.h"
#include "runtime/command_stream/command_stream_receiver.h"
#include "igfxfmid.h"

namespace L0 {

template <GFXCORE_FAMILY gfxCoreFamily> struct CommandQueueHw : public CommandQueueImp {
    using CommandQueueImp::CommandQueueImp;

    xe_result_t createFence(const xe_fence_desc_t *desc, xe_fence_handle_t *phFence) override;
    xe_result_t destroy() override;
    xe_result_t executeCommandLists(uint32_t numCommandLists,
                                    xe_command_list_handle_t *phCommandLists,
                                    xe_fence_handle_t hFence) override;

    void dispatchTaskCountWrite(bool flushDataCache) override;

    void makeCoherent(NEO::GraphicsAllocation &gfxAllocation) override {
        int32_t csr = NEO::DebugManager.flags.SetCommandStreamReceiver.get();
        if (csr != CSR_TBX)
            return;

        using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
        auto tbxCsr = static_cast<NEO::TbxCommandStreamReceiverHw<GfxFamily> *>(csrRT);
        if (tbxCsr->hardwareContextController) {
            tbxCsr->hardwareContextController->readMemory(gfxAllocation.getGpuAddress(),
                    gfxAllocation.getUnderlyingBuffer(), gfxAllocation.getUnderlyingBufferSize(),
                        tbxCsr->getMemoryBank(&gfxAllocation), MemoryConstants::pageSize64k);
            return;
        }

        auto cpuAddress = gfxAllocation.getUnderlyingBuffer();
        auto gpuAddress = gfxAllocation.getGpuAddress();
        auto length = gfxAllocation.getUnderlyingBufferSize();

        if (length) {
            NEO::PageWalker walker = [&](uint64_t physAddress, size_t size,
                    size_t offset, uint64_t entryBits) {
                DEBUG_BREAK_IF(offset > length);
                tbxCsr->tbxStream.readMemory(physAddress, ptrOffset(cpuAddress, offset), size);
            };
            tbxCsr->ppgtt->pageWalk(static_cast<uintptr_t>(gpuAddress), length, 0, 0, walker,
                    tbxCsr->getMemoryBank(&gfxAllocation));
        }
    }

    bool flush(NEO::BatchBuffer &batchBuffer, NEO::ResidencyContainer &allocationsForResidency) override {
        int32_t csr = NEO::DebugManager.flags.SetCommandStreamReceiver.get();
        if (csr != CSR_TBX)
            return false;

        using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
        auto tbxCsr = static_cast<NEO::TbxCommandStreamReceiverHw<GfxFamily> *>(csrRT);

        if (!tbxCsr->hardwareContextController) {
            return false;
        }

        tbxCsr->initializeEngine();

        // Write our batch buffer
        auto pBatchBuffer = ptrOffset(batchBuffer.commandBufferAllocation->getUnderlyingBuffer(),
                batchBuffer.startOffset);
        auto batchBufferGpuAddress = ptrOffset(batchBuffer.commandBufferAllocation->getGpuAddress(),
                batchBuffer.startOffset);
        auto currentOffset = batchBuffer.usedSize;
        DEBUG_BREAK_IF(currentOffset < batchBuffer.startOffset);
        auto sizeBatchBuffer = currentOffset - batchBuffer.startOffset;

        // Write allocations for residency
        tbxCsr->processResidency(allocationsForResidency);

        for (auto &hardwareContext : tbxCsr->hardwareContextController->hardwareContexts) {
            hardwareContext->writeAndSubmitBatchBuffer(batchBufferGpuAddress, pBatchBuffer,
                    sizeBatchBuffer, tbxCsr->getMemoryBank(batchBuffer.commandBufferAllocation),
                        MemoryConstants::pageSize64k);
        }
        return true;
    }
};

} // namespace L0
