${"#"} Programming Guide (Tools)
<%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
    t=tags['$t']
    T=t.upper()
%>
[DO NOT EDIT]: # (generated from /scripts/tools/PROG.md)

The following documents the high-level programming models and guidelines.  

NOTE: This is a **PRELIMINARY** specification, provided for review and feedback.

NOTE2: Use **TODO** to mark portions requiring more work.

${"##"} Table of Contents
* [Hardware Metrics](#hm)
* [Enumeration](#enu)
* [Configuration](#con)
* [Collection](#col)
* [Calculation](#cal)

${"#"} <a name="hm">Hardware Metrics</a>

${"##"} Introduction

Intel GPU includes programmable infrastructure designed to support performance debugging. The API
described in this document provides access to hardware metrics.

Most of the detailed metrics require hardware to be properly programmed by the driver. It is
important to understand that the hardware programming is in most cases global. This generally means
that if a software tool or an application is using the hardware features no other application
can reliably use the same resources.

The intention of this API is to support performance debug and it is not advised to use it in regular execution.

${"###"} Software abstraction of hardware counting

The hardware infrastucture consists of non-programmable pre-defined set of counters, a programmable
network of connections that work with a separate set of counters as well as other types of counters.
For sake of simplicity the smallest unit of configuration is a Metric Group. Metric Groups are
sets of metrics that provide certain perspective on workload's performance. The groups aggregate metrics,
define hardware programming and available collection methods. An application may choose to collect data
from a number of Metric Groups provided that they all belong to different domains. [Domains](#dom) are used
as a software representation of independent hardware resources that can safely be used concurrently.

${"###"} Sampling types

Sampling types are a software representation of hardware capabilities in terms of reading metric values.
Each Metric Group provides information which sampling types it supports.
There are separate sets of APIs supporting each of the sampling types [Time based](#tbs) and [Query based](#queries).

All available sampling types are defined in ::${t}_metric_group_sampling_type.
- Information about supported sampling types for a given Metric Group is provided in 
  ::${t}_metric_group_properties_t.samplingType.
- It's possible that ${OneApi} provides multiple Metric Groups with the same names but different sampling types.
- When enumerating, it's important to choose a Metric Group which supports the desired sampling type.

${"###"} <a name="dom">Domains</a>

Every Metric Group belongs to a given domain (::${t}_metric_group_properties_t.domain). 
- Each domain represents an exclusive resource used by the Metric Group.
- It's possible to simultaneously gather data for two different Metric Groups, only if they belong
  to a different domain i.e. Metric Groups that can be collected concurrently will have different domain values.

${"#"} <a name="enu">Enumeration</a>

A common tool flow is to enumerate metrics looking for specific Metric Groups and/or Metrics.
Depending on the metrics required for a specific scenario a tool may choose to run the workload multiple times
recording different set of Metric Groups each time.
Usually care must be taken to ensure run to run stability and result repeatability if metrics from different runs are meant to be used together.

All available metrics are organized into Metric Groups.
- If required, a Metric Group contains a uniform hardware counter configuration used for measurements.
  The programming is not exposed in the API.
- During data collection, data for the whole Metric Group is gathered.
- Metric Group names don't have to be unique.
- List of available Metric Groups and Metrics depends on hardware and driver.

Each level of the metrics hierarchy (MetricGroups and Metrics) provides all the information needed for
its identification and usage.
- Metric Group properties are accessed through function ::${t}MetricGroupGetProperties, returning
  ::${t}_metric_group_properties_t.
- Metric properties are accessed through function ::${t}MetricGetProperties, returning
  ::${t}_metric_properties_t.

![Metrics](../images/tools_metric_hierarchy.png?raw=true)  
@image latex tools_metric_hierarchy.png

When enumerating Metric tree to find a desired Metric Group, it's important to know in advance with
which sampling type it will be used. 

To enumerate through the Metric tree:
1. Call ::${t}MetricGroupGetCount with ::${x}_device_handle_t to obtain Metric Group count.
2. Iterate over all available Metric Groups using ::${t}MetricGroupGet.
    - At this point it's possible to check e.g. Metric Group name, domain or sampling type.
3. For each Metric Group obtain their Metric count calling ::${t}MetricGroupGetProperties with
   Metric Group handle (::${t}_metric_group_handle_t) and checking ::${t}_metric_group_properties_t.metricCount.
4. Iterate over available Metrics using ::${t}MetricGet with parent Metric Group (::${t}_metric_group_handle_t).
5. Check Metric properties (e.g. name, description) calling ::${t}MetricGetProperties with parent
   Metric (::${t}_metric_handle_t).


The following sample code demonstrates a basic enumaration over all available metric groups and their metrics.
Additionally, it returns a metric group with a chosen name and sampling type. Similar code could be used
for selecting a preferred metric group for a specific type of measurements.
```c
    ${x}_result_t FindMetricGroup( ${x}_device_handle_t hDevice, char* pMetricGroupName, uint32_t desiredSamplingType, ${t}_metric_group_handle_t* phMetricGroup )
    {
        // Obtain available metric group count for the specific device - 'hDevice'
        uint32_t metricGroupCount = 0;
        ${t}MetricGroupGetCount( hDevice, &metricGroupCount );

        *phMetricGroup = nullptr;

        // Interate over all metric groups available for the 'hDevice'
        for( uint32_t i = 0; i < metricGroupCount; i++ )
        {   
            ${t}_metric_group_handle_t hMetricGroup = nullptr;
            ${t}_metric_group_properties_t metricGroupProperties = {${T}_METRIC_GROUP_PROPERTIES_VERSION_CURRENT};

            // Get metric group under index 'i' and its properties
            ${t}MetricGroupGet( hDevice, i, &hMetricGroup );
            ${t}MetricGroupGetProperties( hMetricGroup, &metricGroupProperties );

            printf("Metric Group: %s\n", metricGroupProperties.name);

            // Check whether the obtained metric group supports the desired sampling type
            if((metricGroupProperties.samplingType & desiredSamplingType) == desiredSamplingType)
            {   
                // Check whether the obtained metric group has the desired name
                if( strcmp( pMetricGroupName, metricGroupProperties.name ) == 0 )
                {
                    *phMetricGroup = hMetricGroup;
                }

	            // Interate over all metrics within the 'hMetricGroup'
                for(uint32_t j = 0; j < metricGroupProperties.metricCount; j++)	
                {
                    ${t}_metric_handle_t metricHandle = nullptr;
                    ${t}_metric_properties_t metricProperties = {${T}_METRIC_PROPERTIES_VERSION_CURRENT};   

                    // Get metric under index 'j' and its properties
                    ${t}MetricGet(hMetricGroup, j, &metricHandle);
                    ${t}MetricGetProperties(metricHandle, &metricProperties);

                    printf("Metric: %s\n", metricProperties.name);
                }
            }
        }
    }
```

${"#"} <a name="con">Configuration</a>

Use the ::${t}DeviceActivateMetricGroups API call to configure the hardware for data collection.
- Subsequent calls to the function will disable hardware programming for the metric groups not selected for activation.
- To avoid bogous data only call the ::${t}DeviceActivateMetricGroups between experiments i.e. while not collecting data.

Programming restrictions:
- Any combination of metric groups can be configured simultanously provided that all of them have
  different ::${t}_metric_group_properties_t.domain.
- MetricGroup must be active until ::${t}MetricQueryGetData and ::${t}MetricTracerClose.
- Conflicting Groups cannot be activated, in such case the call to TODO ... would fail.

${"#"} <a name="col">Collection</a>

There are two modes of metrics collection supported: time based and query based.
- Time based collection is using a timer as well as other events to store data samples in circular buffer.
  A metric tracer interface is a software interface for configuration and collection.
- Query based metrics collection is based on a pair of Begin/End events appended to command lists.
  Query result generally characterizes hardware behavior between those events.

${"##"} <a name="tbs">Time Based</a>

Time based collection is using a simple Open/Wait/Read/Close scheme:
- ::${t}MetricTracerOpen opens the tracer.
- ::${x}EventHostSynchronize and ::${x}EventQueryStatus can be used to wait for data.
- ::${t}MetricTracerReadData reads the data.
- ::${t}MetricTracerClose closes the tracer.

**Note:** To avoid incorrect data, do not reconfigure the hardware using ::${t}DeviceActivateMetricGroups while the tracer is opened.

![MetricTracer](../images/tools_metric_tracer.png?raw=true)  
@image latex tools_metric_tracer.png


The following sample code demonstrates a basic sequence for time based collection:
```c
    ${x}_result_t TimeBasedUsageExample( ${x}_device_handle_t hDevice )
    {
        ${t}_metric_group_handle_t     hMetricGroup           = nullptr;
        ${t}_metric_group_properties_t metricGroupProperties  = {};
        ${x}_event_handle_t	          hNotificationEvent     = nullptr;
        ${x}_event_pool_handle_t	      hEventPool             = nullptr;
        ${x}_event_pool_desc_t          eventPoolDesc          = {${X}_EVENT_POOL_DESC_VERSION_CURRENT, ${X}_EVENT_POOL_FLAG_DEFAULT , 1};
        ${x}_event_desc_t               eventDesc              = {${X}_EVENT_DESC_VERSION_CURRENT};
        ${t}_metric_tracer_handle_t    hMetricTracer          = nullptr;
        ${t}_metric_tracer_desc_t      metricTracerDescriptor = {${T}_METRIC_TRACER_DESC_VERSION_CURRENT}; 

        // Find a "RenderBasic" metric group suitable for Time Based collection
        FindMetricGroup( hDevice, "RenderBasic", ${T}_METRIC_GROUP_SAMPLING_TYPE_TIME_BASED, &hMetricGroup );
        ${t}MetricGroupGetProperties( hMetricGroup, &metricGroupProperties );

        // Configure the HW
        ${t}DeviceActivateMetricGroup( hDevice, 1 /* count */, &hMetricGroup );

        // Create notification event
        ${x}EventPoolCreate( hDevice, &eventPoolDesc, &hEventPool );
        eventDesc.index  = 0;
        eventDesc.signal = XE_EVENT_SCOPE_FLAG_HOST;
        eventDesc.wait   = XE_EVENT_SCOPE_FLAG_HOST; 
        ${x}EventCreate( hEventPool, &eventDesc, &hNotificationEvent );
        
        // Open time based sampling
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

${"##"} <a name="queries">Queries</a>

Query API provides a way of acquiring metrics per portions of workload delimited by BEGIN/END events.
Typically, multiple queries are used to characterize a workload so the API is pool based.

- A metric query pool is created and destroyed using ::${t}MetricQueryPoolCreate and ::${t}MetricQueryPoolDestroy calls.
- To work with individual query object, use ::${t}MetricQueryPoolGetMetricQuery to get a handle.
- Then insert BEGIN/END events into a command list using ::${t}CommandListAppendMetricQueryBegin and ::${t}CommandListAppendMetricQueryEnd calls.
- Once the workload has been executed the ::${t}MetricQueryGetData returns the raw data to be later processed by ::${t}MetricGroupCalculateData.

![MetricQuery](../images/tools_metric_query.png?raw=true)  
@image latex tools_metric_query.png

The following sample code demonstrates a basic sequence for query based collection:
```c
    ${x}_result_t MetricQueryUsageExample( ${x}_device_handle_t hDevice )
    {
        ${t}_metric_group_handle_t      hMetricGroup          = nullptr;
        ${t}_metric_group_properties_t  metricGroupProperties = {${T}_METRIC_GROUP_PROPERTIES_VERSION_CURRENT};
        ${x}_event_handle_t              hCompletionEvent      = nullptr;
        ${x}_event_pool_desc_t           eventPoolDesc         = {${X}_EVENT_POOL_DESC_VERSION_CURRENT};
        ${x}_event_desc_t                eventDesc             = {${X}_EVENT_DESC_VERSION_CURRENT};
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
        eventPoolDesc.flags = ${X}_EVENT_POOL_FLAG_DEFAULT;
        eventPoolDesc.count = 1000;
        ${x}EventPoolCreate( hDevice, &eventPoolDesc, &hEventPool );

        // Write BEGIN metric query to command list 
        ${t}MetricQueryPoolGetMetricQuery( hMetricQueryPool, 0 /*slot*/, &hMetricQuery );
        ${t}CommandListAppendMetricQueryBegin( hCommandList, hMetricQuery );

        // build your command list

        // Write END metric query to command list, use an event to determine if the data is available
        eventDesc.index  = 0;
        eventDesc.signal = XE_EVENT_SCOPE_FLAG_HOST;
        eventDesc.wait   = XE_EVENT_SCOPE_FLAG_HOST; 
        ${x}EventCreate( hEventPool, &eventDesc, &hCompletionEvent);
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

Both MetricTracer and MetricQueryPool collect the data in hardware specific, raw form that is not suitable
for application processing. To calculate metric values use ::${t}MetricGroupCalculateData.

- In order to obtain available raw report count the user should call ::${t}MetricTracerReadData or
  ::${t}MetricQueryGetData with rawSize(0) and pRawData(nullptr)
```c
    ${t}MetricTracerReadData( hMetricTracer, &reportCount, 0, nullptr );
    ${t}MetricQueryGetData( hMetricQuery, &reportCount, 0, nullptr );
```

- In order to obtain raw reports the user should use ::${t}MetricTracerReadData or ::${t}MetricQueryGetData
  function with below arguments:
 - pReportCount: report count to read
 - rawDataSize: raw buffer size allocated and passed by the user
 - pRawData: buffer for raw reports
```c
    ${t}MetricTracerReadData( hMetricTracer, &reportCount, rawDataSize, pRawData );
    ${t}MetricQueryGetData( hMetricQuery, &reportCount, rawDataSize, pRawData );
```

- In order to calculate metrics from raw data the user should use ::${t}MetricGroupCalculateData with
  below arguments:
 - hMetricGroup: handle of the metric group
 - pReportCount: report count to calculate
 - rawDataSize:  buffer size with raw reports to calculate 
 - rawData: buffer with raw reports to calculate 
 - calculatedDataSize - buffer size for calculated reports
 - pCalculatedData - buffer for calculated reports allocated by the user
```c
    ${t}MetricGroupCalculateData( hMetricTracer, &reportCount, rawDataSize, pRawData );
```


