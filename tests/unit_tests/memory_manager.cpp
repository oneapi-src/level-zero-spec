#include "memory_manager.h"

namespace xe {

struct MemoryManagerImp : public MemoryManager {
    MemoryManagerImp(void *memoryManagerRT)
        : memoryManagerRT(memoryManagerRT) {
    }

    void *memoryManagerRT;
};

MemoryManager *MemoryManager::create(void *memoryManagerRT) {
    return new MemoryManagerImp(memoryManagerRT);
}

} // namespace xe
