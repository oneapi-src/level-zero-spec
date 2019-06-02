#pragma once
#ifndef CMD_LIST_INTERNAL
#error "Don't #include this file directly."
#endif // CMD_LIST_INTERNAL

#include "cmdlist.h"

namespace L0 {

struct CommandListImp : public CommandList {
    xe_result_t destroy() override;

    xe_result_t appendMetricMemoryBarrier() override;
    xe_result_t appendMetricTracerMarker(xet_metric_tracer_handle_t hMetricTracer,
                                         uint32_t value) override;
    xe_result_t appendMetricQueryBegin(xet_metric_query_handle_t hMetricQuery) override;
    xe_result_t appendMetricQueryEnd(xet_metric_query_handle_t hMetricQuery,
                                     xe_event_handle_t hCompletionEvent) override;

  protected:
    virtual ~CommandListImp() = default;
};

} // namespace L0
