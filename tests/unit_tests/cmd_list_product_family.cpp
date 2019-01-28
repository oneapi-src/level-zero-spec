#include "cmd_list_product_family.h"
#include "igfxfmid.h"

namespace xe {

template <uint32_t productFamily>
xe_result_t CommandListProductFamily<productFamily>::close() {
    return XE_RESULT_SUCCESS;
}

template <uint32_t productFamily>
xe_result_t CommandListProductFamily<productFamily>::destroy() {
    delete this;
    return XE_RESULT_SUCCESS;
}

template <uint32_t productFamily>
xe_result_t CommandListProductFamily<productFamily>::encodeWaitOnEvent(xe_event_handle_t hEvent) {
    return XE_RESULT_SUCCESS;
}

template<uint32_t productFamily>
struct CommandListAllocator {
    static CommandList *allocate() {
        return new CommandListProductFamily<productFamily>;
    }
};

using CommandListAllocatorFn = CommandList *(*)();

CommandListAllocatorFn commandListFactory[IGFX_MAX_PRODUCT] = {};

CommandList *CommandList::create(uint32_t productFamily) {
    commandListFactory[IGFX_SKYLAKE] = CommandListAllocator<IGFX_SKYLAKE>::allocate;

    CommandListAllocatorFn allocator = nullptr;
    if (productFamily < IGFX_MAX_PRODUCT) {
        allocator = commandListFactory[productFamily];
    }

    CommandList *commandList = nullptr;
    if (allocator) {
        commandList = (*allocator)();
    }
    return commandList;
}

} // namespace xe
