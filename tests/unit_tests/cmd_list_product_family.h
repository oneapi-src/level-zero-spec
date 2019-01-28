#pragma once
#include "cmd_list.h"

namespace xe {

template <typename Type>
struct CommandListAllocator {
    static CommandList *allocate() {
        return new Type;
    }
};

using CommandListAllocatorFn = CommandList *(*)();
extern CommandListAllocatorFn commandListFactory[];

template <uint32_t productFamily, typename CommandListType>
struct CommandListProductFamilyPopulateFactory {
    CommandListProductFamilyPopulateFactory() {
        commandListFactory[productFamily] = CommandListAllocator<CommandListType>::allocate;
    }
};
} // namespace xe
