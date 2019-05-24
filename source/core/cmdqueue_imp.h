#pragma once
#include "cmdqueue.h"

#include "substream.h"
#include "runtime/command_stream/submissions_aggregator.h"
#include "runtime/memory_manager/memory_constants.h"
#include "runtime/command_stream/submissions_aggregator.h"

#include <vector>

namespace NEO {
class LinearStream;
}

namespace L0 {
struct CommandList;
struct Function;
struct GraphicsAllocation;

struct CommandQueueImp : public CommandQueue {
    static constexpr size_t defaultQueueCmdBufferSize = 16384u;

    CommandQueueImp(Device *device, void *csrRT)
        : device(device), csrRT(csrRT), allocation(nullptr), commandStream(nullptr) {}

    xe_result_t destroy() override;

    xe_result_t synchronize(uint32_t timeout) override;

    void initialize();

    Device *getDevice() { return device; }

    Substream getCmdSubstream(size_t size);

    virtual void makeCoherent(NEO::GraphicsAllocation &gfxAllocation) {}
    virtual bool flush(NEO::BatchBuffer &batchBuffer, NEO::ResidencyContainer &allocationsForResidency) { return false;}

  protected:
    void processCoherency(CommandList *);
    void submitBatchBuffer(size_t offset);

    xe_result_t synchronizeByPollingForTaskCount(uint32_t timeout);
    virtual void dispatchTaskCountWrite(bool flushDataCache) = 0;

    void printFunctionsPrintfOutput();

    Device *device;
    void *csrRT;
    GraphicsAllocation *allocation;
    NEO::LinearStream *commandStream;
    uint32_t taskCount = 0;
    std::vector<Function *> printfFunctionContainer;
};

} // namespace L0
