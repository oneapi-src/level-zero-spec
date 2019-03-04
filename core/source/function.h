#pragma once
#include "xe_common.h"
#include "xe_module.h"

#include <vector>

struct _xe_function_handle_t {
};

namespace L0 {

struct GraphicsAllocation;
struct Module;

struct Function : public _xe_function_handle_t {
    virtual xe_result_t destroy() = 0;
    virtual xe_result_t setAttribute(xe_function_set_attribute_t attr,
                                     uint32_t value) = 0;
    virtual xe_result_t getAttribute(xe_function_get_attribute_t attr,
                                     uint32_t *pValue) = 0;
    virtual xe_result_t setArgumentValue(uint32_t argIndex,
                                         size_t argSize,
                                         const void *pArgValue) = 0;
    virtual void setGroupCount(uint32_t groupCountX,
                               uint32_t groupCountY,
                               uint32_t groupCountZ) = 0;
    virtual xe_result_t setGroupSize(uint32_t groupSizeX,
                                     uint32_t groupSizeY,
                                     uint32_t groupSizeZ) = 0;
    virtual xe_result_t suggestGroupSize(uint32_t globalSizeX,
                                         uint32_t globalSizeY,
                                         uint32_t globalSizeZ,
                                         uint32_t *groupSizeX,
                                         uint32_t *groupSizeY,
                                         uint32_t *groupSizeZ) = 0;

    virtual const void *getCrossThreadDataHostMem() const = 0;
    virtual size_t getCrossThreadDataSize() const = 0;
    virtual const std::vector<GraphicsAllocation *> &getResidencyContainer() const = 0;

    static Function *create(Module *module, const xe_function_desc_t *desc);

    virtual void getGroupSize(uint32_t &outGroupSizeX,
                              uint32_t &outGroupSizeY,
                              uint32_t &outGroupSizeZ) const = 0;
    virtual const void *getIsaHostMem() const = 0;
    virtual size_t getIsaSize() const = 0;
    virtual const void *getPerThreadDataHostMem() const = 0;
    virtual size_t getPerThreadDataSize() const = 0;
    virtual uint32_t getSimdSize() const = 0;
    virtual uint32_t getThreadsPerThreadGroup() const = 0;
    virtual uint32_t getThreadExecutionMask() const = 0;
    virtual bool getHasBarriers() const = 0;

    Function() = default;
    Function(const Function &) = delete;
    Function(Function &&) = delete;
    Function &operator=(const Function &) = delete;
    Function &operator=(Function &&) = delete;

    static Function *fromHandle(xe_function_handle_t handle) {
        return static_cast<Function *>(handle);
    }

    inline xe_function_handle_t toHandle() {
        return this;
    }
};

} // namespace L0
