# Programming Guide (Tools)

## Hardware Metrics

### Introduction

### Enumeration

Sample code
```cpp
xe_result_t MetricGroupEnumerationExample( xe_device_handle_t hDevice, uint32_t samplingType )
{
    // METRIC GROUP COUNT
    uint32_t deviceProperties = {};
    xeDeviceGetProperties( hDevice, &deviceProperties );

    // METRIC GROUPS
    for( uint32_t i = 0; i < deviceProperties.numMetricGroups; ++i )
    {   
        xe_metric_group_handle_t hMetricGroup = NULL;
        xe_metric_group_properties_t metricGroupProperties = {XE_METRIC_GROUP_PROPERTIES_VERSION};

        xeDeviceGetMetricGroup( hDevice, i, &hMetricGroup );
        xeMetricGroupGetProperties( hMetricGroup, &metricGroupProperties );

        if( metricGroupProperties.samplingType == samplingType ) 		// >> mask
        {   
	   // METRICS
            for( uint32_t j = 0; j < metricGroupProperties.metricCount; ++j )	
            {
                xe_metric_handle_t metricHandle = NULL;
                xe_metric_properties_t metricProperties = {XE_METRIC_PROPERTIES_VERSION};

                xeMetricGroupGetMetric( hMetricGroup, j, &metricHandle );
                xeMetricGetProperties( metricHandle, &metricProperties );
            }
        }
    }
}
```

### Configuration

Use the ```xetDeviceActivateMetricGroups``` to configure the hardware.

Programming restrictions:
- MetricGroup must be active until MetricQueryGetDeta and MetricTracerClose
- Conflicting Groups cannot be activated, in such case the call to ... would fail

### Collection

#### Time Based
```cpp
xe_result_t TimeBasedUsageExample( xe_device_handle_t hDevice )
{
    xe_metric_group_handle_t     hMetricGroup           = NULL;
    xe_metric_group_properties_t metricGroupProperties  = {};
    xe_event_handle_t	    hNotificationEvent     = NULL;
    xe_event_desc_t              eventDesc              = {XE_EVENT_FLAG_DEVICE_TO_HOST};
    xe_metric_tracer_handle_t    hMetricTracer          = NULL;
    xe_metric_tracer_desc_t      metricTracerDescriptor = {XE_METRIC_TRACER_VERSION}; 

    // Find time based metric group
    EnumerateMetricGroup( e.g. "RenderBasic", „Time based”, &hMetricGroup );
    xeMetricGroupGetProperties( hMetricGroup, &metricGroupProperties );

    // Configure HW    
    xeDeviceActivateMetricGroup( hDevice, 1 /* count */, &hMetricGroup );

    // Open time based sampling
    xeDeviceCreateEvent( hDevice, &eventDesc, &hNotificationEvent );
    metricTracerDescriptor.hMetricGroup     	= hMetricGroup;	 // [in]
    metricTracerDescriptor.samplingPeriodNs 	= 100;		 // [in/out]
    metricTracerDescriptor.notifyEveryNReports      	= 1024;		 // [in/out]
    metricTracerDescriptor.hNotificationEvent 	= hNotificationEvent;         // [in]
    xeDeviceOpenMetricTracer( hDevice, &metricTracerDescriptor, &hMetricTracer );

    xeCommandListAppendMetricTracerMarker( hCommandList, hMetricTracer, tool_marker_value ); // Optional: insert markers

    // Run workload (CommandQueueExecute)

    // Wait for data
    xeEventHostSynchronize( metricTracerDescriptor.hNotificationEvent, 1000 /*timeout*/ );
    // reset the event if it fired

    // Read raw data
    uint32_t reportCount = 0;
    xeMetricTracerGetData( hMetricTracer, &reportCount, 0, NULL );	// ask how many reports are available
    uint32_t size = metricGroupProperties.rawReportSize * reportCount;
    uint8_t* rawData = malloc(size); 
    xeMetricTracerGetData( hMetricTracer, &reportCount, size, rawData );
    // LOOP

    // Close metric tracer
    xeMetricTracerClose( hMetricTracer );   
    xeDeviceDeactivateMetricGroups( hDevice );

    // Calculate raw data
    xeMetricGroupCalculateData( ... )
}
```

#### Queries
```cpp
xe_result_t MetricQueryUsageExample( xe_device_handle_t hDevice )
{
    xe_metric_group_handle_t     hMetricGroup          = NULL;
    xe_metric_group_properties_t metricGroupProperties = {};
    xe_event_handle_t            hCompletionEvent      = NULL;
    xe_metric_query_handle_t     hMetricQuery          = NULL;
    xe_event_desc_t              eventDesc             = {XE_EVENT_FLAG_DEVICE_TO_HOST};
    xe_metric_query_desc_t       queryDesc             = {XE_METRIC_QUERY_DESC_VERSION};
    
    // Find event metric group
    EnumerateMetricGroup( e.g. "RenderBasic", „Query”, &hMetricGroup );
    xeMetricGroupGetProperties( hMetricGroup, &metricGroupProperties );

    // Configure HW
    xeDeviceActivateMetricGroups( hDevice, 1 /* count */, &hMetricGroup );

    // Create metric query & completion event
    query.flags            = XE_METRIC_QUERY_FLAG_PERORMANCE;
    queryDesc.hMetricGroup = hMetricGroup;
    queryDesc.slotCount    = 1000;
    xeDeviceCreateMetricQuery( hDevice, &queryDesc, &hMetricQuery );		// TODO Pool & handles to items
    xeDeviceCreateEvent( hDevice, &eventDesc, &hCompletionEvent );		// optional

    // Write BEGIN metric query to command list 
    xeCommandListAppendMetricQueryBegin( hCommandList, hMetricQuery, 0 /* query slot */ );

    // ......... Dispatch / draw ..........

    // Write END metric query to command list 
    xeCommandListAppendMetricQueryEnd( hCommandList, hMetricQuery, 0 /* query slot */, hCompletionEvent );

   
    // Wait for data
    xeEventHostSynchronize( hCompletionEvent, 1000 /*timeout*/ );

    // Read raw data
    int size = metricGroupProperties.rawReportSize;
    uint8_t* rawData = malloc(size); 
    xeMetricQueryGetData( hMetricQuery, 0 /*ordinal*/, size, rawData );

    // Destroy 
    xeEventDestroy( hCompletionEvent );   
    xeMetricQueryDestroy( hMetricQuery );   

    // Deconfigure
    xeDeviceDeactivateMetricGroups( hDevice );

    // Calculate raw data
    xeMetricGroupCalculateData( ... )
}
```

### Calculation

