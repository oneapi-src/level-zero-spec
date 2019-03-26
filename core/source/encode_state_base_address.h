#pragma once
#include "cmdlist.h"
#include "hw_info.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/indirect_heap/indirect_heap.h"

namespace L0 {

template <GFXCORE_FAMILY gfxCoreFamily>
struct EncodeStateBaseAddress {
    using GfxFamily = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;
    using STATE_BASE_ADDRESS = typename GfxFamily::STATE_BASE_ADDRESS;

    static const size_t size = sizeof(STATE_BASE_ADDRESS);

    static void encode(CommandContainer &container) {
        if (container.dirtyHeaps) {
            STATE_BASE_ADDRESS cmd = GfxFamily::cmdInitStateBaseAddress;

            if (container.dirtyHeaps & (1u << CommandContainer::DYNAMIC_STATE)) {
                auto &heap = container.getIndirectHeap(CommandContainer::DYNAMIC_STATE);
                cmd.setDynamicStateBaseAddressModifyEnable(true);
                cmd.setDynamicStateBaseAddress(heap.getHeapGpuBase());
                cmd.setDynamicStateBufferSizeModifyEnable(true);
                cmd.setDynamicStateBufferSize(static_cast<uint32_t>(heap.getMaxAvailableSpace()));
            }

            if (container.dirtyHeaps & (1u << CommandContainer::GENERAL_STATE)) {
                auto &heap = container.getIndirectHeap(CommandContainer::GENERAL_STATE);
                cmd.setGeneralStateBaseAddressModifyEnable(true);
                cmd.setGeneralStateBaseAddress(heap.getHeapGpuBase());
                cmd.setGeneralStateBufferSizeModifyEnable(true);
                cmd.setGeneralStateBufferSize(static_cast<uint32_t>(heap.getMaxAvailableSpace()));
            }

            if (container.dirtyHeaps & (1u << CommandContainer::INDIRECT_OBJECT)) {
                auto &heap = container.getIndirectHeap(CommandContainer::INDIRECT_OBJECT);
                cmd.setIndirectObjectBaseAddressModifyEnable(true);
                cmd.setIndirectObjectBaseAddress(heap.getHeapGpuBase());
                cmd.setIndirectObjectBufferSizeModifyEnable(true);
                cmd.setIndirectObjectBufferSize(static_cast<uint32_t>(heap.getMaxAvailableSpace()));
            }

            if (container.dirtyHeaps & (1u << CommandContainer::SURFACE_STATE)) {
                auto &heap = container.getIndirectHeap(CommandContainer::SURFACE_STATE);
                cmd.setSurfaceStateBaseAddressModifyEnable(true);
                cmd.setSurfaceStateBaseAddress(heap.getHeapGpuBase());
            }

            {
                // note : this doesn't change
                cmd.setInstructionBaseAddressModifyEnable(true);
                cmd.setInstructionBaseAddress(container.getInstructionHeapBaseAddress());
                cmd.setInstructionBufferSizeModifyEnable(true);
                cmd.setInstructionBufferSize(MemoryConstants::sizeOf4GBinPageEntities); // no bounds checking
            }

            auto buffer = container.getCommandStream().getSpace(sizeof(cmd));
            *(STATE_BASE_ADDRESS *)buffer = cmd;

            container.dirtyHeaps = 0u;
        }
    }
};

} // namespace L0
