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

${"##"} Table of Contents
* [Initialization](#init)
* [API Tracing](#at)
* [Metrics](#md)
* [Program Instrumentation](#pin)
* [Program Debug](#dbg)

${"#"} <a name="init">Initialization</a>
The driver must be initialized by calling ::${t}Init after calling ::${x}Init and before calling any other experimental function.
Simultaneous calls to ::${t}Init are thread-safe.

${"#"} <a name="at">API Tracing</a>

${"##"} Introduction
API tracing provides a way for tools to recieve notifications of API calls made by an applicaton.
The callbacks provide direct access to the input and output parameters for viewing and modification.
Tools may also use these notifications as triggers to block and inject new API calls into the command stream, such as metrics.

${"##"} Registration
Tools may independently register for enter and exist callbacks for individual API calls, per driver instance.
* ::${t}TracerSetPrologues is used to specify all the enter callbacks
* ::${t}TracerSetEpilogues is used to specify all the exist callbacks
* If the value of a callback is nullptr, then it will be ignored.

The callbacks are defined as a collection of per-API function pointers, with the following parameters:
* params : a structure capturing pointers to the input and output parameters of the current instance
* result : the current value of the return value
* pTracerUserData : the user's pointer for the tracer's data
* ppTracerInstanceUserData : a per-tracer, per-instance storage location; typically used for passing data from the prologue to the epilogue

Since the creation of a tracer requires a driver handle, on first glance it appears that ::${x}Init and ::${x}DriverGet are not traceable.
However, these APIs are traceable for calls **subsequent** to the creation and enabling of the tracer,
only on the driver which the tracer was created.

${"##"} Enabling/Disabling and Destruction
The tracer is created in a disabled state and must be explicitly enabled by calling ::${t}TracerSetEnabled.
The implementation gaurentees that prologues and epilogues will always be executed in pairs; i.e.
* if the prologue was called then the epilogue is gaurenteed to be called, even if another thread disabled the tracer between execution
* if the prologue was not called then the epilogue is gaurenteed not to be called, even if another thread enabled the tracer between execution

The tracer should be disabled by the application before the tracer is destoryed. 
If multiple threads are in-flight, then it is still possbile that callbacks will continue to execute even after the tracer is disabled;
specifically due to the pairing rules above.
Due to the complexity involved in ensuring no threads are still or will be executing a callback even after its been disabled,
the implementation will stall and wait for any outstanding threads during ::${t}TracerDestroy.

The following sample code demonstrates a basic usage of API tracing:
```c
## --validate=off
    typedef struct _my_tracer_data_t
    {
        uint32_t instance;
    } my_tracer_data_t;

    typedef struct _my_instance_data_t
    {
        clock_t start;
    } my_instance_data_t;

    void OnEnterCommandListAppendLaunchKernel(
        ${x}_command_list_append_launch_function_params_t* params,
        ${x}_result_t result,
        void* pTracerUserData,
        void** ppTracerInstanceUserData )
    {
        my_instance_data_t* instance_data = malloc( sizeof(my_instance_data_t) );
        *ppTracerInstanceUserData = instance_data;
        
        instance_data->start = clock();
    }

    void OnExitCommandListAppendLaunchKernel(
        ${x}_command_list_append_launch_function_params_t* params,
        ${x}_result_t result,
        void* pTracerUserData,
        void** ppTracerInstanceUserData )
    {
        clock_t end = clock();
        
        my_tracer_data_t* tracer_data = (my_tracer_data_t*)pTracerUserData;
        my_instance_data_t* instance_data = *(my_instance_data_t**)ppTracerInstanceUserData;
        
        float time = 1000.f * ( end - instance_data->start ) / CLOCKS_PER_SEC;
        printf("${x}CommandListAppendLaunchKernel #%d takes %.4f ms\n", tracer_data->instance++, time);
        
        free(instance_data);
    }
## --validate=on

    void TracingExample( ... )
    {
        my_tracer_data_t tracer_data = {};
        ${t}_tracer_desc_t tracer_desc;
        tracer_desc.version = ${T}_TRACER_DESC_VERSION_CURRENT;
        tracer_desc.pUserData = &tracer_data;
        ${t}_tracer_handle_t hTracer;
        ${t}TracerCreate(hDriver, &tracer_desc, &hTracer);

        // Set all callbacks
        ${t}_core_callbacks_t prologCbs = {};
        ${t}_core_callbacks_t epilogCbs = {};
        prologCbs.CommandList.pfnAppendLaunchFunction = OnEnterCommandListAppendLaunchKernel;
        epilogCbs.CommandList.pfnAppendLaunchFunction = OnExitCommandListAppendLaunchKernel;

        ${t}TracerSetPrologues(hTracer, &prologCbs, nullptr);
        ${t}TracerSetEpilogues(hTracer, &epilogCbs, nullptr);

        ${t}TracerSetEnabled(hTracer, true);

        ${x}CommandListAppendLaunchKernel(hCommandList, hFunction, &launchArgs, nullptr, 0, nullptr);
        ${x}CommandListAppendLaunchKernel(hCommandList, hFunction, &launchArgs, nullptr, 0, nullptr);
        ${x}CommandListAppendLaunchKernel(hCommandList, hFunction, &launchArgs, nullptr, 0, nullptr);

        ${t}TracerSetEnabled(hTracer, false);
        ${t}TracerDestroy(hTracer);
    }
```


${"#"} <a name="md">Metrics</a>

${"##"} Introduction
Devices provide programmable infrastructure designed to support performance debugging. The API
described in this document provides access to these device metrics.

The following diagram illustrates the relationship between the metric objects described in this document.  
![Metrics](../images/tools_metric_hierarchy.png?raw=true)  
@image latex tools_metric_hierarchy.png

Most of the detailed metrics require the device to be properly programmed before use. It is
important to understand that the device programming is in most cases global. This generally means
that if a software tool or an application is using the metrics then no other application
can reliably use the same device resources.

The use of some metrics may negatively impact the performance of the device.
The intention of this API is to support performance debug and it is not advised to use it in regular execution.

${"##"} Metric Groups
The device infrastucture consists of non-programmable, pre-defined set of counters, and a programmable
network of connections that work with a separate set of counters as well as other types of counters.
For sake of simplicity, the smallest unit of configuration is a Metric Group. Metric Groups are
sets of metrics that provide certain perspective on workload's performance. The groups aggregate metrics,
define device programming and available collection methods. An application may choose to collect data
from a number of Metric Groups provided that they all belong to different domains. [Domains](#dom) are used
as a software representation of independent device resources that can safely be used concurrently.

${"###"} Sampling Types
Sampling types are a software representation of device capabilities in terms of reading metric values.
Each Metric Group provides information which sampling types it supports.
There are separate sets of APIs supporting each of the sampling types [Time-based](#tbs) and [Event-based](#query).

All available sampling types are defined in ::${t}_metric_group_sampling_type_t.
- Information about supported sampling types for a given Metric Group is provided in 
  ::${t}_metric_group_properties_t.samplingType.
- It's possible that a device provides multiple Metric Groups with the same names but different sampling types.
- When enumerating, it's important to choose a Metric Group which supports the desired sampling type.

${"###"} <a name="dom">Domains</a>
Every Metric Group belongs to a given domain (::${t}_metric_group_properties_t.domain). 
- The Metric Group typically define a uniform device counter configuration used for measurements.
- Each domain represents an exclusive resource used by the Metric Group.
- It's possible to simultaneously gather data for two different Metric Groups, only if they belong
  to a different domain i.e. Metric Groups that can be collected concurrently will have different domain values.

${"##"} <a name="enu">Enumeration</a>
All available metrics are organized into Metric Groups.
- During data collection, data for the whole Metric Group is gathered.
- The list of available Metric Groups and their Metrics is device-specific.

The following APIs provide all the information needed for identification and usage.
- Metric Group properties are accessed through function ::${t}MetricGroupGetProperties, returning
  ::${t}_metric_group_properties_t.
- Metric properties are accessed through function ::${t}MetricGetProperties, returning
  ::${t}_metric_properties_t.

A common tool flow is to enumerate metrics looking for a specific Metric Group.
Depending on the metrics required for a specific scenario a tool may choose to run the workload multiple times,
recording different set of Metric Groups each time.
Usually care must be taken to ensure run-to-run stability and result repeatability if metrics from different runs are meant to be used together.
When enumerating Metric tree to find a desired Metric Group, it's important to know in advance which sampling type it will be used. 

To enumerate through the Metric tree:
1. Call ::${t}MetricGroupGet to obtain Metric Group count.
2. Call ::${t}MetricGroupGet to obtain all Metric Groups.
3. Iterate over all available Metric Groups.
    - At this point it's possible to check e.g. Metric Group name, domain or sampling type.
    - Metric Group names may not be unique.
4. For each Metric Group obtain their Metric count calling ::${t}MetricGroupGetProperties with
   Metric Group handle (::${t}_metric_group_handle_t) and checking ::${t}_metric_group_properties_t.metricCount.
5. Iterate over available Metrics using ::${t}MetricGet with parent Metric Group (::${t}_metric_group_handle_t).
6. Check Metric properties (e.g. name, description) calling ::${t}MetricGetProperties with parent
   Metric (::${t}_metric_handle_t).


The following sample code demonstrates a basic enumeration over all available metric groups and their metrics.
Additionally, it returns a metric group with a chosen name and sampling type. Similar code could be used
for selecting a preferred metric group for a specific type of measurements.
```c
    ${x}_result_t FindMetricGroup( ${x}_device_handle_t hDevice,
                                   char* pMetricGroupName,
                                   uint32_t desiredSamplingType,
                                   ${t}_metric_group_handle_t* phMetricGroup )
    {
        // Obtain available metric groups for the specific device
        uint32_t metricGroupCount = 0;
        ${t}MetricGroupGet( hDevice, &metricGroupCount, nullptr );

        ${t}_metric_group_handle_t* phMetricGroups = malloc(metricGroupCount * sizeof(${t}_metric_group_handle_t));
        ${t}MetricGroupGet( hDevice, &metricGroupCount, phMetricGroups );

        // Iterate over all metric groups available
        for( uint32_t i = 0; i < metricGroupCount; i++ )
        {   
            // Get metric group under index 'i' and its properties
            ${t}_metric_group_properties_t metricGroupProperties;
            ${t}MetricGroupGetProperties( phMetricGroups[i], &metricGroupProperties );

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

${"##"} <a name="con">Configuration</a>
Use the ::${t}DeviceActivateMetricGroups API call to configure the device for data collection.
- Subsequent calls to the function will disable device programming for the metric groups not selected for activation.
- To avoid undefined results only call the ::${t}DeviceActivateMetricGroups between experiments i.e. while not collecting data.

Programming restrictions:
- Any combination of metric groups can be configured simultaneously provided that all of them have
  different ::${t}_metric_group_properties_t.domain.
- MetricGroup must be active until ::${t}MetricQueryGetData and ::${t}MetricTracerClose.
- Conflicting Groups cannot be activated, in such case the call to ::${t}DeviceActivateMetricGroups would fail.

${"##"} <a name="col">Collection</a>
There are two modes of metrics collection supported: time-based and event-based.
- Time-based collection is using a timer as well as other events to store data samples.
  A metric tracer interface is the software interface for configuration and collection.
- Event-based metrics collection is based on a pair of Begin/End events appended to command lists.
  A metric query interface is the software interface for configuration and collection.

${"###"} <a name="tbs">Metric Tracer</a>
Time-based collection uses a simple Open, Wait, Read, Close scheme:
- ::${t}MetricTracerOpen opens the tracer.
- ::${x}EventHostSynchronize and ::${x}EventQueryStatus can be used to wait for data.
- ::${t}MetricTracerReadData reads the data to be later processed by ::${t}MetricGroupCalculateMetricValues.
- ::${t}MetricTracerClose closes the tracer.

![MetricTracer](../images/tools_metric_tracer.png?raw=true)  
@image latex tools_metric_tracer.png


The following sample code demonstrates a basic sequence for tracer-based collection:
```c
    ${x}_result_t TimeBasedUsageExample( ${x}_driver_handle_t hDriver,
                                         ${x}_device_handle_t hDevice )
    {
        ${t}_metric_group_handle_t     hMetricGroup           = nullptr;
        ${x}_event_handle_t            hNotificationEvent     = nullptr;
        ${x}_event_pool_handle_t       hEventPool             = nullptr;
        ${x}_event_pool_desc_t         eventPoolDesc          = {${X}_EVENT_POOL_DESC_VERSION_CURRENT, ${X}_EVENT_POOL_FLAG_DEFAULT , 1};
        ${x}_event_desc_t              eventDesc              = {${X}_EVENT_DESC_VERSION_CURRENT};
        ${t}_metric_tracer_handle_t    hMetricTracer          = nullptr;
        ${t}_metric_tracer_desc_t      metricTracerDescriptor = {${T}_METRIC_TRACER_DESC_VERSION_CURRENT}; 

        // Find a "ComputeBasic" metric group suitable for Time Based collection
        FindMetricGroup( hDevice, "ComputeBasic", ${T}_METRIC_GROUP_SAMPLING_TYPE_TIME_BASED, &hMetricGroup );

        // Configure the HW
        ${t}DeviceActivateMetricGroups( hDevice, 1 /* count */, &hMetricGroup );

        // Create notification event
        ${x}EventPoolCreate( hDriver, &eventPoolDesc, 1, &hDevice, &hEventPool );
        eventDesc.index  = 0;
        eventDesc.signal = XE_EVENT_SCOPE_FLAG_HOST;
        eventDesc.wait   = XE_EVENT_SCOPE_FLAG_HOST; 
        ${x}EventCreate( hEventPool, &eventDesc, &hNotificationEvent );
        
        // Open metric tracer
        metricTracerDescriptor.samplingPeriod   	= 1000;
        metricTracerDescriptor.notifyEveryNReports  = 32768;
        ${t}MetricTracerOpen( hDevice, hMetricGroup, &metricTracerDescriptor, hNotificationEvent, &hMetricTracer );

        // Run your workload, in this example we assume the data for the whole experiment fits in the device buffer
        Workload(hDevice);
        // Optionally insert markers during workload execution
        //${t}CommandListAppendMetricTracerMarker( hCommandList, hMetricTracer, tool_marker_value ); 

        // Wait for data, optional in this example since the whole workload has already been executed by now
        //${x}EventHostSynchronize( hNotificationEvent, 1000 /*timeout*/ );
        // reset the event if it fired

        // Read raw data
        size_t rawSize = 0;
        ${t}MetricTracerReadData( hMetricTracer, UINT32_MAX, &rawSize, nullptr );
        uint8_t* rawData = malloc(rawSize); 
        ${t}MetricTracerReadData( hMetricTracer, UINT32_MAX, &rawSize, rawData );

        // Close metric tracer
        ${t}MetricTracerClose( hMetricTracer );   
        ${x}EventDestroy( hNotificationEvent );
        ${x}EventPoolDestroy( hEventPool );

        // Deconfigure the device
        ${t}DeviceActivateMetricGroups( hDevice, 0, nullptr );

        // Calculate metric data
        CalculateMetricsExample( hMetricGroup, rawSize, rawData );
        free(rawData);
    }
```

${"###"} <a name="query">Metric Query</a>
Event-based collection uses a simple Begin, End, GetData scheme:
- ::${t}CommandListAppendMetricQueryBegin defines the start counting event
- ::${t}CommandListAppendMetricQueryEnd defines the finish counting event
- ::${t}MetricQueryGetData reads the raw data to be later processed by ::${t}MetricGroupCalculateMetricValues.

Typically, multiple queries are used and recycled to characterize a workload.
A Query Pool is used to efficiently use and reuse device meory for multiple queries.
- ::${t}MetricQueryPoolCreate creates a pool of homogeneous queries.
- ::${t}MetricQueryPoolDestroy frees the pool. The application must ensure no queries within the pool are in-use before freeing the pool.
- ::${t}MetricQueryCreate obtains a handle to a unique location in the pool.
- ::${t}MetricQueryReset allows for low-cost recycling of a location in the pool.

![MetricQuery](../images/tools_metric_query.png?raw=true)  
@image latex tools_metric_query.png

The following sample code demonstrates a basic sequence for query-based collection:
```c
    ${x}_result_t MetricQueryUsageExample( ${x}_driver_handle_t hDriver,
                                           ${x}_device_handle_t hDevice )
    {
        ${t}_metric_group_handle_t      hMetricGroup          = nullptr;
        ${x}_event_handle_t             hCompletionEvent      = nullptr;
        ${x}_event_pool_desc_t          eventPoolDesc         = {${X}_EVENT_POOL_DESC_VERSION_CURRENT};
        ${x}_event_desc_t               eventDesc             = {${X}_EVENT_DESC_VERSION_CURRENT};
        ${x}_event_pool_handle_t        hEventPool            = nullptr;
        ${t}_metric_query_pool_handle_t hMetricQueryPool      = nullptr;
        ${t}_metric_query_handle_t      hMetricQuery          = nullptr;
        ${t}_metric_query_pool_desc_t   queryPoolDesc         = {${T}_METRIC_QUERY_POOL_DESC_VERSION_CURRENT};
    
        // Find a "ComputeBasic" metric group suitable for Event Based collection
        FindMetricGroup( hDevice, "ComputeBasic", ${T}_METRIC_GROUP_SAMPLING_TYPE_EVENT_BASED, &hMetricGroup );

        // Configure HW
        ${t}DeviceActivateMetricGroups( hDevice, 1 /* count */, &hMetricGroup );

        // Create metric query pool & completion event
        queryPoolDesc.flags        = ${T}_METRIC_QUERY_POOL_FLAG_PERFORMANCE;
        queryPoolDesc.count        = 1000;
        ${t}MetricQueryPoolCreate( hDevice, hMetricGroup, &queryPoolDesc, &hMetricQueryPool );
        eventPoolDesc.flags = ${X}_EVENT_POOL_FLAG_DEFAULT;
        eventPoolDesc.count = 1000;
        ${x}EventPoolCreate( hDriver, &eventPoolDesc, 1, &hDevice, &hEventPool );

        // Write BEGIN metric query to command list 
        ${t}MetricQueryCreate( hMetricQueryPool, 0 /*slot*/, &hMetricQuery );
        ${t}CommandListAppendMetricQueryBegin( hCommandList, hMetricQuery );

        // build your command list

        // Write END metric query to command list, use an event to determine if the data is available
        eventDesc.index  = 0;
        eventDesc.signal = XE_EVENT_SCOPE_FLAG_HOST;
        eventDesc.wait   = XE_EVENT_SCOPE_FLAG_HOST; 
        ${x}EventCreate( hEventPool, &eventDesc, &hCompletionEvent);
        ${t}CommandListAppendMetricQueryEnd( hCommandList, hMetricQuery, hCompletionEvent );

        // use ${x}CommandQueueExecuteCommandLists( , , , ) to submit your workload to the device
   
        // Wait for data
        ${x}EventHostSynchronize( hCompletionEvent, 1000 /*timeout*/ );

        // Read raw data
        size_t rawSize = 0;
        ${t}MetricQueryGetData( hMetricQuery, &rawSize, nullptr );
        uint8_t* rawData = malloc(rawSize); 
        ${t}MetricQueryGetData( hMetricQuery, &rawSize, rawData );

        // Free the resources
        ${x}EventDestroy( hCompletionEvent );
        ${x}EventPoolDestroy( hEventPool );
        ${t}MetricQueryPoolDestroy( hMetricQueryPool );

        // Deconfigure HW
        ${t}DeviceActivateMetricGroups( hDevice, 0, nullptr );

        // Calculate metric data
        CalculateMetricsExample( hMetricGroup, rawSize, rawData );
        free(rawData);
    }
```

${"##"} <a name="cal">Calculation</a>
Both MetricTracer and MetricQueryPool collect the data in device specific, raw form that is not suitable
for application processing. To calculate metric values use ::${t}MetricGroupCalculateMetricValues.

The following sample code demonstrates a basic sequence for metric calculation and interpretation:
```c
    ${x}_result_t CalculateMetricsExample( ${t}_metric_group_handle_t hMetricGroup,
                                           size_t rawSize, uint8_t* rawData )
    {
        // Calculate metric data
        uint32_t numMetricValues = 0;
        ${t}MetricGroupCalculateMetricValues( hMetricGroup, rawSize, rawData, &numMetricValues, nullptr );
        ${t}_typed_value_t* metricValues = malloc( numMetricValues * sizeof(${t}_typed_value_t) );
        ${t}MetricGroupCalculateMetricValues( hMetricGroup, rawSize, rawData, &numMetricValues, metricValues );

        // Obtain available metrics for the specific metric group
        uint32_t metricCount = 0;
        ${t}MetricGet( hMetricGroup, &metricCount, nullptr );

        ${t}_metric_handle_t* phMetrics = malloc(metricCount * sizeof(${t}_metric_handle_t));
        ${t}MetricGet( hMetricGroup, &metricCount, phMetrics );

        // Print metric results
        uint32_t numReports = numMetricValues / metricCount;
        for( uint32_t report = 0; report < numReports; ++report )
        {
            printf("Report: %d\n", report);

            for( uint32_t metric = 0; metric < metricCount; ++metric )
            {
                ${t}_typed_value_t data = metricValues[report * metricCount + metric];

                ${t}_metric_properties_t metricProperties;
                ${t}MetricGetProperties( phMetrics[ metric ], &metricProperties );

                printf("Metric: %s\n", metricProperties.name );

                switch( data.type )
                {
                case ${T}_VALUE_TYPE_UINT32:
                    printf(" Value: %lu\n", data.value.ui32 );
                    break;
                case ${T}_VALUE_TYPE_UINT64:
                    printf(" Value: %llu\n", data.value.ui64 );
                    break;
                case ${T}_VALUE_TYPE_FLOAT32:
                    printf(" Value: %f\n", data.value.fp32 );
                    break;
                case ${T}_VALUE_TYPE_FLOAT64:
                    printf(" Value: %f\n", data.value.fp64 );
                    break;
                case ${T}_VALUE_TYPE_BOOL8:
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

        free(metricValues);
        free(phMetrics);
    }
```

${"#"} <a name="pin">Program Instrumentation</a>

${"##"} Introduction
The program instrumentation APIs provide tools a basic framework for low-level profiling of device programs, 
by allowing direct instrumentation of those programs. These capabilities, in combination with those already provided,
in combination with API tracing, are sufficient for more advanced frameworks to be developed independently.

There are two type of instrumentation available:
1. Inter-Function Instrumentation - intercepting and redirecting function calls
2. Intra-Function Instrumentation - injecting new instructions within a function

${"##"} Inter-Function Instrumentation
The following capabilities allow for a tool to intercept and redirect function calls:
* Inter-module function calls - the ability to call functions between different modules; e.g., the application's module and a tool's module
* [API Tracing](#at)

For example, a tool may use API Tracing in any of the following ways:
* ::${x}ModuleCreate - replace a module handle with instrumented module handle for all functions
* ::${x}KernelCreate - replace a kernel handle with instrumented kernel handle for all call sites
* ::${x}ModuleGetFunctionPointer - replace a function pointer with instrumented function pointer for all call sites
* ::${x}CommandListAppendLaunchKernel - replace a kernel handle with instrumented kernel handle at call site

${"##"} Intra-Function Instrumentation
The following capabilities allow for a tool to inject instructions within a kernel:
* ::${t}ModuleGetDebugInfo - allows a tool to query standard debug info for an application's module
* ::${t}ModuleGetKernelNames - allows for a tool to query for all kernels within an application's module
* ::${t}KernelGetProfileInfo - allows a tool query detailed information on aspects of a kernel
* ::${x}ModuleGetNativeBinary - allows for a tool to retrieve the native binary of the application's module, instrument it, then create a new module using the intrumented version
* [API Tracing](#at) - same usage as Inter-Function Instrumentation above

${"###"} Compilation
A module must be compiled with foreknowledge that instrumentation will be performed in order for the compiler
to generate the proper profiling meta-data.
## --validate=off
Therefore, when the instrumentation layer is enabled, a new build flag is supported:
"-${t}-profile-flags <n>", where "<n>" must be a combination of ::${t}_profile_flag_t, in hexidecimal.
## --validate=on

As an example, a tool could use API Tracing to inject this build flag on each ::${x}ModuleCreate call 
that the tool wishes to instrument.
In another example, a tool could recompile a Module using the build flag and use API Tracing to replace the 
application's Module handle with it's own.

${"###"} Instrumentation
Once the module has been compiled with instrumentation enabled, a tool may use ::${t}ModuleGetDebugInfo and ::${t}KernelGetProfileInfo
in order to decode the application's instructions and register usage for each function in the module.

If a tool requires additional functions to be used, it may create other module(s) and use ::${x}ModuleGetFunctionPointer
to call functions between the application and tool modules.
A tool may use ::${x}ModuleGetFunctionPointer to retrieve the Host and device address of each function in the module.

There are no APIs provided for the actual instrumentation.  Instead this is left up to the tool itself to decode the application module's
native binary and inject native instructions.  This model prevents the instrumentation from being manipulated by
the compiler.

${"####"} Profile Info
TODO: need a picture and write-up from GT-PIN/IGC team on how to use the profile info.

${"###"} Execution
If a tool requires changing the address of an application's function, then it should use API Tracing; for example,
::${x}ModuleGetFunctionPointer and all flavors of ::${x}CommandListAppendLaunchKernel.


${"#"} <a name="dbg">Program Debug</a>

${"##"} Introduction

The program debug APIs provide tools a basic framework for debugging
device code.

The APIs operate on a single device.  When debugging a multi-device
system, the tool would debug each device independently.  The APIs further
operate in the context of a single host process.  When debugging multiple
host processes at the same time, the tool would debug device code
submitted by each host process independently.


${"##"} Attach and Detach

In order to use most of the program debug APIs, a tool needs to attach to
a device by calling ::${t}DebugAttach.  As arguments it passes the
::${x}_device_handle_t and a pointer to a ::${t}_debug_config_t object
that contains the following fields:

  * the requested program debug API version.  Version numbers start at one
    with zero reserved to denote an invalid version.

    All other fields depend on the requested version.  Version one defines
    the following fields:

      * the host process identifier.


If the requested API version is not supported,
::${X}_RESULT_ERROR_UNSUPPORTED is returned.  If the tool supports
different API versions it may try to request a different version.

If the requested API version is supported the following properties are
checked:

  * the requested host process must exist.

  * the tool process must be allowed to debug the requested host process.

    Note that the tool does not need to be attached to the host process
    itself, yet it must have permission to debug the host process.

  * there must be no other tool attached for the requested host process.

    Note that this refers to the device code of that host process, not to
    the host process itself.

  * device debug must be enabled on this system.


If permission is granted, a ::${t}_debug_session_handle_t is provided,
which can be used in other program debug APIs until the tool detaches
again.  The requested API version will be used for all API functions.

To detach a debug session, a tool calls ::${t}DebugDetach passing the
::${t}_debug_session_handle_t that had been provided on the corresponding
::${t}DebugAttach call.

The following sample code demonstrates attaching and detaching:

```c
    ${x}_device_handle_t device = ...;
    ${t}_debug_session_handle_t session;
    ${t}_debug_config_t config;
    ${x}_result_t errcode;

    memset(&config, 0, sizeof(config));
    config.version = 1;
    config.variant.v1.pid = ...;

    errcode = ${t}DebugAttach(device, &config, &session);
    if (errcode)
        return errcode;

    ...

    errcode = ${t}DebugDetach(session);
    if (errcode)
        return errcode;
```


${"###"} Devices and Sub-Devices

A tool may attach to any device and will implicitly be attached to all
sub-devices below that device.

Implementations that use separate code segments per sub-device may further
allow attaching to sub-devices individually.  In that case, a tool may
choose to either attach to the device or to one or more sub-devices.

When attached to a sub-device, writes to the code segment will not be
broadcast to sibling sub-devices, even though they may share the same
address space range.  This allows breakpoints to be contained within one
sub-device.

Once a tool is attached to a sub-device, any attempt to attach to an
ancestor device results in ::${X}_RESULT_ERROR_DEVICE_ACCESS.

Implementations that share code segments across sub-devices will only
allow attaching to devices.  Any attempt to attach to a sub-device results
in ::${X}_RESULT_ERROR_UNSUPPORTED.


${"###"} Device Thread Identification and Resource Restriction

Device threads are identified by their ordinal number starting from one
until the maximum number of threads on that device.  Device thread
identifiers are unique within the same debug session.

If a tool attached to a device, device threads are enumerated for all
sub-devices below that device.

Implementations that allow restricting the number of device threads may
enumerate less than the total number of threads supported by the device.
They may enumerate more threads than had been requested based on hardware
limitations and to allow for oversubmission.  Not all enumerated threads
may be available.

The number of device threads can be queried for each debug session using
the ::${t}DebugGetNumThreads call.


${"###"} Thread Availability

For some devices not all threads may be available at all times.  Some
threads may even not be available at any time.  This may have various
reasons, including:

  * the thread may be idle

  * the thread may be assigned to a different process

  * the thread may be part of an unused oversubmission buffer


For the purpose of this debug tool API, threads may be in one of three
states:

  * running

  * stopped

  * unavailable


Most API functions require the thread they operate on to be stopped.


${"##"} Debug Events

As long as the tool is attached, it will receive debug events from the
device.  To read the topmost event, the tool passes a pointer to a buffer
and its size in bytes.  The size of an event object is defined by the API
version requested on attach.

It also passes a timeout in milliseconds.  A timeout of zero does not wait
and immediately returns if no events are available.  A timeout of
::${T}_DEBUG_TIMEOUT_INFINITE waits indefinitely.  If the timeout expires,
::${X}_RESULT_NOT_READY is returned.

On success, the topmost event is copied into the buffer.

The following sample code demonstrates reading an event:

```c
    ${t}_debug_session_handle_t session = ...;
    ${t}_debug_event_t event;
    ${x}_result_t errcode;

    errcode = ${t}DebugReadEvent(session, ${T}_DEBUG_TIMEOUT_INFINITE, sizeof(event), &event);
    if (errcode)
        return errcode;
```


A debug event is described by the ::${t}_debug_event_t structure.  Note
that the declaration of this structure depends on the API version
requested on attach.  The current version contains:

  * The event type as ::${t}_debug_event_type_t.

  * The thread that reported the event.

    This is either the ordinal number of the thread on the device or one
    of the following special thread identifiers:

      * ::${T}_DEBUG_THREAD_NONE indicates no threads on the device.

      * ::${T}_DEBUG_THREAD_ALL indicates all threads on the device.

  * A bit-vector of ::${t}_debug_event_flags_t, which can be one of the
    following:

    * ::${T}_DEBUG_EVENT_FLAG_STOPPED indicates that the thread that
      reported the event is stopped and needs to be resumed in order to
      proceed.

      If the event was reported by ::${T}_DEBUG_THREAD_ALL, all threads
      have stopped and the tool may resume ::${T}_DEBUG_THREAD_ALL.  The
      tool may also resume individual threads.

      If the event was reported by ::${T}_DEBUG_THREAD_NONE, the event
      occured outside the context of any device thread, yet still blocks
      progress.  The tool needs to resume ::${T}_DEBUG_THREAD_NONE in
      order to acknowledge the event and unblock progress.

      Note that progress may not necessarily be blocked on the device on
      which the event occured.


Following the common fields, the event object contains event-specific
fields depending on the event type.  Not all events have event-specific
fields.

  * ::${T}_DEBUG_EVENT_DETACHED: the tool was detached.

    * The detach reason as ::${t}_debug_detach_reason_t.  This can be one
      of the following reasons:

        * ::${T}_DEBUG_DETACH_HOST_EXIT indicates that the host process
          exited.

  * ::${T}_DEBUG_EVENT_PROCESS_ENTRY: the host process created one or more
    command queues on the device.

  * ::${T}_DEBUG_EVENT_PROCESS_EXIT: the host process destroyed all
    command queues on the device.

  * ::${T}_DEBUG_EVENT_MODULE_LOAD: an in-memory module was loaded onto
    the device.

    The event is generated in the ::${x}ModuleCreate() flow with thread ==
    ::${T}_DEBUG_THREAD_NONE.  If ::${T}_DEBUG_EVENT_FLAG_STOPPED is set,
    the event blocks the ::${x}ModuleCreate() call until the debugger
    acknowledges the event by resuming ::${T}_DEBUG_THREAD_NONE.

    * The begin and end address of the in-memory module.  On all devices
      supported today, the module is an ELF file with optional DWARF debug
      information.

    * The load address of the module.

  * ::${T}_DEBUG_EVENT_MODULE_UNLOAD: an in-memory module is about to get
    unloaded from the device.

    The event is generated in the ::${x}ModuleDestroy() flow with thread
    == ::${T}_DEBUG_THREAD_NONE.  If ::${T}_DEBUG_EVENT_FLAG_STOPPED is
    set, the event blocks the ::${x}ModuleDestroy() call until the
    debugger acknowledges the event by resuming ::${T}_DEBUG_THREAD_NONE.

    * The begin and end address of the in-memory module.  On all devices
      supported today, the module is an ELF file with optional DWARF debug
      information.

    * The load address of the module.

  * ::${T}_DEBUG_EVENT_EXCEPTION: the thread stopped due to a device
    exception.


${"##"} Run Control

The tool may interrupt and resume individual device threads or an entire
debug session.

To interrupt an individual thread or an entire debug session, call
::${t}DebugInterrupt with the number of the thread to interrupt or
::${T}_DEBUG_THREAD_ALL to interrupt an entire debug session.

When interrupting an entire debug session, threads that are already
stopped as well as threads that are not available will be ignored.  After
threads have been interrupted, a ::${T}_DEBUG_EVENT_EXCEPTION event with
thread == ::${T}_DEBUG_THREAD_ALL is created.

To resume an individual thread or an entire debug session, call
::${t}DebugResume with the number of the thread to resume or
::${T}_DEBUG_THREAD_ALL to resume an entire debug session.

Whereas interrupting and resuming an entire debug session will
transparently handle unavailable threads, interrupting and resuming a
single unavailable thread will result in
::${X}_RESULT_ERROR_INVALID_ARGUMENT.

Threads that had been unavailable when interrupting a debug session will
be prevented from entering until the debug session is resumed.

The tool does not know whether any individual thread is available until it
tries to interact with that thread.  Only stopped threads may be resumed
individually.

The following sample code demonstrates how to interrupt and resume a debug
session:

```c
    ${t}_debug_session_handle_t session = ...;
    ${x}_result_t errcode;

    errcode = ${t}DebugInterrupt(session, ${T}_DEBUG_THREAD_ALL);
    if (errcode)
        return errcode;

    ...

    errcode = ${t}DebugResume(session, ${T}_DEBUG_THREAD_ALL);
    if (errcode)
        return errcode;
```

After interrupting one or all threads, the tool needs to wait for the
corresponding ::${T}_DEBUG_EVENT_EXCEPTION event.  Note that there may be
other events preceding that event.  There may further be exception events
for individual threads preceding or succeeding a debug session exception
event.


${"##"} Memory Access

A tool may read and write memory in the context of a stopped device thread
as if that thread had read or written the memory.

Memory may be partitioned into device-specific memory spaces.  Intel
graphics devices, for example, use the following memory spaces defined in
::${t}_debug_memory_space_intel_graphics_t:

  * 0: default memory space
  * 1: shared local memory space

The default memory space may also be accessed in the context of the
special ::${T}_DEBUG_THREAD_NONE thread.

To read and write memory, call the ::${t}DebugReadMemory and
::${t}DebugWriteMemory function, respectively.  The functions take a
::${t}_debug_session_handle_t, a thread handle, a memory space selector,
the virtual address of the memory to access, the size of the access, and
an input or output buffer.

The following example copies 16 bytes of memory from one location in the
context of one Intel graphics device thread to another location in the
default memory space.

```c
    ${t}_debug_session_handle_t session = ...;
    int memSpace = ...;
    uint64_t src = ..., dst = ...;
    uint64_t threadid = ...;
    uint8_t buffer[16];
    ${x}_result_t errcode;

    errcode = ${t}DebugReadMemory(session, threadid, memSpace, src,
                                  sizeof(buffer), buffer);
    if (errcode)
        return errcode;

    ...

    errcode = ${t}DebugWriteMemory(session, ${T}_DEBUG_THREAD_NONE,
                                   ${T}_DEBUG_MEMORY_SPACE_GEN_DEFAULT,
                                   dst, sizeof(buffer), buffer);
    if (errcode)
        return errcode;
```


${"##"} Register State Access

A tool may read and write the register state of a stopped device thread.
The register state is represented as a randomly accessible range of
memory.  It starts with a description of the memory layout followed by the
actual register state content.  The layout is fixed per device thread.

To read and write the register state, use the ::${t}DebugReadState and
::${t}DebugWriteState function, respectively.  They take a
::${t}_debug_session_handle_t, a thread handle, an offset into the
register state area, an access size in bytes, and an input or output
buffer.

The register state area starts with a ::${t}_debug_state_t descriptor
containing the following fields:

  * the size of the register state object in bytes

  * the size of the state descriptor in bytes.

    This also defines the offset of the register file descriptor array.

  * the size of each register file descriptor in bytes.

  * the number of register files contained in this state object.


The state descriptor is followed by an array of register file descriptors
starting at offset ::${t}_debug_state_t.headerSize of the register state
object.  Each describes one register file contained in the state object
via the following fields:

  * the register file type

    This is a device-specific enumeration.  See below for examples.

  * the register file version

    This defines variations of the same basic register file as it evolves
    over time.

    Version numbers start at one with zero reserved to denote an invalid
    or unsupported version of this register file.

    New registers are typically added to the end of a register file
    allowing tools to skip unknown portions while still providing limited
    support for that device.

  * The size of the register file in the register state object in bytes.

  * The offset of the register file in the register state object.


The following sample code demonstrates iterating over register files:

```c
    ${t}_debug_session_handle_t session = ...;
    uint64_t threadid = ...;
    ${t}_debug_state_t state;
    ${x}_result_t errcode;
    uint16_t sec;

    errcode = ${t}DebugReadState(session, threadid, 0ull, sizeof(state),
                                 &state);
    if (errcode)
        return errcode;

    for (sec = 0; sec < state.numSec; ++i) {
        ${t}_debug_state_section_t section;
        uint64_t offset;

        offset = state.headerSize + (state.secSize * sec);

        errcode = ${t}DebugReadState(session, threadid, offset,
                                     sizeof(section), &section);
        if (errcode)
            return errcode;

        ...
    }
```


Intel graphics devices, for example, provide:

  * ::${T}_DEBUG_STATE_GEN_GRF, the general register file.

    In version one, this register file consists of a homogeneous array of
    256 bit wide registers starting at `r0`.

  * ::${T}_DEBUG_STATE_GEN_ACC, the accumulator register file.

    In version one, this register file consists of a homogeneous array of
    256 bit wide registers starting at `acc0`.

  * ::${T}_DEBUG_STATE_GEN_ADDR, the address register file.

    In version one, this register file consists of a homogeneous array of
    256 bit wide registers starting at `a0`.  Each register is split into
    16 elements, each 16 bit wide.

  * ::${T}_DEBUG_STATE_GEN_FLAG, the flags register file.

    In version one, this register file consists of a homogeneous array of
    32 bit wide registers starting at `flag0`.  Each register is split
    into 2 elements, each 16 bit wide.


(to be continued...)
