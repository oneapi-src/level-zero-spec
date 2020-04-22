
<%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
    s=tags['$s']
    S=s.upper()
%>
==========================
 Sysman Programming Guide
==========================


Introduction
============

Sysman is the System Resource Management library used to monitor and
control the power and performance of accelerator devices.

High-level overview
===================

Environment Variables
---------------------

The following environment variables are required to be enabled during initialization for the respective feature.

## --validate=off
+-----------------+-------------------------------------+------------+-----------------------------------------------------------------------------------+
| Category        | Name                                | Values     | Description                                                                       |
+=================+=====================================+============+===================================================================================+
| Sysman          | ${S}_ENABLE_SYSMAN                   | {**0**, 1} | Enables driver initialization and dependencies for system management              |
+-----------------+-------------------------------------+------------+-----------------------------------------------------------------------------------+
## --validate=on

Initialization
--------------

An application wishing to manage power and performance for devices first
needs to use the Level0 Core API to enumerate through available
accelerator devices in the system and select those of interest.

For each selected device handle, applications can cast it to a
**Sysman device handle** to manage system resources of the device.

.. image:: ../images/tools_sysman_object_hierarchy.png

There is a unique handle for each device. Multiple threads can use the
handle. If concurrent accesses are made to the same device property
through the handle, the last request wins.

The pseudo code below shows how to enumerate the GPU devices in the
system and create Sysman handles for them:

.. parsed-literal::

   function main( ... )
       if (${x}Init(${X}_INIT_FLAG_NONE) != ${X}_RESULT_SUCCESS)
           output("Can't initialize the API")
       else
           # Discover all the drivers
           uint32_t driversCount = 0
           ::${x}DriverGet(&driversCount, nullptr)
           ${x}_driver_handle_t* allDrivers = allocate(driversCount * sizeof(${x}_driver_handle_t))
           ::${x}DriverGet(&driversCount, allDrivers)

           ${x}_driver_handle_t hDriver = nullptr
           for(i = 0 .. driversCount-1)
               # Discover devices in a driver
               uint32_t deviceCount = 0
               ::${x}DeviceGet(allDrivers[i], &deviceCount, nullptr)

               ${x}_device_handle_t* allDevices = 
                   allocate_memory(deviceCount * sizeof(${x}_device_handle_t))
               ::${x}DeviceGet(allDrivers[i], &deviceCount, allDevices)

               for(devIndex = 0 .. deviceCount-1)
                   ::${x}_device_properties_t device_properties
                   ::${x}DeviceGetProperties(allDevices[devIndex], &device_properties)
                   if(${X}_DEVICE_TYPE_GPU != device_properties.type)
                       next
                   # Get the Sysman device handle
                   ${s}_device_handle_t hSysmanDevice = (${s}_device_handle_t)allDevices[devIndex]
                   # Start using hSysmanDevice to manage the device

       free_memory(...)

Global device management
------------------------

The following operations are provided to access overall device
information and control aspects of the entire device:

-  Get device UUID, deviceID, number of sub-devices
-  Get Brand/model/vendor name
-  Query the information about processes using this device
-  Get/set scheduler mode and properties
-  Reset device
-  Query if the device has been repaired
-  Query if the device needs to be reset and for what reasons (wedged, initiate repair)
-  PCI information:

   -  Get configured bars
   -  Get maximum supported bandwidth
   -  Query current speed (GEN/no. lanes)
   -  Query current throughput
   -  Query packet retry counters

The full list of available functions is described `below <#glo>`__.

Device component management
---------------------------

Aside from management of the global properties of a device, there are
many device components that can be managed to change the performance
and/or power configuration of the device. Similar components are broken
into **classes** and each class has a set of operations that can be
performed on them.

For example, devices typically have one or more frequency domains. The
Sysman API exposes a class for frequency and an enumeration of all
frequency domains that can be managed.

The table below summarizes the classes that provide device queries and
an example list of components that would be enumerated for a device with
two sub-devices. The table shows the operations (queries) that will be
provided for all components in each class.

+-----------------------+---------------------------------+-------------------------------------------+
| Class                 | Components                      | Operations                                |
+=======================+=================================+===========================================+
| Power_                | Package:                        | Get energy consumption                    |
|                       | power                           |                                           |
|                       |                                 |                                           |
|                       | Sub-device 0: total             |                                           |
|                       | power                           |                                           |
|                       |                                 |                                           |
|                       | Sub-device 1: total             |                                           |
|                       | power                           |                                           |
+-----------------------+---------------------------------+-------------------------------------------+
| Frequency_            | Sub-device 0: GPU frequency     | List available frequencies                |
|                       |                                 |                                           |
|                       | Sub-device 0: Memory frequency  | Set frequency range                       |
|                       |                                 |                                           |
|                       | Sub-device 1: GPU frequency     | Get frequencies                           |
|                       |                                 |                                           |
|                       | Sub-device 1: Memory frequency  | Get throttle reasons                      |
|                       |                                 |                                           |
|                       |                                 | Get throttle time                         |
+-----------------------+---------------------------------+-------------------------------------------+
| Engines_              | Sub-device 0: All engines       | Get busy time                             |
|                       |                                 |                                           |
|                       | Sub-device 0: Compute engines   |                                           |
|                       |                                 |                                           |
|                       | Sub-device 0: Media engines     |                                           |
|                       |                                 |                                           |
|                       | Sub-device 0: Copy engines      |                                           |
|                       |                                 |                                           |
|                       | Sub-device 1: All engines       |                                           |
|                       |                                 |                                           |
|                       | Sub-device 1: Compute engines   |                                           |
|                       |                                 |                                           |
|                       | Sub-device 1: Media engines     |                                           |
|                       |                                 |                                           |
|                       | Sub-device 1: Copy engines      |                                           |
+-----------------------+---------------------------------+-------------------------------------------+
| Firmware_             | Sub-device 0: Enumerates each   | Get firmware name and version             |
|                       | firware                         |                                           |
|                       |                                 | Verify firmware checksum                  |
|                       | Sub-device 1: Enumerates each   |                                           |
|                       | firmware                        |                                           |
+-----------------------+---------------------------------+-------------------------------------------+
| Memory_               | Sub-device 0: Memory module     | Get maximum supported bandwidth           |
|                       |                                 |                                           |
|                       | Sub-device 1: Memory module     | Get free memory                           |
|                       |                                 |                                           |
|                       |                                 | Get current bandwidth                     |
+-----------------------+---------------------------------+-------------------------------------------+
| Fabric-Port_          | Sub-device 0: Enumerates each   | Get port configuration (UP/DOWN)          |
|                       | port                            |                                           |
|                       |                                 | Get physical link details                 |
|                       | Sub-device 1: Enumerates each   |                                           |
|                       | port                            | Get port health (green/yellow/red/black)  |
|                       |                                 |                                           |
|                       |                                 | Get remote port                           |
|                       |                                 |                                           |
|                       |                                 | Get port rx/tx speed                      |
|                       |                                 |                                           |
|                       |                                 | Get port rx/tx bandwidth                  |
+-----------------------+---------------------------------+-------------------------------------------+
| Temperature_          | Package: temperature            | Get current temperature sensor reading    |
|                       |                                 |                                           |
|                       | Sub-device 0: GPU temperature   |                                           |
|                       |                                 |                                           |
|                       | Sub-device 0: Memory            |                                           |
|                       | temperature                     |                                           |
|                       |                                 |                                           |
|                       | Sub-device 1: GPU temperature   |                                           |
|                       |                                 |                                           |
|                       | Sub-device 1: Memory            |                                           |
|                       | temperature                     |                                           |
+-----------------------+---------------------------------+-------------------------------------------+
| PSU_                  | Package: Power supplies         | Get details about the power supply        |
|                       |                                 |                                           |
|                       |                                 | Query current state (temperature,         |
|                       |                                 | current, fan)                             |
+-----------------------+---------------------------------+-------------------------------------------+
| Fan_                  | Package: Fans                   | Get details (max fan speed)               |
|                       |                                 |                                           |
|                       |                                 | Get config (fixed fan speed,              |
|                       |                                 | temperature-speed table)                  |
|                       |                                 |                                           |
|                       |                                 | Query current fan speed                   |
+-----------------------+---------------------------------+-------------------------------------------+
| LED_                  | Package: LEDs                   | Get details (RGB capable)                 |
|                       |                                 |                                           |
|                       |                                 | Query current state (on, color)           |
+-----------------------+---------------------------------+-------------------------------------------+
| RAS_                  | Sub-device 0: One set of RAS    | Read RAS total correctable and            |
|                       | error counters                  | uncorrectable error counters              |
|                       |                                 |                                           |
|                       | Sub-device 1: One set of RAS    | Read breakdown of errors by category      |
|                       | error counters                  | (no. resets, no. programming errors,      |
|                       |                                 | no. programming errors, no. driver        |
|                       |                                 | errors, no. compute errors, no. cache     |
|                       |                                 | errors, no. memory errors, no. PCI        |
|                       |                                 | errors, no. display errors, no.           |
|                       |                                 | non-compute errors)                       |
+-----------------------+---------------------------------+-------------------------------------------+
| Diagnostics_          | Package: SCAN test suite        | Get list of all diagnostics tests         |
|                       |                                 |                                           |
|                       | Package: ARRAY test suite       |                                           |
+-----------------------+---------------------------------+-------------------------------------------+

The table below summarizes the classes that provide device controls and
an example list of components that would be enumerated for a device with
two sub-devices. The table shows the operations (controls) that will be
provided for all components in each class.

+------------------------+---------------------------------+-------------------------------------------+
| Class                  | Components                      | Operations                                |
+========================+=================================+===========================================+
| Power_                 | Package: power                  | Set sustained power limit                 |
|                        |                                 |                                           |
|                        |                                 | Set burst power limit                     |
|                        |                                 |                                           |
|                        |                                 | Set peak power limit                      |
+------------------------+---------------------------------+-------------------------------------------+
| Frequency_             | Sub-device 0: GPU frequency     | Set frequency range                       |
|                        |                                 |                                           |
|                        | Sub-device 0: Memory frequency  |                                           |
|                        |                                 |                                           |
|                        | Sub-device 1: GPU frequency     |                                           |
|                        |                                 |                                           |
|                        | Sub-device 1: Memory frequency  |                                           |
+------------------------+---------------------------------+-------------------------------------------+
| Performance-Factor_    | Sub-device 0: Compute           | Tune workload performance                 |
|                        |                                 |                                           |
|                        | Sub-device 0: Media             |                                           |
|                        |                                 |                                           |
|                        | Sub-device 1: Compute           |                                           |
|                        |                                 |                                           |
|                        | Sub-device 1: Media             |                                           |
+------------------------+---------------------------------+-------------------------------------------+
| Standby_               | Sub-device 0: Control           | Disable opportunistic standby             |
|                        | entire sub-device               | standby                                   |
|                        |                                 |                                           |
|                        | Sub-device 1: Control entire    |                                           |
|                        | sub-device                      |                                           |
+------------------------+---------------------------------+-------------------------------------------+
| Firmware_              | Sub-device 0: Enumerates each   | Flash new firmware                        |
|                        | firmware                        |                                           |
|                        |                                 |                                           |
|                        | Sub-device 1: Enumerates each   |                                           |
|                        | firmware                        |                                           |
+------------------------+---------------------------------+-------------------------------------------+
| Fabric-Port_           | Sub-device 0: Control each port | Configure port UP/DOWN                    |
|                        |                                 |                                           |
|                        | Sub-device 1: Control each port | Turn beaconing ON/OFF                     |
+------------------------+---------------------------------+-------------------------------------------+
| Fan_                   | Package: Fans                   | Set config (fixed speed, temperature-     |
|                        |                                 | speed table)                              |
+------------------------+---------------------------------+-------------------------------------------+
| LED_                   | Package: LEDs                   | Turn LED on/off and set color             |
+------------------------+---------------------------------+-------------------------------------------+
| Diagnostics_           | SCAN test suite                 | Run all or a subset                       |
|                        |                                 | of diagnostic tests                       |
|                        | ARRAY test suite                | in the test suite                         |
+------------------------+---------------------------------+-------------------------------------------+

Device component enumeration
----------------------------

The Sysman API provides functions to enumerate all components in a class
that can be managed.

For example, there is a frequency class which is used to control the
frequency of different parts of the device. On most devices, the
enumerator will provide two handles, one to control the GPU frequency
and one to enumerate the device memory frequency. This is illustrated in
the figure below:

.. image:: ../images/tools_sysman_freq_flow.png

In the C API, each class is associated with a unique handle type
(e.g. ::${s}_freq_handle_t refers to a frequency component). In
the C++ API, each class is a C++ class (e.g. An instance of the class ::${s}::SysmanFrequency
refers to a frequency component).

The pseudo code below shows how to use the Sysman API to enumerate all
GPU frequency components and fix each to a specific frequency if this is
supported:

.. parsed-literal::

   function FixGpuFrequency(${s}_device_handle_t hSysmanDevice, double FreqMHz)
       uint32_t numFreqDomains
       if ((::${s}DeviceEnumFrequencyDomains(hSysmanDevice, &numFreqDomains, NULL) == ${X}_RESULT_SUCCESS))
           ${s}_freq_handle_t* pFreqHandles =
               allocate_memory(numFreqDomains * sizeof(${s}_freq_handle_t))
           if (::${s}DeviceEnumFrequencyDomains(hSysmanDevice, &numFreqDomains, pFreqHandles) == ${X}_RESULT_SUCCESS)
               for (index = 0 .. numFreqDomains-1)
                   ::${s}_freq_properties_t props
                   if (::${s}FrequencyGetProperties(pFreqHandles[index], &props) == ${X}_RESULT_SUCCESS)
                       # Only change the frequency of the domain if:
                       # 1. The domain controls a GPU accelerator
                       # 2. The domain frequency can be changed
                       if (props.type == ${S}_FREQ_DOMAIN_GPU
                           and props.canControl)
                               # Fix the frequency
                               ::${s}_freq_range_t range
                               range.min = FreqMHz
                               range.max = FreqMHz
                               ::${s}FrequencySetRange(pFreqHandles[index], &range)
       free_memory(...)

Sub-device management
---------------------

A Sysman device handle operates at the device level. If a sub-device device handle is passed to
any of the Sysman functions, the result will be as if the device handle was used.

The enumerator for device components will return a list of components that are located in each
sub-device. Properties for each component will indicate in which sub-device it is located. If software
wishing to manage components in only one sub-device should filter the enumerated components using the
sub-device ID (see ::${x}_device_properties_t.subdeviceId).

The figure below shows the frequency components that will be enumerated on a device with two sub-devices where each sub-device has a GPU and
device memory frequency control:

.. image:: ../images/tools_sysman_freq_subdevices.png

The pseudo code below shows how to fix the GPU frequency on a specific
sub-device (notice the additional sub-device check):

.. parsed-literal::

   function FixSubdeviceGpuFrequency(${s}_device_handle_t hSysmanDevice, uint32_t subdeviceId, double FreqMHz)
       uint32_t numFreqDomains
       if ((::${s}DeviceEnumFrequencyDomains(hSysmanDevice, &numFreqDomains, NULL) == ${X}_RESULT_SUCCESS))
           ${s}_freq_handle_t* pFreqHandles =
               allocate_memory(numFreqDomains * sizeof(${s}_freq_handle_t))
           if (::${s}DeviceEnumFrequencyDomains(hSysmanDevice, &numFreqDomains, pFreqHandles) == ${X}_RESULT_SUCCESS)
               for (index = 0 .. numFreqDomains-1)
                   ::${s}_freq_properties_t props
                   if (::${s}FrequencyGetProperties(pFreqHandles[index], &props) == ${X}_RESULT_SUCCESS)
                       # Only change the frequency of the domain if:
                       # 1. The domain controls a GPU accelerator
                       # 2. The domain frequency can be changed
                       # 3. The domain is located in the specified sub-device
                       if (props.type == ${S}_FREQ_DOMAIN_GPU
                           and props.canControl
                           and props.subdeviceId == subdeviceId)
                               # Fix the frequency
                               ::${s}_freq_range_t range
                               range.min = FreqMHz
                               range.max = FreqMHz
                               ::${s}FrequencySetRange(pFreqHandles[index], &range)
       free_memory(...)

Events
------

Events are a way to determine if changes have occurred on a device
e.g. new RAS errors without polling the Sysman API. An application
registers the events that it wishes to receive notification about and
then it listens for notifications. The application can choose to block
when listening - this will put the calling application thread to sleep
until new notifications are received.

The API enables registering for events from multiple devices and
listening for any events coming from any devices by using one function
call.

Once notifications have occurred, the application can use the query
Sysman interface functions to get more details.

The following events are provided:

-  Any RAS errors have occurred

The full list of available functions for handling events is described
`below <#evd>`__.

Interface details
=================

Global operations
-----------------

Device properties
~~~~~~~~~~~~~~~~~

The following operations permit getting properties about the entire
device:

+-----------------------------------+-----------------------------------+
| Function                          | Description                       |
+===================================+===================================+
| ::${s}DeviceGetProperties()  | Get static device properties -    |
|                                   | device UUID, sub-device ID,       |
|                                   | device brand/model/vendor strings |
+-----------------------------------+-----------------------------------+
| ::${s}DeviceGetState()       | Determine device state: was the   |
|                                   | device repaired, does the device  |
|                                   | need to be reset and for what     |
|                                   | reasons (wedged, initiate repair) |
+-----------------------------------+-----------------------------------+

The pseudo code below shows how to display general information about a
device:

.. parsed-literal::

  function ShowDeviceInfo(${s}_device_handle_t hSysmanDevice)
      ::${s}_device_properties_t devProps
      ::${s}_device_state_t devState
      if (::${s}DeviceGetProperties(hSysmanDevice, &devProps) == ${X}_RESULT_SUCCESS)
          output("    UUID:           %s", devProps.core.uuid.id)
          output("    #subdevices:    %u", devProps.numSubdevices)
          output("    brand:          %s", devProps.brandName)
          output("    model:          %s", devProps.modelName)
      if (::${s}DeviceGetState(hSysmanDevice, &devState) == ${X}_RESULT_SUCCESS)
          output("    Was repaired:   %s", (devState.repaired == ${S}_REPAIR_STATUS_PERFORMED) ? "yes" : "no")
          if (devState.reset != ${S}_RESET_REASONS_NONE)
        {
            output("DEVICE RESET REQUIRED:")
            if (devState.reset & ${S}_RESET_REASONS_WEDGED)
                output("- Hardware is wedged")
            if (devState.reset & ${S}_RESET_REASONS_REPAIR)
                output("- Hardware needs to complete repairs")
        }
    }

Host processes
~~~~~~~~~~~~~~

The following functions provide information about host processes that
are using the device:

+--------------------------------------+-----------------------------------+
| Function                             | Description                       |
+======================================+===================================+
| ::${s}DeviceProcessesGetState() | Get information about all         |
|                                      | processes that are using this     |
|                                      | device - process ID, device       |
|                                      | memory allocation size,           |
|                                      | accelerators being used.          |
+--------------------------------------+-----------------------------------+

Using the process ID, an application can determine the owner and the
path to the executable - this information is not returned by the API.

Scheduler operations
~~~~~~~~~~~~~~~~~~~~

Scheduler components control how workloads are executed on accelerator
engines and how to share the hardware resources when multiple workloads are
submitted concurrently. This policy is referred to as a scheduler mode.

The available scheduler operating modes are given by the enum
::${s}_sched_mode_t and summarized in the table below:

+-------------------------------------+-------------------------------------------+
| Scheduler mode                      | Description                               |
+=====================================+===========================================+
| ::${S}_SCHED_MODE_TIMEOUT            | This mode is optimized for                |
|                                     | multiple applications or contexts         |
|                                     | submitting work to the hardware.          |
|                                     | When higher priority work                 |
|                                     | arrives, the scheduler attempts           |
|                                     | to pause the current executing            |
|                                     | work within some timeout                  |
|                                     | interval, then submits the other          |
|                                     | work.It is possible to configure          |
|                                     | (::${s}_sched_timeout_properties_t)  |
|                                     | the watchdog timeout which                |
|                                     | controls the maximum time the             |
|                                     | scheduler will wait for a                 |
|                                     | workload to complete a batch of           |
|                                     | work or yield to other                    |
|                                     | applications before it is                 |
|                                     | terminated. If the watchdog               |
|                                     | timeout is set to                         |
|                                     | ::${S}_SCHED_WATCHDOG_DISABLE, the         |
|                                     | scheduler enforces no fairness.           |
|                                     | This means that if there is other         |
|                                     | work to execute, the scheduler            |
|                                     | will try to submit it but will            |
|                                     | not terminate an executing                |
|                                     | process that does not complete            |
|                                     | quickly.                                  |
+-------------------------------------+-------------------------------------------+
| ::${S}_SCHED_MODE_TIMESLICE          | This mode is optimized to provide         |
|                                     | fair sharing of hardware                  |
|                                     | execution time between multiple           |
|                                     | contexts submitting work to the           |
|                                     | hardware concurrently.It is               |
|                                     | possible to configure                     |
|                                     | (::${s}_sched_timeslice_properties_t)|
|                                     |                                           |
|                                     | the timeslice interval and the            |
|                                     | amount of time the scheduler will         |
|                                     | wait for work to yield to another         |
|                                     | application before it is                  |
|                                     | terminated.                               |
+-------------------------------------+-------------------------------------------+
| ::${S}_SCHED_MODE_EXCLUSIVE          | This mode is optimized for single         |
|                                     | application/context use-cases. It         |
|                                     | permits a context to run                  |
|                                     | indefinitely on the hardware              |
|                                     | without being preempted or                |
|                                     | terminated. All pending work for          |
|                                     | other contexts must wait until            |
|                                     | the running context completes             |
|                                     | with no further submitted work.           |
+-------------------------------------+-------------------------------------------+
| ::${S}_SCHED_MODE_COMPUTE_UNIT_DEBUG | This mode is optimized for                |
|                                     | application debug. It ensures             |
|                                     | that only one command queue can           |
|                                     | execute work on the hardware at a         |
|                                     | given time. Work is permitted to          |
|                                     | run as long as needed without             |
|                                     | enforcing any scheduler fairness          |
|                                     | policies.                                 |
+-------------------------------------+-------------------------------------------+

A device can have multiple scheduler components. Each scheduler component controls
the workload execution behavior on one or more accelerator engines
(::${s}_engine_type_t). The following functions are available for changing
the scheduler mode for each scheduler component:

+--------------------------------------------------+-----------------------------------+
| Function                                         | Description                       |
+==================================================+===================================+
| ::${s}DeviceEnumSchedulers()                | Get handles to each scheduler     |
|                                                  | component.                        |
+--------------------------------------------------+-----------------------------------+
| ::${s}SchedulerGetProperties()              | Get properties of a scheduler     |
|                                                  | component (sub-device, engines    |
|                                                  | linked to this scheduler,         |
|                                                  | supported scheduler modes.        |
+--------------------------------------------------+-----------------------------------+
| ::${s}SchedulerGetCurrentMode()             | Get the current scheduler mode    |
|                                                  | (timeout, timeslice, exclusive,   |
|                                                  | single command queue)             |
+--------------------------------------------------+-----------------------------------+
| ::${s}SchedulerGetTimeoutModeProperties()   | Get the settings for the timeout  |
|                                                  | scheduler mode                    |
+--------------------------------------------------+-----------------------------------+
| ::${s}SchedulerGetTimesliceModeProperties() | Get the settings for the          |
|                                                  | timeslice scheduler mode          |
+--------------------------------------------------+-----------------------------------+
| ::${s}SchedulerSetTimeoutMode()             | Change to timeout scheduler mode  |
|                                                  | and/or change properties          |
+--------------------------------------------------+-----------------------------------+
| ::${s}SchedulerSetTimesliceMode()           | Change to timeslice scheduler     |
|                                                  | mode and/or change properties     |
+--------------------------------------------------+-----------------------------------+
| ::${s}SchedulerSetExclusiveMode()           | Change to exclusive scheduler     |
|                                                  | mode and/or change properties     |
+--------------------------------------------------+-----------------------------------+
| ::${s}SchedulerSetComputeUnitDebugMode()    | Change to compute unit debug      |
|                                                  | scheduler mode and/or change      |
|                                                  | properties                        |
+--------------------------------------------------+-----------------------------------+

The pseudo code below shows how to stop the scheduler enforcing fairness
while permitting other work to attempt to run:

.. parsed-literal::

   function DisableSchedulerWatchdog(${s}_device_handle_t hSysmanDevice)
       uint32_t numSched
       if ((::${s}DeviceEnumSchedulers(hSysmanDevice, &numSched, NULL) == ${X}_RESULT_SUCCESS))
           ${s}_sched_handle_t* pSchedHandles =
               allocate_memory(numSched * sizeof(${s}_sched_handle_t))
           if (::${s}DeviceEnumSchedulers(hSysmanDevice, &numSched, pSchedHandles) == ${X}_RESULT_SUCCESS)
               for (index = 0 .. numSched-1)
                   ${x}_result_t res
                   ${s}_sched_mode_t currentMode
                   res = ::${s}SchedulerGetCurrentMode(pSchedHandles[index], &currentMode)
                   if (res == ${X}_RESULT_SUCCESS)
                       ${x}_bool_t requireReload
                       ::${s}_sched_timeout_properties_t props
                       props.watchdogTimeout = ${S}_SCHED_WATCHDOG_DISABLE
                       res = ::${s}SchedulerSetTimeoutMode(pSchedHandles[index], &props, &requireReload)
                       if (res == ${X}_RESULT_SUCCESS)
                           if (requireReload)
                               output("WARNING: Reload the driver to complete desired configuration.")
                           else
                               output("Schedule mode changed successfully.")
                       else if(res == ${X}_RESULT_ERROR_UNSUPPORTED_FEATURE)
                           output("ERROR: The timeout scheduler mode is not supported on this device.")
                       else if(res == ${X}_RESULT_ERROR_INSUFFICIENT_PERMISSIONS)
                           output("ERROR: Don't have permissions to change the scheduler mode.")
                       else
                           output("ERROR: Problem calling the API to change the scheduler mode.")
                   else if(res == ${X}_RESULT_ERROR_UNSUPPORTED_FEATURE)
                       output("ERROR: Scheduler modes are not supported on this device.")
                   else
                       output("ERROR: Problem calling the API.")

Device reset
~~~~~~~~~~~~

The device can be reset using the following function:

+-----------------------------------+-----------------------------------+
| Function                          | Description                       |
+===================================+===================================+
| ::${s}DeviceReset()          | Requests that the driver          |
|                                   | perform a PCI bus reset of the    |
|                                   | device.                           |
+-----------------------------------+-----------------------------------+

PCI link operations
~~~~~~~~~~~~~~~~~~~

The following functions permit getting data about the PCI endpoint for the device:

+-------------------------------------+-----------------------------------+
| Function                            | Description                       |
+=====================================+===================================+
| ::${s}DevicePciGetProperties() | Get static properties for the PCI |
|                                     | port - BDF address, number of     |
|                                     | bars, maximum supported speed     |
+-------------------------------------+-----------------------------------+
| ::${s}DevicePciGetState()      | Get current PCI port speed        |
|                                     | (number of lanes, generation)     |
+-------------------------------------+-----------------------------------+
| ::${s}DevicePciGetBars()       | Get information about each        |
|                                     | configured PCI bar                |
+-------------------------------------+-----------------------------------+
| ::${s}DevicePciGetStats()      | Get PCI statistics - throughput,  |
|                                     | total packets, number of packet   |
|                                     | replays                           |
+-------------------------------------+-----------------------------------+

The pseudo code below shows how to output the PCI BDF address:

.. parsed-literal::

   function ShowPciInfo(${s}_device_handle_t hSysmanDevice)
       ::${s}_pci_properties_t pciProps;
       if (::${s}DevicePciGetProperties(hSysmanDevice, &pciProps) == ${X}_RESULT_SUCCESS)
           output("    PCI address:        %04u:%02u:%02u.%u",
               pciProps.address.domain,
               pciProps.address.bus,
               pciProps.address.device,
               pciProps.address.function);

.. _Power:

Operations on power domains
---------------------------

The PSU (Power Supply Unit) provides power to a device. The amount of
power drawn by a device is a function of the voltage and frequency, both
of which are controlled by the Punit, a micro-controller on the device.
If the voltage and frequency are too high, two conditions can occur:

1. Over-current - This is where the current drawn by the device exceeds
   the maximum current that the PSU can supply. The PSU asserts a signal
   when this occurs, and it is processed by the Punit.
2. Over-temperature - The device is generating too much heat that cannot
   be dissipated fast enough. The Punit monitors temperatures and reacts
   when the sensors show the maximum temperature exceeds the threshold
   TjMax (typically 100 degrees Celsius).

When either of these conditions occurs, the Punit throttles the
frequencies/voltages of the device down to their minimum values,
severely impacting performance. The Punit avoids such severe throttling
by measuring the actual power being consumed by the system and slowly
throttling the frequencies down when power exceeds some limits. Three
limits are monitored by the Punit:

+-----------------------+-----------------------+-----------------------+
| Limit                 | Window                | Description           |
+=======================+=======================+=======================+
| Peak                  | Instantaneous         | Punit tracks the      |
|                       |                       | instantaneous power.  |
|                       |                       | When this exceeds a   |
|                       |                       | programmable          |
|                       |                       | threshold, the Punit  |
|                       |                       | will aggressively     |
|                       |                       | throttle              |
|                       |                       | frequencies/voltages. |
|                       |                       | The threshold is      |
|                       |                       | referred to as PL4 -  |
|                       |                       | Power Limit 4 - or    |
|                       |                       | peak power.           |
+-----------------------+-----------------------+-----------------------+
| Burst                 | 2ms                   | Punit tracks the 2ms  |
|                       |                       | moving average of     |
|                       |                       | power. When this      |
|                       |                       | exceeds a             |
|                       |                       | programmable          |
|                       |                       | threshold, the Punit  |
|                       |                       | starts throttling     |
|                       |                       | frequencies/voltages. |
|                       |                       | The threshold is      |
|                       |                       | referred to as PL2 -  |
|                       |                       | Power Limit 2 - or    |
|                       |                       | burst power.          |
+-----------------------+-----------------------+-----------------------+
| Sustained             | 28sec                 | Punit tracks the      |
|                       |                       | 28sec moving average  |
|                       |                       | of power. When this   |
|                       |                       | exceeds a             |
|                       |                       | programmable          |
|                       |                       | threshold, the Punit  |
|                       |                       | throttles             |
|                       |                       | frequencies/voltages. |
|                       |                       | The threshold is      |
|                       |                       | referred to as PL1 -  |
|                       |                       | Power Limit 1 - or    |
|                       |                       | sustained power.      |
+-----------------------+-----------------------+-----------------------+

Peak power limit is generally greater than the burst power limit which
is generally greater than the sustained power limit. The default factory
values are tuned assuming the device is operating at normal temperatures
running significant workloads:

-  The peak power limit is tuned to avoid tripping the PSU over-current
   signal for all but the most intensive compute workloads. Most
   workloads should be able to run at maximum frequencies without
   hitting this condition.
-  The burst power limit permits most workloads to run at maximum
   frequencies for short periods.
-  The sustained power limit will be triggered if high frequencies are
   requested for lengthy periods (configurable, default is 28sec) and
   the frequencies will be throttled if the high requests and
   utilization of the device continues.

Some power domains support requesting the event
::${S}_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED be generated when the
energy consumption exceeds some value. This can be a useful technique to
suspend an application until the GPU becomes busy. The technique
involves calling ::${s}PowerSetEnergyThreshold() with some delta
energy threshold, registering to receive the event using the function
::${s}EventSetConfig() and then calling ::${s}EventListen() to
block until the event is triggered. When the energy consumed by the
power domain from the time the call is made exceeds the specified delta,
the event is triggered, and the application is woken up.

The following functions are provided to manage the power of the device:

+--------------------------------------+--------------------------------------------------+
| Function                             | Description                                      |
+======================================+==================================================+
| ::${s}DeviceEnumPowerDomains()  | Enumerate the power domains.                     |
+--------------------------------------+--------------------------------------------------+
| ::${s}PowerGetProperties()      | Get the minimum/maximum power limit that can be  |
|                                      | specified when changing the power limits of a    |
|                                      | specific power domain. Also read the factory     |
|                                      | default sustained power limit of the part.       |
+--------------------------------------+--------------------------------------------------+
| ::${s}PowerGetEnergyCounter()   | Read the energy consumption of                   |
|                                      | the specific domain.                             |
+--------------------------------------+--------------------------------------------------+
| ::${s}PowerGetLimits()          | Get the sustained/burst/peak                     |
|                                      | power limits for the specific                    |
|                                      | power domain.                                    |
+--------------------------------------+--------------------------------------------------+
| ::${s}PowerSetLimits()          | Set the sustained/burst/peak                     |
|                                      | power limits for the specific                    |
|                                      | power domain.                                    |
+--------------------------------------+--------------------------------------------------+
| ::${s}PowerGetEnergyThreshold() | Get the current energy threshold.                |
|                                      |                                                  |
+--------------------------------------+--------------------------------------------------+
| ::${s}PowerSetEnergyThreshold() | Set the energy threshold. Event                  |
|                                      | ::${S}_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED        |
|                                      |                                                  |
|                                      | will be generated when the energy                |
|                                      | consumed since calling this                      |
|                                      | function exceeds the specified                   |
|                                      | threshold.                                       |
+--------------------------------------+--------------------------------------------------+

The pseudo code below shows how to output information about each power
domain on a device:

.. parsed-literal::

   function ShowPowerDomains(${s}_device_handle_t hSysmanDevice)
       uint32_t numPowerDomains
       if (::${s}DeviceEnumPowerDomains(hSysmanDevice, &numPowerDomains, NULL) == ${X}_RESULT_SUCCESS)
           ${s}_pwr_handle_t* phPower =
               allocate_memory(numPowerDomains * sizeof(${s}_pwr_handle_t))
           if (::${s}DeviceEnumPowerDomains(hSysmanDevice, &numPowerDomains, phPower) == ${X}_RESULT_SUCCESS)
               for (pwrIndex = 0 .. numPowerDomains-1)
                   ::${s}_power_properties_t props
                   if (::${s}PowerGetProperties(phPower[pwrIndex], &props) == ${X}_RESULT_SUCCESS)
                       if (props.onSubdevice)
                           output("Sub-device %u power:\n", props.subdeviceId)
                           output("    Can control: %s", props.canControl ? "yes" : "no")
                           call_function ShowPowerLimits(phPower[pwrIndex])
                       else
                           output("Total package power:\n")
                           output("    Can control: %s", props.canControl ? "yes" : "no")
                           call_function ShowPowerLimits(phPower[pwrIndex])
       free_memory(...)
   }

   function ShowPowerLimits(${s}_pwr_handle_t hPower)
       ::${s}_power_sustained_limit_t sustainedLimits
       ::${s}_power_burst_limit_t burstLimits
       ::${s}_power_peak_limit_t peakLimits
       if (::${s}PowerGetLimits(hPower, &sustainedLimits, &burstLimits, &peakLimits) == ${X}_RESULT_SUCCESS)
           output("    Power limits\n")
           if (sustainedLimits.enabled)
               output("        Sustained: %.3f W %.3f sec",
                   sustainedLimits.power / 1000,
                   sustainedLimits.interval / 1000)
           else
               output("        Sustained: Disabled")
           if (burstLimits.enabled)
               output("        Burst:     %.3f", burstLimits.power / 1000)
           else
               output("        Burst:     Disabled")
           output("        Burst:     %.3f", peakLimits.power / 1000)

The pseudo code shows how to output the average power. It assumes that
the function is called regularly (say every 100ms).

.. parsed-literal::

   function ShowAveragePower(${s}_pwr_handle_t hPower, ::${s}_power_energy_counter_t* pPrevEnergyCounter)
       ::${s}_power_energy_counter_t newEnergyCounter;
       if (::${s}PowerGetEnergyCounter(hPower, &newEnergyCounter) == ${X}_RESULT_SUCCESS)
           uint64_t deltaTime = newEnergyCounter.timestamp - pPrevEnergyCounter->timestamp;
           if (deltaTime)
               output("    Average power: %.3f W", (newEnergyCounter.energy - pPrevEnergyCounter->energy) / deltaTime);
               \*pPrevEnergyCounter = newEnergyCounter;

.. _Frequency:

Operations on frequency domains
-------------------------------

The hardware manages frequencies to achieve a balance between best
performance and power consumption. Most devices have one or more
frequency domains.

The following functions are provided to manage the frequency domains on
the device:

+------------------------------------------+-----------------------------------+
| Function                                 | Description                       |
+==========================================+===================================+
| ::${s}DeviceEnumFrequencyDomains()  | Enumerate all the frequency       |
|                                          | domains on the device and         |
|                                          | sub-devices.                      |
+------------------------------------------+-----------------------------------+
| ::${s}FrequencyGetProperties()      | Find out which domain             |
|                                          | ::${s}_freq_domain_t is controlled |
|                                          | by this frequency and min/max     |
|                                          | hardware frequencies.             |
+------------------------------------------+-----------------------------------+
| ::${s}FrequencyGetAvailableClocks() | Get an array of all available     |
|                                          | frequencies that can be requested |
|                                          | on this domain.                   |
+------------------------------------------+-----------------------------------+
| ::${s}FrequencyGetRange()           | Get the current min/max frequency |
|                                          | between which the hardware can    |
|                                          | operate for a frequency domain.   |
+------------------------------------------+-----------------------------------+
| ::${s}FrequencySetRange()           | Set the min/max frequency between |
|                                          | which the hardware can operate    |
|                                          | for a frequency domain.           |
+------------------------------------------+-----------------------------------+
| ::${s}FrequencyGetState()           | Get the current frequency         |
|                                          | request, actual frequency, TDP    |
|                                          | frequency and throttle reasons    |
|                                          | for a frequency domain.           |
+------------------------------------------+-----------------------------------+
| ::${s}FrequencyGetThrottleTime()    | Gets the amount of time a         |
|                                          | frequency domain has been         |
|                                          | throttled.                        |
+------------------------------------------+-----------------------------------+

It is only permitted to set the frequency range if the device property
::${s}_freq_properties_t.canControl is true for the specific frequency
domain.

By setting the min/max frequency range to the same value, software is
effectively disabling the hardware-controlled frequency and getting a
fixed stable frequency providing the Punit does not need to throttle due
to excess power/heat.

Based on the power/thermal conditions, the frequency requested by
software or the hardware may not be respected. This situation can be
determined using the function ::${s}FrequencyGetState() which will
indicate the current frequency request, the actual (resolved) frequency
and other frequency information that depends on the current conditions.
If the actual frequency is below the requested frequency,
::${s}_freq_state_t.throttleReasons will provide the reasons why the
frequency is being limited by the Punit.

When a frequency domain starts being throttled, the event
::${S}_EVENT_TYPE_FREQ_THROTTLED is triggered if this is supported
(check ::${s}_freq_properties_t.isThrottleEventSupported).

Frequency/Voltage overclocking
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Overclocking involves modifying the voltage-frequency (V-F) curve to
either achieve better performance by permitting the hardware to reach
higher frequencies or better efficiency by lowering the voltage for the
same frequency.

By default, the hardware imposes a factory-fused maximum frequency and a
voltage-frequency curve. The voltage-frequency curve specifies how much
voltage is needed to safely reach a given frequency without hitting
overcurrent conditions. If the hardware detects overcurrent (IccMax), it
will severely throttle frequencies in order to protect itself. Also, if
the hardware detects that any part of the chip exceeds a maximum
temperature limit (TjMax) it will also severely throttle frequencies.

To improve maximum performance, the following modifications can be made:

-  Increase the maximum frequency.
-  Increase the voltage to ensure stability at the higher frequency.
-  Increase the maximum current (IccMax).
-  Increase the maximum temperature (TjMax).

All these changes come with the risk of damage the device.

To improve efficiency for a given workload that is not excercising the
full circuitry of the device, the following modifications can be made:

-  Decrease the voltage

Frequency/voltage overclocking is accomplished by calling ::${s}FrequencyOcSetConfig()
with a new overclock configuration ::${s}_oc_config_t. There are two modes that control the
way voltage is handled when overclocking the frequency:

+-----------------------------------+------------------------------------------------+
| Voltage overclock mode            | Description                                    |
+===================================+================================================+
| ::${S}_OC_MODE_OVERRIDE            | In this mode, a fixed                          |
|                                   | user-supplied voltage                          |
|                                   | (::${s}_oc_config_t.voltageTarget +       |
|                                   | ::${s}_oc_config_t.voltageOffset)         |
|                                   | is applied at all times,                       |
|                                   | independent of the frequency                   |
|                                   | request. This is not efficient but             |
|                                   | can improve stability by avoiding              |
|                                   | power-supply voltage changes as the            |
|                                   | frequency changes.                             |
+-----------------------------------+------------------------------------------------+
| ::${S}_OC_MODE_OVERRIDE            | In this mode, a fixed                          |
|                                   | user-supplied voltage is applied               |
|                                   | at all times, independent of the               |
|                                   | frequency request. This is not                 |
|                                   | efficient but can improve                      |
|                                   | stability by avoiding                          |
|                                   | power-supply voltage changes as                |
|                                   | the frequency changes. Generally,              |
|                                   | this mode is used in conjunction               |
|                                   | with a fixed frequency.                        |
+-----------------------------------+------------------------------------------------+

The following functions are provided to handle overclocking:

+-----------------------------------------+-----------------------------------+
| Function                                | Description                       |
+=========================================+===================================+
| ::${s}FrequencyOcGetCapabilities() | Determine the overclock           |
|                                         | capabilities of the device.       |
+-----------------------------------------+-----------------------------------+
| ::${s}FrequencyOcGetConfig()       | Get the overclock configuration   |
|                                         | in effect.                        |
+-----------------------------------------+-----------------------------------+
| ::${s}FrequencyOcSetConfig()       | Set a new overclock               |
|                                         | configuration.                    |
+-----------------------------------------+-----------------------------------+
| ::${s}FrequencyOcGetIccMax()       | Get the maximum current limit in  |
|                                         | effect.                           |
+-----------------------------------------+-----------------------------------+
| ::${s}FrequencyOcSetIccMax()       | Set a new maximum current limit.  |
+-----------------------------------------+-----------------------------------+
| ::${s}FrequencyOcGetTjMax()        | Get the maximum temperature limit |
|                                         | in effect.                        |
+-----------------------------------------+-----------------------------------+
| ::${s}FrequencyOcSetTjMax()        | Set a new maximum temperature     |
|                                         | limit.                            |
+-----------------------------------------+-----------------------------------+

Overclocking can be turned off by calling
::${s}FrequencyOcSetConfig() with mode ::${S}_OC_MODE_OFF and by
calling ::${s}FrequencyOcGetIccMax() and ::${s}FrequencyOcSetTjMax() with values of 0.0.

.. _Performance-Factor:

Tuning workload performance
---------------------------

While hardware attempts to balance system resources effectively, there are
workloads that can benefit from external performance hints. For hardware
where this is possible, the API exposes *Performance Factors* domains that
can be used to provide these hints.

A Performance Factor is defined as a number between 0 and 100 that expresses
a trade-off between the energy provided to the accelerator units and the
energy provided to the supporting units. As an example, a compute heavy
workload benefits from a higher distribution of energy at the computational
units rather than for the memory controller. Alternatively, a memory bounded
workload can benefit by trading off performance of the computational units
for higher throughput in the memory controller. Generally the hardware
will get this balance right, but the Performance Factor can be used to
make the balance more aggressive. In the examples given, a Performance
Factor of 100 would indicate that the workload is completely compute
bounded and requires very little support from the memory controller.
Alternatively, a Performance Factor of 0 would indicate that the workload
is completely memory bounded and the performance of the memory
controller needs to be increased.

Tuning for a workload can involve running the application repeatedly with
different values of the Performance Factor from 0 to 100 and choosing
the value that gives the best performance. The default value is 50.
Alternatively, a more dynamic approach would involve monitoring the
various utilization metrics of the accelerator to determine memory
and compute bounded and moving the Performance Factor up and down
in order to remove the bottleneck.

The API provides a way to enumerate the domains that can be controlled
by a Performance Factor. A domain contains one or more accelerators
whose performance will be affected by this setting. The API provides
functions to change the Performance Factor for a domain.

Here is a summary of the available functions:

+-------------------------------------------------+--------------------------------------------------------------------+
| Function                                        | Description                                                        |
+=================================================+====================================================================+
| ::${s}DeviceEnumPerformanceFactorDomains() | Enumerate the Performance Factor domains available on the          |
|                                                 | hardware.                                                          |
+-------------------------------------------------+--------------------------------------------------------------------+
| ::${s}PerformanceFactorGetProperties()     | Find out if the Performance Factor domain is located on a          |
|                                                 | sub-device and which accelerators are affected by it.              |
+-------------------------------------------------+--------------------------------------------------------------------+
| ::${s}PerformanceFactorGetConfig()         | Read the current performance factor being used by the hardware     |
|                                                 | for a domain.                                                      |
+-------------------------------------------------+--------------------------------------------------------------------+
| ::${s}PerformanceFactorSetConfig()         | Change the Performance Factor of the hardware for a domain.        |
+-------------------------------------------------+--------------------------------------------------------------------+


.. _Engines:

Operations on engine groups
---------------------------

It is possible to monitor the activity of one or engines combined into
an **engine group**. A device can have multiple engine groups and the
possible types are defined in ::${s}_engine_group_t. The current engine
groups supported are global activity across all engines, activity across
all compute accelerators, activity across all media accelerators and
activity across all copy engines.

By taking two snapshots of the activity counters, it is possible to
calculate the average utilization of different parts of the device.

The following functions are provided:

+-------------------------------------+-----------------------------------+
| Function                            | Description                       |
+=====================================+===================================+
| ::${s}DeviceEnumEngineGroups() | Enumerate the engine groups that  |
|                                     | can be queried.                   |
+-------------------------------------+-----------------------------------+
| ::${s}EngineGetProperties()    | Get the properties of an engine   |
|                                     | group. This will return the type  |
|                                     | of engine group (one of           |
|                                     | ::${s}_engine_group_t) and on      |
|                                     | which sub-device the group is     |
|                                     | making measurements.              |
+-------------------------------------+-----------------------------------+
| ::${s}EngineGetActivity()      | Returns the activity counters for |
|                                     | an engine group.                  |
+-------------------------------------+-----------------------------------+

.. _Standby:

Operations on standby domains
-----------------------------

When a device is idle, it will enter a low-power state. Since exit from
low-power states have associated latency, it can hurt performance. The
hardware attempts to stike a balance between saving power when there are
large idle times between workload submissions to the device and keeping
the device awake when it determines that the idle time between submissions
is short.

A device can consist of one or more standby domains - the list of
domains is given by ::${s}_standby_type_t.

The following functions can be used to control how the hardware promotes
to standby states:

+---------------------------------------+-----------------------------------+
| Function                              | Description                       |
+=======================================+===================================+
| ::${s}DeviceEnumStandbyDomains() | Enumerate the standby domains.    |
+---------------------------------------+-----------------------------------+
| ::${s}StandbyGetProperties()     | Get the properties of a standby   |
|                                       | domain. This will return the      |
|                                       | parts of the device that are      |
|                                       | affected by this domain (one of   |
|                                       | ::${s}_engine_group_t) and on      |
|                                       | which sub-device the domain is    |
|                                       | located.                          |
+---------------------------------------+-----------------------------------+
| ::${s}StandbyGetMode()           | Get the current promotion mode    |
|                                       | (one of                           |
|                                       | ::${s}_standby_promo_mode_t) for a |
|                                       | standby domain.                   |
+---------------------------------------+-----------------------------------+
| ::${s}StandbySetMode()           | Set the promotion mode (one of    |
|                                       | ::${s}_standby_promo_mode_t) for a |
|                                       | standby domain.                   |
+---------------------------------------+-----------------------------------+

.. _Firmware:

Operations on firmwares
-----------------------

The following functions are provided to manage firmwares on the device:

+------------------------------------+-----------------------------------+
| Function                           | Description                       |
+====================================+===================================+
| ::${s}DeviceEnumFirmwares()   | Enumerate all firmwares that can  |
|                                    | be managed on the device.         |
+------------------------------------+-----------------------------------+
| ::${s}FirmwareGetProperties() | Find out the name and version of  |
|                                    | a firmware.                       |
+------------------------------------+-----------------------------------+
| ::${s}FirmwareGetChecksum()   | Get the checksum for an installed |
|                                    | firmware.                         |
+------------------------------------+-----------------------------------+
| ::${s}FirmwareFlash()         | Flash a new firmware image.       |
+------------------------------------+-----------------------------------+

.. _Memory:

Querying memory modules
-----------------------

The API provides an enumeration of all device memory modules. For each
memory module, the current and maximum bandwidth can be queried. The API
also provides a health metric which can take one of the following values
(::${s}_mem_health_t):

+-----------------------------------+-----------------------------------+
| Memory health                     | Description                       |
+===================================+===================================+
| ::${S}_MEM_HEALTH_OK               | All memory channels are healthy.  |
+-----------------------------------+-----------------------------------+
| ::${S}_MEM_HEALTH_DEGRADED         | Excessive correctable errors have |
|                                   | been detected on one or more      |
|                                   | channels. Device should be reset. |
+-----------------------------------+-----------------------------------+
| ::${S}_MEM_HEALTH_CRITICAL         | Operating with reduced memory to  |
|                                   | cover banks with too many         |
|                                   | uncorrectable errors.             |
+-----------------------------------+-----------------------------------+
| ::${S}_MEM_HEALTH_REPLACE          | Device should be replaced due to  |
|                                   | excessive uncorrectable errors.   |
+-----------------------------------+-----------------------------------+

When the health state of a memory module changes, the event
::${S}_EVENT_TYPE_MEM_HEALTH is triggered.

The following functions provide access to information about the device
memory modules:

+--------------------------------------+-----------------------------------+
| Function                             | Description                       |
+======================================+===================================+
| ::${s}DeviceEnumMemoryModules() | Enumerate the memory modules.     |
+--------------------------------------+-----------------------------------+
| ::${s}MemoryGetProperties()     | Find out the type of memory and   |
|                                      | maximum physical memory of a      |
|                                      | module.                           |
+--------------------------------------+-----------------------------------+
| ::${s}MemoryGetBandwidth()      | Returns memory bandwidth counters |
|                                      | for a module.                     |
+--------------------------------------+-----------------------------------+
| ::${s}MemoryGetState()          | Returns the currently health free |
|                                      | memory and total physical memory  |
|                                      | for a memory module.              |
+--------------------------------------+-----------------------------------+

.. _Fabric-Port:

Operations on Fabric ports
--------------------------

**Fabric** is the term given to describe high-speed interconnections
between accelerator devices, primarily used to provide low latency fast
access to remote device memory. Devices have one or more **fabric
ports** that transmit and receive data over physical links. Links
connect fabric ports, thus permitting data to travel between devices.
Routing rules determine the flow of traffic through the fabric.

The figure below shows four devices, each with two fabric ports. Each
port has a link that connects it to a port on another device. In this
example, the devices are connected in a ring. Device A and D can access
each other's memory through either device B or device C depending on how
the fabric routing rules are configured. If the connection between
device B and D goes down, the routing rules can be modified such that
device B and D can still access each other's memory by going through two
hops in the fabric (device A and C).

.. image:: ../images/tools_sysman_fabric.png

The API permits enumerating all the ports available on a device. Each
port is uniquely identified within a system by the following information:

- Fabric ID: Unique identifier for the fabric end-point
- Attach ID: Unique identifier for the device attachment point
- Port Number: The logical port number (this is typically marked somewhere on the physical device)

The API provides this information in the struct ::{t}_fabric_port_id_t.
The identifiers are not universal - uniqueness is only guaranteed
within a given system and provided the system configuration does not change.

When a fabric port is connected, the API provides the unique identifier
for the remote fabric port. By enumerating all ports in a system and
matching up the remote port identifies, an application can can build up
a topology map of connectivity.

For each port, the API permits querying its configuration (UP/DOWN) and
its health which can take one of the following values:

+-----------------------------------+-----------------------------------+
| Fabric port health                | Description                       |
+===================================+===================================+
| ::${S}_FABRIC_PORT_STATUS_GREEN    | The port is up and operating as   |
|                                   | expected.                         |
+-----------------------------------+-----------------------------------+
| ::${S}_FABRIC_PORT_STATUS_YELLOW   | The port is up but has quality    |
|                                   | and/or bandwidth degradation.     |
+-----------------------------------+-----------------------------------+
| ::${S}_FABRIC_PORT_STATUS_RED      | Port connection instabilities are |
|                                   | preventing workloads making       |
|                                   | forward progress.                 |
+-----------------------------------+-----------------------------------+
| ::${S}_FABRIC_PORT_STATUS_BLACK    | The port is configured down.      |
+-----------------------------------+-----------------------------------+

If the port is in a yellow state, the API provides additional
information about the types of quality degradation that are being
observed. If the port is in a red state, the API provides additional
information about the causes of the instability.

When a port's health state changes, the event
::${S}_EVENT_TYPE_FABRIC_PORT_HEALTH is triggered.

The API provides the current transmit and receive bitrate of each port.
It also permits measuring the receive and transmit bandwidth flowing
through each port - these metrics include the protocal overhead in addition
to traffic generated by the devices.

Since ports can pass data directly through to another port, the measured
bandwidth at a port can be higher than the actual bandwidth generated by
the accelerators directly connected by two ports. As such, bandwidth
metrics at each port are more relevant for determining points of
congestion in the fabric and less relevant for measuring the total
bandwidth passing between two accelerators.

The following functions can be used to manage Fabric ports:

+--------------------------------------+-----------------------------------+
| Function                             | Description                       |
+======================================+===================================+
| ::${s}DeviceEnumFabricPorts()   | Enumerate all fabric ports on the |
|                                      | device.                           |
+--------------------------------------+-----------------------------------+
| ::${s}FabricPortGetProperties() | Get static properties about the   |
|                                      | port (model, pord Id, max         |
|                                      | receive/transmit speed).          |
+--------------------------------------+-----------------------------------+
| ::${s}FabricPortGetLinkType()   | Get details about the physical    |
|                                      | link connected to the port.       |
+--------------------------------------+-----------------------------------+
| ::${s}FabricPortGetConfig()     | Determine if the port is          |
|                                      | configured UP and if beaconing is |
|                                      | on or off.                        |
+--------------------------------------+-----------------------------------+
| ::${s}FabricPortSetConfig()     | Configure the port UP or DOWN and |
|                                      | turn beaconing on or off.         |
+--------------------------------------+-----------------------------------+
| ::${s}FabricPortGetState()      | Determine the health of the port  |
|                                      | connection, reasons for link      |
|                                      | degradation or connection issues, |
|                                      | current receive/transmit and port |
|                                      | Id of the remote end-point.       |
+--------------------------------------+-----------------------------------+
| ::${s}FabricPortGetThroughput() | Get port receive/transmit         |
|                                      | counters along with current       |
|                                      | receive/transmit port speed.      |
+--------------------------------------+-----------------------------------+

For devices with sub-devices, the fabric ports are usually located in
the sub-device. Given a device handle, ::${s}DeviceEnumFabricPorts() will
include the ports on each sub-device. In this case,
::${s}_fabric_port_properties_t.onSubdevice will be set to true and
::${s}_fabric_port_properties_t.subdeviceId will give the subdevice ID
where that port is located.

The pseudo-code below shows how to get the state of all fabric ports in
the device and sub-devices:

.. parsed-literal::

   void ShowFabricPorts(${s}_device_handle_t hSysmanDevice)
       uint32_t numPorts
       if ((::${s}DeviceEnumFabricPorts(hSysmanDevice, &numPorts, NULL) == ${X}_RESULT_SUCCESS))
           ${s}_fabric_port_handle_t* phPorts =
               allocate_memory(numPorts * sizeof(${s}_fabric_port_handle_t))
           if (::${s}DeviceEnumFabricPorts(hSysmanDevice, &numPorts, phPorts) == ${X}_RESULT_SUCCESS)
               for (index = 0 .. numPorts-1)
                   # Show information about a particular port
                   output("    Port %u:\n", index)
                   call_function ShowFabricPortInfo(phPorts[index])
       free_memory(...)

   function ShowFabricPortInfo(${s}_fabric_port_handle_t hPort)
       ::${s}_fabric_port_properties_t props
       if (::${s}FabricPortGetProperties(hPort, &props) == ${X}_RESULT_SUCCESS)
           ::${s}_fabric_port_state_t state
           if (::${s}FabricPortGetState(hPort, &state) == ${X}_RESULT_SUCCESS)
               ::${s}_fabric_link_type_t link
               if (::${s}FabricPortGetLinkType(hPort, false, &link) == ${X}_RESULT_SUCCESS)
                   ::${s}_fabric_port_config_t config
                   if (::${s}FabricPortGetConfig(hPort, &config) == ${X}_RESULT_SUCCESS)
                       output("        Model:                 %s", props.model)
                       if (props.onSubdevice)
                           output("        On sub-device:         %u", props.subdeviceId)
                       if (config.enabled)
                       {
                           var status
                           output("        Config:                UP")
                           switch (state.status)
                               case ${S}_FABRIC_PORT_STATUS_GREEN:
                                   status = "GREEN - The port is up and operating as expected"
                               case ${S}_FABRIC_PORT_STATUS_YELLOW:
                                   status = "YELLOW - The port is up but has quality and/or bandwidth degradation"
                               case ${S}_FABRIC_PORT_STATUS_RED:
                                   status = "RED - Port connection instabilities"
                               case ${S}_FABRIC_PORT_STATUS_BLACK:
                                   status = "BLACK - The port is configured down"
                               default:
                                   status = "UNKNOWN"
                           output("        Status:                %s", status)
                           output("        Link type:             %s", link.desc)
                           output(
                               "        Max speed (rx/tx):     %llu/%llu bytes/sec",
                               props.maxRxSpeed.bitRate * props.maxRxSpeed.width / 8,
                               props.maxTxSpeed.bitRate * props.maxTxSpeed.width / 8)
                           output(
                               "        Current speed (rx/tx): %llu/%llu bytes/sec",
                               state.rxSpeed.bitRate * state.rxSpeed.width / 8,
                               state.txSpeed.bitRate * state.txSpeed.width / 8)
                       else
                           output("        Config:                DOWN")

.. _Temperature:

Querying temperature
--------------------

A device has multiple temperature sensors embedded at different
locations. The following locations are supported:

+-----------------------------------+-----------------------------------+
| Temperature sensor location       | Description                       |
+===================================+===================================+
| ::${S}_TEMP_SENSORS_GLOBAL         | Returns the maximum measured      |
|                                   | across all sensors in the device. |
+-----------------------------------+-----------------------------------+
| ::${S}_TEMP_SENSORS_GPU            | Returns the maximum measured      |
|                                   | across all sensors in the GPU     |
|                                   | accelerator.                      |
+-----------------------------------+-----------------------------------+
| ::${S}_TEMP_SENSORS_MEMORY         | Returns the maximum measured      |
|                                   | across all sensors in the device  |
|                                   | memory.                           |
+-----------------------------------+-----------------------------------+

For some sensors, it is possible to request that events be triggered
when temperatures cross thresholds. This is accomplished using the
function ::${s}TemperatureGetConfig() and
::${s}TemperatureSetConfig(). Support for specific events is
accomplished by calling ::${s}TemperatureGetProperties(). In
general, temperature events are only supported on the temperature sensor
of type ::${S}_TEMP_SENSORS_GLOBAL. The list below describes the list of
temperature events:

## --validate=off
+-----------------------------------------+-----------------------+-----------------------+
| Event                                   | Check support         | Description           |
+=========================================+=======================+=======================+
| ::${S}_EVENT_TYPE_TEMP_CRITICAL          | ::${s}_temp_properties | The event is          |
|                                         | _t.isCriticalTempSupp | triggered when the    |
|                                         | orted                 | temperature crosses   |
|                                         |                       | into the critical     |
|                                         |                       | zone where severe     |
|                                         |                       | frequency throttling  |
|                                         |                       | will be taking place. |
+-----------------------------------------+-----------------------+-----------------------+
| ::${S}_EVENT_TYPE_TEMP_THRESHOLD1        | ::${s}_temp_properties | The event is          |
|                                         | _t.isThreshold1Suppor | triggered when the    |
|                                         | ted                   | temperature crosses   |
|                                         |                       | the custom threshold  |
|                                         |                       | 1. Flags can be set   |
|                                         |                       | to limit the trigger  |
|                                         |                       | to when crossing from |
|                                         |                       | high to low or low to |
|                                         |                       | high.                 |
+-----------------------------------------+-----------------------+-----------------------+
| ::${S}_EVENT_TYPE_TEMP_THRESHOLD2        | ::${s}_temp_properties | The event is          |
| PE_TEMP_THRESHOLD2                      | _t.isThreshold2Suppor | triggered when the    |
|                                         | ted                   | temperature crosses   |
|                                         |                       | the custom threshold  |
|                                         |                       | 2. Flags can be set   |
|                                         |                       | to limit the trigger  |
|                                         |                       | to when crossing from |
|                                         |                       | high to low or low to |
|                                         |                       | high.                 |
+-----------------------------------------+-----------------------+-----------------------+
## --validate=on

The following function can be used to manage temperature sensors:

+-------------------------------------------+-----------------------------------+
| Function                                  | Description                       |
+===========================================+===================================+
| ::${s}DeviceEnumTemperatureSensors() | Enumerate the temperature sensors |
|                                           | on the device.                    |
+-------------------------------------------+-----------------------------------+
| ::${s}TemperatureGetProperties()     | Get static properties for a       |
|                                           | temperature sensor. In            |
|                                           | particular, this will indicate    |
|                                           | which parts of the device the     |
|                                           | sensor measures (one of           |
|                                           | ::${s}_temp_sensors_t).            |
+-------------------------------------------+-----------------------------------+
| ::${s}TemperatureGetConfig()         | Get information about the current |
|                                           | temperature thresholds -          |
|                                           | enabled/threshold/processID.      |
+-------------------------------------------+-----------------------------------+
| ::${s}TemperatureSetConfig()         | Set new temperature thresholds.   |
|                                           | Events will be triggered when the |
|                                           | temperature crosses these         |
|                                           | thresholds.                       |
+-------------------------------------------+-----------------------------------+
| ::${s}TemperatureGetState()          | Read the temperature of a sensor. |
+-------------------------------------------+-----------------------------------+

.. _PSU:

Operations on power supplies
----------------------------

The following functions can be used to access information about each
power-supply on a device:

+-----------------------------------+-----------------------------------+
| Function                          | Description                       |
+===================================+===================================+
| ::${s}DeviceEnumPsus()       | Enumerate the power supplies on   |
|                                   | the device that can be managed.   |
+-----------------------------------+-----------------------------------+
| ::${s}PsuGetProperties()     | Get static details about the      |
|                                   | power supply.                     |
+-----------------------------------+-----------------------------------+
| ::${s}PsuGetState()          | Get information about the health  |
|                                   | (temperature, current, fan) of    |
|                                   | the power supply.                 |
+-----------------------------------+-----------------------------------+

.. _Fan:

Operations on fans
------------------

If ::${s}DeviceEnumFans() returns one or more fan handles, it is possible to
manage their speed. The hardware can be instructed to run the fan at a fixed
speed (or 0 for silent operations) or to provide a table of temperature-speed
points in which case the hardware will dynamically change the fan speed based
on the current temperature of the chip. This configuration information is
described in the structure ::${s}_fan_config_t. When specifying speed, one
can provide the value in revolutions per minute (::${S}_FAN_SPEED_UNITS_RPM)
or as a percentage of the maximum RPM (::${S}_FAN_SPEED_UNITS_PERCENT).

The following functions are available:

+-----------------------------------+-----------------------------------+
| Function                          | Description                       |
+===================================+===================================+
| ::${s}DeviceEnumFans()       | Enumerate the fans on the device. |
+-----------------------------------+-----------------------------------+
| ::${s}FanGetProperties()     | Get the maximum RPM of the fan    |
|                                   | and the maximum number of points  |
|                                   | that can be specified in the      |
|                                   | temperature-speed table for a     |
|                                   | fan.                              |
+-----------------------------------+-----------------------------------+
| ::${s}FanGetConfig()         | Get the current configuration     |
|                                   | (speed) of a fan.                 |
+-----------------------------------+-----------------------------------+
| ::${s}FanSetConfig()         | Change the configuration (speed)  |
|                                   | of a fan.                         |
+-----------------------------------+-----------------------------------+
| ::${s}FanGetState()          | Get the current speed of a fan.   |
+-----------------------------------+-----------------------------------+

The pseudo code below shows how to output the fan speed of all fans:

.. parsed-literal::

    function ShowFans(${s}_device_handle_t hSysmanDevice)
        uint32_t numFans
        if (::${s}DeviceEnumFans(hSysmanDevice, &numFans, NULL) == ${X}_RESULT_SUCCESS)
            ${s}_fan_handle_t* phFans =
                allocate_memory(numFans * sizeof(${s}_fan_handle_t))
            if (::${s}DeviceEnumFans(hSysmanDevice, &numFans, phFans) == ${X}_RESULT_SUCCESS)
                output("    Fans")
                for (fanIndex = 0 .. numFans-1)
                    uint32_t speed
                    if (::${s}FanGetState(phFans[fanIndex], ${S}_FAN_SPEED_UNITS_RPM, &speed)
                        == ${X}_RESULT_SUCCESS)
                            output("        Fan %u: %u RPM", fanIndex, speed)
        free_memory(...)
    }

The next example shows how to set the fan speed for all fans to a fixed
value in RPM, but only if control is permitted:

.. parsed-literal::

   function SetFanSpeed(${s}_device_handle_t hSysmanDevice, uint32_t SpeedRpm)
   {
       uint32_t numFans
       if (::${s}DeviceEnumFans(hSysmanDevice, &numFans, NULL) == ${X}_RESULT_SUCCESS)
           ${s}_fan_handle_t* phFans =
               allocate_memory(numFans * sizeof(${s}_fan_handle_t))
           if (::${s}DeviceEnumFans(hSysmanDevice, &numFans, phFans) == ${X}_RESULT_SUCCESS)
               ${s}_fan_config_t config
               config.mode = ${S}_FAN_SPEED_MODE_FIXED
               config.speed = SpeedRpm
               config.speedUnits = ${S}_FAN_SPEED_UNITS_RPM
               for (fanIndex = 0 .. numFans-1)
                   ::${s}_fan_properties_t fanprops
                   if (::${s}FanGetProperties(phFans[fanIndex], &fanprops) == ${X}_RESULT_SUCCESS)
                       if (fanprops.canControl)
                           ::${s}FanSetConfig(phFans[fanIndex], &config)
                       else
                           output("ERROR: Can't control fan %u.\n", fanIndex)
       free_memory(...)
   }

.. _LED:

Operations on LEDs
------------------

If ::${s}DeviceEnumLeds() returns one or more LED handles, it is possible
to manage LEDs on the device. This includes turning them off/on and
where the capability exists, changing their color in real-time.

The following functions are available:

+-----------------------------------+-----------------------------------+
| Function                          | Description                       |
+===================================+===================================+
| ::${s}DeviceEnumLeds()       | Enumerate the LEDs on the device  |
|                                   | that can be managed.              |
+-----------------------------------+-----------------------------------+
| ::${s}LedGetProperties()     | Find out if a LED supports color  |
|                                   | changes.                          |
+-----------------------------------+-----------------------------------+
| ::${s}LedGetState()          | Find out if a LED is currently    |
|                                   | off/on and the color where the    |
|                                   | capability is available.          |
+-----------------------------------+-----------------------------------+
| ::${s}LedSetState()          | Turn a LED off/on and set the     |
|                                   | color where the capability is     |
|                                   | available.                        |
+-----------------------------------+-----------------------------------+

.. _RAS:

Querying RAS errors
-------------------

RAS stands for Reliability, Availability and Serviceability. It is a
feature of certain devices that attempts to correct random bit errors
and provide redundancy where permanent damage has occurred.

If a device supports RAS, it maintains counters for hardware and software
errors. There are two types of errors and they are defined in ::${s}_ras_error_type_t:

+------------------------------------+-----------------------------------+
| Error Type                         | Description                       |
+====================================+===================================+
| ::${S}_RAS_ERROR_TYPE_UNCORRECTABLE | Hardware errors occurred which    |
|                                    | most likely resulted in loss of   |
|                                    | data or even a device hang. If an |
|                                    | error results in device lockup, a |
|                                    | warm boot is required before      |
|                                    | those errors will be reported.    |
+------------------------------------+-----------------------------------+
| ::${S}_RAS_ERROR_TYPE_CORRECTABLE   | These are errors that were        |
|                                    | corrected by the hardware and did |
|                                    | not cause data corruption.        |
+------------------------------------+-----------------------------------+

Software can use the function ::${s}RasGetProperties() to find out
if the device supports RAS and if it is enabled. This information is
returned in the structure ::${s}_ras_properties_t.

The function ::${s}DeviceEnumRasErrorSets() enumerates the available sets of RAS
errors. If no handles are returned, the device does not support RAS. A
device without sub-devices will return one handle if RAS is supported. A
device with sub-devices will return a handle for each sub-device.

To determine if errors have occurred, software uses the function
::${s}RasGetState(). This will return the total number of errors of
a given type (correctable/uncorrectable) that have occurred.

When calling ::${s}RasGetState(), software can request that the
error counters be cleared. When this is done, all counters of the
specified type (correctable/uncorrectable) will be set to zero and any
subsequent calls to this function will only show new errors that have
occurred. If software intends to clear errors, it should be the only
application doing so and it should store the counters in an appropriate
database for historical analysis.

::${s}RasGetState() returns a breakdown of errors by category
in the structure ::${s}_ras_state_t. The table below describes the categories:

+------------------------------------------------+----------------------------------+------------------------------------+
| Error category                                 | ::${S}_RAS_ERROR_TYPE_CORRECTABLE | ::${S}_RAS_ERROR_TYPE_UNCORRECTABLE |
|                                                |                                  |                                    |
+================================================+==================================+====================================+
| ::${s}_ras_state_t.numResets              | Always zero.                     | Number of device resets that have  |
|                                                |                                  | taken place.                       |
+------------------------------------------------+----------------------------------+------------------------------------+
| ::${s}_ras_state_t.numProgrammingErrors   | Always zero.                     | Number of hardware                 |
|                                                |                                  | exceptions generated               |
|                                                |                                  | by the way workloads               |
|                                                |                                  | have programmed the                |
|                                                |                                  | hardware.                          |
+------------------------------------------------+----------------------------------+------------------------------------+
| ::${s}_ras_state_t.numDriverErrors        | Always zero.                     | Number of low level                |
|                                                |                                  | driver communication               |
|                                                |                                  | errors have occurred.              |
+------------------------------------------------+----------------------------------+------------------------------------+
| ::${s}_ras_state_t.numComputeErrors       | Number of errors that            | Number of errors that              |
|                                                | have occurred in the             | have occurred in the               |
|                                                | accelerator hardware             | accelerator hardware               |
|                                                | that were corrected.             | that were not                      |
|                                                |                                  | corrected. These                   |
|                                                |                                  | would have caused the              |
|                                                |                                  | hardware to hang and               |
|                                                |                                  | the driver to reset.               |
+------------------------------------------------+----------------------------------+------------------------------------+
| ::${s}_ras_state_t.numNonComputeErrors    | Number of errors                 | Number of errors                   |
|                                                | occurring in                     | occurring in the                   |
|                                                | fixed-function                   | fixed-function                     |
|                                                | accelerator hardware             | accelerator hardware               |
|                                                | that were corrected.             | there could not be                 |
|                                                |                                  | corrected. Typically               |
|                                                |                                  | these will result in               |
|                                                |                                  | a PCI bus reset and                |
|                                                |                                  | driver reset.                      |
+------------------------------------------------+----------------------------------+------------------------------------+
| ::${s}_ras_state_t.numCacheErrors         | Number of ECC                    | Number of ECC                      |
|                                                | correctable errors               | uncorrectable errors               |
|                                                | that have occurred in            | that have occurred in              |
|                                                | the on-chip caches               | the on-chip caches                 |
|                                                | (caches/register                 | (caches/register                   |
|                                                | file/shared local                | file/shared local                  |
|                                                | memory).                         | memory). These would               |
|                                                |                                  | have caused the                    |
|                                                |                                  | hardware to hang and               |
|                                                |                                  | the driver to reset.               |
+------------------------------------------------+----------------------------------+------------------------------------+
| ::${s}_ras_state_t.numMemoryErrors        | Number of times the              | Number of times the                |
|                                                | device memory has                | device memory has                  |
|                                                | transitioned from a              | transitioned from a                |
|                                                | healthy state to a               | healthy/degraded                   |
|                                                | degraded state.                  | state to a                         |
|                                                | Degraded state occurs            | critical/replace                   |
|                                                | when the number of               | state.                             |
|                                                | correctable errors               |                                    |
|                                                | cross a threshold.               |                                    |
+------------------------------------------------+----------------------------------+------------------------------------+
| ::${s}_ras_state_t.numPciErrors           | controllerNumber of              | Number of PCI bus                  |
|                                                | PCI packet replays               | resets.                            |
|                                                | that have occurred.              |                                    |
+------------------------------------------------+----------------------------------+------------------------------------+
| ::${s}_ras_state_t.numFabricErrors        | Number of times one              | Number of times one                |
|                                                | or more ports have               | or more ports have                 |
|                                                | transitioned from a              | transitioned from a                |
|                                                | green status to a                | green/yellow status                |
|                                                | yellow status. This              | to a red status. This              |
|                                                | indicates that links             | indicates that links               |
|                                                | are experiencing                 | are experiencing                   |
|                                                | quality degradation.             | connectivity                       |
|                                                |                                  | statibility issues.                |
+------------------------------------------------+----------------------------------+------------------------------------+
| ::${s}_ras_state_t.numDisplayErrors       | Number of ECC                    | Number of ECC                      |
|                                                | correctable errors               | uncorrectable errors               |
|                                                | that have occurred in            | that have occurred in              |
|                                                | the display.                     | the display.                       |
+------------------------------------------------+----------------------------------+------------------------------------+

Each RAS error type can trigger events when the error counters exceed
thresholds. The events are listed in the table below. Software can use
the functions ::${s}RasGetConfig() and ::${s}RasSetConfig() to
get and set the thresholds for each error type. The default is for all
thresholds to be 0 which means that no events are generated. Thresholds
can be set on the total RAS error counter or on each of the detailed
error counters.

## --validate=off
+------------------------------------+-------------------------------------------+
| RAS error Type                     | Event                                     |
+====================================+===========================================+
| ::${S}_RAS_ERROR_TYPE_UNCORRECTABLE | ::${S}_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS |
+------------------------------------+-------------------------------------------+
| ::${S}_RAS_ERROR_TYPE_CORRECTABLE   | ::${S}_EVENT_TYPE_RAS_CORRECTABLE_ERRORS   |
+------------------------------------+-------------------------------------------+
## --validate=on

The table below summaries all the RAS management functions:

+-------------------------------------+-----------------------------------+
| Function                            | Description                       |
+=====================================+===================================+
| ::${s}DeviceEnumRasErrorSets() | Get handles to the available RAS  |
|                                     | error groups.                     |
+-------------------------------------+-----------------------------------+
| ::${s}RasGetProperties()       | Get properties about a RAS error  |
|                                     | group - type of RAS errors and if |
|                                     | they are enabled.                 |
+-------------------------------------+-----------------------------------+
| ::${s}RasGetConfig()           | Get the current list of           |
|                                     | thresholds for each counter in    |
|                                     | the RAS group. RAS error events   |
|                                     | will be generated when the        |
|                                     | thresholds are exceeded.          |
+-------------------------------------+-----------------------------------+
| ::${s}RasSetConfig()           | Set current list of thresholds    |
|                                     | for each counter in the RAS       |
|                                     | group. RAS error events will be   |
|                                     | generated when the thresholds are |
|                                     | exceeded.                         |
+-------------------------------------+-----------------------------------+
| ::${s}RasGetState()            | Get the current state of the RAS  |
|                                     | error counters. The counters can  |
|                                     | also be cleared.                  |
+-------------------------------------+-----------------------------------+

The pseudo code below shows how to determine if RAS is supported and the
current state of RAS errors:

.. parsed-literal::

   void ShowRasErrors(${s}_device_handle_t hSysmanDevice)
       uint32_t numRasErrorSets
       if ((::${s}DeviceEnumRasErrorSets(hSysmanDevice, &numRasErrorSets, NULL) == ${X}_RESULT_SUCCESS))
           ${s}_ras_handle_t* phRasErrorSets =
               allocate_memory(numRasErrorSets * sizeof(${s}_ras_handle_t))
           if (::${s}DeviceEnumRasErrorSets(hSysmanDevice, &numRasErrorSets, phRasErrorSets) == ${X}_RESULT_SUCCESS)
               for (rasIndex = 0 .. numRasErrorSets)
                   ::${s}_ras_properties_t props
                   if (::${s}RasGetProperties(phRasErrorSets[rasIndex], &props) == ${X}_RESULT_SUCCESS)
                       var pErrorType
                       switch (props.type)
                           case ${S}_RAS_ERROR_TYPE_CORRECTABLE:
                               pErrorType = "Correctable"
                           case ${S}_RAS_ERROR_TYPE_UNCORRECTABLE:
                               pErrorType = "Uncorrectable"
                           default:
                               pErrorType = "Unknown"
                       output("RAS %s errors", pErrorType)
                       if (props.onSubdevice)
                           output("    On sub-device: %u", props.subdeviceId)
                       output("    RAS supported: %s", props.supported ? "yes" : "no")
                       output("    RAS enabled: %s", props.enabled ? "yes" : "no")
                       if (props.supported and props.enabled)
                           ${s}_ras_state_t errorDetails
                           if (::${s}RasGetState(phRasErrorSets[rasIndex], 1, &errorDetails)
                               == ${X}_RESULT_SUCCESS)
                                    uint64_t numErrors = 0
                                    for (int i = 0; i < ZES_RAS_ERROR_CAT_MAX; i++)
                                        numErrors += errorDetails.category[i];
                                    output("    Number new errors: %llu\n", (long long unsigned int)numErrors);
                                    if (numErrors)
                                        call_function OutputRasDetails(&errorDetails)
       free_memory(...)

   function OutputRasDetails(${s}_ras_state_t* pDetails)
       output("        Number new resets:                %llu", pDetails->category[ZES_RAS_ERROR_CAT_RESET])
       output("        Number new programming errors:    %llu", pDetails->category[ZES_RAS_ERROR_CAT_PROGRAMMING_ERRORS])
       output("        Number new driver errors:         %llu", pDetails->category[ZES_RAS_ERROR_CAT_DRIVER_ERRORS])
       output("        Number new compute errors:        %llu", pDetails->category[ZES_RAS_ERROR_CAT_COMPUTE_ERRORS])
       output("        Number new non-compute errors:    %llu", pDetails->category[ZES_RAS_ERROR_CAT_NON_COMPUTE_ERRORS])
       output("        Number new cache errors:          %llu", pDetails->category[ZES_RAS_ERROR_CAT_CACHE_ERRORS])
       output("        Number new display errors:        %llu", pDetails->category[ZES_RAS_ERROR_CAT_DISPLAY_ERRORS])

.. _Diagnostics:

Performing diagnostics
----------------------

Diagnostics is the process of requesting that the hardware run self-checks
and repairs. 

**WARNING:** Performing diagnostics can destroy current device state.
It is important that all workloads are stopped before initiating.

This is achieved using
the function ::${s}DiagnosticsRunTests(). On return from the
function, software can use the diagnostics return code
(::${s}_diag_result_t) to determine the new course of action:

1. ::${S}_DIAG_RESULT_NO_ERRORS - No errors found and workloads can
   resume submission to the hardware.
2. ::${S}_DIAG_RESULT_ABORT - Hardware had problems running diagnostic
   tests.
3. ::${S}_DIAG_RESULT_FAIL_CANT_REPAIR - Hardware had problems setting up
   repair. Card should be removed from the system.
4. ::${S}_DIAG_RESULT_REBOOT_FOR_REPAIR - Hardware has prepared for
   repair and requires a reboot after which time workloads can resume
   submission.

The function ::${s}DeviceGetState() can be used to determine if
the device has been repaired.

There are multiple diagnostic test suites that can be run and these are
defined in the enumerator ::${s}_diag_type_t. The function
::${s}DeviceEnumDiagnosticTestSuites() will enumerate each available test suite and
the function ::${s}DiagnosticsGetProperties() can be used to
determine the type and name of each test suite
(::${s}_diag_properties_t.type and ::${s}_diag_properties_t.type).

Each test suite contains one or more diagnostic tests. On some systems,
it is possible to run only a subset of the tests. Use the function
::${s}DiagnosticsGetProperties() and check that
::${s}_diag_properties_t.haveTests is true to determine if this feature
is available. If it is, the function ::${s}DiagnosticsGetTests()
can be called to get the list of individual tests that can be run.

When running diagnostics for a test suite using
::${s}DiagnosticsRunTests(), it is possible to specify the start
and index of tests in the suite. Setting to ::${S}_DIAG_FIRST_TEST_INDEX
and ::${S}_DIAG_LAST_TEST_INDEX will run all tests in the suite. If it is
possible to run a subset of tests, specify the index of the start test
and the end test - all tests that have an index in this range will be
run.

The table below summaries all the diagnostic management functions:

+---------------------------------------------+-----------------------------------+
| Function                                    | Description                       |
+=============================================+===================================+
| ::${s}DeviceEnumDiagnosticTestSuites() | Get handles to the available      |
|                                             | diagnostic test suites that can   |
|                                             | be run.                           |
+---------------------------------------------+-----------------------------------+
| ::${s}DiagnosticsGetProperties()       | Get information about a test      |
|                                             | suite - type, name, location and  |
|                                             | if individual tests can be run.   |
+---------------------------------------------+-----------------------------------+
| ::${s}DiagnosticsGetTests()            | Get list of individual diagnostic |
|                                             | tests that can be run.            |
+---------------------------------------------+-----------------------------------+
| ::${s}DiagnosticsRunTests()            | Run either all or individual      |
|                                             | diagnostic tests.                 |
+---------------------------------------------+-----------------------------------+

The pseudo code below shows how to discover all test suites and the
tests in each:

.. parsed-literal::

   function ListDiagnosticTests(${s}_device_handle_t hSysmanDevice)
   {
       uint32_t numTestSuites
       if ((::${s}DeviceEnumDiagnosticTestSuites(hSysmanDevice, &numTestSuites, NULL) == ${X}_RESULT_SUCCESS))
           ${s}_diag_handle_t* phTestSuites =
               allocate_memory(numTestSuites * sizeof(${s}_diag_handle_t))
           if (::${s}DeviceEnumDiagnosticTestSuites(hSysmanDevice, &numTestSuites, phTestSuites) == ${X}_RESULT_SUCCESS)
               for (suiteIndex = 0 .. numTestSuites-1)
                   uint32_t numTests = 0
                   ::${s}_diag_test_t* pTests
                   ::${s}_diag_properties_t suiteProps
                   if (::${s}DiagnosticsGetProperties(phTestSuites[suiteIndex], &suiteProps) != ${X}_RESULT_SUCCESS)
                       next_loop(suiteIndex)
                   output("Diagnostic test suite %s:", suiteProps.name)
                   if (!suiteProps.haveTests)
                       output("    There are no individual tests that can be selected.")
                       next_loop(suiteIndex)
                   if (::${s}DiagnosticsGetTests(phTestSuites[suiteIndex], &numTests, NULL) != ${X}_RESULT_SUCCESS)
                       output("    Problem getting list of individual tests.")
                       next_loop(suiteIndex)
                   pTests = allocate_memory(numTests * sizeof(::${s}_diag_test_t*))
                   if (::${s}DiagnosticsGetTests(phTestSuites[suiteIndex], &numTests, pTests) != ${X}_RESULT_SUCCESS)
                       output("    Problem getting list of individual tests.")
                       next_loop(suiteIndex)
                   for (i = 0 .. numTests-1)
                       output("    Test %u: %s", pTests[i].index, pTests[i].name)
       free_memory(...)

.. _events-2:

Events
------

Events are a way to determine if changes have occurred on a device
e.g. new RAS errors. An application registers the events that it wishes
to receive notification about and then it queries to receive
notifications. The query can request a blocking wait - this will put the
calling application thread to sleep until new notifications are
received.

For every device on which the application wants to receive events, it
should perform the following actions:

1. Use ::${s}DeviceCreateEvents() to get an event handler from the Sysman
   handle for the device.
2. Use ::${s}EventSetConfig() to indicate which events it wasnts to
   listen to.
3. For each event, call the appropriate function to set conditions that
   will trigger the event.

Finally, the application calls ::${s}EventListen() with a list of
event handles that it wishes to listen for events on. A wait timeout is
used to request non-blocking operations (timeout =
::${S}_EVENT_WAIT_NONE) or blocking operations (timeout =
::${S}_EVENT_WAIT_INFINITE) or to return after a specified amount of time
even if no events have been received.

Once events have occurred, the application can call
::${s}EventGetState() to determine the list of events that have
been received for each event handle. If events have been received, the
application can use the function relevant to the event to determine the
actual state.

The list of events is given in the table below. For each event, the
corresponding configuration and state functions are shown. Where a
configuration function is not shown, the event is generated
automatically; where a configuration function is shown, it must be
called to enable the event and/or provide threshold conditions.

## --validate=off
+---------------------------------------------------+-----------------------------+---------------------------------------+-----------------------------------+
| Event                                             | Trigger                     | Configuration function                | State function                    |
+===================================================+=============================+=======================================+===================================+
| ::${S}_EVENT_TYPE_DEVICE_RESET                     | Device is about to be reset |                                       |                                   |
|                                                   | by the driver               |                                       |                                   |
+---------------------------------------------------+-----------------------------+---------------------------------------+-----------------------------------+
| ::${S}_EVENT_TYPE_DEVICE_SLEEP_STATE_ENTER         | Device is about to enter a  |                                       |                                   |
|                                                   | deep sleep state            |                                       |                                   |
+---------------------------------------------------+-----------------------------+---------------------------------------+-----------------------------------+
| ::${S}_EVENT_TYPE_DEVICE_SLEEP_STATE_EXIT          | Device is exiting a deep    |                                       |                                   |
|                                                   | sleep state                 |                                       |                                   |
+---------------------------------------------------+-----------------------------+---------------------------------------+-----------------------------------+
| ::${S}_EVENT_TYPE_FREQ_THROTTLED                   | Frequency starts being      |                                       | ::${s}FrequencyGetState()          |
|                                                   | throttled                   |                                       |                                   |
+---------------------------------------------------+-----------------------------+---------------------------------------+-----------------------------------+
| ::${S}_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED         | Energy consumption          | ::${s}PowerSetEnergyThreshold()        |                                   |
|                                                   | threshold is reached        |                                       |                                   |
+---------------------------------------------------+-----------------------------+---------------------------------------+-----------------------------------+
| ::${S}_EVENT_TYPE_TEMP_CRITICAL                    | Critical temperature is     | ::${s}TemperatureSetConfig()           | ::${s}TemperatureGetState()        |
|                                                   | reached                     |                                       |                                   |
+---------------------------------------------------+-----------------------------+---------------------------------------+-----------------------------------+
| ::${S}_EVENT_TYPE_TEMP_THRESHOLD1                  | Temperature crosses         | ::${s}TemperatureSetConfig()           | ::${s}TemperatureGetState()        |
|                                                   | threshold 1                 |                                       |                                   |
+---------------------------------------------------+-----------------------------+---------------------------------------+-----------------------------------+
| ::${S}_EVENT_TYPE_TEMP_THRESHOLD2                  | Temperature crosses         | ::${s}TemperatureSetConfig()           | ::${s}TemperatureGetState()        |
|                                                   | threshold 2                 |                                       |                                   |
+---------------------------------------------------+-----------------------------+---------------------------------------+-----------------------------------+
| ::${S}_EVENT_TYPE_MEM_HEALTH                       | Health of device memory     |                                       | ::${s}MemoryGetState()             |
|                                                   | changes                     |                                       |                                   |
+---------------------------------------------------+-----------------------------+---------------------------------------+-----------------------------------+
| ::${S}_EVENT_TYPE_FABRIC_PORT_HEALTH               | Health of fabric ports      |                                       | ::${s}FabricPortGetState()         |
|                                                   | change                      |                                       | )                                 |
+---------------------------------------------------+-----------------------------+---------------------------------------+-----------------------------------+
| ::${S}_EVENT_TYPE_RAS_CORRECTABLE_ERRORS           | RAS correctable errors      | ::${s}RasSetConfig()                   | ::${s}RasGetState()                |
|                                                   | cross thresholds            |                                       |                                   |
+---------------------------------------------------+-----------------------------+---------------------------------------+-----------------------------------+
| ::${S}_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS         | RAS uncorrectable errors    | ::${s}RasSetConfig()                   | ::${s}RasGetState()                |
|                                                   | cross thresholds            |                                       |                                   |
+---------------------------------------------------+-----------------------------+---------------------------------------+-----------------------------------+
| ::${S}_EVENT_DEVICE_RESET_REQUIRED                 | Driver has determined that  |                                       | ::${s}DeviceGetState()             |
|                                                   | an immediate reset is       |                                       |                                   |
|                                                   | required                    |                                       |                                   |
+---------------------------------------------------+-----------------------------+---------------------------------------+-----------------------------------+
## --validate=on

The call to ::${s}EventListen() requires the driver handle. The
list of event handles must only be for devices that have been enumerated
from that driver, otherwise and error will be returned. If the
application is managing devices from multiple drivers, it will need to
call this function separately for each driver.

The table below summaries all the event management functions:

+-----------------------------------+-----------------------------------+
| Function                          | Description                       |
+===================================+===================================+
| ::${s}DeviceCreateEvents()   | Get the event handle for a        |
|                                   | specific Sysman device.           |
+-----------------------------------+-----------------------------------+
| ::${s}EventGetConfig()       | Get the current list of events    |
|                                   | for a given event handle that     |
|                                   | have been registered.             |
+-----------------------------------+-----------------------------------+
| ::${s}EventSetConfig()       | Set the events that should be     |
|                                   | registered on a given event       |
|                                   | handle.                           |
+-----------------------------------+-----------------------------------+
| ::${s}EventGetState()        | Get the list of events that have  |
|                                   | been received for a given event   |
|                                   | handle.                           |
+-----------------------------------+-----------------------------------+
| ::${s}EventListen()          | Wait for events to arrive for a   |
|                                   | given list of event handles.      |
+-----------------------------------+-----------------------------------+

The pseudo code below shows how to configure all temperature sensors to
trigger an event when the temperature exceeds a specified threshold or
when the critical temperature is reached.

.. parsed-literal::

   function WaitForExcessTemperatureEvent(${s}_driver_handle_t hDriver, double tempLimit)
   {
       # This will contain the number of event handles (devices) that we will listen for events from
       var numEventHandles = 0

       # Get list of all devices under this driver
       uint32_t deviceCount = 0
       ::${x}DeviceGet(hDriver, &deviceCount, nullptr)
       # Allocate memory for all device handles
       ${x}_device_handle_t* phDevices =
           allocate_memory(deviceCount * sizeof(${x}_device_handle_t))
       # Allocate memory for the event handle for each device
       ${s}_event_handle_t* phEvents =
           allocate_memory(deviceCount * sizeof(${s}_event_handle_t))
       # Allocate memory for the event handles that we will actually listen to
       ${s}_event_handle_t* phListenEvents =
           allocate_memory(deviceCount * sizeof(${s}_event_handle_t))
       # Allocate memory so that we can map an event handle in phListenEvent to the device handle
       uint32_t* pListenDeviceIndex = allocate_memory(deviceCount * sizeof(uint32_t))

       # Get all device handles
       ::${x}DeviceGet(hDriver, &deviceCount, phDevices)
       for(devIndex = 0 .. deviceCount-1)
           # Get Sysman handle for the device
           ${s}_device_handle_t hSysmanDevice = (${s}_device_handle_t)phDevices[devIndex]

           # Get event handle for this device
           if (::${s}DeviceCreateEvents(hSysmanDevice, &phEvents[devIndex]) != ${X}_RESULT_SUCCESS)
               next_loop(devIndex)

           # Get handles to all temperature sensors
           uint32_t numTempSensors = 0
           if (::${s}DeviceEnumTemperatureSensors(hSysmanDevice, &numTempSensors, NULL) != ${X}_RESULT_SUCCESS)
               next_loop(devIndex)
           ${s}_temp_handle_t* allTempSensors
               allocate_memory(deviceCount * sizeof(${s}_temp_handle_t))
           if (::${s}DeviceEnumTemperatureSensors(hSysmanDevice, &numTempSensors, allTempSensors) == ${X}_RESULT_SUCCESS)
               # Configure each temperature sensor to trigger a critical event and a threshold1 event
               var numConfiguredTempSensors = 0
               for (tempIndex = 0 .. numTempSensors-1)
                   if (::${s}TemperatureGetConfig(allTempSensors[tempIndex], &config) != ${X}_RESULT_SUCCESS)
                       next_loop(tempIndex)
                   ::${s}_temp_config_t config
                   config.enableCritical = true
                   config.threshold1.enableHighToLow = false
                   config.threshold1.enableLowToHigh = true
                   config.threshold1.threshold = tempLimit
                   config.threshold2.enableHighToLow = false
                   config.threshold2.enableLowToHigh = false
                   if (::${s}TemperatureSetConfig(allTempSensors[tempIndex], &config) == ${X}_RESULT_SUCCESS)
                       numConfiguredTempSensors++

           # If we configured any sensors to generate events, we can now register to receive on this device
           if (numConfiguredTempSensors)
               ::${s}_event_config_t eventConfig
               eventConfig.registered =
                   ${S}_EVENT_TYPE_TEMP_CRITICAL | ${S}_EVENT_TYPE_TEMP_THRESHOLD1
               if (::${s}EventSetConfig(phEvents[devIndex], &eventConfig) == ${X}_RESULT_SUCCESS)
                   phListenEvents[numEventHandles] = phEvents[devIndex]
                   pListenDeviceIndex[numEventHandles] = devIndex
                   numEventHandles++

       # If we registered to receive events on any devices, start listening now
       if (numEventHandles)
           # Block until we receive events
           uint32_t events
           if (::${s}EventListen(hDriver, ${S}_EVENT_WAIT_INFINITE, deviceCount, phListenEvents, &events)
               == ${X}_RESULT_SUCCESS)
                   for (evtIndex .. numEventHandles)
                       if (::${s}EventGetState(phListenEvents[evtIndex], true, &events)
                           != ${X}_RESULT_SUCCESS)
                               next_loop(evtIndex)
                       if (events & ${S}_EVENT_TYPE_TEMP_CRITICAL)
                           output("Device %u: Went above the critical temperature.",
                               pListenDeviceIndex[evtIndex])
                       else if (events & ${S}_EVENT_TYPE_TEMP_THRESHOLD1)
                           output("Device %u: Went above the temperature threshold %f.",
                               pListenDeviceIndex[evtIndex], tempLimit)

       free_memory(...)

Security
========

Linux
-----

The default security provided by the accelerator driver is to permit
querying and controlling of system resources to the UNIX user **root**,
querying only for users that are members of the UNIX group **root** and
no access to any other user. Some queries are permitted from any user
(e.g requesting current frequency, checking standby state).

It is the responsibility of the Linux distribution or the systems
administrator to relax or tighten these permissions. This is typically
done by adding udev daemon rules. For example, many distributions of
Linux have the following rule:

.. parsed-literal::

   root    video   /dev/dri/card0

This will permit all users in the UNIX group **video** to query
information about system resources. In order to open up control access
to users of the video group, udev rules need to be added for each
relevant control. For example, to permit someone in the video group to
disable standby, the following udev daemon rule would be needed:

.. parsed-literal::

   chmod g+w /sys/class/drm/card0/rc6_enable

The full list of sysfs files used by the API are described in the table
below. For each file, the list of affected API functions is given.

+-----------------------+-----------------------+------------------------------------------+
| sysfs file            | Description           | Functions                                |
+=======================+=======================+==========================================+
| /sys/class/drm/card0/ | Used to               | ::${s}DeviceEnumStandbyDomains()    |
| rc6_enable            | enable/disable        | ::${s}StandbyGetProperties()        |
|                       | standby.              | ::${s}StandbyGetMode()              |
|                       |                       | ::${s}StandbySetMode()              |
+-----------------------+-----------------------+------------------------------------------+
| TBD                   | In development        | TBD                                      |
+-----------------------+-----------------------+------------------------------------------+

Windows
-------

At this time, Level0 Sysman does not support Windows.

Privileged telemetry
--------------------

Certain telemetry makes a system vulnerable to side-channel attacks. By
default, these will only be available to the administrator user on the
system. It is up to the administrator to relax those requirements, as
described in the preceding sections. This is the case for the following
API calls:

+--------------------------------------+-----------------------------------+
| Function                             | Description                       |
+======================================+===================================+
| ::${s}DevicePciGetStats()       | Access to total PCI throughput    |
|                                      | and number of packets can reveal  |
|                                      | useful information about the      |
|                                      | workload                          |
+--------------------------------------+-----------------------------------+
| ::${s}MemoryGetBandwidth()      | Access to real-time device local  |
|                                      | memory bandwidth can reveal       |
|                                      | useful information about the      |
|                                      | workload                          |
+--------------------------------------+-----------------------------------+
| ::${s}FabricPortGetThroughput() | Access to real-time fabric data   |
|                                      | bandwidth can reveal useful       |
|                                      | information about the workload    |
+--------------------------------------+-----------------------------------+

Privileged controls
-------------------

Certain controls can be used in denial-of-service attacks. By default,
these will only be available to the administrator user on the system. It
is up to the administrator to relax those requirements, as described in
the preceding sections. This is the case for the following API calls:

+------------------------------------+-----------------------------------+
| Function                           | Description                       |
+====================================+===================================+
| ::${s}DeviceReset()           | Device resets cause loss of data  |
|                                    | for running workloads.            |
+------------------------------------+-----------------------------------+
| ::${s}DeviceEnumFirmwares()   | All firmware operations must be   |
|                                    | handled with care.                |
+------------------------------------+-----------------------------------+
| ::${s}FirmwareGetProperties() | All firmware operations must be   |
|                                    | handled with care.                |
+------------------------------------+-----------------------------------+
| ::${s}FirmwareGetChecksum()   | All firmware operations must be   |
|                                    | handled with care.                |
+------------------------------------+-----------------------------------+
| ::${s}FirmwareFlash()         | All firmware operations must be   |
|                                    | handled with care.                |
+------------------------------------+-----------------------------------+
| ::${s}FabricPortSetConfig()   | Putting fabric ports offline can  |
|                                    | distrupt workloads, causing       |
|                                    | uncorrectable errors.             |
+------------------------------------+-----------------------------------+
| ::${s}DiagnosticsRunTests()   | Diagnostics take a device         |
|                                    | offline.                          |
+------------------------------------+-----------------------------------+

Virtualization
--------------

In virtualization environments, only the host is permitted to access any
features of the API. Attempts to use the API in virtual machines will
fail.

Function summary
----------------

The table below summarizes the default permissions for each API
function:

+---------------------------------------------------+---------------+-------------+-------------+-------------+
| Function                                          | Administrator | Group       | Other       | Virtual     |
|                                                   | access        | access      | access      | machine     |
+===================================================+===============+=============+=============+=============+
| ::${s}DeviceGetProperties()                  | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DeviceEnumSchedulers()                 | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}SchedulerGetProperties()               | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}SchedulerGetCurrentMode()              | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}SchedulerGetTimeoutModeProperties()    | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}SchedulerGetTimesliceModeProperties()  | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}SchedulerSetTimeoutMode()              | read-write    | read-write  | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}SchedulerSetTimesliceMode()            | read-write    | read-write  | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}SchedulerSetExclusiveMode()            | read-write    | read-write  | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}SchedulerSetComputeUnitDebugMode()     | read-write    | read-write  | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DeviceReset()                          | read-write    | no-access   | no-access   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DevicePciGetProperties()               | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DevicePciGetState()                    | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DevicePciGetBars()                     | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DevicePciGetStats()                    | read-only     | no-access   | no-access   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}PowerGetProperties()                   | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}PowerGetEnergyCounter()                | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}PowerGetEnergyThreshold()              | read-only     | read-only   | no-access   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}PowerSetEnergyThreshold()              | read-write    | read-write  | no-access   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}PowerGetLimits()                       | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}PowerSetLimits()                       | read-write    | read-write  | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DeviceEnumFrequencyDomains()           | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FrequencyGetProperties()               | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FrequencyGetAvailableClocks()          | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FrequencyGetRange()                    | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FrequencySetRange()                    | read-write    | read-write  | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FrequencyGetState()                    | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FrequencyGetThrottleTime()             | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FrequencyOcGetCapabilities()           | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FrequencyOcGetConfig()                 | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FrequencyOcSetConfig()                 | read-write    | no-access   | no-access   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FrequencyOcGetIccMax()                 | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FrequencyOcSetIccMax()                 | read-write    | no-access   | no-access   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FrequencyOcGetTjMax()                  | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FrequencyOcSetTjMax()                  | read-write    | no-access   | no-access   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DeviceEnumEngineGroups()               | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}EngineGetProperties()                  | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}EngineGetActivity()                    | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DeviceEnumStandbyDomains()             | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}StandbyGetProperties()                 | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}StandbyGetMode()                       | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}StandbySetMode()                       | read-write    | read-write  | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DeviceEnumFirmwares()                  | read-only     | no-access   | no-access   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FirmwareGetProperties()                | read-only     | no-access   | no-access   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FirmwareGetChecksum()                  | read-only     | no-access   | no-access   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FirmwareFlash()                        | read-write    | no-access   | no-access   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DeviceEnumMemoryModules()              | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}MemoryGetProperties()                  | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}MemoryGetBandwidth()                   | read-only     | no-access   | no-access   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}MemoryGetState()                       | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DeviceEnumFabricPorts()                | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FabricPortGetProperties()              | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FabricPortGetLinkType()                | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FabricPortGetConfig()                  | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FabricPortSetConfig()                  | read-write    | no-access   | no-access   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FabricPortGetState()                   | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FabricPortGetThroughput()              | read-only     | no-access   | no-access   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DeviceEnumTemperatureSensors()         | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}TemperatureGetProperties()             | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}TemperatureGetConfig()                 | read-only     | read-only   | no-access   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}TemperatureSetConfig()                 | read-write    | read-write  | no-access   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}TemperatureGetState()                  | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DeviceEnumPsus()                       | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}PsuGetProperties()                     | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}PsuGetState()                          | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DeviceEnumFans()                       | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FanGetProperties()                     | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FanGetConfig()                         | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FanSetConfig()                         | read-write    | read-write  | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}FanGetState()                          | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DeviceEnumLeds()                       | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}LedGetProperties()                     | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}LedGetState()                          | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}LedSetState()                          | read-write    | read-write  | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DeviceEnumRasErrorSets()               | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}RasGetProperties()                     | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}RasGetConfig()                         | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}RasSetConfig()                         | read-write    | read-write  | no-access   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}RasGetState()                          | read-write    | read-write  | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DeviceCreateEvents()                   | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}EventGetConfig()                       | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}EventSetConfig()                       | read-write    | read-write  | read-write  | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}EventGetState()                        | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}EventListen()                          | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DeviceEnumDiagnosticTestSuites()       | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DiagnosticsGetProperties()             | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DiagnosticsGetTests()                  | read-only     | read-only   | read-only   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
| ::${s}DiagnosticsRunTests()                  | read-write    | no-access   | no-access   | no-access   |
+---------------------------------------------------+---------------+-------------+-------------+-------------+
