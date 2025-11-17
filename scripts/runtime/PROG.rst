
<%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
    r=tags['$r']
    r=r.upper()
%>
<%!
    from parse_specs import _version_compare_less, _version_compare_gequal
%>

.. _Runtime-Programming-Guide:

===========================
 Runtime Programming Guide
===========================

The standard Level Zero APIs require explicit driver object management and complex handle passing, which can be cumbersome for simple or default use cases.

To simplify this, the OneAPI Level Zero Runtime APIs provide a set of higher-level abstractions and default contexts that streamline common operations while still allowing access to the underlying Level Zero functionality when needed.

API Semantics and Considerations:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- New prefix "zer" indicating Level Zero Runtime APIs
- Design goal of the zer API's is to be simple and easy to use
- zer APIs are not designed for robust fine-grained control and low-level aspects; use ze APIs for those requirements
- By default, zer functions always use the driver at index 0 (after loader sorting). This can be overridden using :ref:`ZEL_DRIVERS_ORDER <driver-ordering>`. 
- Level Zero loader will always route zer functions to first driver instance that it reports
- By default, the Level Zero loader ensures that drivers are prioritized as follows: Discrete GPU hardware solutions are reported at index 0 when available. If no discrete GPU is present, any GPU solution will be reported at index 0. This default ordering can be overridden using :ref:`ZEL_DRIVERS_ORDER <driver-ordering>`.
- In the default path, the Level Zero loader routes API calls directly to driver pointers, allowing applications to bypass the loader for lower latency
- When tools are enabled, the Level Zero loader routes API calls through the loader to allow interception by those tools
- After Level Zero Init during zeInitDrivers, the zer runtime initializes the default driver (index 0), the driver at index 0 cannot be changed after initialization is called in the process
- zer and ze API's use the same handle object types and can be used together
- zer getter APIs return the desired object directly whenever feasible
- For zer APIs that don't return ze_result_t, error information can be retrieved using zerGetLastErrorDescription, similar to errno paradigms

**Important Limitation:** zer APIs are designed for applications with full control over the runtime environment and are not intended for advanced multi-driver management, low-level device management, or fine-grained control. Use ze APIs for those requirements.

.. _Default_Contexts:

Default Contexts
~~~~~~~~~~~~~~~~

API Functions:

- ze_context_handle_t ${r}GetDefaultContext();
- ze_context_handle_t ${x}DriverGetDefaultContext(ze_driver_handle_t hDriver);

Semantics:

- ${r}GetDefaultContext returns the default context for the default driver (index 0).
- ${x}DriverGetDefaultContext returns the default context for a specified driver.
- Each driver instance has a single default context containing all its devices.

.. _Device_Integer_indexing:

Device Integer Indexing
~~~~~~~~~~~~~~~~~~~~~~~

Level Zero Runtime APIs represent devices as integer identifiers.

API Functions:

- uint32_t ${r}TranslateDeviceHandleToIdentifier(ze_device_handle_t hDevice);
- ze_device_handle_t ${r}TranslateIdentifierToDeviceHandle(uint32_t identifier);

Semantics:

- Devices are assigned unsigned integer identifiers (uint32_t) starting from 0, corresponding to PCI order.
- When devices are filtered (e.g., with ZE_AFFINITY_MASK), the remaining devices are renumbered starting from 0 with no gaps.
- Sub-device translation is not supported.
- ${r}TranslateDeviceHandleToIdentifier returns the integer identifier for a device handle.
- ${r}TranslateIdentifierToDeviceHandle returns the device handle for a given identifier (driver must be initialized).

.. _Global_Device_Synchronization:

Global Device Synchronization
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

API Function:

- ze_result_t ${x}DeviceSynchronize(ze_device_handle_t hDevice);

Semantics:

- Blocks until all preceding submissions to all queues on the device are complete.
- Returns an error if device execution fails.
- Hangs indefinitely if the device is blocked on a non-signaled event.

.. _Default_Descriptors:

Default Descriptors
~~~~~~~~~~~~~~~~~~~

When creating resources like command lists, command queues, and events, applications can use default descriptor structures for the default driver at index 0.

The current Default Descriptor structures are:

.. parsed-literal::

       ///////////////////////////////////////////////////////////////////////////////
       /// @brief Immediate Command List default descriptor for GPU devices
       static const ze_command_queue_desc_t zeDefaultGPUImmediateCommandQueueDesc = {
           ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC,                                       ///< stype
           0,                                                                          ///< pNext
           0,                                                                          ///< ordinal
           0,                                                                          ///< index
           ZE_COMMAND_QUEUE_FLAG_IN_ORDER | ZE_COMMAND_QUEUE_FLAG_COPY_OFFLOAD_HINT,   ///< flags
           ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS,                                         ///< mode
           ZE_COMMAND_QUEUE_PRIORITY_NORMAL,                                           ///< priority
       };

       ///////////////////////////////////////////////////////////////////////////////
       /// @brief Device Unified Shared Memory Allocation default descriptor for GPU
       ///        devices
       static const ze_device_mem_alloc_desc_t zeDefaultGPUDeviceMemAllocDesc = {
           ZE_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC,                                ///< stype
           0,                                                                      ///< pNext
           ZE_DEVICE_MEM_ALLOC_FLAG_BIAS_CACHED,                                   ///< flags
           0,                                                                      ///< ordinal
       };

       ///////////////////////////////////////////////////////////////////////////////
       /// @brief Host Unified Shared Memory Allocation default descriptor for GPU
       ///        devices
       static const ze_host_mem_alloc_desc_t zeDefaultGPUHostMemAllocDesc = {
           ZE_STRUCTURE_TYPE_HOST_MEM_ALLOC_DESC,                                              ///< stype
           0,                                                                                  ///< pNext
           ZE_HOST_MEM_ALLOC_FLAG_BIAS_CACHED | ZE_HOST_MEM_ALLOC_FLAG_BIAS_INITIAL_PLACEMENT, ///< flags
       };


Example Usage:
~~~~~~~~~~~~~~

These default descriptors can be used when creating resources for the default driver (index 0) to simplify resource creation.

.. parsed-literal::

       // Default Descriptors with Simplification API Usage Example:
       ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
       desc.pNext = nullptr;
       desc.flags = UINT32_MAX; // all driver types requested
       uint32_t driverCount = 0;
       ze_result_t result = zeInitDrivers(&driverCount, nullptr, &desc); // Query the number of drivers
       if (result != ZE_RESULT_SUCCESS) {
           return result; // no drivers found
       }

       ze_driver_handle_t* allDrivers = allocate(driverCount * sizeof(ze_driver_handle_t));
       result = zeInitDrivers(&driverCount, allDrivers, &desc); // Read the driver handles
       if (result != ZE_RESULT_SUCCESS) {
           return result; // no driver handles found
       }
       uint32_t deviceIndex = 0;

       //input to function are int device, size, alignment 
       void \*deviceUsmPtr = nullptr; //output
       void \*hostUsmPtr = nullptr;
       zeMemAllocDevice(zerGetDefaultContext(), &zeDefaultGPUDeviceMemAllocDesc, size, alignment, zerTranslateIdentifierToDeviceHandle(deviceIndex), &deviceUsmPtr);
       zeMemAllocHost(zerGetDefaultContext(), &zeDefaultGPUHostMemAllocDesc, size, alignment, &hostUsmPtr);

       //input to function is int device
       ze_command_list_handle_t cmdList; //output
       zeCommandListCreateImmediate(zerGetDefaultContext(), zerTranslateIdentifierToDeviceHandle(deviceIndex), &zeDefaultGPUImmediateCommandQueueDesc, &cmdList);

       // zer Error Handling Usage Example:
       uint32_t deviceId = UINT32_MAX;
       const char \*errorString = nullptr;
       ze_device_handle_t translatedDevice = zerTranslateIdentifierToDeviceHandle(deviceId);
       if (translatedDevice == nullptr) {
           ze_result_t result = zerGetLastErrorDescription(&errorString);
           std::cerr << "Error translating device ID " << deviceId << ": " << errorString << std::endl;
       }
