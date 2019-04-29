#pragma once

#include "function.h"

#include "runtime/memory_manager/memory_constants.h"

#include <cstdint>

namespace NEO {
class Kernel;
}

namespace L0 {
struct Device;
struct GraphicsAllocation;

struct PrintfHandler {
    static GraphicsAllocation *createPrintfBuffer(Device *device);
    static void printOutput(PtrRef<FunctionImmutableData> function, PtrRef<GraphicsAllocation> printfBuffer, Device *device);

  protected:
    PrintfHandler(const PrintfHandler &) = delete;
    PrintfHandler &operator=(PrintfHandler const &) = delete;
    PrintfHandler() = delete;

    constexpr static size_t printfBufferSize = 4 * MemoryConstants::megaByte;
    constexpr static uint32_t printfSurfaceInitialDataSize = sizeof(uint32_t);
};

} // namespace L0
