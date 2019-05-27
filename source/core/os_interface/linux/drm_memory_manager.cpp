#include "os_interface/linux/drm_memory_manager.h"

namespace L0 {

L0MemoryManagerSepecifics *L0MemoryManagerSepecifics::create() {
    return new DrmL0MemoryManagerSepecifics();
}
xe_result_t DrmL0MemoryManagerSepecifics::ipcGetMemHandle(const void *ptr,
                                                          xe_ipc_mem_handle_t *pIpcHandle) {

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

int DrmL0MemoryManagerSepecifics::openShmFile(const char *shmFileName) {
    int shmFileDescriptor;

    shmFileDescriptor = shm_open(shmFileName, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (shmFileDescriptor > 0) {
        struct stat st;
        if (fstat(shmFileDescriptor, &st) == -1) {
            return -1;
        }
        if (getuid() != st.st_uid) {
            return -1;
        }
    }

    return shmFileDescriptor;
}

void *DrmL0MemoryManagerSepecifics::memoryMapShmFile(size_t size, size_t alignment,
                                                     int shmFileDescriptor) {
    void *mapptr;

    // FIXME: add alignemt
    mapptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shmFileDescriptor, 0);
    if (mapptr == MAP_FAILED) {
        return nullptr;
    }
    close(shmFileDescriptor);
    memset((void *)mapptr, 0, size);
    return mapptr;
}

void *DrmL0MemoryManagerSepecifics::allocateShMemory(size_t size, size_t alignment,
                                                     std::string &shmFileName) {
    // void * DrmL0MemoryManagerSepecifics::allocateShMemory(size_t size, size_t alignment){
    char localFileName[255];
    int shmFileDescriptor;
    void *shmBuffer;

    // Create unique file name
    if (snprintf(localFileName, sizeof(localFileName), "/L0_shm.%d%x%d", (int)getuid(),
                 (int)getpid(), DrmL0MemoryManagerSepecifics::shmFileCounter) < 0) {

        assert(0);
        return nullptr;
    }

    // Open a fle in /dev/shm/*
    if ((shmFileDescriptor = openShmFile(localFileName)) < 0) {
        assert(0);
        return nullptr;
    }

    // Set the size of the shm file
    if (ftruncate(shmFileDescriptor, size) != 0) {
        assert(0);
        return nullptr;
    }

    // Map the /dev/shm/* file to memory
    if ((shmBuffer = memoryMapShmFile(size, alignment, shmFileDescriptor)) == nullptr) {
        assert(0);
        return nullptr;
    }
    shmFileName = localFileName;
    DrmL0MemoryManagerSepecifics::shmFileCounter++;
    return shmBuffer;
}

void DrmL0MemoryManagerSepecifics::freeShMemory(GraphicsAllocation *allocation) {

    if (munmap(allocation->getHostAddress(), allocation->getSize())) {
        assert(0);
    }
    if (shm_unlink(allocation->shmFileName.data())) {
        assert(0);
    }
}

} // namespace L0
