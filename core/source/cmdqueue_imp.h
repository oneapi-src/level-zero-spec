#pragma once
#include "cmdqueue.h"

#include "substream.h"

#include <vector>

namespace OCLRT {
class LinearStream;
}

namespace L0 {
struct CommandList;
struct Function;
struct GraphicsAllocation;

struct CommandQueueImp : public CommandQueue {
    static constexpr size_t defaultQueueCmdBufferSize = 16384u;

    CommandQueueImp(Device *device, void *csrRT)
        : device(device),
          csrRT(csrRT),
          allocation(nullptr),
          commandStream(nullptr) {
    }

    xe_result_t destroy() override;

    xe_result_t synchronize(uint32_t timeout) override;

    void initialize();

    Substream getCmdSubstream(size_t size);

  protected:
    void processResidency(CommandList *);
    void processCoherency(CommandList *);
    void submitBatchBuffer(size_t offset);

    xe_result_t synchronizeByPollingForTaskCount(uint32_t timeout);
    virtual void dispatchTaskCountWrite(bool flushDataCache) = 0;

    void printFunctionsPrintfOutput();

    Device *device;
    void *csrRT;
    GraphicsAllocation *allocation;
    OCLRT::LinearStream *commandStream;
    uint32_t taskCount = 0;
    std::vector<Function *> printfFunctionContainer;
};

} // namespace L0
