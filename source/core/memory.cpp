#include "device.h"
#include "graphics_allocation.h"
#include "memory.h"
#include "memory_manager.h"
#include <cassert>

namespace L0 {

xe_result_t hostMemAlloc(xe_host_mem_alloc_flag_t flags, size_t size, size_t alignment,
                         void **ptr) {
    assert(globalMemoryManager);
    *ptr = globalMemoryManager->allocateHostMemory(size, alignment);

    return XE_RESULT_SUCCESS;
}

xe_result_t ipcCloseMemHandle(const void *ptr) {
    auto ipc = IPCMemoryManager::create();
    xe_result_t result =  ipc->ipcCloseMemHandle(ptr);
    delete ipc;
    return result;
}

xe_result_t ipcGetMemHandle(const void *ptr, xe_ipc_mem_handle_t *pIpcHandle){
    auto ipc = IPCMemoryManager::create();
    xe_result_t result = ipc->ipcGetMemHandle(ptr, pIpcHandle);
    delete ipc;
    return result;
}

xe_result_t ipcOpenMemHandle(xe_device_handle_t hDevice, xe_ipc_mem_handle_t handle,
                             xe_ipc_memory_flag_t flags, void **ptr) {
    auto ipc = IPCMemoryManager::create();
    xe_result_t result = ipc->ipcOpenMemHandle(hDevice, handle, flags, ptr);
    delete ipc;
    return result;
}

xe_result_t deviceMemAlloc(xe_device_handle_t hDevice, xe_device_mem_alloc_flag_t flags,
                           size_t size, size_t alignment, void **ptr) {

    auto device = Device::fromHandle(hDevice);
    GraphicsAllocation *allocation;

    assert(device);
    assert(globalMemoryManager);

    /*FIXME: there is no Windows support for l0mms->allocateShMemory. So, until there is one,
    /* use normal allocations without support for IPC.
    */
#if defined(__linux__)
    void *buffer;
    auto l0mms = IPCMemoryManager::create();
    std::string shmFileName;
    // Allocate shred memory (so later can be shared with other proc using IPC)
    buffer = l0mms->allocateShMemory(size, alignment, shmFileName);
    if (buffer == nullptr) {
        return XE_RESULT_ERROR_UNKNOWN;
    }
    allocation = globalMemoryManager->allocateManagedMemoryFromFault(device, buffer, size);
    allocation->shmFileName = shmFileName;
    allocation->alignment = alignment;
    delete l0mms;
#else
    allocation = globalMemoryManager->allocateManagedMemory(device, size, alignment);
#endif

    assert(allocation);
    allocation->allocType = AllocationType::DEVICE;

    *ptr = allocation->getHostAddress();

    return XE_RESULT_SUCCESS;
}

xe_result_t memFree(const void *ptr) {
    assert(globalMemoryManager);
    globalMemoryManager->freeMemory(ptr);

    return XE_RESULT_SUCCESS;
}

xe_result_t memGetAddressRange(const void *ptr, void **pBase, size_t *pSize) {
    assert(globalMemoryManager);
    return globalMemoryManager->getAddressRange(ptr, pBase, pSize);
}

xe_result_t memGetProperties(const void *ptr, xe_memory_allocation_properties_t *pMemProperties) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t sharedMemAlloc(xe_device_handle_t hDevice, xe_device_mem_alloc_flag_t device_flags,
                           xe_host_mem_alloc_flag_t host_flags, size_t size, size_t alignment,
                           void **ptr) {
    auto device = Device::fromHandle(hDevice);
    assert(device);
    assert(globalMemoryManager);

    auto allocation = globalMemoryManager->allocateManagedMemory(device, size, alignment);
    assert(allocation);
    allocation->allocType = AllocationType::SHARED;

    *ptr = allocation->getHostAddress();

    return XE_RESULT_SUCCESS;
}

} // namespace L0
