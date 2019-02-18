#include "runtime/gen12hp/hw_cmds.h"
#include "runtime/gen12hp/hw_info.h"
#include "runtime/indirect_heap/indirect_heap.h"
#include "cmdlist_hw.inl"
#include "module.h"
#include "igfxfmid.h"

namespace xe {

template <>
bool CommandListHw<IGFX_GEN12_CORE>::initialize() {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<static_cast<GFXCORE_FAMILY>(IGFX_GEN12_CORE)>::GfxFamily;

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

    {
        using CFE_STATE = typename GfxFamily::CFE_STATE;
        CFE_STATE cmd = GfxFamily::cmdInitCfeState;
        auto buffer = commandStream->getSpace(sizeof(cmd));
        *(CFE_STATE *)buffer = cmd;
    }

    return true;
}

template <>
xe_result_t CommandListHw<IGFX_GEN12_CORE>::encodeDispatchFunction(xe_function_handle_t hFunction,
                                                                   xe_function_args_handle_t hFunctionArgs,
                                                                   xe_dispatch_function_arguments_t *pDispatchFuncArgs,
                                                                   xe_event_handle_t hEvent) {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<IGFX_GEN12_CORE>::GfxFamily;
    using COMPUTE_WALKER = typename GfxFamily::COMPUTE_WALKER;
    auto function = Function::fromHandle(hFunction);
    assert(function);
    auto functionArgs = FunctionArgs::fromHandle(hFunctionArgs);
    assert(functionArgs);

    COMPUTE_WALKER cmd = GfxFamily::cmdInitGpgpuWalker;
    cmd.setThreadGroupIdXDimension(pDispatchFuncArgs->groupCountX);
    cmd.setThreadGroupIdYDimension(pDispatchFuncArgs->groupCountY);
    cmd.setThreadGroupIdZDimension(pDispatchFuncArgs->groupCountZ);
    cmd.setEmitLocalId(0u);
    cmd.setExecutionMask(0xfffffffful);

    // Compute the execution mask
    uint32_t lwsX = 0;
    uint32_t lwsY = 0;
    uint32_t lwsZ = 0;
    functionArgs->getGroupSize(lwsX, lwsY, lwsZ);

    auto &idd = cmd.getInterfaceDescriptor();
    idd.setNumberOfThreadsInGpgpuThreadGroup(functionArgs->getThreadsPerThreadGroup());

#if 0
    auto remainderSimdLanes = localWorkSize & (simd - 1);
    uint64_t executionMask = (1ull << remainderSimdLanes) - 1;
    if (!executionMask) {
        executionMask = ~executionMask;
    }
#endif

    auto simdSize = function->getSimdSize();
    auto simdSizeOp =
        COMPUTE_WALKER::SIMD_SIZE_SIMD32 * (1 & (simdSize >> 5)) |
        COMPUTE_WALKER::SIMD_SIZE_SIMD16 * (1 & (simdSize >> 4)) |
        COMPUTE_WALKER::SIMD_SIZE_SIMD8 * (1 & (simdSize >> 3));
    cmd.setSimdSize(static_cast<COMPUTE_WALKER::SIMD_SIZE>(simdSizeOp));

    // Copy the kernel to indirect heap
    // TODO: Allocate kernel in graphics memory to avoid the CPU copy
    {
        auto sizeISA = function->getIsaSize();
        auto ptrISA = function->getIsaHostMem();

        constexpr auto INSTRUCTION_HEAP = OCLRT::IndirectHeap::SURFACE_STATE + 1;
        auto heap = this->indirectHeaps[INSTRUCTION_HEAP];
        assert(heap);

        auto ptr = heap->getSpace(sizeISA);
        assert(ptr);
        memcpy(ptr, ptrISA, sizeISA);

        auto offset = static_cast<uint32_t>(ptrDiff(ptr, heap->getHeapGpuBase()));

        auto &idd = cmd.getInterfaceDescriptor();
        idd.setKernelStartPointer(offset);
        idd.setKernelStartPointerHigh(0u);
    }

    // Copy the threadData to the indirect heap
    {
        auto heap = indirectHeaps[OCLRT::IndirectHeap::GENERAL_STATE];
        assert(heap);

        auto sizeCrossThreadData = static_cast<uint32_t>(functionArgs->getCrossThreadDataSize());
        auto sizePerThreadData = static_cast<uint32_t>(functionArgs->getPerThreadDataSize());
        auto sizeThreadData = sizePerThreadData + sizeCrossThreadData;
        auto ptr = heap->getSpace(sizeThreadData);
        assert(ptr);
        auto offset = ptrDiff(ptr, heap->getCpuBase());
        assert(offset + sizeThreadData <= heap->getMaxAvailableSpace());

        memcpy(ptr, functionArgs->getCrossThreadDataHostMem(), sizeCrossThreadData);
        ptr = ptrOffset(ptr, sizeCrossThreadData);
        memcpy(ptr, functionArgs->getPerThreadDataHostMem(), sizePerThreadData);
        ptr = ptrOffset(ptr, sizePerThreadData);

        cmd.setIndirectDataLength(sizeThreadData);
        cmd.setIndirectDataStartAddress(static_cast<uint32_t>(offset));
    }

    // Attach Function residency to our CommandList residency
    {
        //TODO: functionArgs->getResidencyContainer();
    }

    // Commit our command to the commandStream
    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(decltype(cmd) *)buffer = cmd;

    return XE_RESULT_SUCCESS;
}

static CommandListPopulateFactory<IGFX_TIGERLAKE_HP, CommandListHw<IGFX_GEN12_CORE>> populateTGLHP;

} // namespace xe
