#include "metric.h"

namespace L0 {

struct MetricGroupImp : MetricGroup {
    xe_result_t getProperties(xet_metric_group_properties_t *pProperties) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t calculateData(uint32_t *pReportCount, uint32_t rawDataSize, uint8_t *pRawData,
                              uint32_t calculatedDataSize,
                              xet_typed_value_t *pCalculatedData) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }
};

struct MetricImp : Metric {
    xe_result_t getProperties(xet_metric_properties_t *pProperties) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }
};

struct MetricTracerImp : MetricTracer {
    xe_result_t readData(uint32_t *pReportCount, uint32_t rawDataSize, uint8_t *pRawData) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    };

    xe_result_t close() override { return XE_RESULT_ERROR_UNSUPPORTED; }
};

struct MetricQueryPoolImp : MetricQueryPool {
    xe_result_t getMetricQuery(uint32_t ordinal,
                               xet_metric_query_handle_t *phMetricQuery) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }
};

struct MetricQueryImp : MetricQuery {
    xe_result_t getData(uint32_t *pReportCount, uint32_t rawDataSize, uint8_t *pRawData) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }
};

xe_result_t metricGroupGetCount(xe_device_handle_t hDevice, uint32_t *pCount) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t metricGroupGet(xe_device_handle_t hDevice, uint32_t ordinal,
                           xet_metric_group_handle_t *phMetricGroup) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t metricGet(xet_metric_group_handle_t hMetricGroup, uint32_t ordinal,
                      xet_metric_handle_t *phMetric) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t metricTracerOpen(xe_device_handle_t hDevice, xet_metric_tracer_desc_t *pDesc,
                             xe_event_handle_t hNotificationEvent,
                             xet_metric_tracer_handle_t *phMetricTracer) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t metricQueryPoolCreate(xe_device_handle_t hDevice, xet_metric_query_pool_desc_t *pDesc,
                                  xet_metric_query_pool_handle_t *phMetricQueryPool) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

xe_result_t metricQueryPoolDestroy(xet_metric_query_pool_handle_t hMetricQueryPool) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

} // namespace L0
