
:orphan:

.. _ZET_experimental_metric_tracer:

==========================================
Metric Tracer Experimental Extension
==========================================

API
----
* Enumerations
    * :ref:`zet-metric-tracer-exp-version-t`

    * :ref:`zet-metric-group-sampling-type-flags-t`

    New value :ref:`ZET_METRIC_GROUP_SAMPLING_TYPE_FLAG_EXP_TRACER_BASED <zet-metric-group-sampling-type-flags-t>`

    * :ref:`zet-metric-type-t`

    New Values
        :ref:`ZET_METRIC_TYPE_EVENT_EXP_TIMESTAMP <zet-metric-type-t>`
            Metric type:  have only timestamp and value has no meaning.
        :ref:`ZET_METRIC_TYPE_EVENT_EXP_START <zet-metric-type-t>`
            Metric type: the first event of a start/stop event pair.
        :ref:`ZET_METRIC_TYPE_EVENT_EXP_END <zet-metric-type-t>`
            Metric type: the second event of a start/stop event pair.
        :ref:`ZET_METRIC_TYPE_EVENT_EXP_MONOTONIC_WRAPS_VALUE <zet-metric-type-t>`
            Metric type: value of the event is a monotonic increasing value that can wrap around.


* Structures

    * :ref:`zet-metric-tracer-exp-desc-t`
    * :ref:`zet-metric-entry-exp-t`

* Functions

    * :ref:`zetMetricTracerCreateExp`
    * :ref:`zetMetricTracerDestroyExp`
    * :ref:`zetMetricTracerEnableExp`
    * :ref:`zetMetricTracerDisableExp`
    * :ref:`zetMetricTracerReadDataExp`
    * :ref:`zetMetricDecoderCreateExp`
    * :ref:`zetMetricDecoderDestroyExp`
    * :ref:`zetMetricDecoderGetDecodableMetricsExp`
    * :ref:`zetMetricTracerDecodeExp`

Metric Tracer
~~~~~~~~~~~~~~~~~~~

Metrics collection model that allows retrieving metrics from events generated in asynchronous fashion. A Metrics Tracer is a software interface that allows
configuration for collection of such metrics. Collected raw data can be converted into parsable data with the use of a decoder object.

Enumeration
-----------

Application can use :ref:`zetMetricGroupGet` to enumerate the list of metric groups and :ref:`zetMetricGroupGetProperties` to get metric group sampling type
and search for :ref:`ZET_METRIC_GROUP_SAMPLING_TYPE_FLAG_EXP_TRACER_BASED <zet-metric-group-sampling-type-flags-t>`\.

Configuration
-------------

Use the :ref:`zetContextActivateMetricGroups` API call to configure the device for data collection.
 
Collection
----------

Metric Tracer based collection mode allows the creation of a tracer object for multiple metric groups than can be collected concurrently. Once metric groups are 
activated the tracer can be created using :ref:`zetMetricTracerCreateExp`\. Tracers are created in disabled state, applications have the flexibility to to enable 
(:ref:`zetMetricTracerEnableExp`\) and disable (:ref:`zetMetricTracerDisableExp`\) during workload execution to selectively decide sections on which to collect metrics. 
ata can be retrieved from the tracer with :ref:`zetMetricTracerReadDataExp`\.

Decoding
--------
Metric Tracer collects the data in device specific, raw form that is not suitable for application processing. To convert data into a format that allows 
application parsing a decoder object can be used. The decoder object is created with :ref:`zetMetricDecoderCreateExp` and data can be converted using
:ref:`zetMetricTracerDecodeExp`\. Each event in the data is associated with a decodable metric, which can be retrieved with :ref:`zetMetricDecoderGetDecodableMetricsExp`\.



Sample Code
------------

The following pseudo-code demonstrates how to enumerate Tracer based metric groups and collect data.

.. parsed-literal::


    zet_metric_group_handle_t     hMetricGroup           = nullptr;
    ze_event_handle_t            hNotificationEvent     = nullptr;
    ze_event_pool_handle_t       hEventPool             = nullptr;
    :ref:`ze-event-pool-desc-t`         eventPoolDesc          = {:ref:`ZE_STRUCTURE_TYPE_EVENT_POOL_DESC <ze-structure-type-t>`\, nullptr, 0, 1};
    :ref:`ze-event-desc-t`              eventDesc              = {:ref:`ZE_STRUCTURE_TYPE_EVENT_DESC <ze-structure-type-t>`\};
    zet_metric_tracer_exp_handle_t hMetricTracer         = nullptr; 
    :ref:`zet-metric-tracer-exp-desc-t` tracerDescriptor = { :ref:`ZET_STRUCTURE_TYPE_METRIC_TRACER_EXP_DESC <zet-structure-type-t>`\, nullptr, 1024};
    zet_metric_decoder_exp_handle_t hMetricDecoder       = nullptr;

    // Find the first metric group suitable for Tracer Based collection
    FindMetricGroup(hDevice,  :ref:`ZET_METRIC_GROUP_SAMPLING_TYPE_FLAG_EXP_TRACER_BASED <zet-metric-group-sampling-type-flags-t>`\, &hMetricGroup );
    
    // Configure the HW
    :ref:`zetContextActivateMetricGroups`\( hContext, hDevice, /\* count= \*/ 1, &hMetricGroup );

    // Create notification event
    :ref:`zeEventPoolCreate`\( hContext, &eventPoolDesc, 1, &hDevice, &hEventPool );
    eventDesc.index  = 0;
    eventDesc.signal = :ref:`ZE_EVENT_SCOPE_FLAG_HOST <ze-event-scope-flags-t>`\;
    eventDesc.wait   = :ref:`ZE_EVENT_SCOPE_FLAG_HOST <ze-event-scope-flags-t>`\;
    :ref:`zeEventCreate`\( hEventPool, &eventDesc, &hNotificationEvent );
    
    // Create tracer
    :ref:`zetMetricTracerCreateExp`\(hContext, hDevice, 1, &hMetricGroup , &tracerDescriptor, hNotificationEvent, &hMetricTracer);

    // create decoder
    :ref:`zetMetricDecoderCreateExp`\( hMetricTracer,  &hMetricDecoder);

    // Get decodable metrics
    uint32_t numDecodableMetrics = 0;
    :ref:`zetMetricDecoderGetDecodableMetricsExp`\(hMetricDecoder, &numDecodableMetrics, nullptr);
    std::vector<zet_metric_handle_t>decodableMetrics(numDecodableMetrics);
    :ref:`zetMetricDecoderGetDecodableMetricsExp`\(hMetricDecoder, &numDecodableMetrics, decodableMetrics.data());

    // Enable the tracer
    :ref:`zetMetricTracerEnableExp`\(hMetricTracer, true);

    // Run your workload
    Workload(hDevice);

    // Wait for data, optional in this example
    :ref:`zeEventHostSynchronize`\( hNotificationEvent, 1000 /\*timeout\*/ );
    // reset the event if it fired

    // Read raw data
    size_t rawDataSize = 0;
    :ref:`zetMetricTracerReadDataExp`\(hMetricTracer, &rawDataSize, nullptr);
    std::vector<uint8_t>rawData(rawDataSize);
    :ref:`zetMetricTracerReadDataExp`\(hMetricTracer, &rawDataSize, rawData.data());

    // decode
    uint32_t totalNumEntries = 0;
    uint32_t setCount = 0;
    :ref:`zetMetricTracerDecodeExp`\(hMetricDecoder,  &rawDataSize, rawData.data(), numDecodableMetrics, decodableMetrics.data(), &setCount, nullptr, &totalNumEntries, nullptr);
    std::vector<ze_metric_entry_exp_t> decodedEntries(totalNumEntries)
    std::vector<uint32_t> metricEntriesCountPerSet(setCount);
    :ref:`zetMetricTracerDecodeExp`\(hMetricDecoder,  &rawDataSize, rawData.data(), numDecodableMetrics, decodableMetrics.data(), &setCount, metricEntriesCountPerSet.data(), &totalNumEntries, decodedEntries.data());

  uint32_t setEntryStart = 0;
    for (uint8_t setIndex = 0; setIndex < setCount; setIndex++) {
        for (uint32_t index = setEntryStart;  index < metricEntriesCountPerSet[setIndex]; index++) {
            :ref:`zet-metric-entry-exp-t` metricEntry = decodedEntries[index];
            :ref:`zet-metric-properties-t` metricProperties = {};
            :ref:`zetMetricGetProperties`\(decodableMetrics[metricEntry.metricIndex], &metricProperties);
            std::cout << "Component: " << metricProperties.component ". Decodable metric name: " << metricProperties.name;
            switch (metricProperties.resultType) {
            case :ref:`ZET_VALUE_TYPE_UINT8 <zet-value-type-t>`\:
            case :ref:`ZET_VALUE_TYPE_UINT16 <zet-value-type-t>`\:
            case :ref:`ZET_VALUE_TYPE_UINT32 <zet-value-type-t>`\:
                std::cout << ".\t value: " << metricEntry.value.ui32 << std::endl;
            break;
            case :ref:`ZET_VALUE_TYPE_UINT64 <zet-value-type-t>`\:
                std::cout << ".\t value: " << metricEntry.value.ui64 << std::endl;
            break;
            case :ref:`ZET_VALUE_TYPE_FLOAT32 <zet-value-type-t>`\:
                std::cout << ".\t value: " << metricEntry.value.fp32 << std::endl;
            break;
            case :ref:`ZET_VALUE_TYPE_FLOAT64 <zet-value-type-t>`\:
                std::cout << ".\t value: " << metricEntry.value.fp64 << std::endl;
            break;
            case :ref:`ZET_VALUE_TYPE_BOOL8 <zet-value-type-t>`\:
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
    :ref:`zetMetricTracerDisableExp`\(hMetricTracer, true);
    :ref:`zetMetricDecoderDestroyExp`\(hMetricDecoder);
    :ref:`zetMetricTracerDestroyExp`\(hMetricTracer);
    :ref:`zeEventDestroy`\( hNotificationEvent );
    :ref:`zeEventPoolDestroy`\( hEventPool );

    // Clean device configuration and free memory
    :ref:`zetContextActivateMetricGroups`\( hContext, hDevice, 0, nullptr );