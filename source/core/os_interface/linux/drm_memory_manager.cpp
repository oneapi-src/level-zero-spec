#include "os_interface/linux/drm_memory_manager.h"

namespace L0 {

IPC *IPC::create() { return new DrmIPC(); }
xe_result_t DrmIPC::ipcGetMemHandle(const void *ptr, xe_ipc_mem_handle_t *pIpcHandle) {

    GraphicsAllocation *allocation = globalMemoryManager->findGraphicsAllocation(ptr);
    int gem_handle =
        static_cast<NEO::DrmAllocation *>(allocation->allocationRT)->getBO()->peekHandle();
    auto drm =
        static_cast<NEO::ExecutionEnvironment *>(allocation->getDevice()->getExecEnvironment())
            ->osInterface->get()
            ->getDrm();
    drm_prime_handle prime_handle = {0, 0, 0};
    prime_handle.handle = gem_handle;

    auto ret = drm->ioctl(DRM_IOCTL_PRIME_HANDLE_TO_FD, &prime_handle);
    if (ret != 0) {
        int err = errno; // Do something with errno?
        assert(0);
        return XE_RESULT_ERROR_UNKNOWN;
    }

    *pIpcHandle = static_cast<xe_ipc_mem_handle_t>(malloc(sizeof(DrmIpcHande)));
    assert(*pIpcHandle);

    // FIXME Need to associate the pIpcHandle with the Graphics allocation so it is freed as
    // xe_memFree()
    static_cast<DrmIpcHande *>(*pIpcHandle)->fd = prime_handle.fd;

    return XE_RESULT_SUCCESS;
}

} // namespace L0
