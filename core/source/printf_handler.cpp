#include "printf_handler.h"
#include "device.h"
#include "graphics_allocation.h"
#include "memory_manager.h"

namespace L0 {

GraphicsAllocation *PrintfHandler::createPrintfBuffer(Device *device) {
    return device->getMemoryManager()->allocateManagedMemory(PrintfHandler::printfBufferSize, MemoryConstants::pageSize64k);
}

} // namespace L0
