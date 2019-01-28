#pragma once

namespace xe {

struct MemoryManager {
    static MemoryManager *create(void *memoryManagerRT);
};

} // namespace xe
