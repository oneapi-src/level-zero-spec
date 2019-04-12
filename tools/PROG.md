# Programming Guide (Tools)

[DO NOT EDIT]: # (generated from /scripts/tools/PROG.md)

The following documents the high-level programming models and guidelines.  

NOTE: This is a **PRELIMINARY** specification, provided for review and feedback.

NOTE2: Use **TODO** to mark portions requiring more work.

## Table of Contents
* [Hardware Metrics](#hm)
* [Enumeration](#enu)
* [Configuration](#con)
* [Collection](#col)
* [Calculation](#cal)

# <a name="hm">Hardware Metrics</a>

## Introduction

Available metrics are organized into Metric Groups.
- Individual Metric Group represents a uniform hardware counter configuration used for measurements.
- During data collection, data for the whole Metric Group is gathered.
- Metric Group names don't have to be unique.
- List of available Metric Groups and Metrics may be different on different hardwares.

Each level of the metrics hierarchy (MetricGroups and Metrics) provides all information needed for
its identification and usage.
- Metric Group properties are accessed through function ::xetMetricGroupGetProperties, returning
  ::xet_metric_group_properties_t.
- Metric properties are accessed through function ::xetMetricGetProperties, returning
  ::xet_metric_properties_t.

![Metrics](../images/tools_metric_hierarchy.png?raw=true)  
@image latex tools_metric_hierarchy.png

### Sampling types

Metric Groups are designed to be used only with a specifed type of measurements, called sampling types.

All available sampling types are defined in ::xet_metric_group_sampling_type.
- Information about supported sampling types for a given Metric Group is provided in 
  ::xet_metric_group_properties_t.samplingType.
- It's possible Xe provides multiple Metric Groups with the same names but different sampling types.
- When enumerating, it's important to choose a Metric Group which supports the desired sampling type.

### Domains

Every Metric Group belongs to a given domain (::xet_metric_group_properties_t.domain). 
- Each domain represents an exclusive resource used by the Metric Group.
- It's possible to simultaneously gather data for two different Metric Groups, only if they belong
  to a different domain.

# <a name="enu">Enumeration</a>

When enumerating Metric tree to find a desired Metric Group, it's important to know in advance with
which sampling type it will be used. 

To enumerate through the Metric tree:
1. Call ::xetMetricGroupGetCount with ::xe_device_handle_t to obtain Metric Group count.
2. Iterate over all available Metric Groups using ::xetMetricGroupGet.
    - At this point it's possible to check e.g. Metric Group name, domain or sampling type.
3. For each Metric Group obtain their Metric count calling ::xetMetricGroupGetProperties with
   Metric Group handle (::xet_metric_group_handle_t) and checking ::xet_metric_group_properties_t.metricCount.
4. Iterate over available Metrics using ::xetMetricGet with parent Metric Group (::xet_metric_group_handle_t).
5. Check Metric properties (e.g. name, description) calling ::xetMetricGetProperties with parent
   Metric (::xet_metric_handle_t).


- TODO: provide sample data?

The following sample code demonstrates basic enumeration:
```c
    xe_result_t FindMetricGroup( xe_device_handle_t hDevice, char* pMetricGroupName, uint32_t desiredSamplingType, xet_metric_group_handle_t* phMetricGroup )
    {
        // METRIC GROUP COUNT
        uint32_t metricGroupCount = 0;
        xetMetricGroupGetCount( hDevice, &metricGroupCount );

        *phMetricGroup = nullptr;

        // METRIC GROUPS
        for( uint32_t i = 0; i < metricGroupCount; i++ )
        {   
            xet_metric_group_handle_t hMetricGroup = nullptr;
            xet_metric_group_properties_t metricGroupProperties = {XET_METRIC_GROUP_PROPERTIES_VERSION_CURRENT};

            xetMetricGroupGet( hDevice, i, &hMetricGroup );
            xetMetricGroupGetProperties( hMetricGroup, &metricGroupProperties );

            printf("Metric Group: %s\n", metricGroupProperties.name);

            if((metricGroupProperties.samplingType & desiredSamplingType) == desiredSamplingType)
            {   
                if( strcmp( pMetricGroupName, metricGroupProperties.name ) == 0 )
                {
                    *phMetricGroup = hMetricGroup;
                }
	            // list METRICS
                for(uint32_t j = 0; j < metricGroupProperties.metricCount; j++)	
                {
                    xet_metric_handle_t metricHandle = nullptr;
                    xet_metric_properties_t metricProperties = {XET_METRIC_PROPERTIES_VERSION_CURRENT};   

                    xetMetricGet(hMetricGroup, j, &metricHandle);
                    xetMetricGetProperties(metricHandle, &metricProperties);

                    printf("Metric: %s\n", metricProperties.name);
                }
            }
        }
    }
```

# <a name="con">Configuration</a>

Use the ::xetDeviceActivateMetricGroups API call to configure the hardware for data collection.
- Subsequent calls to the function will disable hardware programming for the metric groups not selected for activation.
- To avoid bogous data only call the ::xetDeviceActivateMetricGroups between experiments i.e. while not collecting data.

Programming restrictions:
- Any combination of metric groups can be configured simultanously provided that all of them have
  different ::xet_metric_group_properties_t.domain.
- MetricGroup must be active until ::xetMetricQueryGetData and ::xetMetricTracerClose.
- Conflicting Groups cannot be activated, in such case the call to TODO ... would fail.

# <a name="col">Collection</a>

There are two modes of metrics collection supported: time based and query based.
- Time based collection is using a timer as well as other events to store data samples in circular buffer.
  A metric tracer interface is a software interface for configuration and collection.
- Query based metrics collection is based on a pair of Begin/End events appended to command lists.
  Query result generally characterizes hardware behavior between those events.

## Time Based

Time based collection is using a simple Open/Wait/Read/Close scheme:
- ::xetMetricTracerOpen opens the tracer.
- ::xeEventHostSynchronize and ::xeEventQueryStatus can be used to wait for data.
- ::xetMetricTracerReadData reads the data.
- ::xetMetricTracerClose closes the tracer.

**Note:** To avoid incorrect data, do not reconfigure the hardware using ::xetDeviceActivateMetricGroups while the tracer is opened.

```c
    xe_result_t TimeBasedUsageExample( xe_device_handle_t hDevice )
    {
        xet_metric_group_handle_t     hMetricGroup           = nullptr;
        xet_metric_group_properties_t metricGroupProperties  = {};
        xe_event_handle_t	          hNotificationEvent     = nullptr;
        xe_event_pool_handle_t	      hEventPool             = nullptr;
        xe_event_pool_desc_t          eventPoolDesc          = {XE_EVENT_POOL_DESC_VERSION_CURRENT, XE_EVENT_POOL_FLAG_DEVICE_TO_HOST, 1};
        xet_metric_tracer_handle_t    hMetricTracer          = nullptr;
        xet_metric_tracer_desc_t      metricTracerDescriptor = {XET_METRIC_TRACER_DESC_VERSION_CURRENT}; 

        // Find a "RenderBasic" metric group suitable for Time Based collection
        FindMetricGroup( hDevice, "RenderBasic", XET_METRIC_GROUP_SAMPLING_TYPE_TIME_BASED, &hMetricGroup );
        xetMetricGroupGetProperties( hMetricGroup, &metricGroupProperties );

        // Configure the HW
        xetDeviceActivateMetricGroup( hDevice, 1 /* count */, &hMetricGroup );

        // Open time based sampling
        xeEventPoolCreate( hDevice, &eventPoolDesc, &hEventPool );
        xeEventCreate( hEventPool, 0 /*slot*/, &hNotificationEvent );
        metricTracerDescriptor.hMetricGroup     	= hMetricGroup;
        metricTracerDescriptor.samplingPeriodNs 	= 1000;
        metricTracerDescriptor.notifyEveryNReports  = 32768;
        xetMetricTracerOpen( hDevice, &metricTracerDescriptor, hNotificationEvent, &hMetricTracer );

        // Run your workload, in this example we assume the data for the whole experiment fits in the hardware buffer
        Workload(hDevice);
        // Optionally insert markers during workload execution
        //xetCommandListAppendMetricTracerMarker( hCommandList, hMetricTracer, tool_marker_value ); 

        // Wait for data, optional in this example since the whole workload has already been executedby now
        //xeEventHostSynchronize( hNotificationEvent, 1000 /*timeout*/ );
        // reset the event if it fired

        // Read raw data
        uint32_t reportCount = 0;
        xetMetricTracerReadData( hMetricTracer, &reportCount, 0, nullptr ); // first check how many reports are available
        uint32_t size = metricGroupProperties.rawReportSize * reportCount;
        uint8_t* rawData = malloc(size); 
        xetMetricTracerGetData( hMetricTracer, &reportCount, size, rawData );

        // Close metric tracer
        xetMetricTracerClose( hMetricTracer );   
        xeEventDestroy( hNotificationEvent );
        xeEventPoolDestroy( hEventPool );

        // Deconfigure the hardware
        xetDeviceActivateMetricGroups( hDevice, 0, nullptr );

        // Calculate metric data
        uint32_t calculatedDataSize = 0;
        xetMetricGroupCalculateData( hMetricGroup, &reportCount, size, &calculatedDataSize, nullptr );
        xet_typed_value_t* calculatedData = (xet_typed_value_t*)malloc( calculatedDataSize );
        xetMetricGroupCalculateData( hMetricGroup, &reportCount, size, rawData, &calculatedDataSize, calculatedData );
    }
```

## Queries

Query API provides a way of acquiring metrics per portions of workload delimited by BEGIN/END events.
Typically, multiple queries are used to characterize a workload so the API is pool based.

- A metric query pool is created and destroyed using ::xetMetricQueryPoolCreate and ::xetMetricQueryPoolDestroy calls.
- To work with individual query object, use ::xetMetricQueryPoolGetMetricQuery to get a handle.
- Then insert BEGIN/END events into a command list using ::xetCommandListAppendMetricQueryBegin and ::xetCommandListAppendMetricQueryEnd calls.
- Once the workload has been executed the ::xetMetricQueryGetData returns the raw data to be later processed by ::xetMetricGroupCalculateData.

```c
    xe_result_t MetricQueryUsageExample( xe_device_handle_t hDevice )
    {
        xet_metric_group_handle_t      hMetricGroup          = nullptr;
        xet_metric_group_properties_t  metricGroupProperties = {XET_METRIC_GROUP_PROPERTIES_VERSION_CURRENT};
        xe_event_handle_t              hCompletionEvent      = nullptr;
        xe_event_pool_desc_t           eventPoolDesc         = {XE_EVENT_POOL_DESC_VERSION_CURRENT};
        xe_event_pool_handle_t         hEventPool            = nullptr;
        xet_metric_query_pool_handle_t hMetricQueryPool      = nullptr;
        xet_metric_query_handle_t      hMetricQuery          = nullptr;
        xet_metric_query_pool_desc_t   queryPoolDesc         = {XET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT};
    
        // Find event metric group
        FindMetricGroup( hDevice, "RenderBasic", XET_METRIC_GROUP_SAMPLING_TYPE_EVENT_BASED, &hMetricGroup );
        xetMetricGroupGetProperties( hMetricGroup, &metricGroupProperties );

        // Configure HW
        xetDeviceActivateMetricGroups( hDevice, 1 /* count */, &hMetricGroup );

        // Create metric query pool & completion event
        queryPoolDesc.flags        = XET_METRIC_QUERY_POOL_FLAG_PERFORMANCE;
        queryPoolDesc.hMetricGroup = hMetricGroup;
        queryPoolDesc.count        = 1000;
        xetMetricQueryPoolCreate( hDevice, &queryPoolDesc, &hMetricQueryPool );
        eventPoolDesc.flags = XE_EVENT_POOL_FLAG_DEVICE_TO_HOST;
        eventPoolDesc.count = 1000;
        xeEventPoolCreate( hDevice, &eventPoolDesc, &hEventPool );

        // Write BEGIN metric query to command list 
        xetMetricQueryPoolGetMetricQuery( hMetricQueryPool, 0 /*slot*/, &hMetricQuery );
        xetCommandListAppendMetricQueryBegin( hCommandList, hMetricQuery );

        // build your command list

        // Write END metric query to command list, use an event to determine if the data is available
        xeEventCreate( hEventPool, 0 /*slot*/, hCompletionEvent);
        xetCommandListAppendMetricQueryEnd( hCommandList, hMetricQuery, hCompletionEvent );

        // use xeCommandQueueExecuteCommandLists( , , , ) to submit your workload to the hardware
   
        // Wait for data
        xeEventHostSynchronize( hCompletionEvent, 1000 /*timeout*/ );

        // Read raw data
        uint32_t rawSize = metricGroupProperties.rawReportSize;
        uint8_t* rawData = malloc(rawSize); 
        uint32_t reportCount = 1;
        xetMetricQueryGetData( hMetricQuery, &reportCount, rawSize, rawData );

        // Free the resources
        xeEventDestroy( hCompletionEvent );
        xeEventPoolDestroy( hEventPool );
        xetMetricQueryPoolDestroy( hMetricQueryPool );

        // Deconfigure HW
        xetDeviceActivateMetricGroups( hDevice, 0, nullptr );

        // Calculate metric data
        uint32_t calculatedDataSize = metricGroupProperties.calculatedReportSize * reportCount;
        xet_typed_value_t* calculatedData = (xet_typed_value_t*)malloc( calculatedDataSize );
        xetMetricGroupCalculateData( hMetricGroup, &reportCount, rawSize, rawData, &calculatedDataSize, calculatedData );
    }
```

# <a name="cal">Calculation</a>

Both MetricTracer and MetricQueryPool collect the data in hardware specific, raw form that is not suitable
for application processing. To calculate metric values use ::xetMetricGroupCalculateData.

- In order to obtain available raw report count the user should call ::xetMetricTracerReadData or
  ::xetMetricQueryGetData with rawSize(0) and pRawData(nullptr)
```c
    xetMetricTracerReadData( hMetricTracer, &reportCount, 0, nullptr );
    xetMetricQueryGetData( hMetricQuery, &reportCount, 0, nullptr );
```

- In order to obtain raw reports the user should use ::xetMetricTracerReadData or ::xetMetricQueryGetData
  function with below arguments:
 - pReportCount: report count to read
 - rawDataSize: raw buffer size allocated and passed by the user
 - pRawData: buffer for raw reports
```c
    xetMetricTracerReadData( hMetricTracer, &reportCount, rawDataSize, pRawData );
    xetMetricQueryGetData( hMetricQuery, &reportCount, rawDataSize, pRawData );
```

- In order to calculate metrics from raw data the user should use ::xetMetricGroupCalculateData with
  below arguments:
 - hMetricGroup: handle of the metric group
 - pReportCount: report count to calculate
 - rawDataSize:  buffer size with raw reports to calculate 
 - rawData: buffer with raw reports to calculate 
 - calculatedDataSize - buffer size for calculated reports
 - pCalculatedData - buffer for calculated reports allocated by the user
```c
    xetMetricGroupCalculateData( hMetricTracer, &reportCount, rawDataSize, pRawData );
```


