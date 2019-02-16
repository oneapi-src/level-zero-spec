#include "cmdlist_hw.h"
#include "event.h"
#include "graphics_allocation.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/helpers/hw_info.h"
#include <cassert>

namespace xe {

template <uint32_t gfxCoreFamily>
bool CommandListHw<gfxCoreFamily>::initialize() {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(gfxCoreFamily)>::GfxFamily;

    if (!BaseClass::initialize()) {
        return false;
    }

    using STATE_BASE_ADDRESS = typename GfxFamily::STATE_BASE_ADDRESS;
    STATE_BASE_ADDRESS cmd = GfxFamily::cmdInitStateBaseAddress;

    {
        auto allocationHeap = this->allocationIndirectHeaps[INSTRUCTION];
        assert(allocationHeap != nullptr);
        cmd.setInstructionBaseAddressModifyEnable(true);
        cmd.setInstructionBaseAddress(allocationHeap->getGpuAddress());
    }

    {
        auto allocationHeap = this->allocationIndirectHeaps[GENERAL_STATE];
        assert(allocationHeap != nullptr);
        cmd.setGeneralStateBaseAddressModifyEnable(true);
        cmd.setGeneralStateBaseAddress(allocationHeap->getGpuAddress());
    }

    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(STATE_BASE_ADDRESS *)buffer = cmd;

    return true;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::close() {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(gfxCoreFamily)>::GfxFamily;
    using MI_BATCH_BUFFER_END = typename GfxFamily::MI_BATCH_BUFFER_END;
    MI_BATCH_BUFFER_END cmd = GfxFamily::cmdInitBatchBufferEnd;
    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(MI_BATCH_BUFFER_END *)buffer = cmd;

    return XE_RESULT_SUCCESS;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeDispatchFunction(xe_function_handle_t hFunction,
                                                                 xe_function_args_handle_t hFunctionArgs,
                                                                 xe_dispatch_function_arguments_t *pDispatchFuncArgs,
                                                                 xe_event_handle_t hEvent) {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(gfxCoreFamily)>::GfxFamily;

    return XE_RESULT_SUCCESS;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeSignalEvent(xe_event_handle_t hEvent) {
    auto event = Event::fromHandle(hEvent);
    assert(event);
    residencyContainer.push_back(event->getAllocation().allocationRT);

    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(gfxCoreFamily)>::GfxFamily;
    using PIPE_CONTROL = typename GfxFamily::PIPE_CONTROL;
    using POST_SYNC_OPERATION = typename PIPE_CONTROL::POST_SYNC_OPERATION;
    PIPE_CONTROL cmd = GfxFamily::cmdInitPipeControl;
    cmd.setPostSyncOperation(POST_SYNC_OPERATION::POST_SYNC_OPERATION_WRITE_IMMEDIATE_DATA);
    cmd.setImmediateData(0u);
    cmd.setCommandStreamerStallEnable(true);
    auto gpuAddress = event->getGpuAddress();
    cmd.setAddressHigh(gpuAddress >> 32u);
    cmd.setAddress(uint32_t(gpuAddress));

    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(PIPE_CONTROL *)buffer = cmd;
    return XE_RESULT_SUCCESS;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListHw<gfxCoreFamily>::encodeWaitOnEvent(xe_event_handle_t hEvent) {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(gfxCoreFamily)>::GfxFamily;
    using MI_SEMAPHORE_WAIT = typename GfxFamily::MI_SEMAPHORE_WAIT;
    MI_SEMAPHORE_WAIT cmd = GfxFamily::cmdInitMiSemaphoreWait;
    auto event = Event::fromHandle(hEvent);
    assert(event);
    residencyContainer.push_back(event->getAllocation().allocationRT);

    cmd.setSemaphoreGraphicsAddress(event->getGpuAddress());
    cmd.setSemaphoreDataDword(1u);
    cmd.setCompareOperation(MI_SEMAPHORE_WAIT::COMPARE_OPERATION::COMPARE_OPERATION_SAD_NOT_EQUAL_SDD);

    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(MI_SEMAPHORE_WAIT *)buffer = cmd;
    return XE_RESULT_SUCCESS;
}

} // namespace xe
