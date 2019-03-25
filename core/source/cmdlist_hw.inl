#include "cmdlist_hw.h"
#include "encode_flush.h"
#include "encode_state_base_address.h"
#include "event.h"
#include "graphics_allocation.h"
#include "image.h"
#include "memory_manager.h"
#include "module.h"
#include "builtins.h"
#include "builtin_functions_lib.h"
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

    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
void *CommandListCoreFamily<gfxCoreFamily>::getHeapSpaceAllowGrow(CommandContainer::HeapType heapType, size_t size) {
    auto &indirectHeap = *indirectHeaps[heapType];

    if (indirectHeap.getAvailableSpace() < size) {
        // grow

        size_t newSize = indirectHeap.getUsed() + indirectHeap.getAvailableSpace();
        newSize *= 2; // grow by factor of 2
        newSize = std::max(newSize, indirectHeap.getAvailableSpace() + size);
        newSize = alignUp(newSize, 4096U);
        auto oldAlloc = this->allocationIndirectHeaps[heapType];
        auto newAlloc = globalMemoryManager->allocateDeviceMemory(newSize, 4096u);
        assert(oldAlloc);
        assert(newAlloc);
        indirectHeap.replaceGraphicsAllocation(newAlloc->allocationRT);
        indirectHeap.replaceBuffer(newAlloc->allocationRT->getUnderlyingBuffer(), newAlloc->allocationRT->getUnderlyingBufferSize());
        this->residencyContainer.push_back(newAlloc->allocationRT);
        this->deallocationContainer.push_back(oldAlloc);
        allocationIndirectHeaps[heapType] = newAlloc;
        this->dirtyHeaps |= 1u << heapType;
    }
    return indirectHeap.getSpace(size);
}

template <GFXCORE_FAMILY gfxCoreFamily>
void CommandListCoreFamily<gfxCoreFamily>::enableGpgpu() {
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;

    using PIPELINE_SELECT = typename GfxFamily::PIPELINE_SELECT;
    PIPELINE_SELECT cmd = GfxFamily::cmdInitPipelineSelect;
    cmd.setPipelineSelection(PIPELINE_SELECT::PIPELINE_SELECTION_GPGPU);
    cmd.setMaskBits(3u); //TODO:  Add support for DOP clock gating

    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(PIPELINE_SELECT *)buffer = cmd;
}

template <GFXCORE_FAMILY gfxCoreFamily>
void CommandListCoreFamily<gfxCoreFamily>::programFrontEndState() {
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;

    using MEDIA_VFE_STATE = typename GfxFamily::MEDIA_VFE_STATE;
    MEDIA_VFE_STATE cmd = GfxFamily::cmdInitMediaVfeState;
    cmd.setNumberOfUrbEntries(1u);
    uint32_t urbEntryAllocationSize = 0x782; //TODO:  Gen family specific
    cmd.setUrbEntryAllocationSize(urbEntryAllocationSize);
    uint32_t maxNumThreads = 16u; //TODO:  get this from HwInfo
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

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::close() {
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using MI_BATCH_BUFFER_END = typename GfxFamily::MI_BATCH_BUFFER_END;
    MI_BATCH_BUFFER_END cmd = GfxFamily::cmdInitBatchBufferEnd;
    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(MI_BATCH_BUFFER_END *)buffer = cmd;

    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
void CommandListCoreFamily<gfxCoreFamily>::programL3(bool isSLMused) {
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendCommandLists(uint32_t numCommandLists,
                                                                     xe_command_list_handle_t *phCommandLists) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

// Returned binding table pointer is relative to given heap (which is assumed to be the Surface state base addess)
// as required by the INTERFACE_DESCRIPTOR_DATA.
template <GFXCORE_FAMILY gfxCoreFamily>
uint32_t CommandListCoreFamily<gfxCoreFamily>::copyBindingTableAndSurfaceStates(NEO::IndirectHeap *ssh,
                                                                                const void *srcSsh, uint32_t srcSshSize,
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

    // Compiler sends BTI table that is already populated with surface state pointers relative to local SSH.
    // We may need to patch these pointers so that they are relative to surface state base address
    if (dstSurfaceState == ssh->getCpuBase()) {
        // nothing to patch, we're at the start of heap (which is assumed to be the surface state base address)
        // we need to simply copy the ssh (including BTIs from compiler)
        memcpy_s(dstSurfaceState, srcSshSize, srcSsh, srcSshSize);
        return offsetOfBindingTable;
    }

    // We can copy-over the surface states, but BTIs will need to be patched
    memcpy_s(dstSurfaceState, srcSshSize, srcSsh, offsetOfBindingTable);

    uint32_t surfaceStatesOffset = static_cast<uint32_t>(ptrDiff(dstSurfaceState, ssh->getCpuBase()));

    // march over BTIs and offset the pointers based on surface state base address
    auto *dstBindingTable = reinterpret_cast<BINDING_TABLE_STATE *>(ptrOffset(dstSurfaceState, offsetOfBindingTable));
    assert(reinterpret_cast<uintptr_t>(dstBindingTable) % INTERFACE_DESCRIPTOR_DATA::BINDINGTABLEPOINTER_ALIGN_SIZE == 0);

    auto *srcBindingTable = reinterpret_cast<const BINDING_TABLE_STATE *>(ptrOffset(srcSsh, offsetOfBindingTable));
    BINDING_TABLE_STATE bts = GfxFamily::cmdInitBindingTableState;

    for (uint32_t i = 0; i < numberOfBindingTableStates; ++i) {
        uint32_t localSurfaceStateOffset = srcBindingTable[i].getSurfaceStatePointer();
        uint32_t offsetedSurfaceStateOffset = localSurfaceStateOffset + surfaceStatesOffset;

        bts.setSurfaceStatePointer(offsetedSurfaceStateOffset);
        dstBindingTable[i] = bts;
        assert(bts.getRawData(0) % sizeof(BINDING_TABLE_STATE::SURFACESTATEPOINTER_ALIGN_SIZE) == 0);
    }

    return static_cast<uint32_t>(ptrDiff(dstBindingTable, ssh->getCpuBase()));
}

// Copy our sampler state if it exists
template <GFXCORE_FAMILY gfxCoreFamily>
uint32_t CommandListCoreFamily<gfxCoreFamily>::copySamplerState(NEO::IndirectHeap *dsh,
                                                                const iOpenCL::SPatchSamplerStateArray *samplerStateArray,
                                                                const void *fnDynamicStateHeap) {
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using INTERFACE_DESCRIPTOR_DATA = typename GfxFamily::INTERFACE_DESCRIPTOR_DATA;
    using SAMPLER_STATE = typename GfxFamily::SAMPLER_STATE;

    assert(dsh);
    assert(samplerStateArray);
    assert(fnDynamicStateHeap);

    uint32_t samplerStateOffset = 0;
    uint32_t borderColorOffset = 0;
    uint32_t samplerCount = samplerStateArray->Count;
    auto sizeSamplerState = sizeof(SAMPLER_STATE) * samplerCount;
    auto borderColorSize = samplerStateArray->Offset - samplerStateArray->BorderColorOffset;

    dsh->align(alignIndirectStatePointer);
    borderColorOffset = static_cast<uint32_t>(dsh->getUsed());

    auto borderColor = dsh->getSpace(borderColorSize);

    memcpy_s(borderColor, borderColorSize,
             ptrOffset(fnDynamicStateHeap, samplerStateArray->BorderColorOffset),
             borderColorSize);

    dsh->align(INTERFACE_DESCRIPTOR_DATA::SAMPLERSTATEPOINTER_ALIGN_SIZE);
    samplerStateOffset = static_cast<uint32_t>(dsh->getUsed());

    auto samplerState = dsh->getSpace(sizeSamplerState);

    memcpy_s(samplerState, sizeSamplerState,
             ptrOffset(fnDynamicStateHeap, samplerStateArray->Offset),
             sizeSamplerState);

    auto pSmplr = reinterpret_cast<SAMPLER_STATE *>(samplerState);
    for (uint32_t i = 0; i < samplerCount; i++) {
        pSmplr[i].setIndirectStatePointer((uint32_t)borderColorOffset);
    }

    return samplerStateOffset;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendLaunchFunction(xe_function_handle_t hFunction,
                                                                       const xe_thread_group_dimensions_t *pThreadGroupDimensions,
                                                                       xe_event_handle_t hEvent) {
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using GPGPU_WALKER = typename GfxFamily::GPGPU_WALKER;
    using MEDIA_STATE_FLUSH = typename GfxFamily::MEDIA_STATE_FLUSH;
    using MEDIA_INTERFACE_DESCRIPTOR_LOAD = typename GfxFamily::MEDIA_INTERFACE_DESCRIPTOR_LOAD;
    using INTERFACE_DESCRIPTOR_DATA = typename GfxFamily::INTERFACE_DESCRIPTOR_DATA;
    using STATE_BASE_ADDRESS = typename GfxFamily::STATE_BASE_ADDRESS;
    using SAMPLER_STATE = typename GfxFamily::SAMPLER_STATE;

    const auto function = Function::fromHandle(hFunction);
    assert(function);
    auto sizeCrossThreadData = function->getCrossThreadDataSize();
    auto sizePerThreadData = function->getPerThreadDataSize();
    auto sizePerThreadDataForWholeGroup = function->getPerThreadDataSizeForWholeThreadGroup();

    GPGPU_WALKER cmd = GfxFamily::cmdInitGpgpuWalker;
    auto idd = GfxFamily::cmdInitInterfaceDescriptorData;

    // Point kernel start pointer to the proper offset of instruction heap
    {
        auto alloc = function->getIsaGraphicsAllocation();
        assert(nullptr != alloc);
        auto offset = alloc->getGpuAddressOffsetFromHeapBase();
        idd.setKernelStartPointer(offset);
        idd.setKernelStartPointerHigh(0u);
    }

    auto threadsPerThreadGroup = function->getThreadsPerThreadGroup();
    idd.setNumberOfThreadsInGpgpuThreadGroup(threadsPerThreadGroup);

    idd.setBarrierEnable(function->getHasBarriers());
    idd.setSharedLocalMemorySize(function->getSlmSize() > 0
                                     ? INTERFACE_DESCRIPTOR_DATA::SHARED_LOCAL_MEMORY_SIZE_ENCODES_64K
                                     : INTERFACE_DESCRIPTOR_DATA::SHARED_LOCAL_MEMORY_SIZE_ENCODES_0K);

    // Set up binding table and surface states
    {
        auto bindingTableStateCount = function->getBindingTableStateCount();
        uint32_t bindingTablePointer = 0u;

        if (bindingTableStateCount > 0u) {
            auto ssh = indirectHeaps[SURFACE_STATE];
            assert(ssh);
            bindingTablePointer = copyBindingTableAndSurfaceStates(ssh,
                                                                   function->getSurfaceStateHeap(),
                                                                   function->getSurfaceStateHeapSize(),
                                                                   bindingTableStateCount,
                                                                   function->getBindingTableOffset());
        }

        idd.setBindingTablePointer(bindingTablePointer);

        auto bindingTableStatePrefetchCount = std::min(31u, 0u); //TODO: bindingTableStateCount
        idd.setBindingTableEntryCount(bindingTableStatePrefetchCount);
    }

    auto heap = indirectHeaps[DYNAMIC_STATE];
    assert(heap);

    uint32_t samplerStateOffset = 0;
    uint32_t samplerCount = 0;
    const auto samplerStateArray = function->getSamplerStateArray();

    // Copy our sampler state if it exists
    if (samplerStateArray) {
        samplerCount = samplerStateArray->Count;
        samplerStateOffset = copySamplerState(heap, samplerStateArray, function->getDynamicStateHeap());
    }

    idd.setSamplerStatePointer(samplerStateOffset);
    auto samplerCountState = static_cast<typename INTERFACE_DESCRIPTOR_DATA::SAMPLER_COUNT>((samplerCount + 3) / 4);
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

        memcpy(ptr, function->getCrossThreadDataHostMem(), sizeCrossThreadData);
        ptr = ptrOffset(ptr, sizeCrossThreadData);
        memcpy(ptr, function->getPerThreadDataHostMem(), sizePerThreadDataForWholeGroup);
    }

    // Update any non-pipelined state if it changes
    auto slmSizeNew = function->getSlmSize();
    bool flush = this->slmSize != slmSizeNew ||
                 this->dirtyHeaps;

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
        numIDD = 0U; // change to IDD within MEDIA_INTERFACE_DESCRIPTOR_LOAD once we start grouping IDDs

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
    auto simdSize = function->getSimdSize();
    auto simdSizeOp =
        GPGPU_WALKER::SIMD_SIZE_SIMD32 * (simdSize == 32) |
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
        EncodeFlush<gfxCoreFamily>::encodeWithQwordWrite(*this,
                                                         event->getGpuAddress(),
                                                         Event::STATE_SIGNALED);
        addToResidencyContainer(&event->getAllocation());
    }

    {
        // A MEDIA_STATE_FLUSH with no options must be added after a GPGPU_WALKER command which doesn't use either SLM or barriers.
        auto mediaStateFlush = commandStream->getSpace(sizeof(MEDIA_STATE_FLUSH));
        *reinterpret_cast<MEDIA_STATE_FLUSH *>(mediaStateFlush) = GfxFamily::cmdInitMediaStateFlush;
    }

    // Attach Function residency to our CommandList residency
    {
        addToResidencyContainer(function->getIsaGraphicsAllocation().get());
        auto &residencyContainer = function->getResidencyContainer();
        for (auto resource : residencyContainer) {
            addToResidencyContainer(resource);
        }
    }

    // Store PrintfBuffer from a function
    {
        if (function->hasPrintfOutput()) {
            this->storePrintfFunction(function);
        }
    }

    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendLaunchFunctionIndirect(xe_function_handle_t hFunction,
                                                                               const xe_thread_group_dimensions_t *pDispatchArgumentsBuffer,
                                                                               xe_event_handle_t hEvent) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendLaunchHostFunction(xe_host_pfn_t pfnHostFunc,
                                                                           void *pUserData) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendLaunchMultipleFunctionsIndirect(uint32_t numFunctions,
                                                                                        const xe_function_handle_t *phFunctions,
                                                                                        const size_t *pNumLaunchArguments,
                                                                                        const xe_thread_group_dimensions_t *pLaunchArgumentsBuffer,
                                                                                        xe_event_handle_t hEvent) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendEventReset(xe_event_handle_t hEvent) {
    auto event = Event::fromHandle(hEvent);
    assert(event);
    addToResidencyContainer(&event->getAllocation());

    EncodeFlush<gfxCoreFamily>::encodeWithQwordWrite(*this,
                                                     event->getGpuAddress(),
                                                     Event::STATE_CLEARED);

    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendExecutionBarrier() {
    EncodeFlush<gfxCoreFamily>::encode(*this);

    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendImageCopyFromMemory(xe_image_handle_t hDstImage,
                                                                            xe_image_region_t *pDstRegion,
                                                                            const void *srcPtr,
                                                                            xe_event_handle_t hEvent) {

    // Use for now the AppendMemoryCopy, as images are internally allocated linearly
    auto dstImage = L0::Image::fromHandle(hDstImage);
    GraphicsAllocation *dstAlloc = dstImage->getAllocation();
    uint64_t dstPtr = dstAlloc->getGpuAddress();
    size_t offset;
    size_t size;

    if (pDstRegion) {
        offset = pDstRegion->offset;
        size = pDstRegion->size;
    } else {
        offset = 0;
        size = dstImage->getSizeInBytes();
    }

    return this->appendMemoryCopy(reinterpret_cast<void *>(dstPtr + offset),
                                  srcPtr, size, nullptr);
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendImageCopyToMemory(void *dstPtr,
                                                                          xe_image_handle_t hSrcImage,
                                                                          xe_image_region_t *pSrcRegion,
                                                                          xe_event_handle_t hEvent) {

    // Use for now the AppendMemoryCopy, as images are internally allocated linearly
    auto srcImage = L0::Image::fromHandle(hSrcImage);
    GraphicsAllocation *srcAlloc = srcImage->getAllocation();
    uint64_t srcPtr = srcAlloc->getGpuAddress();
    size_t offset;
    size_t size;

    if (pSrcRegion) {
        offset = pSrcRegion->offset;
        size = pSrcRegion->size;
    } else {
        offset = 0;
        size = srcImage->getSizeInBytes();
    }

    return this->appendMemoryCopy(dstPtr,
                                  reinterpret_cast<void *>(srcPtr + offset),
                                  size, hEvent);
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendImageCopyRegion(xe_image_handle_t hDstImage,
                                                                        xe_image_region_t *pDstRegion,
                                                                        xe_image_handle_t hSrcImage,
                                                                        xe_image_region_t *pSrcRegion,
                                                                        xe_event_handle_t hEvent) {

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
        dstOffset = pDstRegion->offset;
        size = pDstRegion->size;
    } else {
        dstOffset = 0;
        size = dstImage->getSizeInBytes();
    }

    if (pSrcRegion) {
        srcOffset = pSrcRegion->offset;
        srcSize = pSrcRegion->size;
    } else {
        srcOffset = 0;
        srcSize = srcImage->getSizeInBytes();
    }

    if (size > srcSize) {
        size = srcSize;
    }

    return this->appendMemoryCopy(
        reinterpret_cast<void *>(dstPtr + dstOffset),
        reinterpret_cast<void *>(srcPtr + srcOffset),
        size, hEvent);
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendImageCopy(xe_image_handle_t hDstImage,
                                                                  xe_image_handle_t hSrcImage,
                                                                  xe_event_handle_t hEvent) {
    return this->appendImageCopyRegion(hDstImage, NULL, hSrcImage, NULL, hEvent);
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendMemAdvise(xe_device_handle_t hDevice,
                                                                  const void *ptr,
                                                                  size_t size,
                                                                  xe_memory_advice_t advice) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendMemoryCopy(void *dstptr,
                                                                   const void *srcptr,
                                                                   size_t size,
                                                                   xe_event_handle_t hEvent) {
    auto builtinFunction = this->device->getBuiltinFunctionsLib()->getFunction(Builtin::CopyBufferBytes); // no thread safety!

    uint32_t groupSizeX = builtinFunction->getSimdSize(); // TODO : consider ATS fused threads
    uint32_t groupSizeY = 1u;
    uint32_t groupSizeZ = 1u;
    if (builtinFunction->setGroupSize(groupSizeX, groupSizeY, groupSizeZ))
        return XE_RESULT_ERROR_UNKNOWN;

    GraphicsAllocation *alloc = globalMemoryManager->findAllocation(dstptr);
    if (alloc == nullptr) {
        // Trying to access non-driver memallocated for dstptr: Allocate managed memory using the host's buffer
        globalMemoryManager->allocateManagedMemoryFromFault(dstptr, size);
    }
    builtinFunction->setArgumentValue(0, sizeof(dstptr), &dstptr);

    alloc = globalMemoryManager->findAllocation(srcptr);
    if (alloc == nullptr) {
        // Trying to access non-driver memallocated for dstptr: Allocate managed memory using the host's buffer
        globalMemoryManager->allocateManagedMemoryFromFault(const_cast<void *>(srcptr), size);
    }
    builtinFunction->setArgumentValue(1, sizeof(srcptr), &srcptr);

    constexpr auto elementSize = sizeof(char);
    assert(size / (groupSizeX * elementSize) < MemoryConstants::gigaByte);
    uint32_t whole = static_cast<uint32_t>(size / (groupSizeX * elementSize));
    uint32_t rest = static_cast<uint32_t>(size - whole * groupSizeX * elementSize);
    xe_thread_group_dimensions_t dispatchFuncArgs{whole, 1u, 1u};

    auto ret = XE_RESULT_SUCCESS;
    if (whole > 0) {
        ret = this->appendLaunchFunction(builtinFunction->toHandle(), &dispatchFuncArgs, nullptr);
    }
    if ((XE_RESULT_SUCCESS != ret) || (rest == 0)) {
        return ret;
    }
    dstptr = ptrOffset(dstptr, whole * groupSizeX * elementSize);
    srcptr = ptrOffset(srcptr, whole * groupSizeX * elementSize);
    builtinFunction->setArgumentValue(0, sizeof(dstptr), &dstptr);
    builtinFunction->setArgumentValue(1, sizeof(srcptr), &srcptr);
    if (builtinFunction->setGroupSize(rest, 1u, 1u)) {
        return XE_RESULT_ERROR_UNKNOWN;
    }
    dispatchFuncArgs.groupCountX = 1;

    return this->appendLaunchFunction(builtinFunction->toHandle(), &dispatchFuncArgs, nullptr);
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendMemoryPrefetch(const void *ptr,
                                                                       size_t count) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendMemorySet(void *ptr,
                                                                  int value,
                                                                  size_t size,
                                                                  xe_event_handle_t hEvent) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendSignalEvent(xe_event_handle_t hEvent) {
    auto event = Event::fromHandle(hEvent);
    assert(event);
    addToResidencyContainer(&event->getAllocation());

    EncodeFlush<gfxCoreFamily>::encodeWithQwordWrite(*this,
                                                     event->getGpuAddress(),
                                                     Event::STATE_SIGNALED);

    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::appendWaitOnEvent(xe_event_handle_t hEvent) {
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using MI_SEMAPHORE_WAIT = typename GfxFamily::MI_SEMAPHORE_WAIT;
    MI_SEMAPHORE_WAIT cmd = GfxFamily::cmdInitMiSemaphoreWait;
    auto event = Event::fromHandle(hEvent);
    assert(event);
    addToResidencyContainer(&event->getAllocation());

    cmd.setSemaphoreGraphicsAddress(event->getGpuAddress());
    cmd.setSemaphoreDataDword(Event::STATE_CLEARED);
    cmd.setCompareOperation(MI_SEMAPHORE_WAIT::COMPARE_OPERATION::COMPARE_OPERATION_SAD_NOT_EQUAL_SDD);

    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(MI_SEMAPHORE_WAIT *)buffer = cmd;
    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::getParameter(xe_command_list_parameter_t parameter, uint32_t *value) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::reserveSpace(size_t size,
                                                               void **ptr) {
    auto availableSpace = commandStream->getAvailableSpace();
    if (availableSpace < size) {
        *ptr = nullptr;
    } else {
        *ptr = commandStream->getSpace(size);
    }
    return XE_RESULT_SUCCESS;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::reset() {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::resetParameters() {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

template <GFXCORE_FAMILY gfxCoreFamily>
xe_result_t CommandListCoreFamily<gfxCoreFamily>::setParameter(xe_command_list_parameter_t parameter,
                                                               uint32_t value) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

} // namespace L0
