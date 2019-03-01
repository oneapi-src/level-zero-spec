#include "cmdlist_hw.h"
#include "event.h"
#include "graphics_allocation.h"
#include "module.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/helpers/hw_info.h"
#include "runtime/indirect_heap/indirect_heap.h"
#include <cassert>

namespace L0 {

template <uint32_t gfxCoreFamily>
bool CommandListCoreFamily<gfxCoreFamily>::initialize() {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(gfxCoreFamily)>::GfxFamily;

    if (!BaseClass::initialize()) {
        return false;
    }

    {
        using STATE_BASE_ADDRESS = typename GfxFamily::STATE_BASE_ADDRESS;
        STATE_BASE_ADDRESS cmd = GfxFamily::cmdInitStateBaseAddress;

        {
            auto heap = this->indirectHeaps[INSTRUCTION];
            assert(heap != nullptr);
            cmd.setInstructionBaseAddressModifyEnable(true);
            cmd.setInstructionBaseAddress(heap->getHeapGpuBase());
            cmd.setInstructionBufferSizeModifyEnable(true);
            cmd.setInstructionBufferSize(static_cast<uint32_t>(heap->getMaxAvailableSpace()));
        }

        {
            auto heap = this->indirectHeaps[GENERAL_STATE];
            assert(heap != nullptr);
            cmd.setGeneralStateBaseAddressModifyEnable(true);
            cmd.setGeneralStateBaseAddress(heap->getHeapGpuBase());
            cmd.setGeneralStateBufferSizeModifyEnable(true);
            cmd.setGeneralStateBufferSize(static_cast<uint32_t>(heap->getMaxAvailableSpace()));
        }

        auto buffer = commandStream->getSpace(sizeof(cmd));
        *(STATE_BASE_ADDRESS *)buffer = cmd;
    }

    return true;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::close() {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(gfxCoreFamily)>::GfxFamily;
    using MI_BATCH_BUFFER_END = typename GfxFamily::MI_BATCH_BUFFER_END;
    MI_BATCH_BUFFER_END cmd = GfxFamily::cmdInitBatchBufferEnd;
    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(MI_BATCH_BUFFER_END *)buffer = cmd;

    return XE_RESULT_SUCCESS;
}

template <uint32_t gfxCoreFamily>
void CommandListCoreFamily<gfxCoreFamily>::programL3() {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(gfxCoreFamily)>::GfxFamily;
    {
        using PIPE_CONTROL = typename GfxFamily::PIPE_CONTROL;
        PIPE_CONTROL cmd = GfxFamily::cmdInitPipeControl;
        cmd.setCommandStreamerStallEnable(true);
        cmd.setDcFlushEnable(true);
        auto buffer = commandStream->getSpace(sizeof(cmd));
        *(PIPE_CONTROL *)buffer = cmd;
    }

    {
        using MI_LOAD_REGISTER_IMM = typename GfxFamily::MI_LOAD_REGISTER_IMM;
        MI_LOAD_REGISTER_IMM cmd = GfxFamily::cmdInitLoadRegisterImm;
        uint32_t offsetL3CNTL = 0x7013u;
        uint32_t dataL3CNTL = 0x80000140u;
        cmd.setRegisterOffset(offsetL3CNTL);
        cmd.setDataDword(dataL3CNTL);
        auto buffer = commandStream->getSpace(sizeof(cmd));
        *(MI_LOAD_REGISTER_IMM *)buffer = cmd;
    }
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeCommandLists(uint32_t numCommandLists,
                                                                     xe_command_list_handle_t *phCommandLists) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeCommands(xe_command_format_t format,
                                                                 size_t size,
                                                                 void *pBlob) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeDispatchFunction(xe_function_handle_t hFunction,
                                                                         const xe_dispatch_function_arguments_t *pDispatchFuncArgs,
                                                                         xe_event_handle_t hEvent) {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(gfxCoreFamily)>::GfxFamily;
    using GPGPU_WALKER = typename GfxFamily::GPGPU_WALKER;
    using MEDIA_INTERFACE_DESCRIPTOR_LOAD = typename GfxFamily::MEDIA_INTERFACE_DESCRIPTOR_LOAD;
    using INTERFACE_DESCRIPTOR_DATA = typename GfxFamily::INTERFACE_DESCRIPTOR_DATA;

    // For now program L3 here.
    programL3();

    const auto function = Function::fromHandle(hFunction);
    assert(function);

    // Copy the kernel to indirect heap
    // TODO: Allocate kernel in graphics memory to avoid the CPU copy
    uint64_t kernelStartPointer = 0u;
    {
        auto sizeISA = function->getIsaSize();
        auto ptrISA = function->getIsaHostMem();

        auto heap = this->indirectHeaps[INSTRUCTION];
        assert(heap);

        auto ptr = heap->getSpace(sizeISA);
        assert(ptr);
        memcpy(ptr, ptrISA, sizeISA);

        kernelStartPointer = ptrDiff(ptr, heap->getHeapGpuBase());
    }

    uint32_t offsetIDD = 0u;
    auto sizeCrossThreadData = static_cast<uint32_t>(function->getCrossThreadDataSize());
    auto sizePerThreadData = static_cast<uint32_t>(function->getPerThreadDataSize());
    {
        auto heap = indirectHeaps[OCLRT::IndirectHeap::DYNAMIC_STATE];
        assert(heap);

        auto sizeIDD = sizeof(INTERFACE_DESCRIPTOR_DATA);
        auto ptr = heap->getSpace(sizeIDD);
        assert(ptr);
        auto offset = ptrDiff(ptr, heap->getCpuBase());
        assert(offset + sizeIDD <= heap->getMaxAvailableSpace());

        INTERFACE_DESCRIPTOR_DATA idd = GfxFamily::cmdInitInterfaceDescriptorData;

        idd.setKernelStartPointerHigh(static_cast<uint32_t>(kernelStartPointer >> 32u));
        idd.setKernelStartPointer(static_cast<uint32_t>(kernelStartPointer));
        idd.setNumberOfThreadsInGpgpuThreadGroup(function->getThreadsPerThreadGroup());

        auto numGrfCrossThreadData = static_cast<uint32_t>(sizeCrossThreadData / sizeof(float[8]));
        assert(numGrfCrossThreadData > 0u);
        idd.setCrossThreadConstantDataReadLength(numGrfCrossThreadData);

        auto numGrfPerThreadData = static_cast<uint32_t>(sizePerThreadData / sizeof(float[8]));
        assert(numGrfPerThreadData > 0u);
        idd.setConstantIndirectUrbEntryReadLength(numGrfPerThreadData);

        memcpy(ptr, &idd, sizeof(idd));

        MEDIA_INTERFACE_DESCRIPTOR_LOAD cmd = GfxFamily::cmdInitMediaInterfaceDescriptorLoad; 
        cmd.setInterfaceDescriptorDataStartAddress(offsetIDD);
        cmd.setInterfaceDescriptorTotalLength(sizeof(INTERFACE_DESCRIPTOR_DATA));

        auto buffer = commandStream->getSpace(sizeof(cmd));
        *(decltype(cmd) *)buffer = cmd;
    }

    GPGPU_WALKER cmd = GfxFamily::cmdInitGpgpuWalker;

    // Copy the threadData to the indirect heap
    {
        auto heap = indirectHeaps[INDIRECT_OBJECT];
        assert(heap);

        auto sizeThreadData = sizePerThreadData + sizeCrossThreadData;
        assert((sizeCrossThreadData % GPGPU_WALKER::INDIRECTDATASTARTADDRESS_ALIGN_SIZE) == 0u);
        assert((sizePerThreadData % GPGPU_WALKER::INDIRECTDATASTARTADDRESS_ALIGN_SIZE) == 0u);
        assert((sizeThreadData % GPGPU_WALKER::INDIRECTDATASTARTADDRESS_ALIGN_SIZE) == 0u);

        auto ptr = heap->getSpace(sizeThreadData);
        assert(ptr);
        auto offset = ptrDiff(ptr, heap->getCpuBase());
        assert(offset + sizeThreadData <= heap->getMaxAvailableSpace());

        memcpy(ptr, function->getCrossThreadDataHostMem(), sizeCrossThreadData);
        ptr = ptrOffset(ptr, sizeCrossThreadData);
        memcpy(ptr, function->getPerThreadDataHostMem(), sizePerThreadData);
        ptr = ptrOffset(ptr, sizePerThreadData);

        cmd.setIndirectDataLength(sizeThreadData);
        cmd.setIndirectDataStartAddress(static_cast<uint32_t>(offset));
    }

    // Set # of threadgroups in each dimension
    assert(pDispatchFuncArgs);
    assert(pDispatchFuncArgs->version == XE_DISPATCH_FUNCTION_ARGS_VERSION);
    cmd.setThreadGroupIdXDimension(pDispatchFuncArgs->groupCountX);
    cmd.setThreadGroupIdYDimension(pDispatchFuncArgs->groupCountY);
    cmd.setThreadGroupIdZDimension(pDispatchFuncArgs->groupCountZ);

    // Set simd size
    auto simdSize = function->getSimdSize();
    auto simdSizeOp =
        GPGPU_WALKER::SIMD_SIZE_SIMD32 * (simdSize == 32) |
        GPGPU_WALKER::SIMD_SIZE_SIMD16 * (simdSize == 16) |
        GPGPU_WALKER::SIMD_SIZE_SIMD8 * (simdSize == 8);
    cmd.setSimdSize(static_cast<typename GPGPU_WALKER::SIMD_SIZE>(simdSizeOp));
    cmd.setRightExecutionMask(function->getThreadExecutionMask());
    cmd.setBottomExecutionMask(0xffffffff);

    // Commit our command to the commandStream
    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(decltype(cmd) *)buffer = cmd;

    return XE_RESULT_SUCCESS;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeDispatchFunctionIndirect(xe_function_handle_t hFunction,
                                                                                 const xe_dispatch_function_indirect_arguments_t *pDispatchArgumentsBuffer,
                                                                                 xe_event_handle_t hEvent) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeDispatchHostFunction(xe_host_pfn_t pfnHostFunc,
                                                                             void *pUserData) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeEventReset(xe_event_handle_t hEvent) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeExecutionBarrier() {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeImageCopyFromMemory(xe_image_handle_t hDstImage,
                                                                            xe_image_region_t *pDstRegion,
                                                                            void *srcptr) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeImageCopyToMemory(void *dstptr,
                                                                          xe_image_handle_t hSrcImage,
                                                                          xe_image_region_t *pSrcRegion) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeImageCopyRegion(xe_image_handle_t hDstImage,
                                                                        xe_image_region_t *pDstRegion,
                                                                        xe_image_handle_t hSrcImage,
                                                                        xe_image_region_t *pSrcRegion) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeImageCopy(xe_image_handle_t hDstImage,
                                                                  xe_image_handle_t hSrcImage) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeMemAdvise(xe_device_handle_t hDevice,
                                                                  const void *ptr,
                                                                  size_t size,
                                                                  xe_memory_advice_t advice) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeMemoryCopy(void *dstptr,
                                                                   const void *srcptr,
                                                                   size_t size) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeMemoryPrefetch(const void *ptr,
                                                                       size_t count) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeMemorySet(void *ptr,
                                                                  int value,
                                                                  size_t size) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeSemaphoreSignal(xe_semaphore_handle_t hSemaphore,
                                                                        xe_semaphore_value_t value) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeSemaphoreWait(xe_semaphore_handle_t hSemaphore,
                                                                      xe_semaphore_wait_operation_t operation,
                                                                      xe_semaphore_value_t value) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeSignalEvent(xe_event_handle_t hEvent) {
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
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeSignalMultipleEvents(uint32_t numEvents,
                                                                             xe_event_handle_t *phEvents) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeWaitOnEvent(xe_event_handle_t hEvent) {
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

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::encodeWaitOnMultipleEvents(uint32_t numEvents,
                                                                             xe_event_handle_t *phEvents) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::getParameter(xe_command_list_parameter_t parameter, uint32_t *value) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::reset() {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::resetParameters() {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <uint32_t gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::setParameter(xe_command_list_parameter_t parameter,
                                                               uint32_t value) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

} // namespace L0
