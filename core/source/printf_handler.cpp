#include "printf_handler.h"
#include "device.h"
#include "graphics_allocation.h"
#include "memory_manager.h"

namespace L0 {

GraphicsAllocation *PrintfHandler::createPrintfBuffer(Device *device) {
    auto allocation = device->getMemoryManager()->allocateManagedMemory(PrintfHandler::printfBufferSize, MemoryConstants::pageSize64k);
    *reinterpret_cast<uint32_t *>(allocation->getHostAddress()) = PrintfHandler::printfSurfaceInitialDataSize;
    return allocation;
}

} // namespace L0
