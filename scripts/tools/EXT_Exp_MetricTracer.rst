<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
    t=tags['$t']
    T=t.upper()
%>
:orphan:

.. _ZET_experimental_metric_tracer:

==========================================
Metric Tracer Experimental Extension
==========================================

API
----
* Enumerations
    * ${t}_metric_tracer_exp_version_t

    * ${t}_metric_group_sampling_type_flags_t

    New value ${T}_METRIC_GROUP_SAMPLING_TYPE_FLAG_EXP_TRACER_BASED

    * ${t}_metric_type_t

    New Values
        ${T}_METRIC_TYPE_EVENT_EXP_TIMESTAMP
            Metric type:  have only timestamp and value has no meaning.
        ${T}_METRIC_TYPE_EVENT_EXP_START
            Metric type: the first event of a start/stop event pair.
        ${T}_METRIC_TYPE_EVENT_EXP_END
            Metric type: the second event of a start/stop event pair.
        ${T}_METRIC_TYPE_EVENT_EXP_MONOTONIC_WRAPS_VALUE
            Metric type: value of the event is a monotonic increasing value that can wrap around.


* Structures

    * ${t}_metric_tracer_exp_desc_t
    * ${t}_metric_entry_exp_t

* Functions

    * ${t}MetricTracerCreateExp
    * ${t}MetricTracerDestroyExp
    * ${t}MetricTracerEnableExp
    * ${t}MetricTracerDisableExp
    * ${t}MetricTracerReadDataExp
    * ${t}MetricDecoderCreateExp
    * ${t}MetricDecoderDestroyExp
    * ${t}MetricDecoderGetDecodableMetricsExp
    * ${t}MetricTracerDecodeExp

Metric Tracer
~~~~~~~~~~~~~~~~~~~

Metrics collection model that allows retrieving metrics from events generated in asynchronous fashion. A Metrics Tracer is a software interface that allows
configuration for collection of such metrics. Collected raw data can be converted into parsable data with the use of a decoder object.

Enumeration
-----------

Application can use ${t}MetricGroupGet to enumerate the list of metric groups and ${t}MetricGroupGetProperties to get metric group sampling type
and search for ${T}_METRIC_GROUP_SAMPLING_TYPE_FLAG_EXP_TRACER_BASED.

Configuration
-------------

Use the ${t}ContextActivateMetricGroups API call to configure the device for data collection.

Collection
----------

Metric Tracer based collection mode allows the creation of a tracer object for multiple metric groups than can be collected concurrently. Once metric groups are
activated the tracer can be created using ${t}MetricTracerCreateExp. Tracers are created in disabled state, applications have the flexibility to to enable
(${t}MetricTracerEnableExp) and disable (${t}MetricTracerDisableExp) during workload execution to selectively decide sections on which to collect metrics.
ata can be retrieved from the tracer with ${t}MetricTracerReadDataExp.

Decoding
--------
Metric Tracer collects the data in device specific, raw form that is not suitable for application processing. To convert data into a format that allows
application parsing a decoder object can be used. The decoder object is created with ${t}MetricDecoderCreateExp and data can be converted using
${t}MetricTracerDecodeExp. Each event in the data is associated with a decodable metric, which can be retrieved with ${t}MetricDecoderGetDecodableMetricsExp.



Sample Code
------------

The following pseudo-code demonstrates how to enumerate Tracer based metric groups and collect data.

.. parsed-literal::


    ${t}_metric_group_handle_t     hMetricGroup           = nullptr;
    ${x}_event_handle_t            hNotificationEvent     = nullptr;
    ${x}_event_pool_handle_t       hEventPool             = nullptr;
    ${x}_event_pool_desc_t         eventPoolDesc          = {${X}_STRUCTURE_TYPE_EVENT_POOL_DESC, nullptr, 0, 1};
    ${x}_event_desc_t              eventDesc              = {${X}_STRUCTURE_TYPE_EVENT_DESC};
    ${t}_metric_tracer_exp_handle_t hMetricTracer         = nullptr;
    ${t}_metric_tracer_exp_desc_t tracerDescriptor = { ${T}_STRUCTURE_TYPE_METRIC_TRACER_EXP_DESC, nullptr, 1024};
    ${t}_metric_decoder_exp_handle_t hMetricDecoder       = nullptr;

    // Find the first metric group suitable for Tracer Based collection
    FindMetricGroup(hDevice,  ${T}_METRIC_GROUP_SAMPLING_TYPE_FLAG_EXP_TRACER_BASED, &hMetricGroup );
    
    // Configure the HW
    ${t}ContextActivateMetricGroups( hContext, hDevice, /\* count= \*/ 1, &hMetricGroup );

    // Create notification event
    ${x}EventPoolCreate( hContext, &eventPoolDesc, 1, &hDevice, &hEventPool );
    eventDesc.index  = 0;
    eventDesc.signal = ${X}_EVENT_SCOPE_FLAG_HOST;
    eventDesc.wait   = ${X}_EVENT_SCOPE_FLAG_HOST;
    ${x}EventCreate( hEventPool, &eventDesc, &hNotificationEvent );
    
    // Create tracer
    ${t}MetricTracerCreateExp(hContext, hDevice, 1, &hMetricGroup , &tracerDescriptor, hNotificationEvent, &hMetricTracer);

    // create decoder
    ${t}MetricDecoderCreateExp( hMetricTracer,  &hMetricDecoder);

    // Get decodable metrics
    uint32_t numDecodableMetrics = 0;
    ${t}MetricDecoderGetDecodableMetricsExp(hMetricDecoder, &numDecodableMetrics, nullptr);
    std::vector<zet_metric_handle_t>decodableMetrics(numDecodableMetrics);
    ${t}MetricDecoderGetDecodableMetricsExp(hMetricDecoder, &numDecodableMetrics, decodableMetrics.data());

    // Enable the tracer
    ${t}MetricTracerEnableExp(hMetricTracer, true);

    // Run your workload
    Workload(hDevice);

    // Wait for data, optional in this example
    ${x}EventHostSynchronize( hNotificationEvent, 1000 /\*timeout\*/ );
    // reset the event if it fired

    // Read raw data
    size_t rawDataSize = 0;
    ${t}MetricTracerReadDataExp(hMetricTracer, &rawDataSize, nullptr);
    std::vector<uint8_t>rawData(rawDataSize);
    ${t}MetricTracerReadDataExp(hMetricTracer, &rawDataSize, rawData.data());

    // decode
    uint32_t totalNumEntries = 0;
    uint32_t setCount = 0;
    ${t}MetricTracerDecodeExp(hMetricDecoder,  &rawDataSize, rawData.data(), numDecodableMetrics, decodableMetrics.data(), &setCount, nullptr, &totalNumEntries, nullptr);
    std::vector<ze_metric_entry_exp_t> decodedEntries(totalNumEntries)
    std::vector<uint32_t> metricEntriesCountPerSet(setCount);
    ${t}MetricTracerDecodeExp(hMetricDecoder,  &rawDataSize, rawData.data(), numDecodableMetrics, decodableMetrics.data(), &setCount, metricEntriesCountPerSet.data(), &totalNumEntries, decodedEntries.data());

  uint32_t setEntryStart = 0;
    for (uint8_t setIndex = 0; setIndex < setCount; setIndex++) {
        for (uint32_t index = setEntryStart;  index < metricEntriesCountPerSet[setIndex]; index++) {
            ${t}_metric_entry_exp_t metricEntry = decodedEntries[index];
            ${t}_metric_properties_t metricProperties = {};
            ${t}MetricGetProperties(decodableMetrics[metricEntry.metricIndex], &metricProperties);
            std::cout << "Component: " << metricProperties.component ". Decodable metric name: " << metricProperties.name;
            switch (metricProperties.resultType) {
            case ${T}_VALUE_TYPE_UINT8:
            case ${T}_VALUE_TYPE_UINT16:
            case ${T}_VALUE_TYPE_UINT32:
                std::cout << ".\t value: " << metricEntry.value.ui32 << std::endl;
            break;
            case ${T}_VALUE_TYPE_UINT64:
                std::cout << ".\t value: " << metricEntry.value.ui64 << std::endl;
            break;
            case ${T}_VALUE_TYPE_FLOAT32:
                std::cout << ".\t value: " << metricEntry.value.fp32 << std::endl;
            break;
            case ${T}_VALUE_TYPE_FLOAT64:
                std::cout << ".\t value: " << metricEntry.value.fp64 << std::endl;
            break;
            case ${T}_VALUE_TYPE_BOOL8:
                if( metricEntry.value.b8 ){
                    std::cout << ".\t value: true" << std::endl;
                else
                    std::cout << ".\t value: false" << std::endl;
                }
            break;
            default:
            break;
            }
            
            setEntryStart = metricEntriesCountPerSet[setIndex];
        }
    }

    // Close metric tracer
    ${t}MetricTracerDisableExp(hMetricTracer, true);
    ${t}MetricDecoderDestroyExp(hMetricDecoder);
    ${t}MetricTracerDestroyExp(hMetricTracer);
    ${x}EventDestroy( hNotificationEvent );
    ${x}EventPoolDestroy( hEventPool );

    // Clean device configuration and free memory
    ${t}ContextActivateMetricGroups( hContext, hDevice, 0, nullptr );
