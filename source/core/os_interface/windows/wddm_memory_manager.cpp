#include "os_interface/windows/wddm_memory_manager.h"

namespace L0 {

IPCMemoryManager *IPCMemoryManager::create() { return new WddmIPCMemoryManager(); }

xe_result_t WddmIPCMemoryManager::ipcGetMemHandle(const void *ptr,
                                                  xe_ipc_mem_handle_t *pIpcHandle) {

    return XE_RESULT_ERROR_UNSUPPORTED;
}
xe_result_t WddmIPCMemoryManager::ipcOpenMemHandle(xe_device_handle_t hDevice,
                                                   xe_ipc_mem_handle_t handle,
                                                   xe_ipc_memory_flag_t flags, void **ptr) {

    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t WddmIPCMemoryManager::ipcCloseMemHandle(const void *ptr) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

void *WddmIPCMemoryManager::allocateShMemory(size_t *size, size_t alignment,
                                             std::string &shmFileName) {
    return nullptr;
}

void WddmIPCMemoryManager::freeShMemory(GraphicsAllocation *allocation) { ; }
} // namespace L0
