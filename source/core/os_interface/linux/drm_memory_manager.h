#pragma once

#include "runtime/memory_manager/memory_constants.h"
#include "runtime/helpers/aligned_memory.h"

#include "graphics_allocation.h"
#include "memory_manager.h"
#include "xe_common.h"
#include "device.h"

#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>    /* For O_* constants */
#include <sys/types.h>
#include <unistd.h>

struct _xe_ipc_mem_handle_t {};

struct DrmIpcHandle : _xe_ipc_mem_handle_t {
    size_t alignment;
    size_t size;
    char shmFileName[255];
};

namespace L0 {

class DrmIPCMemoryManager : public IPCMemoryManager {
  public:
    xe_result_t ipcGetMemHandle(const void *ptr, xe_ipc_mem_handle_t *pIpcHandle) override;
    xe_result_t ipcOpenMemHandle(xe_device_handle_t hDevice, xe_ipc_mem_handle_t handle,
                                 xe_ipc_memory_flag_t flags, void **ptr) override;
    xe_result_t ipcCloseMemHandle(const void *ptr) override;
    void *allocateShMemory(size_t size, size_t alignment, std::string &shmFileName) override;
    void freeShMemory(GraphicsAllocation *graphAllocation) override;

    static unsigned int shmFileCounter;

  protected:
    int openShmFile(const char *shmFileName, bool mustExist);
    void *memoryMapShmFile(size_t size, size_t alignment, int shmFileDescriptor);
};

unsigned int DrmIPCMemoryManager::shmFileCounter = 0;

} // namespace L0
