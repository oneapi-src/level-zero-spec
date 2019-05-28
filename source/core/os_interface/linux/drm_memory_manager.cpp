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
    void *mapPtr;
    uintptr_t alignedPtr;

    size_t total_size = size + alignment;

    mapPtr = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_SHARED, shmFileDescriptor, 0);
    if (mapPtr == MAP_FAILED) {
        return nullptr;
    }
    close(shmFileDescriptor);
    memset((void *)mapPtr, 0, total_size);

    alignedPtr = reinterpret_cast<uintptr_t>(mapPtr) + alignment;
    alignedPtr -= alignedPtr % alignment;

    // Store the original pointer to facilitate deallocation
    reinterpret_cast<void **>(alignedPtr)[-1] = mapPtr;

    return reinterpret_cast<void *>(alignedPtr);
}

void *DrmL0MemoryManagerSepecifics::allocateShMemory(size_t size, size_t alignment,
                                                     std::string &shmFileName) {
    char localFileName[255];
    int shmFileDescriptor;
    void *shmBuffer;

    const size_t minAlignment = MemoryConstants::allocationAlignment;
    size_t cAlignment = alignUp(std::max(alignment, minAlignment), minAlignment);
    // When size == 0 allocate allocationAlignment
    // It's needed to prevent overlapping pages with user pointers
    size_t cSize = std::max(alignUp(size, minAlignment), minAlignment);

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
    if (ftruncate(shmFileDescriptor, cSize + cAlignment) != 0) {
        assert(0);
        return nullptr;
    }

    // Map the /dev/shm/* file to memory
    if ((shmBuffer = memoryMapShmFile(cSize, cAlignment, shmFileDescriptor)) == nullptr) {
        assert(0);
        return nullptr;
    }
    shmFileName = localFileName;
    DrmL0MemoryManagerSepecifics::shmFileCounter++;
    return shmBuffer;
}

void DrmL0MemoryManagerSepecifics::freeShMemory(GraphicsAllocation *allocation) {

    auto hostAddress = allocation->getHostAddress();
    auto originalAddress = reinterpret_cast<char **>(hostAddress)[-1];

    if (munmap(originalAddress, allocation->getSize())) {
        assert(0);
    }
    if (shm_unlink(allocation->shmFileName.data())) {
        assert(0);
    }
}

} // namespace L0
