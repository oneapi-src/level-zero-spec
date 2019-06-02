#pragma once
#include "xet_api.h"

struct _xet_metric_group_handle_t {};
struct _xet_metric_handle_t {};
struct _xet_metric_tracer_handle_t {};
struct _xet_metric_query_pool_handle_t {};
struct _xet_metric_query_handle_t {};

namespace L0 {

struct MetricGroup : _xet_metric_group_handle_t {
    virtual xe_result_t getProperties(xet_metric_group_properties_t *pProperties) = 0;

    virtual xe_result_t calculateData(uint32_t *pReportCount, uint32_t rawDataSize,
                                      uint8_t *pRawData, uint32_t calculatedDataSize,
                                      xet_typed_value_t *pCalculatedData) = 0;

    static MetricGroup *fromHandle(xet_metric_group_handle_t handle) {
        return static_cast<MetricGroup *>(handle);
    }

    inline xet_metric_group_handle_t toHandle() { return this; }
};

struct Metric : _xet_metric_handle_t {
    virtual xe_result_t getProperties(xet_metric_properties_t *pProperties) = 0;

    static Metric *fromHandle(xet_metric_handle_t handle) { return static_cast<Metric *>(handle); }

    inline xet_metric_handle_t toHandle() { return this; }
};

struct MetricTracer : _xet_metric_tracer_handle_t {
    virtual xe_result_t readData(uint32_t *pReportCount, uint32_t rawDataSize,
                                 uint8_t *pRawData) = 0;

    virtual xe_result_t close() = 0;

    static MetricTracer *fromHandle(xet_metric_tracer_handle_t handle) {
        return static_cast<MetricTracer *>(handle);
    }

    inline xet_metric_tracer_handle_t toHandle() { return this; }
};

struct MetricQueryPool : _xet_metric_query_pool_handle_t {
    virtual xe_result_t getMetricQuery(uint32_t ordinal,
                                       xet_metric_query_handle_t *phMetricQuery) = 0;

    static MetricQueryPool *fromHandle(xet_metric_query_pool_handle_t handle) {
        return static_cast<MetricQueryPool *>(handle);
    }

    inline xet_metric_query_pool_handle_t toHandle() { return this; }
};

struct MetricQuery : _xet_metric_query_handle_t {

    virtual xe_result_t getData(uint32_t *pReportCount, uint32_t rawDataSize,
                                uint8_t *pRawData) = 0;

    static MetricQuery *fromHandle(xet_metric_query_handle_t handle) {
        return static_cast<MetricQuery *>(handle);
    }

    inline xet_metric_query_handle_t toHandle() { return this; }
};

xe_result_t metricGroupGetCount(xe_device_handle_t hDevice, uint32_t *pCount);

xe_result_t metricGroupGet(xe_device_handle_t hDevice, uint32_t ordinal,
                           xet_metric_group_handle_t *phMetricGroup);

xe_result_t metricGet(xet_metric_group_handle_t hMetricGroup, uint32_t ordinal,
                      xet_metric_handle_t *phMetric);

xe_result_t metricTracerOpen(xe_device_handle_t hDevice, xet_metric_tracer_desc_t *pDesc,
                             xe_event_handle_t hNotificationEvent,
                             xet_metric_tracer_handle_t *phMetricTracer);

xe_result_t metricQueryPoolCreate(xe_device_handle_t hDevice, xet_metric_query_pool_desc_t *pDesc,
                                  xet_metric_query_pool_handle_t *phMetricQueryPool);

xe_result_t metricQueryPoolDestroy(xet_metric_query_pool_handle_t hMetricQueryPool);

} // namespace L0
