#pragma once
#define FUNCTION_INTERNAL
#include "function_imp.h"
#undef FUNCTION_INTERNAL

#include "graphics_allocation.h"
#include "encode_surface_state.h"
#include "mocs_mapper.h"
#include "module.h"

#include "igfxfmid.h"

#include <algorithm>

namespace L0 {

template <GFXCORE_FAMILY gfxCoreFamily> struct FunctionHw : public FunctionImp {
    using FunctionImp::FunctionImp;

    void setBufferSurfaceState(uint32_t argIndex, void *address,
                               GraphicsAllocation *alloc) override {
        uintptr_t baseAddress = reinterpret_cast<uintptr_t>(alloc->getHostAddress());
        auto sshAlignmentMask =
            EncodeSurfaceState<gfxCoreFamily>::getSurfaceBaseAddressAlignmentMask();

        baseAddress &= sshAlignmentMask; // chop-off misalligned bytes
                                         // take them into account in bufferOffset patch token

        auto offset = ptrDiff(address, reinterpret_cast<void *>(baseAddress));
        size_t sizeTillEndOfSurface = alloc->getSize() - offset;
        auto argInfo = funcImmData->getSignature().explicitArgs.args[argIndex]->as<ArgPointer>();
        bool offsetWasPatched = FunctionSignature::patchNonPointer(
            this->crossThreadData.weakRef(), this->crossThreadDataSize, argInfo.bufferOffset,
            static_cast<uint32_t>(offset));
        // TODO : work with IGC to always compile with buffer offset arg. Otherwise, no way to
        // handle surface base address alignment corner cases
        if (false == offsetWasPatched) {
            // fallback to handling offset in surface state
            baseAddress = reinterpret_cast<uintptr_t>(address);
            assert(baseAddress == (baseAddress & sshAlignmentMask));
            offset = 0;
        }

        auto surfaceStateAddress = surfaceStateHeapData.weakRef().offsetBytesBy(argInfo.stateful);
        void *bufferAddressForSsh = reinterpret_cast<void *>(baseAddress);
        auto alignment = EncodeSurfaceState<gfxCoreFamily>::getSurfaceBaseAddressAlignment();
        size_t bufferSizeForSsh =
            ptrDiff(bufferAddressForSsh, alloc->getHostAddress()) +
            sizeTillEndOfSurface; // take address alignment offset into account
        bufferSizeForSsh = alignUp(bufferSizeForSsh, alignment);

        // TODO : Buffer MOCS can't be cached unconditionally for e.g. when false cacheline sharing
        // with CPU (hotptrs)
        auto mocs = this->module->getDevice()->getMOCSMapper()->getFullyCachedMOCS();
        bool requiresCoherency;
        EncodeSurfaceState<gfxCoreFamily>::encodeBuffer(surfaceStateAddress.get(),
                                                        bufferAddressForSsh, bufferSizeForSsh, mocs,
                                                        requiresCoherency = false);
    }

    PtrOwn<Function> clone() const override {
        PtrOwn<Function> ret{new FunctionHw<gfxCoreFamily>};
        PtrRef<FunctionHw<gfxCoreFamily>> cloned = ret.weakRef<FunctionHw<gfxCoreFamily>>();

        cloned->funcImmData = funcImmData.weakRef();
        cloned->module = module.weakRef();
        cloned->kernelArgHandlers.assign(this->kernelArgHandlers.begin(),
                                         this->kernelArgHandlers.end());
        cloned->residencyContainer.assign(this->residencyContainer.begin(),
                                          this->residencyContainer.end());

        if (printfBuffer != nullptr) {
            const auto &it =
                std::find(cloned->residencyContainer.rbegin(), cloned->residencyContainer.rend(),
                          this->printfBuffer.weakRef().get());
            if (it == cloned->residencyContainer.rbegin()) {
                cloned->residencyContainer.resize(cloned->residencyContainer.size() - 1);
            } else {
                std::iter_swap(it, cloned->residencyContainer.rbegin());
            }
            cloned->createPrintfBuffer();
        }

        std::copy(this->groupSize, this->groupSize + 3, cloned->groupSize);
        cloned->threadsPerThreadGroup = this->threadsPerThreadGroup;
        cloned->threadExecutionMask = this->threadExecutionMask;

        if (this->surfaceStateHeapDataSize > 0) {
            cloned->surfaceStateHeapData.rebind(new uint8_t[this->surfaceStateHeapDataSize],
                                                this->surfaceStateHeapDataSize);
            memcpy(cloned->surfaceStateHeapData.weakRef().get(),
                   this->surfaceStateHeapData.weakRef().get(), this->surfaceStateHeapDataSize);
            cloned->surfaceStateHeapDataSize = this->surfaceStateHeapDataSize;
        }

        if (this->crossThreadDataSize != 0) {
            cloned->crossThreadData.rebind(new uint8_t[this->crossThreadDataSize],
                                           this->crossThreadDataSize);
            memcpy(cloned->crossThreadData.weakRef().get(), this->crossThreadData.weakRef().get(),
                   this->crossThreadDataSize);
            cloned->crossThreadDataSize = this->crossThreadDataSize;
        }

        if (this->dynamicStateHeapDataSize != 0) {
            cloned->dynamicStateHeapData.rebind(new uint8_t[this->dynamicStateHeapDataSize],
                                                this->dynamicStateHeapDataSize);
            memcpy(cloned->dynamicStateHeapData.weakRef().get(),
                   this->dynamicStateHeapData.weakRef().get(), this->dynamicStateHeapDataSize);
            cloned->dynamicStateHeapDataSize = this->dynamicStateHeapDataSize;
        }

        if (this->perThreadDataForWholeThreadGroup != nullptr) {
            cloned->perThreadDataForWholeThreadGroup.rebind(
                static_cast<uint8_t *>(alignedMalloc(perThreadDataSizeForWholeThreadGroupAllocated,
                                                     32))); // alignment for vector instructions
            memcpy(cloned->perThreadDataForWholeThreadGroup.weakRef().get(),
                   this->perThreadDataForWholeThreadGroup.weakRef().get(),
                   this->perThreadDataSizeForWholeThreadGroupAllocated);
            cloned->perThreadDataSizeForWholeThreadGroupAllocated =
                this->perThreadDataSizeForWholeThreadGroupAllocated;
            cloned->perThreadDataSizeForWholeThreadGroup =
                this->perThreadDataSizeForWholeThreadGroup;
            cloned->perThreadDataSize = this->perThreadDataSize;
        }

        return PtrOwn<Function>{std::move(ret)};
    }
};

} // namespace L0
