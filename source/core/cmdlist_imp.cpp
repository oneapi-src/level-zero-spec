#define CMD_LIST_INTERNAL
#include "cmdlist_imp.h"
#undef CMD_LIST_INTERNAL
#include "device.h"
#include "graphics_allocation.h"
#include "igfxfmid.h"
#include "memory_manager.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/indirect_heap/indirect_heap.h"

#include <algorithm>
#include <cassert>

namespace L0 {

CommandListAllocatorFn commandListFactory[IGFX_MAX_PRODUCT] = {};

xe_result_t CommandListImp::destroy() {
    delete this;
    return XE_RESULT_SUCCESS;
}

xe_result_t CommandListImp::appendMetricMemoryBarrier() { return XE_RESULT_ERROR_UNSUPPORTED; }

xe_result_t CommandListImp::appendMetricTracerMarker(xet_metric_tracer_handle_t hMetricTracer,
                                                     uint32_t value) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t CommandListImp::appendMetricQueryBegin(xet_metric_query_handle_t hMetricQuery) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t CommandListImp::appendMetricQueryEnd(xet_metric_query_handle_t hMetricQuery,
                                                 xe_event_handle_t hCompletionEvent) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

CommandList *CommandList::create(uint32_t productFamily, Device *device) {
    CommandListAllocatorFn allocator = nullptr;
    if (productFamily < IGFX_MAX_PRODUCT) {
        allocator = commandListFactory[productFamily];
    }

    CommandListImp *commandList = nullptr;
    if (allocator) {
        commandList = static_cast<CommandListImp *>((*allocator)());

        commandList->initialize(device);
    }
    return commandList;
}

} // namespace L0
