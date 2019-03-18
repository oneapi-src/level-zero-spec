#pragma once
#include "xe_cmdlist.h"
#include "xe_copy.h"
#include "xe_module.h"
#include "device.h"
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

    OCLRT::LinearStream &getCommandStream() {
        return *commandStream;
    }

    virtual bool initialize(Device *device);

    virtual ~CommandContainer();

  protected:
    void storePrintfBuffer(GraphicsAllocation *printfBuffer);
    Device *device = nullptr;

    GraphicsAllocation *allocation = nullptr;
    GraphicsAllocation *allocationIndirectHeaps[NUM_HEAPS];

    OCLRT::LinearStream *commandStream = nullptr;
    OCLRT::IndirectHeap *indirectHeaps[NUM_HEAPS];
    OCLRT::ResidencyContainer residencyContainer;
    std::vector<GraphicsAllocation *> printfBufferContainer;
};

struct CommandList : public CommandContainer {
    template <typename Type>
    struct Allocator {
        static CommandList *allocate() {
            return new Type;
        }
    };

    virtual xe_result_t close() = 0;
    virtual xe_result_t destroy() = 0;
    virtual xe_result_t appendCommandLists(uint32_t numCommandLists,
                                           xe_command_list_handle_t *phCommandLists) = 0;
    virtual xe_result_t appendEventReset(xe_event_handle_t hEvent) = 0;
    virtual xe_result_t appendExecutionBarrier() = 0;
    virtual xe_result_t appendImageCopyFromMemory(xe_image_handle_t hDstImage,
                                                  xe_image_region_t *pDstRegion,
                                                  const void *srcptr) = 0;
    virtual xe_result_t appendImageCopyToMemory(void *dstptr,
                                                xe_image_handle_t hSrcImage,
                                                xe_image_region_t *pSrcRegion) = 0;
    virtual xe_result_t appendImageCopyRegion(xe_image_handle_t hDstImage,
                                              xe_image_region_t *pDstRegion,
                                              xe_image_handle_t hSrcImage,
                                              xe_image_region_t *pSrcRegion) = 0;
    virtual xe_result_t appendImageCopy(xe_image_handle_t hDstImage,
                                        xe_image_handle_t hSrcImage) = 0;
    virtual xe_result_t appendLaunchFunction(xe_function_handle_t hFunction,
                                             const xe_thread_group_dimensions_t *pDispatchFuncArgs,
                                             xe_event_handle_t hEvent) = 0;
    virtual xe_result_t appendLaunchFunctionIndirect(xe_function_handle_t hFunction,
                                                     const xe_thread_group_dimensions_t *pDispatchArgumentsBuffer,
                                                     xe_event_handle_t hEvent) = 0;
    virtual xe_result_t appendLaunchHostFunction(xe_host_pfn_t pfnHostFunc,
                                                 void *pUserData) = 0;
    virtual xe_result_t appendLaunchMultipleFunctionsIndirect(uint32_t numFunctions,
                                                              const xe_function_handle_t *phFunctions,
                                                              const size_t *pNumLaunchArguments,
                                                              const xe_thread_group_dimensions_t *pLaunchArgumentsBuffer,
                                                              xe_event_handle_t hEvent) = 0;
    virtual xe_result_t appendMemAdvise(xe_device_handle_t hDevice,
                                        const void *ptr,
                                        size_t size,
                                        xe_memory_advice_t advice) = 0;
    virtual xe_result_t appendMemoryCopy(void *dstptr,
                                         const void *srcptr,
                                         size_t size) = 0;
    virtual xe_result_t appendMemorySet(void *ptr,
                                        int value,
                                        size_t size) = 0;
    virtual xe_result_t appendMemoryPrefetch(const void *ptr,
                                             size_t count) = 0;
    virtual xe_result_t appendSignalEvent(xe_event_handle_t hEvent) = 0;
    virtual xe_result_t appendWaitOnEvent(xe_event_handle_t hEvent) = 0;
    virtual xe_result_t getParameter(xe_command_list_parameter_t parameter, uint32_t *value) = 0;
    virtual xe_result_t reserveSpace(size_t size,
                                     void **ptr) = 0;
    virtual xe_result_t reset() = 0;
    virtual xe_result_t resetParameters() = 0;
    virtual xe_result_t setParameter(xe_command_list_parameter_t parameter,
                                     uint32_t value) = 0;

    static CommandList *create(uint32_t productFamily, Device *device);

    static CommandList *fromHandle(xe_command_list_handle_t handle) {
        return static_cast<CommandList *>(handle);
    }

    inline xe_command_list_handle_t toHandle() {
        return this;
    }

  protected:
    virtual ~CommandList() = default;
};

using CommandListAllocatorFn = CommandList *(*)();
extern CommandListAllocatorFn commandListFactory[];

template <uint32_t productFamily, typename CommandListType>
struct CommandListPopulateFactory {
    CommandListPopulateFactory() {
        commandListFactory[productFamily] = CommandList::Allocator<CommandListType>::allocate;
    }
};

} // namespace L0
