#pragma once

#include "graphics_allocation.h"
#include "memory_manager.h"
#include "xe_common.h"
#include "device.h"

struct _xe_ipc_mem_handle_t {};

struct WddmIpcHandle : _xe_ipc_mem_handle_t {
    int fd;
};

namespace L0 {

class WddmIPCMemoryManager : public IPCMemoryManager {
  public:
    xe_result_t ipcGetMemHandle(const void *ptr, xe_ipc_mem_handle_t *pIpcHandle) override;
    xe_result_t ipcOpenMemHandle(xe_device_handle_t hDevice, xe_ipc_mem_handle_t handle,
                                 xe_ipc_memory_flag_t flags, void **ptr) override;
    xe_result_t ipcCloseMemHandle(const void *ptr) override;
    void *allocateShMemory(size_t size, size_t alignment, std::string &shmFileName) override;
    void freeShMemory(GraphicsAllocation *graphAllocation) override;
};

} // namespace L0
