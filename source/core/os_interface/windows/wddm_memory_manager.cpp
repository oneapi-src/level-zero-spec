#include "os_interface/windows/wddm_memory_manager.h"

namespace L0 {

L0MemoryManagerSepecifics *L0MemoryManagerSepecifics::create() {
    return new WddmL0MemoryManagerSepecifics();
}

xe_result_t WddmL0MemoryManagerSepecifics::ipcGetMemHandle(const void *ptr, xe_ipc_mem_handle_t *pIpcHandle) {

    return XE_RESULT_ERROR_UNSUPPORTED;
}

void *WddmL0MemoryManagerSepecifics::allocateShMemory(size_t size, size_t alignment,
                                                      std::string &shmFileName) {
    return nullptr;
}

void WddmL0MemoryManagerSepecifics::freeShMemory(GraphicsAllocation *allocation) { ; }
} // namespace L0
