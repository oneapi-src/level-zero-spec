#pragma once
#include "cmdlist.h"
#include "device.h"
#include "xe_semaphore.h"

struct _xe_semaphore_handle_t {
};

namespace L0 {

struct Semaphore : public _xe_semaphore_handle_t {
    virtual xe_result_t destroy() = 0;
    virtual xe_result_t queryValue() = 0;
    virtual xe_result_t reset() = 0;

    static Semaphore *fromHandle(xe_semaphore_handle_t handle) {
        return static_cast<Semaphore *>(handle);
    }

    inline xe_semaphore_handle_t toHandle() {
        return this;
    }
};

} // namespace L0
