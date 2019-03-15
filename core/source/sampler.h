#pragma once
#include "device.h"
#include "xe_sampler.h"

struct _xe_sampler_handle_t {
};

namespace L0 {

struct Sampler : public _xe_sampler_handle_t {
    template <typename Type>
    struct Allocator {
        static Sampler *allocate() {
            return new Type();
        }
    };

    virtual xe_result_t destroy() = 0;

    static Sampler *create(Device *device);

    static Sampler *fromHandle(xe_sampler_handle_t handle) {
        return static_cast<Sampler *>(handle);
    }

    inline xe_sampler_handle_t toHandle() {
        return this;
    }
};

} // namespace L0
