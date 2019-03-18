#pragma once
#include "cmdqueue.h"

namespace OCLRT {
class LinearStream;
}

namespace L0 {
struct CommandList;
struct GraphicsAllocation;

struct CommandQueueImp : public CommandQueue {
    CommandQueueImp(Device *device, void *csrRT)
        : device(device),
          csrRT(csrRT),
          allocation(nullptr),
          commandStream(nullptr) {
    }

    xe_result_t destroy() override;

    xe_result_t synchronize(uint32_t timeout) override;

    void initialize();

  protected:
    void processResidency(CommandList *);
    void processCoherency(CommandList *);
    void submitBatchBuffer();

    xe_result_t synchronizeByPollingForTaskCount(uint32_t timeout);
    virtual void dispatchTaskCountWrite(bool flushDataCache) = 0;

    Device *device;
    void *csrRT;
    GraphicsAllocation *allocation;
    OCLRT::LinearStream *commandStream;
    uint32_t taskCount = 0;
};

} // namespace L0
