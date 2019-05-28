#include "cmdlist_hw.h"
#include "encode_flush.h"
#include "encode_state_base_address.h"
#include "event.h"
#include "graphics_allocation.h"
#include "image.h"
#include "memory_manager.h"
#include "module.h"
#include "builtins.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/command_stream/preemption.h"
#include "runtime/built_ins/built_ins.h"
#include "runtime/helpers/hw_info.h"
#include "runtime/helpers/kernel_commands.h"
#include "runtime/helpers/hw_helper.h"
#include "runtime/helpers/string.h"
#include "runtime/indirect_heap/indirect_heap.h"
#include <cassert>

namespace L0 {

template <GFXCORE_FAMILY gfxCoreFamily>
bool CommandListCoreFamily<gfxCoreFamily>::initialize(Device *device) {
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;

    if (!BaseClass::initialize(device)) {
        return false;
    }

    EncodeStateBaseAddress<gfxCoreFamily>::encode(*this);
    this->dirtyHeaps = 0u;

    enableGpgpu();
    programFrontEndState();
    programPreemption();

    return true;
}

template <GFXCORE_FAMILY gfxCoreFamily>
void *
CommandListCoreFamily<gfxCoreFamily>::getHeapSpaceAllowGrow(CommandContainer::HeapType heapType,
                                                            size_t size) {
    auto &indirectHeap = *indirectHeaps[heapType];

    if (indirectHeap.getAvailableSpace() < size) {
        // grow

        size_t newSize = indirectHeap.getUsed() + indirectHeap.getAvailableSpace();
        newSize *= 2; // grow by factor of 2
        newSize = std::max(newSize, indirectHeap.getAvailableSpace() + size);
        newSize = alignUp(newSize, 4096U);
        auto oldAlloc = this->allocationIndirectHeaps[heapType];
        auto newAlloc = globalMemoryManager->allocateDeviceMemory(device, newSize, 4096u);
        assert(oldAlloc);
        assert(newAlloc);
        indirectHeap.replaceGraphicsAllocation(newAlloc->allocationRT);
        indirectHeap.replaceBuffer(newAlloc->allocationRT->getUnderlyingBuffer(),
                                   newAlloc->allocationRT->getUnderlyingBufferSize());
        this->residencyContainer.push_back(newAlloc->allocationRT);
        this->deallocationContainer.push_back(oldAlloc);
        allocationIndirectHeaps[heapType] = newAlloc;
        this->dirtyHeaps |= 1u << heapType;
    }
    return indirectHeap.getSpace(size);
}

template <GFXCORE_FAMILY gfxCoreFamily> void CommandListCoreFamily<gfxCoreFamily>::enableGpgpu() {
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;

    using PIPELINE_SELECT = typename GfxFamily::PIPELINE_SELECT;
    PIPELINE_SELECT cmd = GfxFamily::cmdInitPipelineSelect;
    cmd.setPipelineSelection(PIPELINE_SELECT::PIPELINE_SELECTION_GPGPU);
    cmd.setMaskBits(3u); // TODO:  Add support for DOP clock gating

    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(PIPELINE_SELECT *)buffer = cmd;
}

template <GFXCORE_FAMILY gfxCoreFamily>
void CommandListCoreFamily<gfxCoreFamily>::programFrontEndState() {
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;

    using MEDIA_VFE_STATE = typename GfxFamily::MEDIA_VFE_STATE;
    MEDIA_VFE_STATE cmd = GfxFamily::cmdInitMediaVfeState;
    cmd.setNumberOfUrbEntries(1u);
    uint32_t urbEntryAllocationSize = 0x782; // TODO:  Gen family specific
    cmd.setUrbEntryAllocationSize(urbEntryAllocationSize);
    uint32_t maxNumThreads = this->device->getMaxNumHwThreads();
    cmd.setMaximumNumberOfThreads(maxNumThreads);

    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(MEDIA_VFE_STATE *)buffer = cmd;
}

template <GFXCORE_FAMILY gfxCoreFamily>
void CommandListCoreFamily<gfxCoreFamily>::programPreemption() {
    // TODO : Add support for midthread preemption
    // TODO : Reuse NEO's PreemptionHelper (requires refactoring because of linker problems)
    constexpr uint32_t mmioAddress = 0x2580;
    constexpr uint32_t maskVal = (1 << 1) | (1 << 2);
    constexpr uint32_t maskShift = 16;
    constexpr uint32_t mask = maskVal << maskShift;
    constexpr uint32_t threadGroupVal = (1 << 1);
    constexpr uint32_t regVal = threadGroupVal | mask;
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    NEO::LriHelper<GfxFamily>::program(commandStream, mmioAddress, regVal);
}

template <GFXCORE_FAMILY gfxCoreFamily> xe_result_t CommandListCoreFamily<gfxCoreFamily>::close() {
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using MI_BATCH_BUFFER_END = typename GfxFamily::MI_BATCH_BUFFER_END;
    MI_BATCH_BUFFER_END cmd = GfxFamily::cmdInitBatchBufferEnd;
    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(MI_BATCH_BUFFER_END *)buffer = cmd;

    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
void CommandListCoreFamily<gfxCoreFamily>::programL3(bool isSLMused) {}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t
CommandListCoreFamily<gfxCoreFamily>::appendCommandLists(uint32_t numCommandLists,
                                                         xe_command_list_handle_t *phCommandLists) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

// Returned binding table pointer is relative to given heap (which is assumed to be the Surface
// state base addess) as required by the INTERFACE_DESCRIPTOR_DATA.
template <GFXCORE_FAMILY gfxCoreFamily>
uint32_t CommandListCoreFamily<gfxCoreFamily>::copyBindingTableAndSurfaceStates(
    NEO::IndirectHeap *ssh, const void *srcSsh, uint32_t srcSshSize,
    uint32_t numberOfBindingTableStates, uint32_t offsetOfBindingTable) {
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using BINDING_TABLE_STATE = typename GfxFamily::BINDING_TABLE_STATE;
    using INTERFACE_DESCRIPTOR_DATA = typename GfxFamily::INTERFACE_DESCRIPTOR_DATA;

    assert(ssh);
    assert(srcSsh);
    assert(srcSshSize > offsetOfBindingTable);

    // Align the heap and allocate space for new ssh data
    ssh->align(BINDING_TABLE_STATE::SURFACESTATEPOINTER_ALIGN_SIZE);
    auto dstSurfaceState = ssh->getSpace(srcSshSize);

    // Compiler sends BTI table that is already populated with surface state pointers relative to
    // local SSH. We may need to patch these pointers so that they are relative to surface state
    // base address
    if (dstSurfaceState == ssh->getCpuBase()) {
        // nothing to patch, we're at the start of heap (which is assumed to be the surface state
        // base address) we need to simply copy the ssh (including BTIs from compiler)
        memcpy_s(dstSurfaceState, srcSshSize, srcSsh, srcSshSize);
        return offsetOfBindingTable;
    }

    // We can copy-over the surface states, but BTIs will need to be patched
    memcpy_s(dstSurfaceState, srcSshSize, srcSsh, offsetOfBindingTable);

    uint32_t surfaceStatesOffset =
        static_cast<uint32_t>(ptrDiff(dstSurfaceState, ssh->getCpuBase()));

    // march over BTIs and offset the pointers based on surface state base address
    auto *dstBindingTable =
        reinterpret_cast<BINDING_TABLE_STATE *>(ptrOffset(dstSurfaceState, offsetOfBindingTable));
    assert(reinterpret_cast<uintptr_t>(dstBindingTable) %
               INTERFACE_DESCRIPTOR_DATA::BINDINGTABLEPOINTER_ALIGN_SIZE ==
           0);

    auto *srcBindingTable =
        reinterpret_cast<const BINDING_TABLE_STATE *>(ptrOffset(srcSsh, offsetOfBindingTable));
    BINDING_TABLE_STATE bts = GfxFamily::cmdInitBindingTableState;

    for (uint32_t i = 0; i < numberOfBindingTableStates; ++i) {
        uint32_t localSurfaceStateOffset = srcBindingTable[i].getSurfaceStatePointer();
        uint32_t offsetedSurfaceStateOffset = localSurfaceStateOffset + surfaceStatesOffset;

        bts.setSurfaceStatePointer(offsetedSurfaceStateOffset);
        dstBindingTable[i] = bts;
        assert(bts.getRawData(0) % sizeof(BINDING_TABLE_STATE::SURFACESTATEPOINTER_ALIGN_SIZE) ==
               0);
    }

    return static_cast<uint32_t>(ptrDiff(dstBindingTable, ssh->getCpuBase()));
}

// Copy our sampler state if it exists
template <GFXCORE_FAMILY gfxCoreFamily>
uint32_t CommandListCoreFamily<gfxCoreFamily>::copySamplerState(NEO::IndirectHeap *dsh,
                                                                uint32_t samplerStateOffset,
                                                                uint32_t samplerCount,
                                                                uint32_t borderColorOffset,
                                                                const void *fnDynamicStateHeap) {
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using INTERFACE_DESCRIPTOR_DATA = typename GfxFamily::INTERFACE_DESCRIPTOR_DATA;
    using SAMPLER_STATE = typename GfxFamily::SAMPLER_STATE;

    assert(dsh);
    assert(fnDynamicStateHeap);

    auto sizeSamplerState = sizeof(SAMPLER_STATE) * samplerCount;
    auto borderColorSize = samplerStateOffset - borderColorOffset;

    dsh->align(alignIndirectStatePointer);
    auto borderColorOffsetInDsh = static_cast<uint32_t>(dsh->getUsed());

    auto borderColor = dsh->getSpace(borderColorSize);

    memcpy_s(borderColor, borderColorSize, ptrOffset(fnDynamicStateHeap, borderColorOffset),
             borderColorSize);

    dsh->align(INTERFACE_DESCRIPTOR_DATA::SAMPLERSTATEPOINTER_ALIGN_SIZE);
    auto samplerStateOffsetInDsh = static_cast<uint32_t>(dsh->getUsed());

    auto samplerState = dsh->getSpace(sizeSamplerState);

    memcpy_s(samplerState, sizeSamplerState, ptrOffset(fnDynamicStateHeap, samplerStateOffset),
             sizeSamplerState);

    auto pSmplr = reinterpret_cast<SAMPLER_STATE *>(samplerState);
    for (uint32_t i = 0; i < samplerCount; i++) {
        pSmplr[i].setIndirectStatePointer((uint32_t)borderColorOffsetInDsh);
    }

    return samplerStateOffsetInDsh;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendLaunchFunction(
    xe_function_handle_t hFunction, const xe_thread_group_dimensions_t *pThreadGroupDimensions,
    xe_event_handle_t hEvent, uint32_t numWaitEvents, xe_event_handle_t *phWaitEvents) {
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using GPGPU_WALKER = typename GfxFamily::GPGPU_WALKER;
    using MEDIA_STATE_FLUSH = typename GfxFamily::MEDIA_STATE_FLUSH;
    using MEDIA_INTERFACE_DESCRIPTOR_LOAD = typename GfxFamily::MEDIA_INTERFACE_DESCRIPTOR_LOAD;
    using INTERFACE_DESCRIPTOR_DATA = typename GfxFamily::INTERFACE_DESCRIPTOR_DATA;
    using STATE_BASE_ADDRESS = typename GfxFamily::STATE_BASE_ADDRESS;
    using SAMPLER_STATE = typename GfxFamily::SAMPLER_STATE;

    const auto function = Function::fromHandle(hFunction);
    assert(function);
    const auto functionImmutableData = function->getImmutableData();
    const auto &functionSignature = functionImmutableData->getSignature();
    auto sizeCrossThreadData = function->getCrossThreadDataSize();
    auto sizePerThreadData = function->getPerThreadDataSize();
    auto sizePerThreadDataForWholeGroup = function->getPerThreadDataSizeForWholeThreadGroup();

    GPGPU_WALKER cmd = GfxFamily::cmdInitGpgpuWalker;
    auto idd = GfxFamily::cmdInitInterfaceDescriptorData;

    // Point kernel start pointer to the proper offset of instruction heap
    {
        auto alloc = functionImmutableData->getIsaGraphicsAllocation();
        assert(nullptr != alloc);
        auto offset = alloc->getGpuAddressOffsetFromHeapBase();
        idd.setKernelStartPointer(offset);
        idd.setKernelStartPointerHigh(0u);
    }

    auto threadsPerThreadGroup = function->getThreadsPerThreadGroup();
    idd.setNumberOfThreadsInGpgpuThreadGroup(threadsPerThreadGroup);

    idd.setBarrierEnable(functionSignature.attributes.flags.hasBarriers);
    idd.setSharedLocalMemorySize(
        functionSignature.attributes.slmInlineSize > 0
            ? INTERFACE_DESCRIPTOR_DATA::SHARED_LOCAL_MEMORY_SIZE_ENCODES_64K
            : INTERFACE_DESCRIPTOR_DATA::SHARED_LOCAL_MEMORY_SIZE_ENCODES_0K);

    // Set up binding table and surface states
    {
        auto bindingTableStateCount = functionSignature.bindingTable.numSurfaceStates;
        uint32_t bindingTablePointer = 0u;

        if (bindingTableStateCount > 0u) {
            auto ssh = indirectHeaps[SURFACE_STATE];
            assert(ssh);
            bindingTablePointer = copyBindingTableAndSurfaceStates(
                ssh, function->getSurfaceStateHeapData().get(),
                function->getSurfaceStateHeapDataSize(), bindingTableStateCount,
                functionSignature.bindingTable.tableOffset);
        }

        idd.setBindingTablePointer(bindingTablePointer);

        auto bindingTableStatePrefetchCount = std::min(31u, 0u); // TODO: bindingTableStateCount
        idd.setBindingTableEntryCount(bindingTableStatePrefetchCount);
    }

    auto heap = indirectHeaps[DYNAMIC_STATE];
    assert(heap);

    uint32_t samplerStateOffset = 0;
    uint32_t samplerCount = 0;

    // Copy our sampler state if it exists
    if (functionSignature.samplerTable.numSamplers > 0) {
        samplerCount = functionSignature.samplerTable.numSamplers;
        samplerStateOffset = copySamplerState(heap, functionSignature.samplerTable.tableOffset,
                                              functionSignature.samplerTable.numSamplers,
                                              functionSignature.samplerTable.borderColor,
                                              function->getDynamicStateHeapData().get());
    }

    idd.setSamplerStatePointer(samplerStateOffset);
    auto samplerCountState =
        static_cast<typename INTERFACE_DESCRIPTOR_DATA::SAMPLER_COUNT>((samplerCount + 3) / 4);
    idd.setSamplerCount(samplerCountState);

    auto numGrfCrossThreadData = static_cast<uint32_t>(sizeCrossThreadData / sizeof(float[8]));
    assert(numGrfCrossThreadData > 0u);
    idd.setCrossThreadConstantDataReadLength(numGrfCrossThreadData);

    auto numGrfPerThreadData = static_cast<uint32_t>(sizePerThreadData / sizeof(float[8]));
    assert(numGrfPerThreadData > 0u);
    idd.setConstantIndirectUrbEntryReadLength(numGrfPerThreadData);

    // Copy the INTERFACE_DESCRIPTOR_DATA to indirect heap
    uint32_t numIDD = 0u;
    uint32_t offsetIDD = 0u;
    {
        heap->align(NEO::KernelCommandsHelper<GfxFamily>::alignInterfaceDescriptorData);

        auto sizeIDD = sizeof(INTERFACE_DESCRIPTOR_DATA);
        auto ptr = getHeapSpaceAllowGrow(DYNAMIC_STATE, sizeIDD);
        assert(ptr);
        offsetIDD = static_cast<uint32_t>(ptrDiff(ptr, heap->getCpuBase()));
        assert(offsetIDD + sizeIDD <= heap->getMaxAvailableSpace());
        assert(0 == offsetIDD % sizeof(INTERFACE_DESCRIPTOR_DATA));

        memcpy(ptr, &idd, sizeof(idd));
    }

    // Copy the threadData to the indirect heap
    uint32_t sizeThreadData = sizePerThreadDataForWholeGroup + sizeCrossThreadData;
    uint32_t offsetThreadData = 0u;
    {
        function->setGroupCount(pThreadGroupDimensions->groupCountX,
                                pThreadGroupDimensions->groupCountY,
                                pThreadGroupDimensions->groupCountZ);

        auto heap = indirectHeaps[INDIRECT_OBJECT];
        assert(heap);
        heap->align(GPGPU_WALKER::INDIRECTDATASTARTADDRESS_ALIGN_SIZE);

        auto ptr = getHeapSpaceAllowGrow(INDIRECT_OBJECT, sizeThreadData);
        assert(ptr);
        offsetThreadData = static_cast<uint32_t>(ptrDiff(ptr, heap->getCpuBase()));
        assert(offsetThreadData + sizeThreadData <= heap->getMaxAvailableSpace());

        memcpy(ptr, function->getCrossThreadData().get(), sizeCrossThreadData);
        ptr = ptrOffset(ptr, sizeCrossThreadData);
        memcpy(ptr, function->getPerThreadData().get(), sizePerThreadDataForWholeGroup);
    }

    // Update any non-pipelined state if it changes
    auto slmSizeNew = functionSignature.attributes.slmInlineSize;
    bool flush = this->slmSize != slmSizeNew || this->dirtyHeaps;

    if (flush) {
        EncodeFlush<gfxCoreFamily>::encode(*this);

        if (this->slmSize != slmSizeNew) {
            programL3(slmSizeNew != 0u);
            this->slmSize = slmSizeNew;
        }

        if (this->dirtyHeaps) {
            EncodeStateBaseAddress<gfxCoreFamily>::encode(*this);
            this->dirtyHeaps = 0u;
        }
    }

    {
        // A Media_State_Flush should be used before MEDIA_INTERFACE_DESCRIPTOR_LOAD to ensure that
        // the temporary Interface Descriptor storage is cleared.
        auto mediaStateFlush = commandStream->getSpace(sizeof(MEDIA_STATE_FLUSH));
        *reinterpret_cast<MEDIA_STATE_FLUSH *>(mediaStateFlush) = GfxFamily::cmdInitMediaStateFlush;

        MEDIA_INTERFACE_DESCRIPTOR_LOAD cmd = GfxFamily::cmdInitMediaInterfaceDescriptorLoad;
        cmd.setInterfaceDescriptorDataStartAddress(offsetIDD);
        cmd.setInterfaceDescriptorTotalLength(sizeof(INTERFACE_DESCRIPTOR_DATA));
        numIDD =
            0U; // change to IDD within MEDIA_INTERFACE_DESCRIPTOR_LOAD once we start grouping IDDs

        auto buffer = commandStream->getSpace(sizeof(cmd));
        *(decltype(cmd) *)buffer = cmd;
    }

    cmd.setIndirectDataStartAddress(offsetThreadData);
    cmd.setIndirectDataLength(sizeThreadData);
    cmd.setInterfaceDescriptorOffset(numIDD);

    // Set # of threadgroups in each dimension
    assert(pThreadGroupDimensions);
    cmd.setThreadGroupIdXDimension(pThreadGroupDimensions->groupCountX);
    cmd.setThreadGroupIdYDimension(pThreadGroupDimensions->groupCountY);
    cmd.setThreadGroupIdZDimension(pThreadGroupDimensions->groupCountZ);

    // Set simd size
    auto simdSize = functionSignature.attributes.simdSize;
    auto simdSizeOp = GPGPU_WALKER::SIMD_SIZE_SIMD32 * (simdSize == 32) |
                      GPGPU_WALKER::SIMD_SIZE_SIMD16 * (simdSize == 16) |
                      GPGPU_WALKER::SIMD_SIZE_SIMD8 * (simdSize == 8);
    cmd.setSimdSize(static_cast<typename GPGPU_WALKER::SIMD_SIZE>(simdSizeOp));

    // Set the last thread execution mask
    cmd.setRightExecutionMask(function->getThreadExecutionMask());
    cmd.setBottomExecutionMask(0xffffffff);
    cmd.setThreadWidthCounterMaximum(threadsPerThreadGroup);

    // Commit our command to the commandStream
    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(decltype(cmd) *)buffer = cmd;

    // If we are generating an event, append a flush w/ memory write
    if (hEvent) {
        auto event = Event::fromHandle(hEvent);
        assert(event);
        EncodeFlush<gfxCoreFamily>::encodeWithQwordWrite(*this, event->getGpuAddress(),
                                                         Event::STATE_SIGNALED);
        addToResidencyContainer(&event->getAllocation());
    }

    {
        // A MEDIA_STATE_FLUSH with no options must be added after a GPGPU_WALKER command which
        // doesn't use either SLM or barriers.
        auto mediaStateFlush = commandStream->getSpace(sizeof(MEDIA_STATE_FLUSH));
        *reinterpret_cast<MEDIA_STATE_FLUSH *>(mediaStateFlush) = GfxFamily::cmdInitMediaStateFlush;
    }

    // Attach Function residency to our CommandList residency
    {
        addToResidencyContainer(functionImmutableData->getIsaGraphicsAllocation().get());
        auto &residencyContainer = function->getResidencyContainer();
        for (auto resource : residencyContainer) {
            addToResidencyContainer(resource);
        }
    }

    // Store PrintfBuffer from a function
    {
        if (functionImmutableData->getSignature().attributes.flags.hasPrintf) {
            this->storePrintfFunction(function);
        }
    }

    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendLaunchFunctionIndirect(
    xe_function_handle_t hFunction, const xe_thread_group_dimensions_t *pDispatchArgumentsBuffer,
    xe_event_handle_t hEvent, uint32_t numWaitEvents, xe_event_handle_t *phWaitEvents) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t
CommandListCoreFamily<gfxCoreFamily>::appendLaunchHostFunction(xe_host_pfn_t pfnHostFunc,
                                                               void *pUserData) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendLaunchMultipleFunctionsIndirect(
    uint32_t numFunctions, const xe_function_handle_t *phFunctions,
    const size_t *pNumLaunchArguments, const xe_thread_group_dimensions_t *pLaunchArgumentsBuffer,
    xe_event_handle_t hEvent, uint32_t numWaitEvents, xe_event_handle_t *phWaitEvents) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendEventReset(xe_event_handle_t hEvent) {
    auto event = Event::fromHandle(hEvent);
    assert(event);
    addToResidencyContainer(&event->getAllocation());

    EncodeFlush<gfxCoreFamily>::encodeWithQwordWrite(*this, event->getGpuAddress(),
                                                     Event::STATE_CLEARED);

    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendBarrier(xe_event_handle_t hSignalEvent,
                                                                uint32_t numWaitEvents,
                                                                xe_event_handle_t *phWaitEvents) {
    EncodeFlush<gfxCoreFamily>::encode(*this);

    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendMemoryRangesBarrier(
    uint32_t numRanges, const size_t *pRangeSizes, const void **pRanges,
    xe_event_handle_t hSignalEvent, uint32_t numWaitEvents, xe_event_handle_t *phWaitEvents) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendImageCopyFromMemory(
    xe_image_handle_t hDstImage, const void *srcPtr, xe_image_region_t *pDstRegion,
    xe_event_handle_t hEvent, uint32_t numWaitEvents, xe_event_handle_t *phWaitEvents) {

    // Use for now the AppendMemoryCopy, as images are internally allocated linearly
    auto dstImage = L0::Image::fromHandle(hDstImage);
    GraphicsAllocation *dstAlloc = dstImage->getAllocation();
    uint64_t dstPtr = dstAlloc->getGpuAddress();
    size_t offset;
    size_t size;

    if (pDstRegion) {
        offset = pDstRegion->originX; // Get the origin in X as the offset
        size = pDstRegion->width;
    } else {
        offset = 0;
        size = dstImage->getSizeInBytes();
    }

    return this->appendMemoryCopy(reinterpret_cast<void *>(dstPtr + offset), srcPtr, size, hEvent,
                                  numWaitEvents, phWaitEvents);
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendImageCopyToMemory(
    void *dstPtr, xe_image_handle_t hSrcImage, xe_image_region_t *pSrcRegion,
    xe_event_handle_t hEvent, uint32_t numWaitEvents, xe_event_handle_t *phWaitEvents) {

    // Use for now the AppendMemoryCopy, as images are internally allocated linearly
    auto srcImage = L0::Image::fromHandle(hSrcImage);
    GraphicsAllocation *srcAlloc = srcImage->getAllocation();
    uint64_t srcPtr = srcAlloc->getGpuAddress();
    size_t offset;
    size_t size;

    if (pSrcRegion) {
        offset = pSrcRegion->originX; // Get the origin in X as the offse
        size = pSrcRegion->width;
    } else {
        offset = 0;
        size = srcImage->getSizeInBytes();
    }

    return this->appendMemoryCopy(dstPtr, reinterpret_cast<void *>(srcPtr + offset), size, hEvent,
                                  numWaitEvents, phWaitEvents);
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendImageCopyRegion(
    xe_image_handle_t hDstImage, xe_image_handle_t hSrcImage, xe_image_region_t *pDstRegion,
    xe_image_region_t *pSrcRegion, xe_event_handle_t hSignalEvent, uint32_t numWaitEvents,
    xe_event_handle_t *phWaitEvents) {

    // Use for now the AppendMemoryCopy, as images are internally allocated linearly
    auto dstImage = L0::Image::fromHandle(hDstImage);
    auto srcImage = L0::Image::fromHandle(hSrcImage);
    uint64_t dstPtr = dstImage->getAllocation()->getGpuAddress();
    uint64_t srcPtr = srcImage->getAllocation()->getGpuAddress();
    size_t dstOffset;
    size_t srcOffset;
    size_t srcSize;
    size_t size;

    if (pDstRegion) {
        dstOffset = pDstRegion->originX; // Get the origin in X as the offse
        size = pDstRegion->width;
    } else {
        dstOffset = 0;
        size = dstImage->getSizeInBytes();
    }

    if (pSrcRegion) {
        srcOffset = pSrcRegion->originX; // Get the origin in X as the offse
        srcSize = pSrcRegion->width;
    } else {
        srcOffset = 0;
        srcSize = srcImage->getSizeInBytes();
    }

    if (size > srcSize) {
        size = srcSize;
    }

    return this->appendMemoryCopy(reinterpret_cast<void *>(dstPtr + dstOffset),
                                  reinterpret_cast<void *>(srcPtr + srcOffset), size, hSignalEvent,
                                  numWaitEvents, phWaitEvents);
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendImageCopy(xe_image_handle_t hDstImage,
                                                                  xe_image_handle_t hSrcImage,
                                                                  xe_event_handle_t hEvent,
                                                                  uint32_t numWaitEvents,
                                                                  xe_event_handle_t *phWaitEvents) {
    return this->appendImageCopyRegion(hDstImage, hSrcImage, nullptr, nullptr, hEvent,
                                       numWaitEvents, phWaitEvents);
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendMemAdvise(xe_device_handle_t hDevice,
                                                                  const void *ptr, size_t size,
                                                                  xe_memory_advice_t advice) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendMemoryCopyKernel(
    void *dstptr, const void *srcptr, uint32_t size, Builtin builtin, uint32_t elementSize) {
    auto builtinFunction = this->device->getBuiltinFunctionsLib()->getFunction(builtin);

    uint32_t groupSizeX = builtinFunction->getImmutableData()
                              ->getSignature()
                              .attributes.simdSize; // TODO : consider ATS fused threads
    uint32_t groupSizeY = 1u;
    uint32_t groupSizeZ = 1u;

    if (builtinFunction->setGroupSize(groupSizeX, groupSizeY, groupSizeZ))
        return XE_RESULT_ERROR_UNKNOWN;

    builtinFunction->setArgumentValue(0, sizeof(dstptr), &dstptr);
    builtinFunction->setArgumentValue(1, sizeof(srcptr), &srcptr);
    uint32_t elems = size / elementSize;
    builtinFunction->setArgumentValue(2, sizeof(elems), &elems);

    uint32_t groups = (size + ((groupSizeX * elementSize) - 1)) / (groupSizeX * elementSize);
    xe_thread_group_dimensions_t dispatchFuncArgs{groups, 1u, 1u};

    return this->appendLaunchFunction(builtinFunction->toHandle(), &dispatchFuncArgs, nullptr, 0,
                                      nullptr);
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendMemoryCopy(
    void *dstptr, const void *srcptr, size_t size, xe_event_handle_t hSignalEvent,
    uint32_t numWaitEvents, xe_event_handle_t *phWaitEvents) {

    uintptr_t start = reinterpret_cast<uintptr_t>(dstptr);

    size_t middleAlignment = MemoryConstants::cacheLineSize;
    size_t middleElSize = sizeof(uint32_t) * 4;

    uintptr_t leftSize = start % middleAlignment;
    leftSize = (leftSize > 0) ? (middleAlignment - leftSize) : 0;
    // calc left leftover size
    leftSize = std::min(leftSize, size);
    // clamp left leftover size to requested size

    uintptr_t rightSize = (start + size) % middleAlignment;
    // calc right leftover size
    rightSize = std::min(rightSize, size - leftSize);
    // clamp

    uintptr_t middleSizeBytes = size - leftSize - rightSize;
    // calc middle size

    if (!isAligned<4>(reinterpret_cast<uintptr_t>(srcptr) + leftSize)) {
        // corner case - src relative to dst does not have DWORD alignment
        leftSize += middleSizeBytes;
        middleSizeBytes = 0;
    }

    auto middleSizeEls = middleSizeBytes / middleElSize;
    assert(size == leftSize + middleSizeBytes + rightSize);

    auto alloc = globalMemoryManager->findMemAllocation(dstptr);
    if (alloc == nullptr) {
        // Trying to access non-driver memallocated for dstptr: Allocate managed memory using the
        // host's buffer
        auto dstAlloc = globalMemoryManager->allocateManagedMemoryFromFault(device, dstptr, size);
        this->deallocationContainer.push_back(dstAlloc);
    } else {
        assert(alloc->getSize() >= size);
    }

    alloc = globalMemoryManager->findMemAllocation(srcptr);
    if (alloc == nullptr) {
        // Trying to access non-driver memallocated for dstptr: Allocate managed memory using the
        // host's buffer
        auto srcAlloc = globalMemoryManager->allocateManagedMemoryFromFault(
            device, const_cast<void *>(srcptr), size);
        this->deallocationContainer.push_back(srcAlloc);
    } else {
        assert(alloc->getSize() >= size);
    }

    // Confirm device has access to both pointers
    if (!globalMemoryManager->checkMemoryAccessFromDevice(this->getDevice(), dstptr) ||
        !globalMemoryManager->checkMemoryAccessFromDevice(this->getDevice(), srcptr)) {
        // TODO: Confirm this is the correct code
        return XE_RESULT_ERROR_INVALID_PARAMETER;
    }

    xe_result_t ret = XE_RESULT_SUCCESS;

    if (ret == XE_RESULT_SUCCESS && leftSize) {
        ret = appendMemoryCopyKernel(dstptr, srcptr, static_cast<uint32_t>(leftSize),
                                     Builtin::CopyBufferToBufferSide, 1);
    }

    if (ret == XE_RESULT_SUCCESS && middleSizeBytes) {
        ret = appendMemoryCopyKernel(ptrOffset(dstptr, leftSize),
                                     ptrOffset(srcptr, leftSize),
                                     static_cast<uint32_t>(middleSizeBytes),
                                     Builtin::CopyBufferToBufferMiddle,
                                     static_cast<uint32_t>(middleElSize));
    }

    if (ret == XE_RESULT_SUCCESS && rightSize) {
        ret = appendMemoryCopyKernel(ptrOffset(dstptr, (leftSize + middleSizeBytes)),
                                     ptrOffset(srcptr, (leftSize + middleSizeBytes)),
                                     static_cast<uint32_t>(rightSize),
                                     Builtin::CopyBufferToBufferSide, 1);
    }

    return ret;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendMemoryPrefetch(const void *ptr,
                                                                       size_t count) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendMemorySet(void *ptr, int value, size_t size,
                                                                  xe_event_handle_t hEvent,
                                                                  uint32_t numWaitEvents,
                                                                  xe_event_handle_t *phWaitEvents) {

    // Confirm dstptr has been previously allocated
    MemAllocation *allocation = globalMemoryManager->findMemAllocation(ptr);
    if (allocation == nullptr)
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Create buffer and allocation with init values
    uint8_t *initBuffer = new uint8_t[size];
    assert(initBuffer);
    memset(initBuffer, static_cast<int>(size), static_cast<uint8_t>(value));
    auto initAlloc = globalMemoryManager->allocateManagedMemoryFromFault(device, initBuffer, size);
    assert(initAlloc);
    initAlloc->setFlagInternalMemory();
    this->deallocationContainer.push_back(initAlloc);

    return appendMemoryCopy(ptr, initBuffer, size, hEvent, numWaitEvents, phWaitEvents);
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendSignalEvent(xe_event_handle_t hEvent) {
    auto event = Event::fromHandle(hEvent);
    assert(event);
    addToResidencyContainer(&event->getAllocation());

    EncodeFlush<gfxCoreFamily>::encodeWithQwordWrite(*this, event->getGpuAddress(),
                                                     Event::STATE_SIGNALED);

    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendWaitOnEvents(uint32_t numEvents,
                                                                     xe_event_handle_t *phEvent) {

    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using MI_SEMAPHORE_WAIT = typename GfxFamily::MI_SEMAPHORE_WAIT;

    for (uint32_t i = 0; i < numEvents; i++) {
        MI_SEMAPHORE_WAIT cmd = GfxFamily::cmdInitMiSemaphoreWait;
        auto event = Event::fromHandle(phEvent[i]);
        assert(event);
        addToResidencyContainer(&event->getAllocation());

        cmd.setSemaphoreGraphicsAddress(event->getGpuAddress());
        cmd.setSemaphoreDataDword(Event::STATE_CLEARED);
        cmd.setCompareOperation(
            MI_SEMAPHORE_WAIT::COMPARE_OPERATION::COMPARE_OPERATION_SAD_NOT_EQUAL_SDD);

        auto buffer = commandStream->getSpace(sizeof(cmd));
        *(MI_SEMAPHORE_WAIT *)buffer = cmd;
    }
    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t
CommandListCoreFamily<gfxCoreFamily>::getParameter(xe_command_list_parameter_t parameter,
                                                   uint32_t *value) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::reserveSpace(size_t size, void **ptr) {
    auto availableSpace = commandStream->getAvailableSpace();
    if (availableSpace < size) {
        *ptr = nullptr;
    } else {
        *ptr = commandStream->getSpace(size);
    }
    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily> xe_result_t CommandListCoreFamily<gfxCoreFamily>::reset() {
    // CommandListImp::destroy does 'delete this', not what we want here.
    CommandContainer::destroy();

    if (!this->initialize(device)) {
        return XE_RESULT_ERROR_DEVICE_LOST;
    }
    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::resetParameters() {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t
CommandListCoreFamily<gfxCoreFamily>::setParameter(xe_command_list_parameter_t parameter,
                                                   uint32_t value) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

} // namespace L0
