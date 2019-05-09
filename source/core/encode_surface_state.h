#pragma once
#include "cmdlist.h"
#include "hw_cmds.h"
#include "hw_info.h"

#include "runtime/helpers/aligned_memory.h"
#include "runtime/helpers/hw_helper.h"

namespace L0 {

template <GFXCORE_FAMILY gfxCoreFamily> struct EncodeSurfaceState {
    using GfxFamily = typename NEO::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;

    static void encodeBuffer(void *dst, void *address, size_t size, uint32_t mocs,
                             bool cpuCoherent) {
        using R_SURFACE_STATE = typename GfxFamily::RENDER_SURFACE_STATE;
        using SURFACE_FORMAT = typename R_SURFACE_STATE::SURFACE_FORMAT;
        using AUXILIARY_SURFACE_MODE = typename R_SURFACE_STATE::AUXILIARY_SURFACE_MODE;

        auto ss = reinterpret_cast<R_SURFACE_STATE *>(dst);

        // The graphics allocation for Host Ptr surface will be created in makeResident call and GPU
        // address is expected to be the same as CPU address
        assert(isAligned<getSurfaceBaseAddressAlignment()>(address));
        assert(isAligned<getSurfaceBaseAddressAlignment()>(size));

        NEO::SURFACE_STATE_BUFFER_LENGTH Length = {0};
        Length.Length = static_cast<uint32_t>(size - 1);

        ss->setWidth(Length.SurfaceState.Width + 1);
        ss->setHeight(Length.SurfaceState.Height + 1);
        ss->setDepth(Length.SurfaceState.Depth + 1);

        ss->setSurfaceType((address != nullptr) ? R_SURFACE_STATE::SURFACE_TYPE_SURFTYPE_BUFFER
                                                : R_SURFACE_STATE::SURFACE_TYPE_SURFTYPE_NULL);
        ss->setSurfaceFormat(SURFACE_FORMAT::SURFACE_FORMAT_RAW);
        ss->setSurfaceVerticalAlignment(R_SURFACE_STATE::SURFACE_VERTICAL_ALIGNMENT_VALIGN_4);
        ss->setSurfaceHorizontalAlignment(R_SURFACE_STATE::SURFACE_HORIZONTAL_ALIGNMENT_HALIGN_4);

        ss->setTileMode(R_SURFACE_STATE::TILE_MODE_LINEAR);
        ss->setVerticalLineStride(0);
        ss->setVerticalLineStrideOffset(0);
        ss->setMemoryObjectControlState(mocs);
        ss->setSurfaceBaseAddress(reinterpret_cast<uintptr_t>(address));

        ss->setCoherencyType(cpuCoherent ? R_SURFACE_STATE::COHERENCY_TYPE_IA_COHERENT
                                         : R_SURFACE_STATE::COHERENCY_TYPE_GPU_COHERENT);
        // TODO : Add support for compression
        ss->setAuxiliarySurfaceMode(AUXILIARY_SURFACE_MODE::AUXILIARY_SURFACE_MODE_AUX_NONE);
    }

    static constexpr uintptr_t getSurfaceBaseAddressAlignmentMask() {
        return ~(getSurfaceBaseAddressAlignment() - 1);
    }

    static constexpr uintptr_t getSurfaceBaseAddressAlignment() { return 4; }
};

} // namespace L0
