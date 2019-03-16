#pragma once

#include "runtime/memory_manager/memory_constants.h"

namespace L0 {
struct Device;
struct GraphicsAllocation;

struct PrintfHandler {
    static GraphicsAllocation *createPrintfBuffer(Device *device);

  protected:
    PrintfHandler(const PrintfHandler &) = delete;
    PrintfHandler &operator=(PrintfHandler const &) = delete;
    PrintfHandler() = delete;

    constexpr static size_t printfBufferSize = 4 * MemoryConstants::megaByte;
};

} // namespace L0
