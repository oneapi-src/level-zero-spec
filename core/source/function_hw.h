#pragma once
#define FUNCTION_INTERNAL
#include "function_imp.h"
#undef FUNCTION_INTERNAL

#include "graphics_allocation.h"
#include "encode_surface_state.h"
#include "mocs_mapper.h"
#include "module.h"

#include "igfxfmid.h"

namespace L0 {

template <GFXCORE_FAMILY gfxCoreFamily>
struct FunctionHw : public FunctionImp {
    using FunctionImp::FunctionImp;

    void setBufferSurfaceState(uint32_t argIndex, void *address, GraphicsAllocation *alloc) override {
        uintptr_t baseAddress = reinterpret_cast<uintptr_t>(alloc->getHostAddress());
        auto sshAlignmentMask = EncodeSurfaceState<gfxCoreFamily>::getSurfaceBaseAddressAlignmentMask();

        baseAddress &= sshAlignmentMask; // chop-off misalligned bytes
                                         // take them into account in bufferOffset patch token

        auto offset = ptrDiff(address, reinterpret_cast<void *>(baseAddress));
        size_t sizeTillEndOfSurface = alloc->getSize() - offset;
        auto argInfo = funcImmData->getSignature().explicitArgs.args[argIndex]->as<ArgPointer>();
        bool offsetWasPatched = FunctionSignature::patchNonPointer(this->crossThreadData.weakRef(), this->crossThreadDataSize,
                                                                   argInfo.bufferOffset, static_cast<uint32_t>(offset));
        // TODO : work with IGC to always compile with buffer offset arg. Otherwise, no way to handle surface base address alignment corner cases
        if (false == offsetWasPatched) {
            // fallback to handling offset in surface state
            baseAddress = reinterpret_cast<uintptr_t>(address);
            assert(baseAddress == (baseAddress & sshAlignmentMask));
            offset = 0;
        }

        auto surfaceStateAddress = ptrOffset(getSurfaceStateHeap(), argInfo.stateful);
        void *bufferAddressForSsh = reinterpret_cast<void *>(baseAddress);
        auto alignment = EncodeSurfaceState<gfxCoreFamily>::getSurfaceBaseAddressAlignment();
        size_t bufferSizeForSsh = ptrDiff(alloc->getHostAddress(), bufferAddressForSsh) + sizeTillEndOfSurface; // take address alignment offset into account
        bufferSizeForSsh = alignUp(bufferSizeForSsh, alignment);

        // TODO : Buffer MOCS can't be cached unconditionally for e.g. when false cacheline sharing with CPU (hotptrs)
        auto mocs = this->module->getDevice()->getMOCSMapper()->getFullyCachedMOCS();
        bool requiresCoherency;
        EncodeSurfaceState<gfxCoreFamily>::encodeBuffer(surfaceStateAddress, bufferAddressForSsh, bufferSizeForSsh,
                                                        mocs, requiresCoherency = false);
    }
};

} // namespace L0