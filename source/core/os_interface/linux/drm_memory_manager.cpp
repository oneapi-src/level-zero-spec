#include "os_interface/linux/drm_memory_manager.h"

namespace L0 {

L0MemoryManagerSepecifics *L0MemoryManagerSepecifics::create() {
    return new DrmL0MemoryManagerSepecifics();
}

xe_result_t DrmL0MemoryManagerSepecifics::ipcGetMemHandle(const void *ptr,
                                                          xe_ipc_mem_handle_t *pIpcHandle) {

    GraphicsAllocation *allocation = globalMemoryManager->findGraphicsAllocation(ptr);

    DrmIpcHandle *handle = new DrmIpcHandle;
    strncpy(handle->shmFileName, allocation->shmFileName.c_str(), allocation->shmFileName.length () + 1);
    handle->alignment = allocation->alignment;
    handle->size = allocation->getSize();

    // FIXME Need to associate the pIpcHandle with the Graphics allocation so it is freed as
    // xe_memFree()
    *pIpcHandle = handle;

    return XE_RESULT_SUCCESS;
}

xe_result_t DrmL0MemoryManagerSepecifics::ipcOpenMemHandle(xe_device_handle_t hDevice,
                                                           xe_ipc_mem_handle_t handle,
                                                           xe_ipc_memory_flag_t flags, void **ptr) {

    /*NOTE: hDevice and flags are unused*/

    const char *shmFileName = static_cast<DrmIpcHandle *>(handle)->shmFileName;
    size_t alignment = static_cast<DrmIpcHandle *>(handle)->alignment;
    size_t size = static_cast<DrmIpcHandle *>(handle)->size;
    int shmFileDescriptor = -1;
    void *shmBuffer;

    const size_t minAlignment = MemoryConstants::allocationAlignment;
    size_t cAlignment = alignUp(std::max(alignment, minAlignment), minAlignment);
    // When size == 0 allocate allocationAlignment
    // It's needed to prevent overlapping pages with user pointers
    size_t cSize = std::max(alignUp(size, minAlignment), minAlignment);

    shmFileDescriptor = openShmFile(shmFileName, true);
    if (shmFileDescriptor < 0) {
        assert(0);
        return XE_RESULT_ERROR_UNKNOWN;
    }

    shmBuffer = memoryMapShmFile(cSize, cAlignment, shmFileDescriptor);
    if (nullptr == shmBuffer) {
        assert(0);
        return XE_RESULT_ERROR_UNKNOWN;
    }

    *ptr = shmBuffer;

    return XE_RESULT_SUCCESS;
}

xe_result_t DrmL0MemoryManagerSepecifics::ipcCloseMemHandle(const void *ptr) {

    void *ptrCopy = const_cast<void *>(ptr);
    void *realAddress = reinterpret_cast<void **>(ptrCopy)[-1];
    uintptr_t sizeStoredAddress =
        reinterpret_cast<uintptr_t>(ptrCopy) - (sizeof(void *) + sizeof(size_t));
    size_t size = *(reinterpret_cast<size_t *>(sizeStoredAddress));

    if (munmap(realAddress, size)) {
        assert(0);
        return XE_RESULT_ERROR_UNKNOWN;
    }

    return XE_RESULT_SUCCESS;
}

int DrmL0MemoryManagerSepecifics::openShmFile(const char *shmFileName, bool mustExist) {
    int shmFileDescriptor;

    //ipcOpenMemHandle must make sure the file already exixts, becuse the filename
    // may be corrupt and shm_open will NOT fail.
    if (mustExist){
        shmFileDescriptor = shm_open(shmFileName, O_RDWR | O_CREAT| O_EXCL, S_IRUSR | S_IWUSR);
        if (shmFileDescriptor > 0)  {
            if (shm_unlink(shmFileName)) {
                assert(0);
            }
            return -1;
        }
    }

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
    else{
        return -1;
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
        assert(0);
        return nullptr;
    }
    close(shmFileDescriptor);

    alignedPtr = reinterpret_cast<uintptr_t>(mapPtr) + alignment;
    alignedPtr -= alignedPtr % alignment;

    // Store the original pointer to facilitate deallocation
    reinterpret_cast<void **>(alignedPtr)[-1] = mapPtr;

    // Also store the size, needed at ipcCloseMemHandle()
    uintptr_t sizeStoredAddress =
        reinterpret_cast<uintptr_t>(alignedPtr) - (sizeof(void *) + sizeof(size_t));
    *(reinterpret_cast<size_t *>(sizeStoredAddress)) = total_size;

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

    if (snprintf(localFileName, sizeof(localFileName), "/L0_shm.%d%x%d", (int)getuid(),
                 (int)getpid(), DrmL0MemoryManagerSepecifics::shmFileCounter) < 0) {

        assert(0);
        return nullptr;
    }

    // Open a fle in /dev/shm/*
    shmFileDescriptor = openShmFile(localFileName, false);
    if (shmFileDescriptor < 0) {
        assert(0);
        return nullptr;
    }

    // Set the size of the shm file
    if (ftruncate(shmFileDescriptor, cSize + cAlignment) != 0) {
        assert(0);
        return nullptr;
    }

    // Map the /dev/shm/* file to memory
    shmBuffer = memoryMapShmFile(cSize, cAlignment, shmFileDescriptor);
    if (nullptr == shmBuffer) {
        assert(0);
        return nullptr;
    }
    shmFileName = localFileName;
    DrmL0MemoryManagerSepecifics::shmFileCounter++;
    return shmBuffer;
}

void DrmL0MemoryManagerSepecifics::freeShMemory(GraphicsAllocation *allocation) {

    auto userAddress = allocation->getHostAddress();
    auto realAddress = reinterpret_cast<char **>(userAddress)[-1];
    uintptr_t sizeStoredAddress =
        reinterpret_cast<uintptr_t>(userAddress) - (sizeof(void *) + sizeof(size_t));
    size_t size = *(reinterpret_cast<size_t *>(sizeStoredAddress));

    if (munmap(reinterpret_cast<void *>(realAddress), size)) {
        assert(0);
    }

    if (shm_unlink(allocation->shmFileName.data())) {
        assert(0);
    }
}

} // namespace L0
