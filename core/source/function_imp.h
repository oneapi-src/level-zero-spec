#pragma once
#ifndef FUNCTION_INTERNAL
#error "Don't #include this file directly."
#endif //FUNCTION_INTERNAL

#include "device.h"
#include "function.h"
#include "memory_manager.h"

#include "runtime/program/kernel_info.h"
#include "runtime/command_queue/gpgpu_walker.h"

#include <cassert>
#include <memory>

namespace L0 {

struct GraphicsAllocation;

struct FunctionImp : Function {
    FunctionImp(Module *module);

    virtual ~FunctionImp();

    xe_result_t destroy() override {
        delete this;
        return XE_RESULT_SUCCESS;
    }

    xe_result_t setAttribute(xe_function_set_attribute_t attr,
                             uint32_t value) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t getAttribute(xe_function_get_attribute_t attr,
                             uint32_t *pValue) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t setArgumentValue(uint32_t argIndex,
                                 size_t argSize,
                                 const void *pArgValue) override;

    void setGroupCount(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) override;

    xe_result_t setGroupSize(uint32_t groupSizeX,
                             uint32_t groupSizeY,
                             uint32_t groupSizeZ) override;

    xe_result_t suggestGroupSize(uint32_t globalSizeX,
                                 uint32_t globalSizeY,
                                 uint32_t globalSizeZ,
                                 uint32_t *groupSizeX,
                                 uint32_t *groupSizeY,
                                 uint32_t *groupSizeZ) override;

    const void *getCrossThreadDataHostMem() const override {
        return crossThreadData.weakRef().get();
    }

    uint32_t getCrossThreadDataSize() const override {
        return crossThreadDataSize;
    }

    const std::vector<GraphicsAllocation *> &getResidencyContainer() const override {
        return residencyContainer;
    }

    void getGroupSize(uint32_t &outGroupSizeX, uint32_t &outGroupSizeY, uint32_t &outGroupSizeZ) const override {
        outGroupSizeX = this->groupSize[0];
        outGroupSizeY = this->groupSize[1];
        outGroupSizeZ = this->groupSize[2];
    }

    xe_result_t setArgImmediate(uint32_t argIndex, size_t argSize, const void *argVal);

    xe_result_t setArgBuffer(uint32_t argIndex, size_t argSize, const void *argVal);

    xe_result_t setArgImage(uint32_t argIndex, size_t argSize, const void *argVal);

    virtual void setBufferSurfaceState(uint32_t argIndex, void *address, GraphicsAllocation *alloc) = 0;

    bool initialize(const xe_function_desc_t *desc);

    const void *getPerThreadDataHostMem() const override {
        return perThreadDataForWholeThreadGroup.weakRef().get();
    }

    uint32_t getPerThreadDataSizeForWholeThreadGroup() const override {
        return perThreadDataSizeForWholeThreadGroup;
    }

    uint32_t getPerThreadDataSize() const override {
        return perThreadDataSize;
    }
    uint32_t getThreadsPerThreadGroup() const override {
        return threadsPerThreadGroup;
    }

    uint32_t getThreadExecutionMask() const override {
        return threadExecutionMask;
    }

    GraphicsAllocation *getPrintfBufferAllocation() override {
        return this->printfBuffer.weakRef().get();
    }

    void printPrintfOutput() override;

    void *getSurfaceStateHeap() const {
        return surfaceStateHeapData.weakRef().get();
    }

    uint32_t getSurfaceStateHeapSize() const {
        return surfaceStateHeapDataSize;
    }

    const void *getDynamicStateHeap() const {
        return dynamicStateHeapData.weakRef().get();
    }
    const size_t getDynamicStateHeapSize() const override {
        return dynamicStateHeapDataSize;
    }

    PtrRef<FunctionImmutableData> getImmutableData() const override {
        return funcImmData.weakRef();
    }

    PtrRef<Module> getModule() const {
        return module.weakRef();
    }

  protected:
    void patchWorkgroupSizeInCrossThreadData(uint32_t x, uint32_t y, uint32_t z);

    void createPrintfBuffer();

    PtrRef<FunctionImmutableData> funcImmData = nullptr;
    PtrRef<Module> module = nullptr;

    typedef xe_result_t (FunctionImp::*FunctionArgHandler)(uint32_t argIndex, size_t argSize, const void *argVal);
    std::vector<FunctionImp::FunctionArgHandler> kernelArgHandlers;
    std::vector<GraphicsAllocation *> residencyContainer;

    PtrOwn<GraphicsAllocation> printfBuffer = nullptr;
    PtrOwn<GraphicsAllocation> privateMemAllocation = nullptr; // TODO : move to FunctionImmutableData along with kernelRT

    uint32_t groupSize[3] = {0u, 0u, 0u};
    uint32_t threadsPerThreadGroup = 0u;
    uint32_t threadExecutionMask = 0u;

    PtrOwn<uint8_t[]> crossThreadData = 0;
    uint32_t crossThreadDataSize = 0;

    PtrOwn<uint8_t[]> surfaceStateHeapData = nullptr;
    uint32_t surfaceStateHeapDataSize = 0;

    PtrOwn<uint8_t[]> dynamicStateHeapData = nullptr;
    uint32_t dynamicStateHeapDataSize = 0;

    PtrOwn<uint8_t[]> perThreadDataForWholeThreadGroup = nullptr;
    uint32_t perThreadDataSizeForWholeThreadGroupAllocated = 0; // length of underlying buffer behind perThreadDataForWholeThreadGroup
    uint32_t perThreadDataSizeForWholeThreadGroup = 0u;         // part of perThreadDataForWholeThreadGroup used by current group size
    uint32_t perThreadDataSize = 0u;
};

} // namespace L0
