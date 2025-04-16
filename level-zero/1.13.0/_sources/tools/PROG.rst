



.. _tools-programming-guide:

=========================
 Tools Programming Guide
=========================

Initialization
==============

Environment Variables
---------------------

The following environment variables are required to be enabled during :ref:`zeInit` for the respective feature.

+-----------------+-------------------------------------+------------+-----------------------------------------------------------------------------------+
| Category        | Name                                | Values     | Description                                                                       |
+=================+=====================================+============+===================================================================================+
| Tools           | ZET_ENABLE_API_TRACING_EXP          | {**0**, 1} | Enables driver instrumentation for API tracing                                    |
|                 |                                     |            | **Note**: This tracing environment variable is **deprecated**. Please use the     |
|                 |                                     |            | tracing loader layer instead.                                                     |
|                 +-------------------------------------+------------+-----------------------------------------------------------------------------------+
|                 | ZET_ENABLE_METRICS                  | {**0**, 1} | Enables driver instrumentation and dependencies for device metrics                |
|                 +-------------------------------------+------------+-----------------------------------------------------------------------------------+
|                 | ZET_ENABLE_PROGRAM_INSTRUMENTATION  | {**0**, 1} | Enables driver instrumentation and dependencies for program instrumentation       |
|                 +-------------------------------------+------------+-----------------------------------------------------------------------------------+
|                 | ZET_ENABLE_PROGRAM_DEBUGGING        | {**0**, 1} | Enables driver instrumentation and dependencies for program debugging             |
+-----------------+-------------------------------------+------------+-----------------------------------------------------------------------------------+

.. _API-Tracing:

API Tracing
===========

**Experimental Extension** - this feature will be removed post-1.0 and replaced with custom loader layers.

Introduction
------------

API tracing provides a way for tools to receive notifications of API
calls made by an application. The callbacks provide direct access to the
input and output parameters for viewing and modification. Tools may also
use these notifications as triggers to block and inject new API calls
into the command stream, such as metrics.

Registration
------------

Tools may independently register for enter and exit callbacks for individual API calls, per driver instance.

* :ref:`zetTracerExpSetPrologues` is used to specify all the enter callbacks
* :ref:`zetTracerExpSetEpilogues` is used to specify all the exit callbacks
* If the value of a callback is nullptr, then it will be ignored.

The callbacks are defined as a collection of per-API function pointers, with the following parameters:

* params : a structure capturing pointers to the input and output parameters of the current instance
* result : the current value of the return value
* pTracerUserData : the user's pointer for the tracer's data
* ppTracerInstanceUserData : a per-tracer, per-instance thread-local storage location; typically used for passing data from the prologue to the epilogue

Note: since the creation of a tracer requires a device, on first glance
it appears that :ref:`zeInit`\, :ref:`zeDriverGet` and :ref:`zeDeviceGet` are not
traceable. However, these APIs **are** traceable for all calls
subsequent from the creation and enabling of the tracer itself.

Enabling/Disabling and Destruction
----------------------------------

The tracer is created in a disabled state and must be explicitly enabled
by calling :ref:`zetTracerExpSetEnabled`\. The implementation guarantees that
prologues and epilogues will always be executed in pairs; i.e.

* if the prologue was called then the epilogue is guaranteed to be called, even if another thread disabled the tracer between execution
* if the prologue was not called then the epilogue is guaranteed not to be called, even if another thread enabled the tracer between execution

The tracer should be disabled by the application before the tracer is
destroyed. If multiple threads are in-flight, then it is still possible
that callbacks will continue to execute even after the tracer is
disabled; specifically, due to the pairing rules above. Due to the
complexity involved in ensuring no threads are still or will be
executing a callback even after its been disabled, the implementation
will stall and wait for any outstanding threads during :ref:`zetTracerExpDestroy`\.

The following pseudo-code demonstrates a basic usage of API tracing:


.. parsed-literal::

       typedef struct _my_tracer_data_t
       {
           uint32_t instance;
       } my_tracer_data_t;

       typedef struct _my_instance_data_t
       {
           clock_t start;
       } my_instance_data_t;

       void OnEnterCommandListAppendLaunchKernel(
           ze_command_list_append_launch_kernel_params_t* params,
           ze_result_t result,
           void* pTracerUserData,
           void** ppTracerInstanceUserData )
       {
           my_instance_data_t* instance_data = malloc( sizeof(my_instance_data_t) );
           \*ppTracerInstanceUserData = instance_data;
           
           instance_data->start = clock();
       }

       void OnExitCommandListAppendLaunchKernel(
           ze_command_list_append_launch_kernel_params_t* params,
           ze_result_t result,
           void* pTracerUserData,
           void** ppTracerInstanceUserData )
       {
           clock_t end = clock();
           
           my_tracer_data_t* tracer_data = (my_tracer_data_t*)pTracerUserData;
           my_instance_data_t* instance_data = *(my_instance_data_t**)ppTracerInstanceUserData;
           
           float time = 1000.f * ( end - instance_data->start ) / CLOCKS_PER_SEC;
           printf("zeCommandListAppendLaunchKernel #%d takes %.4f ms\n", tracer_data->instance++, time);
           
           free(instance_data);
       }

       void TracingExample( ... )
       {
           my_tracer_data_t tracer_data = {};
           :ref:`zet-tracer-exp-desc-t` tracer_desc {};
           tracer_desc.stype = :ref:`ZET_STRUCTURE_TYPE_TRACER_EXP_DESC <zet-structure-type-t>`\;
           tracer_desc.pUserData = &tracer_data;
           zet_tracer_exp_handle_t hTracer;
           :ref:`zetTracerExpCreate`\(hDevice, &tracer_desc, &hTracer);

           // Set all callbacks
           zet_core_callbacks_t prologCbs = {};
           zet_core_callbacks_t epilogCbs = {};
           prologCbs.CommandList.pfnAppendLaunchFunction = OnEnterCommandListAppendLaunchKernel;
           epilogCbs.CommandList.pfnAppendLaunchFunction = OnExitCommandListAppendLaunchKernel;

           :ref:`zetTracerExpSetPrologues`\(hTracer, &prologCbs);
           :ref:`zetTracerExpSetEpilogues`\(hTracer, &epilogCbs);

           :ref:`zetTracerExpSetEnabled`\(hTracer, true);

           :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hFunction, &launchArgs, nullptr, 0, nullptr);
           :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hFunction, &launchArgs, nullptr, 0, nullptr);
           :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hFunction, &launchArgs, nullptr, 0, nullptr);

           :ref:`zetTracerExpSetEnabled`\(hTracer, false);
           :ref:`zetTracerExpDestroy`\(hTracer);
       }

Metrics
=======

.. _introduction-1:

Introduction
------------

Devices provide programmable infrastructure designed to support
performance debugging. The API described in this document provides
access to these device metrics. The intention of this API is to support
performance debug and it is not advised to use it in regular execution
as overall performance can be negatively impacted.

| The following diagram illustrates the relationship between the metric
  objects described in this document.

.. image:: ../images/tools_metric_hierarchy.png

Most of the detailed metrics require the device to be properly
programmed before use. It is important to understand that the device
programming is in most cases global. This generally means that if a
software tool or an application is using the metrics then no other
application can reliably use the same device resources.

Metric Groups
-------------

The device infrastructure consists of a pre-defined set of non-programmable
counters, and a programmable network of connections that work with a
separate set of counters as well as other types of counters. For sake of
simplicity, the smallest unit of configuration is a Metric Group. Metric
Groups are sets of metrics that provide certain perspective on
workload's performance. The groups aggregate metrics, define device
programming and available collection methods. An application may choose
to collect data from several Metric Groups provided that they all
belong to different domains. :ref:`Domains` are used as a software
representation of independent device resources that can safely be used
concurrently.

Sampling Types
~~~~~~~~~~~~~~

Sampling types are a software representation of device capabilities in
terms of reading metric values. Each Metric Group provides information
on which sampling types it supports. There are separate sets of APIs
supporting each of the sampling types Time-based_ and Event-based_.

All available sampling types are defined in :ref:`zet-metric-group-sampling-type-flags-t`\.

- Information about supported sampling types for a given Metric Group is provided in :ref:`zet-metric-group-properties-t`\.samplingType.
- It's possible that a device provides multiple Metric Groups with the same names but different sampling types.
- When enumerating, it's important to choose a Metric Group which supports the desired sampling type.

.. _Domains:

Domains
~~~~~~~

Every Metric Group belongs to a given domain (:ref:`zet-metric-group-properties-t`\.domain).

- The Metric Group typically define a uniform device counter configuration used for measurements.
- Each domain represents an exclusive resource used by the Metric Group.
- It's possible to simultaneously gather data for two different Metric Groups, only if they belong to a different domain i.e. Metric Groups that can be collected concurrently will have different domain values.

Enumeration
-----------

All available metrics are organized into Metric Groups.

- During data collection, data for the whole Metric Group is gathered.
- The list of available Metric Groups and their Metrics is device-specific.

The following APIs provide all the information needed for identification and usage.

- Metric Group properties are accessed through the function :ref:`zetMetricGroupGetProperties` which returns :ref:`zet-metric-group-properties-t`\.
- Metric properties are accessed through the function :ref:`zetMetricGetProperties` which returns :ref:`zet-metric-properties-t`\.

A common tool flow is to enumerate metrics looking for a specific Metric
Group. Depending on the metrics required for a specific scenario a tool
may choose to run the workload multiple times, recording different set
of Metric Groups each time. Usually care must be taken to ensure
run-to-run stability and result repeatability if metrics from different
runs are meant to be used together. When enumerating metrics to find
a desired Metric Group, it's important to know in advance which sampling
type will be used.

To enumerate through the Metric tree:

1. Call :ref:`zetMetricGroupGet` to obtain Metric Group count.
2. Call :ref:`zetMetricGroupGet` to obtain all Metric Groups.
3. Iterate over all available Metric Groups.

    - At this point it's possible to check Metric Group name, domain or sampling type.
    - Metric Group names may not be unique.

4. Obtain the metric count for each Metric Group by calling :ref:`zetMetricGroupGetProperties` with Metric Group handle (zet_metric_group_handle_t) and checking :ref:`zet-metric-group-properties-t`\.metricCount.
5. Iterate over available Metrics using :ref:`zetMetricGet` with parent Metric Group (zet_metric_group_handle_t).
6. Check Metric properties (e.g. name, description) calling :ref:`zetMetricGetProperties` with parent Metric (zet_metric_handle_t).

The following pseudo-code demonstrates a basic enumeration over all
available metric groups and their metrics. Additionally, it returns a
metric group with a chosen name and sampling type. Similar code could be
used for selecting a preferred metric group for a specific type of
measurements.

.. parsed-literal::

       :ref:`ze-result-t` FindMetricGroup( ze_device_handle_t hDevice,
                                      char* pMetricGroupName,
                                      uint32_t desiredSamplingType,
                                      zet_metric_group_handle_t* phMetricGroup )
       {
           // Obtain available metric groups for the specific device
           uint32_t metricGroupCount = 0;
           :ref:`zetMetricGroupGet`\( hDevice, &metricGroupCount, nullptr );

           zet_metric_group_handle_t* phMetricGroups = malloc(metricGroupCount * sizeof(zet_metric_group_handle_t));
           :ref:`zetMetricGroupGet`\( hDevice, &metricGroupCount, phMetricGroups );

           // Iterate over all metric groups available
           for( i = 0; i < metricGroupCount; i++ )
           {   
               // Get metric group under index 'i' and its properties
               :ref:`zet-metric-group-properties-t` metricGroupProperties {};
               metricGroupProperties.stype = :ref:`ZET_STRUCTURE_TYPE_METRIC_GROUP_PROPERTIES <zet-structure-type-t>`\;
               :ref:`zetMetricGroupGetProperties`\( phMetricGroups[i], &metricGroupProperties );

               printf("Metric Group: %s\n", metricGroupProperties.name);

               // Check whether the obtained metric group supports the desired sampling type
               if((metricGroupProperties.samplingType & desiredSamplingType) == desiredSamplingType)
               {   
                   // Check whether the obtained metric group has the desired name
                   if( strcmp( pMetricGroupName, metricGroupProperties.name ) == 0 )
                   {
                       \*phMetricGroup = phMetricGroups[i];
                       break;
                   }
               }
           }

           free(phMetricGroups);
       }

Configuration
-------------

Use the :ref:`zetContextActivateMetricGroups` API call to configure the device
for data collection.

- Subsequent calls to the function will disable device programming for the metric groups not selected for activation.
- To avoid undefined results only call the :ref:`zetContextActivateMetricGroups` between experiments i.e. while not collecting data.

Programming restrictions:

- Any combination of metric groups can be configured simultaneously provided that all of them have a different :ref:`zet-metric-group-properties-t`\.domain.
- MetricGroup must be active until :ref:`zetMetricStreamerClose` and the last :ref:`zetCommandListAppendMetricQueryEnd` completes.

Collection
----------

There are two modes of metrics collection supported: :ref:`time-based<time-based>` and :ref:`event-based<event-based>`.

- Time-based collection is using a timer as well as other events to store data samples. A metric streamer interface is the software interface for configuration and collection.
- Event-based collection is based on a pair of Begin/End events appended to command lists. A metric query interface is the software interface for configuration and collection.

.. _Time-based:

Metric Streamer
~~~~~~~~~~~~~~~

Time-based collection uses a simple Open, Read, Close scheme:

- :ref:`zetMetricStreamerOpen` opens the streamer.
- :ref:`zetMetricStreamerReadData` reads the raw data to be later processed by :ref:`zetMetricGroupCalculateMetricValues`\.
- :ref:`zetMetricStreamerClose` closes the streamer.

.. image:: ../images/tools_metric_streamer.png

The following pseudo-code demonstrates a basic sequence for time-based collection:

.. parsed-literal::

       :ref:`ze-result-t` TimeBasedUsageExample( ze_context_handle_t hContext,
                                            ze_device_handle_t hDevice )
       {
           zet_metric_group_handle_t     hMetricGroup           = nullptr;
           ze_event_handle_t            hNotificationEvent     = nullptr;
           ze_event_pool_handle_t       hEventPool             = nullptr;
           :ref:`ze-event-pool-desc-t`         eventPoolDesc          = {:ref:`ZE_STRUCTURE_TYPE_EVENT_POOL_DESC <ze-structure-type-t>`\, nullptr, 0, 1};
           :ref:`ze-event-desc-t`              eventDesc              = {:ref:`ZE_STRUCTURE_TYPE_EVENT_DESC <ze-structure-type-t>`\};
           zet_metric_streamer_handle_t  hMetricStreamer        = nullptr;
           :ref:`zet-metric-streamer-desc-t`    metricStreamerDesc     = {:ref:`ZET_STRUCTURE_TYPE_METRIC_STREAMER_DESC <zet-structure-type-t>`\}; 

           // Find a "ComputeBasic" metric group suitable for Time Based collection
           FindMetricGroup( hDevice, "ComputeBasic", :ref:`ZET_METRIC_GROUP_SAMPLING_TYPE_FLAG_TIME_BASED <zet-metric-group-sampling-type-flags-t>`\, &hMetricGroup );

           // Configure the HW
           :ref:`zetContextActivateMetricGroups`\( hContext, hDevice, /\* count= \*/ 1, &hMetricGroup );

           // Create notification event
           :ref:`zeEventPoolCreate`\( hContext, &eventPoolDesc, 1, &hDevice, &hEventPool );
           eventDesc.index  = 0;
           eventDesc.signal = :ref:`ZE_EVENT_SCOPE_FLAG_HOST <ze-event-scope-flags-t>`\;
           eventDesc.wait   = :ref:`ZE_EVENT_SCOPE_FLAG_HOST <ze-event-scope-flags-t>`\; 
           :ref:`zeEventCreate`\( hEventPool, &eventDesc, &hNotificationEvent );
           
           // Open metric streamer
           metricStreamerDesc.samplingPeriod       = 1000;
           metricStreamerDesc.notifyEveryNReports  = 32768;
           :ref:`zetMetricStreamerOpen`\( hContext, hDevice, hMetricGroup, &metricStreamerDesc, hNotificationEvent, &hMetricStreamer );

           // Run your workload, in this example we assume the data for the whole experiment fits in the device buffer
           Workload(hDevice);
           // Optionally insert markers during workload execution
           //:ref:`zetCommandListAppendMetricStreamerMarker`\( hCommandList, hMetricStreamer, tool_marker_value ); 

           // Wait for data, optional in this example since the whole workload has already been executed by now
           //:ref:`zeEventHostSynchronize`\( hNotificationEvent, 1000 /\*timeout\*/ );
           // reset the event if it fired

           // Read raw data
           size_t rawSize = 0;
           :ref:`zetMetricStreamerReadData`\( hMetricStreamer, UINT32_MAX, &rawSize, nullptr );
           uint8_t* rawData = malloc(rawSize); 
           :ref:`zetMetricStreamerReadData`\( hMetricStreamer, UINT32_MAX, &rawSize, rawData );

           // Close metric streamer
           :ref:`zetMetricStreamerClose`\( hMetricStreamer );   
           :ref:`zeEventDestroy`\( hNotificationEvent );
           :ref:`zeEventPoolDestroy`\( hEventPool );

           // Deconfigure the device
           :ref:`zetContextActivateMetricGroups`\( hContext, hDevice, 0, nullptr );

           // Calculate metric data
           CalculateMetricsExample( hMetricGroup, rawSize, rawData );
           free(rawData);
       }

.. _Event-based:

Metric Query
~~~~~~~~~~~~

Event-based collection uses a simple Begin, End, GetData scheme:

- :ref:`zetCommandListAppendMetricQueryBegin` defines the start counting event
- :ref:`zetCommandListAppendMetricQueryEnd` defines the finish counting event
- :ref:`zetMetricQueryGetData` reads the raw data to be later processed by :ref:`zetMetricGroupCalculateMetricValues`\.

Typically, multiple queries are used and recycled to characterize a workload. A Query Pool is used to efficiently use and reuse device memory for multiple queries.

- :ref:`zetMetricQueryPoolCreate` creates a pool of homogeneous queries.
- :ref:`zetMetricQueryPoolDestroy` frees the pool. The application must ensure no queries within the pool are in-use before freeing the pool.
- :ref:`zetMetricQueryCreate` obtains a handle to a unique location in the pool.
- :ref:`zetMetricQueryReset` allows for low-cost recycling of a location in the pool.

.. image:: ../images/tools_metric_query.png

The following pseudo-code demonstrates a basic sequence for query-based collection:

.. parsed-literal::

       :ref:`ze-result-t` MetricQueryUsageExample( ze_context_handle_t hContext,
                                              ze_device_handle_t hDevice )
       {
           zet_metric_group_handle_t      hMetricGroup          = nullptr;
           ze_event_handle_t             hCompletionEvent      = nullptr;
           :ref:`ze-event-pool-desc-t`          eventPoolDesc         = {:ref:`ZE_STRUCTURE_TYPE_EVENT_POOL_DESC <ze-structure-type-t>`\, nullptr};
           :ref:`ze-event-desc-t`               eventDesc             = {:ref:`ZE_STRUCTURE_TYPE_EVENT_DESC <ze-structure-type-t>`\, nullptr};
           ze_event_pool_handle_t        hEventPool            = nullptr;
           zet_metric_query_pool_handle_t hMetricQueryPool      = nullptr;
           zet_metric_query_handle_t      hMetricQuery          = nullptr;
           :ref:`zet-metric-query-pool-desc-t`   queryPoolDesc         = {:ref:`ZET_STRUCTURE_TYPE_METRIC_QUERY_POOL_DESC <zet-structure-type-t>`\, nullptr};
       
           // Find a "ComputeBasic" metric group suitable for Event Based collection
           FindMetricGroup( hDevice, "ComputeBasic", :ref:`ZET_METRIC_GROUP_SAMPLING_TYPE_FLAG_EVENT_BASED <zet-metric-group-sampling-type-flags-t>`\, &hMetricGroup );

           // Configure HW
           :ref:`zetContextActivateMetricGroups`\( hContext, hDevice, 1 /\* count \*/, &hMetricGroup );

           // Create metric query pool & completion event
           queryPoolDesc.type         = :ref:`ZET_METRIC_QUERY_POOL_TYPE_PERFORMANCE <zet-metric-query-pool-type-t>`\;
           queryPoolDesc.count        = 1000;
           :ref:`zetMetricQueryPoolCreate`\( hContext, hDevice, hMetricGroup, &queryPoolDesc, &hMetricQueryPool );
           eventPoolDesc.flags = 0;
           eventPoolDesc.count = 1000;
           :ref:`zeEventPoolCreate`\( hContext, &eventPoolDesc, 1, &hDevice, &hEventPool );

           // Write BEGIN metric query to command list 
           :ref:`zetMetricQueryCreate`\( hMetricQueryPool, 0 /\*slot\*/, &hMetricQuery );
           :ref:`zetCommandListAppendMetricQueryBegin`\( hCommandList, hMetricQuery );

           // build your command list
           ...

           // Write END metric query to command list, use an event to determine if the data is available
           eventDesc.index  = 0;
           eventDesc.signal = :ref:`ZE_EVENT_SCOPE_FLAG_HOST <ze-event-scope-flags-t>`\;
           eventDesc.wait   = :ref:`ZE_EVENT_SCOPE_FLAG_HOST <ze-event-scope-flags-t>`\; 
           :ref:`zeEventCreate`\( hEventPool, &eventDesc, &hCompletionEvent);
           :ref:`zetCommandListAppendMetricQueryEnd`\( hCommandList, hMetricQuery, hCompletionEvent, 0, nullptr );

           // use :ref:`zeCommandQueueExecuteCommandLists`\( , , , ) to submit your workload to the device
      
           // Wait for data
           :ref:`zeEventHostSynchronize`\( hCompletionEvent, 1000 /\*timeout\*/ );

           // Read raw data
           size_t rawSize = 0;
           :ref:`zetMetricQueryGetData`\( hMetricQuery, &rawSize, nullptr );
           uint8_t* rawData = malloc(rawSize); 
           :ref:`zetMetricQueryGetData`\( hMetricQuery, &rawSize, rawData );

           // Free the resources
           :ref:`zeEventDestroy`\( hCompletionEvent );
           :ref:`zeEventPoolDestroy`\( hEventPool );
           :ref:`zetMetricQueryPoolDestroy`\( hMetricQueryPool );

           // Deconfigure HW
           :ref:`zetContextActivateMetricGroups`\( hContext, hDevice, 0, nullptr );

           // Calculate metric data
           CalculateMetricsExample( hMetricGroup, rawSize, rawData );
           free(rawData);
       }

Calculation
-----------

Both MetricStreamer and MetricQuery collect the data in device specific, raw form that is not suitable for application processing. 
To calculate metric values use :ref:`zetMetricGroupCalculateMetricValues`\.

The following pseudo-code demonstrates a basic sequence for metric calculation and interpretation:

.. parsed-literal::

       :ref:`ze-result-t` CalculateMetricsExample( zet_metric_group_handle_t hMetricGroup,
                                              size_t rawSize, uint8_t* rawData )
       {
           // Calculate metric data
           uint32_t numMetricValues = 0;
           :ref:`zet-metric-group-calculation-type-t` calculationType = :ref:`ZET_METRIC_GROUP_CALCULATION_TYPE_METRIC_VALUES <zet-metric-group-calculation-type-t>`\;
           :ref:`zetMetricGroupCalculateMetricValues`\( hMetricGroup, calculationType, rawSize, rawData, &numMetricValues, nullptr );
           :ref:`zet-typed-value-t`\* metricValues = malloc( numMetricValues * sizeof(:ref:`zet-typed-value-t`\) );
           :ref:`zetMetricGroupCalculateMetricValues`\( hMetricGroup, calculationType, rawSize, rawData, &numMetricValues, metricValues );

           // Obtain available metrics for the specific metric group
           uint32_t metricCount = 0;
           :ref:`zetMetricGet`\( hMetricGroup, &metricCount, nullptr );

           zet_metric_handle_t* phMetrics = malloc(metricCount * sizeof(zet_metric_handle_t));
           :ref:`zetMetricGet`\( hMetricGroup, &metricCount, phMetrics );

           // Print metric results
           uint32_t numReports = numMetricValues / metricCount;
           for( uint32_t report = 0; report < numReports; ++report )
           {
               printf("Report: %d\n", report);

               for( uint32_t metric = 0; metric < metricCount; ++metric )
               {
                   :ref:`zet-typed-value-t` data = metricValues[report * metricCount + metric];

                   :ref:`zet-metric-properties-t` metricProperties {};
                   metricProperties.stype = :ref:`ZET_STRUCTURE_TYPE_METRIC_PROPERTIES <zet-structure-type-t>`\;
                   :ref:`zetMetricGetProperties`\( phMetrics[ metric ], &metricProperties );

                   printf("Metric: %s\n", metricProperties.name );

                   switch( data.type )
                   {
                   case :ref:`ZET_VALUE_TYPE_UINT32 <zet-value-type-t>`\:
                       printf(" Value: %lu\n", data.value.ui32 );
                       break;
                   case :ref:`ZET_VALUE_TYPE_UINT64 <zet-value-type-t>`\:
                       printf(" Value: %llu\n", data.value.ui64 );
                       break;
                   case :ref:`ZET_VALUE_TYPE_FLOAT32 <zet-value-type-t>`\:
                       printf(" Value: %f\n", data.value.fp32 );
                       break;
                   case :ref:`ZET_VALUE_TYPE_FLOAT64 <zet-value-type-t>`\:
                       printf(" Value: %f\n", data.value.fp64 );
                       break;
                   case :ref:`ZET_VALUE_TYPE_BOOL8 <zet-value-type-t>`\:
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


Program Instrumentation
=======================

.. _introduction-2:

Introduction
------------

The program instrumentation APIs provide tools a basic framework for low-level profiling of device kernels, 
by allowing direct instrumentation of those programs. 
These capabilities, in combination with those already provided, and in combination with a custom loader layer, 
are sufficient for more advanced frameworks to be developed.

There are two types of instrumentation available:

1. Inter-Function Instrumentation - intercepting and redirecting function calls
2. Intra-Function Instrumentation - injecting new instructions within a function

Inter-Function Instrumentation
------------------------------

The following capabilities allow for a tool to intercept and redirect function calls:

* Inter-module function calls - the ability to call functions between different modules; e.g., the application's module and a tool's module
* Custom loader layer - the ability to intercept and inject API calls

For example, a tool may use a custom loader layer in any of the following ways:

* :ref:`zeModuleCreate` - replace a module handle with instrumented module handle for all functions
* :ref:`zeKernelCreate` - replace a kernel handle with instrumented kernel handle for all call sites
* :ref:`zeModuleGetFunctionPointer` - replace a function pointer with instrumented function pointer for all call sites
* :ref:`zeCommandListAppendLaunchKernel` - replace a kernel handle with instrumented kernel handle at call site

Intra-Function Instrumentation
------------------------------

The following capabilities allow for a tool to inject instructions within a kernel:

* :ref:`zetModuleGetDebugInfo` - allows a tool to query standard debug info for an application's module
* :ref:`zetKernelGetProfileInfo` - allows a tool to query detailed information on aspects of a kernel
* :ref:`zeModuleGetNativeBinary` - allows for a tool to retrieve the native binary of the application's module, instrument it, then create a new module using the instrumented version
* Custom loader layer - same usage as Inter-Function Instrumentation above

Compilation
~~~~~~~~~~~

A module must be compiled with foreknowledge that instrumentation will be performed for the compiler to generate the proper profiling meta-data.
Therefore, when the instrumentation layer is enabled, a new
build flag is supported: "-zet-profile-flags \<value\>", where \<value\> must be a
combination of :ref:`zet-profile-flags-t`\, in hexidecimal.

As an example, a tool could use a custom loader layer to inject this build flag on each :ref:`zeModuleCreate` call that the tool wishes to instrument.
In another example, a tool could recompile a Module using the build flag and use a custom loader layer to replace the application's Module handle with it's own.

Instrumentation
~~~~~~~~~~~~~~~

Once the module has been compiled with instrumentation enabled, a tool may use :ref:`zetModuleGetDebugInfo` and :ref:`zetKernelGetProfileInfo` 
in order to decode the application's instructions and register usage for each function in the module.

If a tool requires additional functions to be used, it may create other module(s) and use :ref:`zeModuleGetFunctionPointer` 
to call functions between the application and tool modules.
A tool may use :ref:`zeModuleGetFunctionPointer` to retrieve the Host and device address of each function in the module.

There are no APIs provided for the actual instrumentation. 
Instead this is left up to the tool itself to decode the application module's native binary and inject native instructions.
This model prevents the instrumentation from being manipulated by the compiler.

Execution
~~~~~~~~~

If a tool requires changing the address of an application's function,
then it should use a custom loader layer to intercept API calls dealing with function pointers.
For example, :ref:`zeModuleGetFunctionPointer` and all flavors of :ref:`zeCommandListAppendLaunchKernel`\.


Program Debug
=============

.. _introduction-3:

Introduction
------------

The program debug APIs provide tools a basic framework for debugging device code.

The debug APIs only operate on a single device.
When debugging a multi-device system, the tool must debug each device independently.  

The debug APIs only operate in the context of a single host process.
When debugging multiple host processes at the same time, the tool must debug device code
submitted by each host process independently.


Device Debug Properties
-----------------------

A tool may query the debug properties of a device by calling :ref:`zetDeviceGetDebugProperties`\.

To start a debug session, a tool should first query the debug properties of the device it wants to attach to.
Support for attaching debuggers is indicated by the :ref:`ZET_DEVICE_DEBUG_PROPERTY_FLAG_ATTACH <zet-device-debug-property-flags-t>` flag in :ref:`zet-device-debug-properties-t`\.

.. parsed-literal::

    :ref:`zet-device-debug-properties-t` props {};
    props.stype = :ref:`ZET_STRUCTURE_TYPE_DEVICE_DEBUG_PROPERTIES <zet-structure-type-t>`\;
    :ref:`zetDeviceGetDebugProperties`\(hDevice, &props);

    if (:ref:`ZET_DEVICE_DEBUG_PROPERTY_FLAG_ATTACH <zet-device-debug-property-flags-t>` & props.flags == 0)
        return; // debugging not supporting


Attach and Detach
-----------------

A tool must attach to a device by calling :ref:`zetDebugAttach`\.
The library will check the following properties:

  * the device must support attaching debuggers.

  * the requested host process must exist.

  * the tool process must be allowed to debug the requested host process.

    Note that this does not require the tool to be attached to the host process.

  * there must be no other tool attached at the same time.

  * device debug must be enabled on this system.


If permission is granted, a zet_debug_session_handle_t is provided.
The debug session handle can be used in other program debug APIs until the tool detaches again.

To end a debug session, a tool calls :ref:`zetDebugDetach` passing the
zet_debug_session_handle_t that had been provided on the corresponding
:ref:`zetDebugAttach` call.

The following sample code demonstrates attaching and detaching:

.. parsed-literal::

    zet_debug_session_handle_t hDebug;

    :ref:`zet-debug-config-t` config;
    memset(&config, 0, sizeof(config));
    config.pid = ...;

    errcode = :ref:`zetDebugAttach`\(hDevice, &config, &hDebug);
    if (errcode)
        return errcode;

    ...

    errcode = :ref:`zetDebugDetach`\(hDebug);
    if (errcode)
        return errcode;


Devices and Sub-Devices
~~~~~~~~~~~~~~~~~~~~~~~

A tool may attach to any device and will implicitly be attached to all sub-devices of that device.

Implementations that use separate code segments per sub-device may further allow attaching to sub-devices individually.
Support for this can be determined by calling :ref:`zetDeviceGetDebugProperties` using a sub-device handle and
checking for the :ref:`ZET_DEVICE_DEBUG_PROPERTY_FLAG_ATTACH <zet-device-debug-property-flags-t>` flag in :ref:`zet-device-debug-properties-t`\.
In that case, a tool may choose to either attach to the device or to one or more sub-devices.

When attached to a sub-device, writes to the code segment will not be broadcast to other sub-devices,
even though they may share the same address space range.
This allows breakpoints to be contained within one sub-device.

If a tool is attached to a sub-device, any attempt to attach to an parent device results in :ref:`ZE_RESULT_ERROR_NOT_AVAILABLE <ze-result-t>`\.

Implementations that share code segments across sub-devices will only allow attaching to devices.
Any attempt to attach to a sub-device results in :ref:`ZE_RESULT_ERROR_NOT_AVAILABLE <ze-result-t>`\.

Device Thread Identification
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Device threads are identified by their slice, sub-slice, EU, and thread numbers,
which lie between zero and the respective number reported by :ref:`ze-device-properties-t` minus one.

If a tool is attached to a device, device threads are enumerated for all sub-devices within that device.

The total number of threads on a device can be computed using device properties as shown in this sample code:

.. parsed-literal::

    :ref:`ze-device-properties-t` properties {};
    properties.stype = :ref:`ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES <ze-structure-type-t>`\;
    uint64_t num_threads;

    :ref:`zeDeviceGetProperties`\(hDevice, &properties);

    num_threads = properties.numSlices * properties.numSubslicesPerSlice *
        properties.numEUsPerSubslice * properties.numThreadsPerEU;


Tools may enumerate all possible thread identifiers based on device properties
by iterating over the number of slices, sub-slices, EUs, and threads.

Thread Availability
~~~~~~~~~~~~~~~~~~~

Not all threads may be available at all times and some threads may not be available at any time.
This may have various reasons, including:

* the thread may be idle
* the thread may be assigned to a different process

For the purpose of this debug tool API, threads may be in one of three states:

* running
* stopped
* unavailable


Debug Events
------------

As soon as the debug session has been started, it will receive debug events from the device.
To read the topmost event in the FIFO, the tool must call :ref:`zetDebugReadEvent`\.

The following sample code demonstrates reading an event:

.. parsed-literal::

    :ref:`zet-debug-event-t` event;
    errcode = :ref:`zetDebugReadEvent`\(hDebug, UINT64_MAX, &event);
    if (errcode)
        return errcode;

    ...

    if (event.flags & :ref:`ZET_DEBUG_EVENT_FLAG_NEED_ACK <zet-debug-event-flags-t>`\) {
        errcode = :ref:`zetDebugAcknowledgeEvent`\(hDebug, &event);
        if (errcode)
            return errcode;
    }


A debug event is described by the :ref:`zet-debug-event-t` structure, which contains:

  * The event type as :ref:`zet-debug-event-type-t`\.

  * A bit-vector of :ref:`zet-debug-event-flags-t`\, which can be:

    * :ref:`ZET_DEBUG_EVENT_FLAG_NEED_ACK <zet-debug-event-flags-t>` indicates that the event needs to be acknowledged by calling :ref:`zetDebugAcknowledgeEvent`\.
      This allows tools to perform any action in response to an event and indicate their completion by acknowledging the event.

      Implementations are allowed to block reading of new events until the previous event has been acknowledged.
      If an implementation allows reading further events, it must allow acknowledging events out of order.


Following the common fields, the event object contains event-specific fields depending on the event type.
Not all events have event-specific fields.

  * :ref:`ZET_DEBUG_EVENT_TYPE_DETACHED <zet-debug-event-type-t>`\: the tool was detached.

    * The detach reason as :ref:`zet-debug-detach-reason-t`\. This can be:

        * :ref:`ZET_DEBUG_DETACH_REASON_HOST_EXIT <zet-debug-detach-reason-t>` indicates that the host process exited.

  * :ref:`ZET_DEBUG_EVENT_TYPE_PROCESS_ENTRY <zet-debug-event-type-t>`\: the host process created one or more command queues on the device.

  * :ref:`ZET_DEBUG_EVENT_TYPE_PROCESS_EXIT <zet-debug-event-type-t>`\: the host process destroyed all command queues on the device.

  * :ref:`ZET_DEBUG_EVENT_TYPE_MODULE_LOAD <zet-debug-event-type-t>`\: an in-memory module was loaded onto the device.

  * :ref:`ZET_DEBUG_EVENT_TYPE_MODULE_UNLOAD <zet-debug-event-type-t>`\: an in-memory module is about to get unloaded from the device.

  * :ref:`ZET_DEBUG_EVENT_TYPE_THREAD_STOPPED <zet-debug-event-type-t>`\: threads stopped due to a device exception.

    The reported threads remain stopped until they are resumed by a call to :ref:`zetDebugResume`\.

  * :ref:`ZET_DEBUG_EVENT_TYPE_THREAD_UNAVAILABLE <zet-debug-event-type-t>`\: threads cannot be interrupted because they are unavailable.

    The event is generated in response to an interrupt request if none of the requested threads is available to be interrupted.

  * :ref:`ZET_DEBUG_EVENT_TYPE_PAGE_FAULT <zet-debug-event-type-t>`\: there was a page fault on the device

    The event provides the page fault reason, the faulting address aligned to the page granularity, and a mask specifying the alignment.

    To mask can be bit-wise ANDed with an address to obtain an address that is similarly aligned to the same page granularity as the provided faulting address.


Run Control
-----------

The tool may interrupt and resume device threads by calling :ref:`zetDebugInterrupt` and :ref:`zetDebugResume`\, respectively.

The thread argument may specify a single thread, a group of threads, or all threads on the device.
To specify all threads, the tool must set all fields in :ref:`ze-device-thread-t` to their maximum value.
By setting some but not all fields to their maximum value, a tool may specify a group of threads.

The :ref:`zetDebugInterrupt` call is not blocking.
When all specified threads either stopped or are determined to be currently unavailable,
the tool receives a :ref:`ZET_DEBUG_EVENT_TYPE_THREAD_STOPPED <zet-debug-event-type-t>` event if at least one thread could be stopped
or a :ref:`ZET_DEBUG_EVENT_TYPE_THREAD_UNAVAILABLE <zet-debug-event-type-t>` event if none of the threads is currently available.

If the thread argument specified a group of threads or all threads on the device,
the event may be preceded by :ref:`ZET_DEBUG_EVENT_TYPE_THREAD_STOPPED <zet-debug-event-type-t>` events of individual threads.

The tool does not know whether a thread stopped or is unavailable until it tries to access its state or access memory through it.
Unavailable threads may become available at any time.

The following sample code demonstrates how to interrupt and resume all threads in a debug session:

.. parsed-literal::

    :ref:`ze-device-thread-t` allthreads;
    allthreads.slice = UINT32_MAX;
    allthreads.subslice = UINT32_MAX;
    allthreads.eu = UINT32_MAX;
    allthreads.thread = UINT32_MAX;

    errcode = :ref:`zetDebugInterrupt`\(hDebug, allthreads);
    if (errcode)
        return errcode;

    ...

    errcode = :ref:`zetDebugResume`\(hDebug, allthreads);
    if (errcode)
        return errcode;


Memory Access
-------------

A tool may read and write memory in the context of a stopped device thread as if that thread had read or written the memory.

Memory may be partitioned into device-specific memory spaces.
For example, GPU devices support the following memory spaces, defined by :ref:`zet-debug-memory-space-type-t`\:

  * :ref:`ZET_DEBUG_MEMORY_SPACE_TYPE_DEFAULT <zet-debug-memory-space-type-t>` - default memory space

  * :ref:`ZET_DEBUG_MEMORY_SPACE_TYPE_SLM <zet-debug-memory-space-type-t>` - shared local memory space

The default memory space may also be accessed in the context of the special thread with all fields set to their maximum value.

To read and write memory, call the :ref:`zetDebugReadMemory` and :ref:`zetDebugWriteMemory` function, respectively.
The functions specify the thread(s), memory space and input or output buffer, respectively.

The following example copies 16 bytes of memory from one location in the context of one device thread to another location in the default memory space:

.. parsed-literal::

    :ref:`zet-debug-memory-space-desc-t` srcSpace = {
        :ref:`ZET_STRUCTURE_TYPE_DEBUG_MEMORY_SPACE_DESC <zet-structure-type-t>`\,
        nullptr,
        :ref:`ZET_DEBUG_MEMORY_SPACE_TYPE_DEFAULT <zet-debug-memory-space-type-t>`\,
        srcAddress
    };
    :ref:`zet-debug-memory-space-desc-t` dstSpace = {
        :ref:`ZET_STRUCTURE_TYPE_DEBUG_MEMORY_SPACE_DESC <zet-structure-type-t>`\,
        nullptr,
        :ref:`ZET_DEBUG_MEMORY_SPACE_TYPE_DEFAULT <zet-debug-memory-space-type-t>`\,
        dstAddress
    };

    :ref:`ze-device-thread-t` thread0 = {
        0, 0, 0, 0
    };

    uint8_t buffer[16];
    errcode = :ref:`zetDebugReadMemory`\(hDebug, thread0, &srcSpace, sizeof(buffer), buffer);
    if (errcode)
        return errcode;

    ...

    errcode = :ref:`zetDebugWriteMemory`\(hDebug, allthreads, &dstSpace, sizeof(buffer), buffer);
    if (errcode)
        return errcode;


Register State Access
---------------------

A tool may read and write the register state of a stopped device thread.

Registers are grouped into sets of similar registers.
The types of register sets supported by a device can be queried using
:ref:`zetDebugGetRegisterSetProperties` and :ref:`zetDebugGetThreadRegisterSetProperties`\.
The former provides general information about the register sets supported on a device.  The latter provides the concrete register set for the argument thread.  The register set may depend on dynamic properties and may change between stops.
The register set properties specify details about each register set,
such as the maximum number of registers in each set, and whether the register set is read-only.

The actual type of registers is device-specific and will be defined by the device vendor.

The following pseudo-code demonstrates obtaining register set properties for a device:

.. parsed-literal::

    uint32_t nRegSets = 0;
    :ref:`zetDebugGetRegisterSetProperties`\(hDevice, &nRegSets, nullptr);
    
    :ref:`zet-debug-regset-properties-t`\* pRegSets = allocate(nRegSets * sizeof(:ref:`zet-debug-regset-properties-t`\));
    :ref:`zetDebugGetRegisterSetProperties`\(hDevice, &nRegSets, pRegSets);

The following pseudo-code demonstrates obtaining register set properties for a thread:

.. parsed-literal::

    :ref:`ze-device-thread-t` thread0 = {
        0, 0, 0, 0
    };
    uint32_t nRegSets = 0;
    :ref:`zetDebugGetThreadRegisterSetProperties`\(hDebug, thread0, &nRegSets, nullptr);

    :ref:`zet-debug-regset-properties-t`\* pRegSets = allocate(nRegSets * sizeof(:ref:`zet-debug-regset-properties-t`\));
    :ref:`zetDebugGetThreadRegisterSetProperties`\(hDebug, thread0, &nRegSets, pRegSets);

To read and write the register state, use the :ref:`zetDebugReadRegisters` and :ref:`zetDebugWriteRegisters` function, respectively.

The following pseudo-code demonstrates iterating over register sets:

.. parsed-literal::

    for (i = 0; i < nRegSets; ++i) {
        void* values = allocate(pRegSets[i].count * pRegSets[i].valueSize);

        errcode = :ref:`zetDebugReadRegisters`\(hDebug, thread0, pRegSets[i].type, 0, pRegSets[i].count, values);
        if (errcode)
            return errcode;

        ...

        errcode = :ref:`zetDebugWriteRegisters`\(hDebug, thread0, pRegSets[i].type, 0, pRegSets[i].count, values);
        if (errcode)
            return errcode;

        free(values);
    }


