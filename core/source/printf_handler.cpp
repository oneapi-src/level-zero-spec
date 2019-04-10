#include "printf_handler.h"
#include "device.h"
#include "graphics_allocation.h"
#include "memory_manager.h"

#include "runtime/kernel/kernel.h"
#include "runtime/program/print_formatter.h"

namespace L0 {

GraphicsAllocation *PrintfHandler::createPrintfBuffer(Device *device) {
    auto allocation = globalMemoryManager->allocateManagedMemory(PrintfHandler::printfBufferSize, MemoryConstants::pageSize64k);
    *reinterpret_cast<uint32_t *>(allocation->getHostAddress()) = PrintfHandler::printfSurfaceInitialDataSize;
    return allocation;
}

void PrintfHandler::printOutput(NEO::Kernel *kernel, GraphicsAllocation *printfBuffer) {
    NEO::PrintFormatter printFormatter(*kernel, *printfBuffer->allocationRT);
    printFormatter.printKernelOutput();

    // reset to initial state after printing
    *reinterpret_cast<uint32_t *>(printfBuffer->getHostAddress()) = PrintfHandler::printfSurfaceInitialDataSize;
}

} // namespace L0
