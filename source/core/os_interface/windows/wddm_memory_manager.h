#pragma once

#include "graphics_allocation.h"
#include "memory_manager.h"
#include "xe_common.h"
#include "device.h"

struct _xe_ipc_mem_handle_t {};

struct WinIpcHande : _xe_ipc_mem_handle_t {
    int fd;
};

namespace L0 {

class WinIPC : public IPC {
  public:
    xe_result_t ipcGetMemHandle(const void *ptr, xe_ipc_mem_handle_t *pIpcHandle) override;
};

} // namespace L0
