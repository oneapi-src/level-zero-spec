${"#"} Programming Guide (Tools)

[DO NOT EDIT]: # (generated from /scripts/tools/PROG.md)

The following documents the high-level programming models and guidelines.  

NOTE: This is a **PRELIMINARY** specification, provided for review and feedback.

${"##"} Table of Contents
* [Hardware Metrics](#hm)
* [Enumeration](#enu)
* [Configuration](#con)
* [Collection](#col)
* [Calculation](#cal)

${"#"} <a name="hm">Hardware Metrics</a>

${"##"} Introduction

![Metrics](../images/tools_metric_hierarchy.png?raw=true)  
@image latex tools_metric_hierarchy.png

**note: use TODO to mark portions requiring more work**

${"#"} <a name="enu">Enumeration</a>

- TODO: metric group hierarchy description, graphs missing, use bitmaps ?
- TODO: describe the concept of domains
- TODO: provide sample data?
- TODO: add p to pointers


The following sample code demonstrates a basic enumeration:
```c
${x}_result_t FindMetricGroup( ${x}_device_handle_t hDevice, char* pMetricGroupName, uint32_t desiredSamplingType, ${t}_metric_group_handle_t* phMetricGroup )
{
    // METRIC GROUP COUNT
    uint32_t metricGroupCount = 0;
    ${t}MetricGroupGetCount( hDevice, &metricGroupCount );

    *phMetricGroup = nullptr;

    // METRIC GROUPS
    for( uint32_t i = 0; i < metricGroupCount; i++ )
    {   
        ${t}_metric_group_handle_t hMetricGroup = nullptr;
        ${t}_metric_group_properties_t metricGroupProperties = {${T}_METRIC_GROUP_PROPERTIES_VERSION_CURRENT};

        ${t}MetricGroupGet( hDevice, i, &hMetricGroup );
        ${t}MetricGroupGetProperties( hMetricGroup, &metricGroupProperties );
        cout << "Metric Group: " << metricGroupProperties.name << "\n";

        if( (metricGroupProperties.samplingType & desiredSamplingType) == desiredSamplingType )
        {   
            if( strcmp( pMetricGroupName, metricGroupProperties.name ) == 0 )
            {
                *phMetricGroup = hMetricGroup;
            }
	        // list METRICS
            for( uint32_t j = 0; j < metricGroupProperties.metricCount; j++ )	
            {
                ${t}_metric_handle_t metricHandle = nullptr;
                ${t}_metric_properties_t metricProperties = {${T}_METRIC_PROPERTIES_VERSION_CURRENT};

                ${t}MetricGet( hMetricGroup, j, &metricHandle );
                ${t}MetricGetProperties( metricHandle, &metricProperties );
                cout << "Metric: " << metricProperties.name << "\n";
            }
        }
    }
}
```

${"#"} <a name="con">Configuration</a>

Use the ::${t}DeviceActivateMetricGroups API call to configure the hardware for data collection.
Subsequent calls to the function will disable hardware programming for the metric groups not selected for activation.
To avoid bogous data only call the ::${t}DeviceActivateMetricGroups between experiments i.e. while not collecting data.

Programming restrictions:
- Any combination of metric groups can be configured simultanously provided that all of them have different ::${t}_metric_group_properties_t.domain.
- MetricGroup must be active until MetricQueryGetDeta and MetricTracerClose.
- Conflicting Groups cannot be activated, in such case the call to TODO ... would fail.

${"#"} <a name="col">Collection</a>

There are two modes of metrics collection supported: time based and query based.
Time based collection is using a timer as well as other events to store data samples in circular buffer. A metric tracer interface is a software interface for configuration and collection.
Query based metrics collection is based on a pair of Begin/End events appended to command lists. Query result generally characterizes hardware behavior between those events.

${"##"} Time Based

Time based collection is using a simple Open/Wait/Read/Close scheme:
- ::${t}MetricTracerOpen opens the tracer.
- ::${x}EventHostSynchronize and ::${x}EventQueryStatus can be used to wait for data.
- ::${t}MetricTracerReadData reads the data.
- ::${t}MetricTracerClose closes the tracer.

**Note:** to avoid incorrect data, do not reconfigure the hardware using ::${t}DeviceActivateMetricGroups while the tracer is opened.

```c
${x}_result_t TimeBasedUsageExample( ${x}_device_handle_t hDevice )
{
    ${t}_metric_group_handle_t     hMetricGroup           = nullptr;
    ${t}_metric_group_properties_t metricGroupProperties  = {};
    ${x}_event_handle_t	          hNotificationEvent     = nullptr;
    ${x}_event_pool_handle_t	      hEventPool             = nullptr;
    ${x}_event_pool_desc_t          eventPoolDesc          = {XE_EVENT_POOL_DESC_VERSION_CURRENT, ${X}_EVENT_POOL_FLAG_DEVICE_TO_HOST, 1};
    ${t}_metric_tracer_handle_t    hMetricTracer          = nullptr;
    ${t}_metric_tracer_desc_t      metricTracerDescriptor = {${T}_METRIC_TRACER_DESC_VERSION_CURRENT}; 

    // Find a "RenderBasic" metric group suitable for Time Based collection
    FindMetricGroup( hDevice, "RenderBasic", ${T}_METRIC_GROUP_SAMPLING_TYPE_TIME_BASED, &hMetricGroup );
    ${t}MetricGroupGetProperties( hMetricGroup, &metricGroupProperties );

    // Configure the HW
    ${t}DeviceActivateMetricGroup( hDevice, 1 /* count */, &hMetricGroup );

    // Open time based sampling
    ${x}EventPoolCreate( hDevice, &eventPoolDesc, &hEventPool );
    ${x}EventCreate( hEventPool, 0 /*slot*/, &hNotificationEvent );
    metricTracerDescriptor.hMetricGroup     	= hMetricGroup;
    metricTracerDescriptor.samplingPeriodNs 	= 1000;
    metricTracerDescriptor.notifyEveryNReports  = 32768;
    ${t}MetricTracerOpen( hDevice, &metricTracerDescriptor, hNotificationEvent, &hMetricTracer );

    // Run your workload, in this example we assume the data for the whole experiment fits in the hardware buffer
    Workload(hDevice);
    // Optionally insert markers during workload execution
    //${t}CommandListAppendMetricTracerMarker( hCommandList, hMetricTracer, tool_marker_value ); 

    // Wait for data, optional in this example since the whole workload has already been executedby now
    //${x}EventHostSynchronize( hNotificationEvent, 1000 /*timeout*/ );
    // reset the event if it fired

    // Read raw data
    uint32_t reportCount = 0;
    ${t}MetricTracerReadData( hMetricTracer, &reportCount, 0, nullptr ); // first check how many reports are available
    uint32_t size = metricGroupProperties.rawReportSize * reportCount;
    uint8_t* rawData = malloc(size); 
    ${t}MetricTracerGetData( hMetricTracer, &reportCount, size, rawData );

    // Close metric tracer
    ${t}MetricTracerClose( hMetricTracer );   
    ${x}EventDestroy( hNotificationEvent );
    ${x}EventPoolDestroy( hEventPool );

    // Deconfigure the hardware
    ${t}DeviceActivateMetricGroups( hDevice, 0, nullptr );

    // Calculate metric data
    uint32_t calculatedDataSize = 0;
    ${t}MetricGroupCalculateData( hMetricGroup, &reportCount, size, &calculatedDataSize, nullptr );
    ${t}_typed_value_t* calculatedData = (${t}_typed_value_t*)malloc( calculatedDataSize );
    ${t}MetricGroupCalculateData( hMetricGroup, &reportCount, size, rawData, &calculatedDataSize, calculatedData );
}
```

${"##"} Queries

Query API provides a way of acquiring metrics per portions of workload delimited by BEGIN/END events.
Tpically multiple queries are used to characterize a workload so the API is pool based.
A metric query pool is created and destroyed using ::${t}MetricQueryPoolCreate and ::${t}MetricQueryPoolDestroy calls.
To work with individual query object, use ::${t}MetricQueryPoolGetMetricQuery to get a handle.
Then insert BEGIN/END events into a command list using ::${t}CommandListAppendMetricQueryBegin and ::${t}CommandListAppendMetricQueryEnd calls.
Once the workload has been executed the ::${t}MetricQueryGetData returns the raw data to be later processed by ::${t}MetricGroupCalculateData.

```c
${x}_result_t MetricQueryUsageExample( ${x}_device_handle_t hDevice )
{
    ${t}_metric_group_handle_t      hMetricGroup          = nullptr;
    ${t}_metric_group_properties_t  metricGroupProperties = {${T}_METRIC_GROUP_PROPERTIES_VERSION_CURRENT};
    ${x}_event_handle_t              hCompletionEvent      = nullptr;
    ${x}_event_pool_desc_t           eventPoolDesc         = {${X}_EVENT_POOL_DESC_VERSION_CURRENT};
    ${x}_event_pool_handle_t         hEventPool            = nullptr;
    ${t}_metric_query_pool_handle_t hMetricQueryPool      = nullptr;
    ${t}_metric_query_handle_t      hMetricQuery          = nullptr;
    ${t}_metric_query_pool_desc_t   queryPoolDesc         = {${T}_METRIC_QUERY_POOL_DESC_VERSION_CURRENT};
    
    // Find event metric group
    FindMetricGroup( hDevice, "RenderBasic", ${T}_METRIC_GROUP_SAMPLING_TYPE_EVENT_BASED, &hMetricGroup );
    ${t}MetricGroupGetProperties( hMetricGroup, &metricGroupProperties );

    // Configure HW
    ${t}DeviceActivateMetricGroups( hDevice, 1 /* count */, &hMetricGroup );

    // Create metric query pool & completion event
    queryPoolDesc.flags        = ${T}_METRIC_QUERY_POOL_FLAG_PERFORMANCE;
    queryPoolDesc.hMetricGroup = hMetricGroup;
    queryPoolDesc.count        = 1000;
    ${t}MetricQueryPoolCreate( hDevice, &queryPoolDesc, &hMetricQueryPool );
    eventPoolDesc.flags = ${X}_EVENT_POOL_FLAG_DEVICE_TO_HOST;
    eventPoolDesc.count = 1000;
    ${x}EventPoolCreate( hDevice, &eventPoolDesc, &hEventPool );

    // Write BEGIN metric query to command list 
    ${t}MetricQueryPoolGetMetricQuery( hMetricQueryPool, 0 /*slot*/, &hMetricQuery );
    ${t}CommandListAppendMetricQueryBegin( hCommandList, hMetricQuery );

    // build your command list

    // Write END metric query to command list, use an event to determine if the data is available
    ${x}EventCreate( hEventPool, 0 /*slot*/, hCompletionEvent);
    ${t}CommandListAppendMetricQueryEnd( hCommandList, hMetricQuery, hCompletionEvent );

    // use ${x}CommandQueueExecuteCommandLists( , , , ) to submit your workload to the hardware
   
    // Wait for data
    ${x}EventHostSynchronize( hCompletionEvent, 1000 /*timeout*/ );

    // Read raw data
    uint32_t rawSize = metricGroupProperties.rawReportSize;
    uint8_t* rawData = malloc(rawSize); 
    uint32_t reportCount = 1;
    ${t}MetricQueryGetData( hMetricQuery, &reportCount, rawSize, rawData );

    // Free the resources
    ${x}EventDestroy( hCompletionEvent );
    ${x}EventPoolDestroy( hEventPool );
    ${t}MetricQueryPoolDestroy( hMetricQueryPool );

    // Deconfigure HW
    ${t}DeviceActivateMetricGroups( hDevice, 0, nullptr );

    // Calculate metric data
    uint32_t calculatedDataSize = metricGroupProperties.calculatedReportSize * reportCount;
    ${t}_typed_value_t* calculatedData = (${t}_typed_value_t*)malloc( calculatedDataSize );
    ${t}MetricGroupCalculateData( hMetricGroup, &reportCount, rawSize, rawData, &calculatedDataSize, calculatedData );
}
```

${"#"} <a name="cal">Calculation</a>

Both MetricTracer and MetricQueryPool collect the data in it's hardware specific, raw form that is not suitable for application processing. To calculate metric values use the ::${t}MetricGroupCalculateData.

- In order to obtain available raw report count the user should call ::${t}MetricTracerReadData or ::${t}MetricQueryGetData with rawSize(0) and pRawData(nullptr)
```c
${t}MetricTracerReadData( hMetricTracer, &reportCount, 0, nullptr );
${t}MetricQueryGetData( hMetricQuery, &reportCount, 0, nullptr );
```

- In order to obtain raw reports the user should use ::${t}MetricTracerReadData or ::${t}MetricQueryGetData function with below arguments:
 - pReportCount: report count to read
 - rawDataSize: raw buffer size allocated and passed by the user
 - pRawData: buffer for raw reports
```c
${t}MetricTracerReadData( hMetricTracer, &reportCount, rawDataSize, pRawData );
${t}MetricQueryGetData( hMetricQuery, &reportCount, rawDataSize, pRawData );
```

- In order to calculate metrics from raw data the user should use ::${t}MetricGroupCalculateData with below arguments:
 - hMetricGroup: handle of the metric group
 - pReportCount: report count to calculate
 - rawDataSize:  buffer size with raw reports to calculate 
 - rawData: buffer with raw reports to calculate 
 - calculatedDataSize - buffer size for calculated reports
 - pCalculatedData - buffer for calculated reports allocated by the user
```c
${t}MetricGroupCalculateData( hMetricTracer, &reportCount, rawDataSize, pRawData );
```


