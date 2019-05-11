#include "os_interface/windows/wddm_memory_manager.h"

namespace L0 {

IPC *IPC::create() { return new WinIPC(); }
xe_result_t WinIPC::ipcGetMemHandle(const void *ptr, xe_ipc_mem_handle_t *pIpcHandle) {

    return XE_RESULT_ERROR_UNSUPPORTED;
}

} // namespace L0
