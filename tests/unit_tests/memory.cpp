#include "device.h"
#include "graphics_allocation.h"
#include "memory.h"
#include "memory_manager.h"
#include <cassert>

namespace xe {

xe_result_t __xecall
xeSharedMemAlloc(
    xe_mem_allocator_handle_t hMemAllocHandle,
    xe_device_handle_t hDevice,
    xe_device_mem_alloc_flag_t device_flags,
    xe_host_mem_alloc_flag_t host_flags,
    size_t size,
    size_t alignment,
    void **ptr) {
    auto device = Device::fromHandle(hDevice);
    assert(device);
    auto memoryManager = device->getMemoryManager();
    assert(memoryManager);

    auto allocation = memoryManager->allocateManagedMemory(size, alignment);
    assert(allocation);
    *ptr = allocation->getHostAddress();

    return XE_RESULT_SUCCESS;
}

} // namespace xe