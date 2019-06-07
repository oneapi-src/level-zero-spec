# Programming Guide (Tools)

[DO NOT EDIT]: # (generated from /scripts/tools/PROG.md)

The following documents the high-level programming models and guidelines.  

NOTE: This is a **PRELIMINARY** specification, provided for review and feedback.

## Table of Contents
* [Metrics](#md)
* [Program Instrumentation](#pin)
* [Program Debug](#dbg)
* [API Tracing](#at)
* [Power](#pm)
* [System Management](#sm)

# <a name="md">Metrics</a>

## Introduction
Devices provide programmable infrastructure designed to support performance debugging. The API
described in this document provides access to these device metrics.

Most of the detailed metrics require the device to be properly programmed by the driver. It is
important to understand that the device programming is in most cases global. This generally means
that if a software tool or an application is using the metrics then no other application
can reliably use the same device resources.

The intention of this API is to support performance debug and it is not advised to use it in regular execution.

### Software abstraction of device counting
The device infrastucture consists of non-programmable pre-defined set of counters, a programmable
network of connections that work with a separate set of counters as well as other types of counters.
For sake of simplicity the smallest unit of configuration is a Metric Group. Metric Groups are
sets of metrics that provide certain perspective on workload's performance. The groups aggregate metrics,
define device programming and available collection methods. An application may choose to collect data
from a number of Metric Groups provided that they all belong to different domains. [Domains](#dom) are used
as a software representation of independent device resources that can safely be used concurrently.

### Sampling types
Sampling types are a software representation of device capabilities in terms of reading metric values.
Each Metric Group provides information which sampling types it supports.
There are separate sets of APIs supporting each of the sampling types [Time based](#tbs) and [Query based](#queries).

All available sampling types are defined in ::xet_metric_group_sampling_type_t.
- Information about supported sampling types for a given Metric Group is provided in 
  ::xet_metric_group_properties_t.samplingType.
- It's possible that Xe provides multiple Metric Groups with the same names but different sampling types.
- When enumerating, it's important to choose a Metric Group which supports the desired sampling type.

### <a name="dom">Domains</a>
Every Metric Group belongs to a given domain (::xet_metric_group_properties_t.domain). 
- Each domain represents an exclusive resource used by the Metric Group.
- It's possible to simultaneously gather data for two different Metric Groups, only if they belong
  to a different domain i.e. Metric Groups that can be collected concurrently will have different domain values.

## <a name="enu">Enumeration</a>
A common tool flow is to enumerate metrics looking for specific Metric Groups and/or Metrics.
Depending on the metrics required for a specific scenario a tool may choose to run the workload multiple times
recording different set of Metric Groups each time.
Usually care must be taken to ensure run to run stability and result repeatability if metrics from different runs are meant to be used together.

All available metrics are organized into Metric Groups.
- If required, a Metric Group contains a uniform device counter configuration used for measurements.
  The programming is not exposed in the API.
- During data collection, data for the whole Metric Group is gathered.
- Metric Group names don't have to be unique.
- List of available Metric Groups and Metrics depends on device and driver.

Each level of the metrics hierarchy (MetricGroups and Metrics) provides all the information needed for
its identification and usage.
- Metric Group properties are accessed through function ::xetMetricGroupGetProperties, returning
  ::xet_metric_group_properties_t.
- Metric properties are accessed through function ::xetMetricGetProperties, returning
  ::xet_metric_properties_t.

![Metrics](../images/tools_metric_hierarchy.png?raw=true)  
@image latex tools_metric_hierarchy.png

When enumerating Metric tree to find a desired Metric Group, it's important to know in advance with
which sampling type it will be used. 

To enumerate through the Metric tree:
1. Call ::xetMetricGroupGet to obtain Metric Group count.
2. Call ::xetMetricGroupGet to obtain all Metric Groups.
3. Iterate over all available Metric Groups.
    - At this point it's possible to check e.g. Metric Group name, domain or sampling type.
4. For each Metric Group obtain their Metric count calling ::xetMetricGroupGetProperties with
   Metric Group handle (::xet_metric_group_handle_t) and checking ::xet_metric_group_properties_t.metricCount.
5. Iterate over available Metrics using ::xetMetricGet with parent Metric Group (::xet_metric_group_handle_t).
6. Check Metric properties (e.g. name, description) calling ::xetMetricGetProperties with parent
   Metric (::xet_metric_handle_t).


The following sample code demonstrates a basic enumaration over all available metric groups and their metrics.
Additionally, it returns a metric group with a chosen name and sampling type. Similar code could be used
for selecting a preferred metric group for a specific type of measurements.
```c
    xe_result_t FindMetricGroup( xe_device_group_handle_t hDeviceGroup, char* pMetricGroupName, uint32_t desiredSamplingType, xet_metric_group_handle_t* phMetricGroup )
    {
        // Obtain available metric groups for the specific device group
        uint32_t metricGroupCount = 0;
        xetMetricGroupGet( hDeviceGroup, &metricGroupCount, nullptr );

        xet_metric_group_handle_t* phMetricGroups = malloc(metricGroupCount * sizeof(xet_metric_group_handle_t));
        xetMetricGroupGet( hDeviceGroup, &metricGroupCount, phMetricGroups );

        // Interate over all metric groups available
        for( uint32_t i = 0; i < metricGroupCount; i++ )
        {   
            // Get metric group under index 'i' and its properties
            xet_metric_group_properties_t metricGroupProperties;
            xetMetricGroupGetProperties( phMetricGroups[i], &metricGroupProperties );

            printf("Metric Group: %s\n", metricGroupProperties.name);

            // Check whether the obtained metric group supports the desired sampling type
            if((metricGroupProperties.samplingType & desiredSamplingType) == desiredSamplingType)
            {   
                // Check whether the obtained metric group has the desired name
                if( strcmp( pMetricGroupName, metricGroupProperties.name ) == 0 )
                {
                    *phMetricGroup = phMetricGroups[i];
                    break;
                }
            }
        }

        free(phMetricGroups);
    }
```

## <a name="con">Configuration</a>
Use the ::xetDeviceActivateMetricGroups API call to configure the device for data collection.
- Subsequent calls to the function will disable device programming for the metric groups not selected for activation.
- To avoid bogous data only call the ::xetDeviceActivateMetricGroups between experiments i.e. while not collecting data.

Programming restrictions:
- Any combination of metric groups can be configured simultanously provided that all of them have
  different ::xet_metric_group_properties_t.domain.
- MetricGroup must be active until ::xetMetricQueryGetData and ::xetMetricTracerClose.
- Conflicting Groups cannot be activated, in such case the call to TODO ... would fail.

## <a name="col">Collection</a>
There are two modes of metrics collection supported: time based and query based.
- Time based collection is using a timer as well as other events to store data samples in circular buffer.
  A metric tracer interface is a software interface for configuration and collection.
- Query based metrics collection is based on a pair of Begin/End events appended to command lists.
  Query result generally characterizes device behavior between those events.

### <a name="tbs">Time Based</a>
Time based collection is using a simple Open/Wait/Read/Close scheme:
- ::xetMetricTracerOpen opens the tracer.
- ::xeEventHostSynchronize and ::xeEventQueryStatus can be used to wait for data.
- ::xetMetricTracerReadData reads the data.
- ::xetMetricTracerClose closes the tracer.

**Note:** To avoid incorrect data, do not reconfigure the device using ::xetDeviceActivateMetricGroups while the tracer is opened.

![MetricTracer](../images/tools_metric_tracer.png?raw=true)  
@image latex tools_metric_tracer.png


The following sample code demonstrates a basic sequence for time based collection:
```c
    xe_result_t TimeBasedUsageExample( xe_device_group_handle_t hDeviceGroup, xe_device_handle_t hDevice )
    {
        xet_metric_group_handle_t     hMetricGroup           = nullptr;
        xe_event_handle_t            hNotificationEvent     = nullptr;
        xe_event_pool_handle_t       hEventPool             = nullptr;
        xe_event_pool_desc_t         eventPoolDesc          = {XE_EVENT_POOL_DESC_VERSION_CURRENT, XE_EVENT_POOL_FLAG_DEFAULT , 1};
        xe_event_desc_t              eventDesc              = {XE_EVENT_DESC_VERSION_CURRENT};
        xet_metric_tracer_handle_t    hMetricTracer          = nullptr;
        xet_metric_tracer_desc_t      metricTracerDescriptor = {XET_METRIC_TRACER_DESC_VERSION_CURRENT}; 

        // Find a "ComputeBasic" metric group suitable for Time Based collection
        FindMetricGroup( hDeviceGroup, "ComputeBasic", XET_METRIC_GROUP_SAMPLING_TYPE_TIME_BASED, &hMetricGroup );

        // Configure the HW
        xetDeviceActivateMetricGroups( hDevice, 1 /* count */, &hMetricGroup );

        // Create notification event
        xeEventPoolCreate( hDeviceGroup, &eventPoolDesc, 1, &hDevice, &hEventPool );
        eventDesc.index  = 0;
        eventDesc.signal = XE_EVENT_SCOPE_FLAG_HOST;
        eventDesc.wait   = XE_EVENT_SCOPE_FLAG_HOST; 
        xeEventCreate( hEventPool, &eventDesc, &hNotificationEvent );
        
        // Open time based sampling
        metricTracerDescriptor.samplingPeriod   	= 1000;
        metricTracerDescriptor.notifyEveryNReports  = 32768;
        xetMetricTracerOpen( hDevice, hMetricGroup, &metricTracerDescriptor, hNotificationEvent, &hMetricTracer );

        // Run your workload, in this example we assume the data for the whole experiment fits in the device buffer
        Workload(hDevice);
        // Optionally insert markers during workload execution
        //xetCommandListAppendMetricTracerMarker( hCommandList, hMetricTracer, tool_marker_value ); 

        // Wait for data, optional in this example since the whole workload has already been executedby now
        //xeEventHostSynchronize( hNotificationEvent, 1000 /*timeout*/ );
        // reset the event if it fired

        // Read raw data
        size_t rawSize = 0;
        xetMetricTracerReadData( hMetricTracer, &rawSize, nullptr );
        uint8_t* rawData = malloc(rawSize); 
        xetMetricTracerReadData( hMetricTracer, &rawSize, rawData );

        // Close metric tracer
        xetMetricTracerClose( hMetricTracer );   
        xeEventDestroy( hNotificationEvent );
        xeEventPoolDestroy( hEventPool );

        // Deconfigure the device
        xetDeviceActivateMetricGroups( hDevice, 0, nullptr );

        // Calculate metric data
        CalculateMetricsExample( hMetricGroup, rawSize, rawData );
    }
```

### <a name="queries">Queries</a>
Query API provides a way of acquiring metrics per portions of workload delimited by BEGIN/END events.
Typically, multiple queries are used to characterize a workload so the API is pool based.

- A metric query pool is created and destroyed using ::xetMetricQueryPoolCreate and ::xetMetricQueryPoolDestroy calls.
- To work with individual query object, use ::xetMetricQueryCreate to get a handle.
- Then insert BEGIN/END events into a command list using ::xetCommandListAppendMetricQueryBegin and ::xetCommandListAppendMetricQueryEnd calls.
- Once the workload has been executed the ::xetMetricQueryGetData returns the raw data to be later processed by ::xetMetricGroupCalculateData.

![MetricQuery](../images/tools_metric_query.png?raw=true)  
@image latex tools_metric_query.png

The following sample code demonstrates a basic sequence for query based collection:
```c
    xe_result_t MetricQueryUsageExample( xe_device_group_handle_t hDeviceGroup, xe_device_handle_t hDevice )
    {
        xet_metric_group_handle_t      hMetricGroup          = nullptr;
        xe_event_handle_t             hCompletionEvent      = nullptr;
        xe_event_pool_desc_t          eventPoolDesc         = {XE_EVENT_POOL_DESC_VERSION_CURRENT};
        xe_event_desc_t               eventDesc             = {XE_EVENT_DESC_VERSION_CURRENT};
        xe_event_pool_handle_t        hEventPool            = nullptr;
        xet_metric_query_pool_handle_t hMetricQueryPool      = nullptr;
        xet_metric_query_handle_t      hMetricQuery          = nullptr;
        xet_metric_query_pool_desc_t   queryPoolDesc         = {XET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT};
    
        // Find a "ComputeBasic" metric group suitable for Event Based collection
        FindMetricGroup( hDeviceGroup, "ComputeBasic", XET_METRIC_GROUP_SAMPLING_TYPE_EVENT_BASED, &hMetricGroup );

        // Configure HW
        xetDeviceActivateMetricGroups( hDevice, 1 /* count */, &hMetricGroup );

        // Create metric query pool & completion event
        queryPoolDesc.flags        = XET_METRIC_QUERY_POOL_FLAG_PERFORMANCE;
        queryPoolDesc.count        = 1000;
        xetMetricQueryPoolCreate( hDevice, hMetricGroup, &queryPoolDesc, &hMetricQueryPool );
        eventPoolDesc.flags = XE_EVENT_POOL_FLAG_DEFAULT;
        eventPoolDesc.count = 1000;
        xeEventPoolCreate( hDeviceGroup, &eventPoolDesc, 1, &hDevice, &hEventPool );

        // Write BEGIN metric query to command list 
        xetMetricQueryCreate( hMetricQueryPool, 0 /*slot*/, &hMetricQuery );
        xetCommandListAppendMetricQueryBegin( hCommandList, hMetricQuery );

        // build your command list

        // Write END metric query to command list, use an event to determine if the data is available
        eventDesc.index  = 0;
        eventDesc.signal = XE_EVENT_SCOPE_FLAG_HOST;
        eventDesc.wait   = XE_EVENT_SCOPE_FLAG_HOST; 
        xeEventCreate( hEventPool, &eventDesc, &hCompletionEvent);
        xetCommandListAppendMetricQueryEnd( hCommandList, hMetricQuery, hCompletionEvent );

        // use xeCommandQueueExecuteCommandLists( , , , ) to submit your workload to the device
   
        // Wait for data
        xeEventHostSynchronize( hCompletionEvent, 1000 /*timeout*/ );

        // Read raw data
        size_t rawSize = 0;
        xetMetricQueryGetData( hMetricQuery, &rawSize, nullptr );
        uint8_t* rawData = malloc(rawSize); 
        xetMetricQueryGetData( hMetricQuery, &rawSize, rawData );

        // Free the resources
        xeEventDestroy( hCompletionEvent );
        xeEventPoolDestroy( hEventPool );
        xetMetricQueryPoolDestroy( hMetricQueryPool );

        // Deconfigure HW
        xetDeviceActivateMetricGroups( hDevice, 0, nullptr );

        // Calculate metric data
        CalculateMetricsExample( hMetricGroup, rawSize, rawData );
    }
```

## <a name="cal">Calculation</a>
Both MetricTracer and MetricQueryPool collect the data in device specific, raw form that is not suitable
for application processing. To calculate metric values use ::xetMetricGroupCalculateData.

The following sample code demonstrates a basic sequence for metric calculation and interpretation:
```c
    xe_result_t CalculateMetricsExample( xet_metric_group_handle_t hMetricGroup, size_t rawSize, uint8_t* rawData )
    {
        // Calculate metric data
        uint32_t calculatedDataCount = 0;
        xetMetricGroupCalculateData( hMetricGroup, rawSize, rawData, &calculatedDataCount, nullptr );
        xet_typed_value_t* calculatedData = malloc( calculatedDataCount * sizeof(xet_typed_value_t) );
        xetMetricGroupCalculateData( hMetricGroup, rawSize, rawData, &calculatedDataCount, calculatedData );

        // Obtain available metrics for the specific metric group
        uint32_t metricCount = 0;
        xetMetricGet( hMetricGroup, &metricCount, nullptr );

        xet_metric_handle_t* phMetrics = malloc(metricCount * sizeof(xet_metric_handle_t));
        xetMetricGet( hMetricGroup, &metricCount, phMetrics );

        // Print metric results
        uint32_t numReports = calculatedDataCount / metricCount;
        for( uint32_t report = 0; report < numReports; ++report )
        {
            printf("Report: %d\n", report);

            for( uint32_t metric = 0; metric < metricCount; ++metric )
            {
                xet_typed_value_t data = calculatedData[report * metricCount + metric];

                xet_metric_properties_t metricProperties;
                xetMetricGetProperties( phMetrics[ metric ], &metricProperties );

                printf("Metric: %s\n", metricProperties.name );

                switch( data.type )
                {
                case XET_VALUE_TYPE_UINT32:
                    printf(" Value: %lu\n", data.value.ui32 );
                    break;
                case XET_VALUE_TYPE_UINT64:
                    printf(" Value: %llu\n", data.value.ui64 );
                    break;
                case XET_VALUE_TYPE_FLOAT32:
                    printf(" Value: %f\n", data.value.fp32 );
                    break;
                case XET_VALUE_TYPE_FLOAT64:
                    printf(" Value: %f\n", data.value.fp64 );
                    break;
                case XET_VALUE_TYPE_BOOL8:
                    if( data.value.ui32 )
                        printf(" Value: true\n" );
                    else
                        printf(" Value: false\n" );
                    break;
                default:
                    break;
                };
            }
        }
    }
```

# <a name="pm">Power</a>

## Introduction


# <a name="sm">System Management</a>

## Introduction
