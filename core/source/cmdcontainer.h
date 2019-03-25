#pragma once
#include <vector>

struct _xe_command_list_handle_t {
};

namespace OCLRT {
class IndirectHeap;
class LinearStream;
class GraphicsAllocation;

using ResidencyContainer = std::vector<GraphicsAllocation *>;
} // namespace OCLRT

namespace L0 {

struct Device;
struct Function;
struct GraphicsAllocation;

struct CommandContainer : public _xe_command_list_handle_t {
    enum HeapType : uint32_t { // TODO: Remove - after moving ISA to 4GB heap - this is a duplicate of NEO's counterpart
        DYNAMIC_STATE = 0u,
        GENERAL_STATE,
        INDIRECT_OBJECT,
        SURFACE_STATE,
        NUM_HEAPS
    };

    CommandContainer() {
        for (auto &indirectHeap : indirectHeaps) {
            indirectHeap = nullptr;
        }

        for (auto &allocationIndirectHeap : allocationIndirectHeaps) {
            allocationIndirectHeap = nullptr;
        }
    }

    GraphicsAllocation &getAllocation() {
        return *allocation;
    }

    OCLRT::ResidencyContainer &getResidencyContainer() {
        return residencyContainer;
    }

    void addToResidencyContainer(GraphicsAllocation *alloc);

    OCLRT::LinearStream &getCommandStream() {
        return *commandStream;
    }

    std::vector<Function *> &getPrintfFunctionContainer() {
        return this->printfFunctionContainer;
    }

    virtual bool initialize(Device *device);

    virtual ~CommandContainer();

  protected:
    void storePrintfFunction(Function *function);
    Device *device = nullptr;

    GraphicsAllocation *allocation = nullptr;
    GraphicsAllocation *allocationIndirectHeaps[NUM_HEAPS];

    OCLRT::LinearStream *commandStream = nullptr;
    OCLRT::IndirectHeap *indirectHeaps[NUM_HEAPS];
    OCLRT::ResidencyContainer residencyContainer;
    std::vector<Function *> printfFunctionContainer;
};

} // namespace L0
