#pragma once

#include "runtime/execution_environment/execution_environment.h"
#include "runtime/os_interface/os_interface.h"
#include "runtime/os_interface/linux/os_interface.h"

#include "runtime/os_interface/linux/drm_allocation.h"
#include "runtime/os_interface/linux/drm_buffer_object.h"
#include "runtime/memory_manager/memory_constants.h"
#include "runtime/helpers/aligned_memory.h"

#include "drm/i915_drm.h" //FIXME Most likely not needed.

#include "graphics_allocation.h"
#include "memory_manager.h"
#include "xe_common.h"
#include "device.h"

#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */

struct _xe_ipc_mem_handle_t {};

struct DrmIpcHande : _xe_ipc_mem_handle_t {
    int fd;
};

namespace L0 {

class DrmL0MemoryManagerSepecifics : public L0MemoryManagerSepecifics {
  public:
    xe_result_t ipcGetMemHandle(const void *ptr, xe_ipc_mem_handle_t *pIpcHandle) override;
    virtual void *allocateShMemory(size_t size, size_t alignment,
                                   std::string &shmFileName) override;
    virtual void freeShMemory(GraphicsAllocation *graphAllocation) override;
    static unsigned int shmFileCounter;

  protected:
    int openShmFile(const char *shmFileName);
    void *memoryMapShmFile(size_t size, size_t alignment, int shmFileDescriptor);
};

unsigned int DrmL0MemoryManagerSepecifics::shmFileCounter = 0;

} // namespace L0
