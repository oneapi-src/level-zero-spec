#include "runtime/memory_manager/graphics_allocation.h"

namespace L0 {

class OsEvent {
    public:
        OsEvent(void *execEnvRT) : execEnvRT(execEnvRT) {}

        static OsEvent *create(void * execEnvRT);
        virtual bool hostSynchronize(NEO::GraphicsAllocation* allocation,
                                     uint32_t timeout) = 0;
    protected:
        void *execEnvRT = nullptr;
};

} // namespace L0
