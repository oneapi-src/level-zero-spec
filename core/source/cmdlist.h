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
    virtual xe_result_t encodeCommandLists(uint32_t numCommandLists,
                                           xe_command_list_handle_t *phCommandLists) = 0;
    virtual xe_result_t encodeCommands(xe_command_format_t format,
                                       size_t size,
                                       void *pBlob) = 0;
    virtual xe_result_t encodeDispatchFunction(xe_function_handle_t hFunction,
                                               const xe_dispatch_function_arguments_t *pDispatchFuncArgs,
                                               xe_event_handle_t hEvent) = 0;
    virtual xe_result_t encodeDispatchFunctionIndirect(xe_function_handle_t hFunction,
                                                       const xe_dispatch_function_indirect_arguments_t *pDispatchArgumentsBuffer,
                                                       xe_event_handle_t hEvent) = 0;
    virtual xe_result_t encodeDispatchHostFunction(xe_host_pfn_t pfnHostFunc,
                                                   void *pUserData) = 0;
    virtual xe_result_t encodeEventReset(xe_event_handle_t hEvent) = 0;
    virtual xe_result_t encodeExecutionBarrier() = 0;
    virtual xe_result_t encodeImageCopyFromMemory(xe_image_handle_t hDstImage,
                                                  xe_image_region_t *pDstRegion,
                                                  const void *srcptr) = 0;
    virtual xe_result_t encodeImageCopyToMemory(void *dstptr,
                                                xe_image_handle_t hSrcImage,
                                                xe_image_region_t *pSrcRegion) = 0;
    virtual xe_result_t encodeImageCopyRegion(xe_image_handle_t hDstImage,
                                              xe_image_region_t *pDstRegion,
                                              xe_image_handle_t hSrcImage,
                                              xe_image_region_t *pSrcRegion) = 0;
    virtual xe_result_t encodeImageCopy(xe_image_handle_t hDstImage,
                                        xe_image_handle_t hSrcImage) = 0;
    virtual xe_result_t encodeMemAdvise(xe_device_handle_t hDevice,
                                        const void *ptr,
                                        size_t size,
                                        xe_memory_advice_t advice) = 0;
    virtual xe_result_t encodeMemoryCopy(void *dstptr,
                                         const void *srcptr,
                                         size_t size) = 0;
    virtual xe_result_t encodeMemorySet(void *ptr,
                                        int value,
                                        size_t size) = 0;
    virtual xe_result_t encodeMemoryPrefetch(const void *ptr,
                                             size_t count) = 0;
    virtual xe_result_t encodeSemaphoreSignal(xe_semaphore_handle_t hSemaphore,
                                              xe_semaphore_value_t value) = 0;
    virtual xe_result_t encodeSemaphoreWait(xe_semaphore_handle_t hSemaphore,
                                            xe_semaphore_wait_operation_t operation,
                                            xe_semaphore_value_t value) = 0;
    virtual xe_result_t encodeSignalEvent(xe_event_handle_t hEvent) = 0;
    virtual xe_result_t encodeSignalMultipleEvents(uint32_t numEvents,
                                                   xe_event_handle_t *phEvents) = 0;
    virtual xe_result_t encodeWaitOnEvent(xe_event_handle_t hEvent) = 0;
    virtual xe_result_t encodeWaitOnMultipleEvents(uint32_t numEvents,
                                                   xe_event_handle_t *phEvents) = 0;
    virtual xe_result_t getParameter(xe_command_list_parameter_t parameter, uint32_t *value) = 0;
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
