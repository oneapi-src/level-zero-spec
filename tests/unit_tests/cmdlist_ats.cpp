#include "runtime/gen12hp/hw_cmds.h"
#include "runtime/gen12hp/hw_info.h"
#include "runtime/indirect_heap/indirect_heap.h"
#include "cmdlist_hw.inl"
#include "module.h"
#include "igfxfmid.h"

namespace xe {

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

        auto &idd = cmd.getInterfaceDescriptor();
        idd.setKernelStartPointer(static_cast<uint32_t>(reinterpret_cast<uint64_t>(ptr)));
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

        memcpy(ptr, functionArgs->getPerThreadDataHostMem(), sizePerThreadData);
        ptr = ptrOffset(ptr, sizePerThreadData);
        memcpy(ptr, functionArgs->getCrossThreadDataHostMem(), sizeCrossThreadData);

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
