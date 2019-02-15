#include "runtime/gen12hp/hw_cmds.h"
#include "runtime/gen12hp/hw_info.h"
#include "cmdlist_hw.inl"
#include "igfxfmid.h"

namespace xe {

template <>
xe_result_t CommandListHw<IGFX_GEN12_CORE>::encodeDispatchFunction(xe_function_handle_t hFunction,
                                                                   xe_function_args_handle_t hFunctionArgs,
                                                                   xe_dispatch_function_arguments_t *pDispatchFuncArgs,
                                                                   xe_event_handle_t hEvent) {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<IGFX_GEN12_CORE>::GfxFamily;
    using COMPUTE_WALKER = typename GfxFamily::COMPUTE_WALKER;

    COMPUTE_WALKER cmd = GfxFamily::cmdInitGpgpuWalker;
    cmd.setThreadGroupIdXDimension(pDispatchFuncArgs->groupCountX);
    cmd.setThreadGroupIdYDimension(pDispatchFuncArgs->groupCountY);
    cmd.setThreadGroupIdZDimension(pDispatchFuncArgs->groupCountZ);
    cmd.setEmitLocalId(0u);
    cmd.setExecutionMask(0xfffffffful);
    cmd.setSimdSize(COMPUTE_WALKER::SIMD_SIZE_SIMD32);

    auto buffer = commandStream->getSpace(sizeof(cmd));
    *(decltype(cmd) *)buffer = cmd;
    return XE_RESULT_SUCCESS;
}

static CommandListPopulateFactory<IGFX_TIGERLAKE_HP, CommandListHw<IGFX_GEN12_CORE>> populateTGLHP;

} // namespace xe
