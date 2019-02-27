#pragma once
#ifndef CMD_LIST_INTERNAL
#error "Don't #include this file directly."
#endif //CMD_LIST_INTERNAL

#include "cmdlist.h"
#include <vector>

namespace OCLRT {
class IndirectHeap;
class LinearStream;
class GraphicsAllocation;

using ResidencyContainer = std::vector<GraphicsAllocation *>;
}

namespace L0 {

struct CommandListImp : public CommandList {
    CommandListImp(Device *device)
        : device(device),
          commandStream(nullptr) {
        for (auto &indirectHeap : indirectHeaps) {
            indirectHeap = nullptr;
        }

        for (auto &allocationIndirectHeap : allocationIndirectHeaps) {
            allocationIndirectHeap = nullptr;
        }
    }

    xe_result_t destroy() override;

    virtual bool initialize();

    OCLRT::ResidencyContainer &getResidencyContainer() {
        return residencyContainer;
    }

  protected:
    virtual ~CommandListImp();

    Device *device;
    OCLRT::LinearStream *commandStream;
    OCLRT::IndirectHeap *indirectHeaps[NUM_HEAPS];
    OCLRT::ResidencyContainer residencyContainer;
};

} // namespace L0
