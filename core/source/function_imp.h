#pragma once
#ifndef FUNCTION_INTERNAL
#error "Don't #include this file directly."
#endif //FUNCTION_INTERNAL

#include "device.h"
#include "function.h"
#include "memory_manager.h"

#include "runtime/program/kernel_info.h"

#include <cassert>
#include <memory>

namespace OCLRT_temporary {
struct LightweightOclKernel;
} // namespace OCLRT_temporary

namespace L0 {

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
                                 uint32_t *groupSizeZ) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    const void *getCrossThreadDataHostMem() const override {
        return crossThreadData;
    }

    size_t getCrossThreadDataSize() const override {
        return crossThreadDataSize;
    }

    const std::vector<GraphicsAllocation *> &getResidencyContainer() const override {
        return residencyContainer;
    }

    void getGroupSize(uint32_t &outGroupSizeX, uint32_t &outGroupSizeY, uint32_t &outGroupSizeZ) const override {
        outGroupSizeX = this->groupSizeX;
        outGroupSizeY = this->groupSizeY;
        outGroupSizeZ = this->groupSizeZ;
    }

    xe_result_t setArgImmediate(uint32_t argIndex, size_t argSize, const void *argVal);

    xe_result_t setArgBuffer(uint32_t argIndex, size_t argSize, const void *argVal);

    bool initialize(const xe_function_desc_t *desc);

    const void *getIsaHostMem() const override;

    size_t getIsaSize() const override;

    GraphicsAllocation *getIsaGraphicsAllocation() const override {
        return immFuncInfo->isaGraphicsAllocation;
    }

    OCLRT::KernelInfo *getKernelInfo() const {
        return static_cast<OCLRT::KernelInfo *>(immFuncInfo->kernelInfoRT);
    }

    const void *getPerThreadDataHostMem() const override {
        return perThreadData;
    }

    size_t getPerThreadDataSize() const override {
        return perThreadDataSize;
    }

    uint32_t getSimdSize() const override;

    uint32_t getThreadsPerThreadGroup() const override {
        return threadsPerThreadGroup;
    }

    uint32_t getThreadExecutionMask() const override {
        return threadExecutionMask;
    }

    bool getHasBarriers() const override;

    uint32_t getSlmSize() const override;

  protected:
    template <typename T>
    void patchCrossThreadData(uint32_t location, const T &value);

    void patchWorkgroupSizeInCrossThreadData(uint32_t x, uint32_t y, uint32_t z);

    typedef xe_result_t (FunctionImp::*FunctionArgHandler)(uint32_t argIndex, size_t argSize, const void *argVal);

    struct OCLInternal;
    OCLInternal *oclInternals = nullptr;

    OCLRT_temporary::LightweightOclKernel *kernelRT = nullptr;
    ImmutableFunctionInfo *immFuncInfo;
    Module *module = nullptr;

    std::vector<GraphicsAllocation *> residencyContainer;

    uint32_t groupSizeX = 0u;
    uint32_t groupSizeY = 0u;
    uint32_t groupSizeZ = 0u;

    char *crossThreadData = 0;
    uint32_t crossThreadDataSize = 0;

    void *perThreadData = nullptr;
    size_t perThreadDataSize = 0u;

    uint32_t threadsPerThreadGroup = 0u;
    uint32_t threadExecutionMask = 0u;
};

} // namespace L0
