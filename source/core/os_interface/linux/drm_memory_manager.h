#pragma once

#include "runtime/execution_environment/execution_environment.h"
#include "runtime/os_interface/os_interface.h"
#include "runtime/os_interface/linux/os_interface.h"

#include "runtime/os_interface/linux/drm_allocation.h"
#include "runtime/os_interface/linux/drm_buffer_object.h"

#include "drm/i915_drm.h"

#include "graphics_allocation.h"
#include "memory_manager.h"
#include "xe_common.h"
#include "device.h"

struct _xe_ipc_mem_handle_t {};

struct DrmIpcHande : _xe_ipc_mem_handle_t {
    int fd;
};

namespace L0 {

class DrmIPC : public IPC {
  public:
    xe_result_t ipcGetMemHandle(const void *ptr, xe_ipc_mem_handle_t *pIpcHandle) override;
};

} // namespace L0
