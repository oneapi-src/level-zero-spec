#pragma once

#include "graphics_allocation.h"
#include "memory_manager.h"
#include "xe_common.h"
#include "device.h"

struct _xe_ipc_mem_handle_t {};

struct WddmIpcHande : _xe_ipc_mem_handle_t {
    int fd;
};

namespace L0 {

class WddmL0MemoryManagerSepecifics : public L0MemoryManagerSepecifics {
  public:
    xe_result_t ipcGetMemHandle(const void *ptr, xe_ipc_mem_handle_t *pIpcHandle) override;
    virtual void *allocateShMemory(size_t size, size_t alignment,
                                   std::string &shmFileName) override;
    virtual void freeShMemory(GraphicsAllocation *graphAllocation) override;
};

} // namespace L0
