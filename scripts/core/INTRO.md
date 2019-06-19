${"#"} Introduction
<%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
[DO NOT EDIT]: # (generated from /scripts/core/INTRO.md)

${"##"} Table of Contents
* [Objective](#obj)
* [API Specification](#spec)
* [Driver Architecture](#drv)
* [Tools](#tls)

${"#"} <a name="obj">Objective</a>
The objective of the Level-Zero API is to provide direct-to-metal interfaces to offload accelerator devices. 
It is a programming interface that can be published at a cadence that better matches Intel hardware releases and can be tailored to any device needs. 
It can be adapted to support broader set of languages features, such as function pointers, virtual functions, unified memory, and  I/O capabilities.

![Driver](../images/one_api_sw_stack.png?raw=true)  
@image latex one_api_sw_stack.png

The Level-Zero API provides the lowest-level, fine-grain and most explicit control over:
- Device Discovery
- Memory Allocation
- Peer-to-Peer Communication
- Inter-Process Sharing
- Kernel Submission
- Asynchronous Execution and Scheduling
- Synchronization Primitives
- Metrics Reporting

Most applications should not require the additional control provided by the Level-Zero API.
The Level-Zero API is intended for providing explicit controls needed by higher-level runtime APIs and libraries.

While heavily influenced by other low-level APIs, such as OpenCL, the Level-Zero APIs are designed to evolve independently.
While heavily influenced by GPU archtiecture, the Level-Zero APIs are designed to be supportable across different compute device architectures, such as FPGAs, CSAs, etc.

${"##"} Devices
The API architecture exposes both physical and logical abstraction of the underlying devices capabilities. 
The device, sub device and memory are exposed at physical level while command queues, events and synchronization methods are defined as logical entities. 
All logical entities will be bound to device level physical capabilities.

Device discovery APIs enumerate the accelerators functional features. 
These APIs provide interface to query information like compute unit count within the device or sub device, 
available memory and affinity to the compute, user managed cache size and work submission command queues.

${"##"} Memory & Caches
Memory is visible to the upper-level software stack as unified memory with a single virtual address space covering both the Host and a specific device.

For GPUs, the API exposes two levels of the device memory hierarchy:
1. Local Device Memory: can be managed at the device and/or sub device level. 
2. Device Cache(s):
    + Last Level Cache (L3) can be controled through memory allocation APIs.
    + Low Level Cache (L1) can be controlled through program language intrinsics.

The API allows allocation of buffers and images at device and sub device granularity with full cacheablity hints. 
- Buffers are transperant memory accessed through virtual address pointers
- Images are opaque objects accessed through handles

The memory APIs provide allocation methods to allocate either device, host or shared memory. 
The APIs enable both implicit and explicit management of the resources by the application or runtimes. 
The interface also provides query capabilities for all memory objects.

${"##"} Multi-Die Device Support
GPUs are typically built with multiple dies, also called as "Tiles" with in the package. 
Each Tile is interconnected with neighboring tile using high bandwidth link. 
Even though tiles have direct connection to its own memory, the high bandwidth link allows each tile to access its neighboring tile's memory at very low latency. 
The cross-tile memory is stacked within package allowing applications to access all the device memory with the single continuous view.

The API represents tiles as sub-devices and there are functions to query and obtain a sub-device. 
Outside of these functions there are no distinction between sub-devices and devices. 
For example, a sub-device can be used with memory allocation and tasks and allow placement and submission to a specific sub-device.

${"##"} Peer-to-Peer Communication
Peer to Peer API's provide capabilities to marshall data across Host to Device, Device to Host and Device to Device. 
The data marshalling API can be scheduled as asynchronous operations or can be synchronized with kernel execution through command queues. 
Data coherency is maintained by the driver with out any explicit involement from the application.

${"##"} Inter-Process Communication
The API allows sharing of memory objects across different device processes. 
Since each process has it's own virtual address space, there is no guarantee that the same virtual address will be available when the memory object is shared in new process. 
There are a set of APIs that makes it easier to share the memory objects with ease. 

${"#"} <a name="spec">API Specification</a>
The following section provides high-level design philosophy of the APIs.
For more detailed information, refer to the programming guides and detailed specification pages.

${"##"} Terminology
This specification uses key words based on [RFC2119](https://www.ietf.org/rfc/rfc2119.txt) to indicate requirement level. 
In particular, the following words are used to describe the actions of an implementation of this specification:
- **May**: the word _may_, or the adjective _optional_, mean that conforming implementations are permitted to, but need not behave as described.
- **Should**: the word _should_, or the adjective _recommended_, mean that there could be reasons for an implementations to deviate from the behavior described, but that such deviation should be avoided.  
- **Must**: the word _must_, or the term _required_ or _shall_, mean that the behavior described is an absolute requirement of the specification.

${"##"} Naming Convention
The following naming conventions are followed in order to avoid conflicts within the API, or with other APIs and libraries:
## --validate=off
- all driver entry points are prefixed with ${x}
- all types follow **${x}_\<name\>_t** convention
- all macros and enumerator values use all caps **${X}_\<SCOPE\>_\<NAME\>** convention
- all functions use camel case **${x}\<Object\>\<Action\>** convention
    + exception: since "driver" functions use implicit \<Object\>, it is omitted
- all structure members and function parameters use camel case convention
## --validate=on

In addition, the following coding standards are followed:
- all function input parameters precede output parameters
- all functions return ::${x}_result_t

Note: "${OneApi}" is a placeholder until One API branding is decided.

${"##"} Versioning
There are multiple versions that should be used by the application to determine compatibility:
1. API Version - this is the version of the API supported by the device.
    - This is typically used to determine if the device supports the minimum set of APIs required by the application.
    - There is a single API version that represents a collection of APIs.
    - The value is determined from calling ::${x}DeviceGroupGetApiVersion
    - The value returned will be the minimum of the ::${x}_api_version_t supported by the device and known by the driver.
2. Structure Version - these are the versions of the structures passed-by-pointer to the driver.
    - These are typically used by the driver to support applications written to older versions of the API.
    - They are provided as the first member of every structure passed to the driver.
3. Driver Version - this is the version of the driver installed in the system.
    - This is typically used to mitigate driver implementation issues for a feature.
    - The value is determined from calling ::${x}DeviceGroupGetDriverVersion


${"##"} Error Handling
The following design philosophies are adopted in order to reduce Host-side overhead:
- by default, the driver implementation does no parameter validation of any kind
    + this can be enabled via environment variables, described below
- by default, neither the driver nor device provide any protection against the following:
    + invalid API programming
    + invalid function arguments
    + function infinite loops or recusions
    + synchronization primitive deadlocks
    + non-visible memory access by the Host or device
    + non-resident memeory access by the device
- all API functions return ::${x}_result_t
    + this allows for a consistent pattern on the application side for catching errors; especially when validation layer is enabled

${"##"} Multithreading and Concurrency
The following design philosophies are adopted in order to maximize Host thread concurrency:
- APIs are free-threaded when the driver object handle is different.
    + the driver should avoid thread-locks for these API calls
- APIs are not thread-safe when the driver object handle is the same, except when explicitly noted.
    + the application is responsible for ensuring multiple threads do not enter an API when the handle is the same
- APIs are not thread-safe with other APIs that use the same driver object handle
    + the application is responsible for ensuring multiple threads do not enter these APIs when the handle is the same
- APIs do not support reference counting of handles.
    + the application is responsible for tracking ownership and explicitly freeing handles and memory
    + the application is responsible for ensuring that all driver objects and memory are no longer in-use by the device before freeing; otherwise the Host or device may fault
    + no implcit garabage collection is supported by the driver

The expectation is that an application is in direct control over all Host thread creation and usage.
The driver should never implicitly create threads. 
If there is a need for an implementation to use a background thread, then that thread should be create and provided by the application.

Each API function must document details on the multithreading requirements for that call.

The primary usage-models enabled by these rules is:
- multiple, simultaneous threads may operate on independent driver objects with no implicit thread-locks
- driver object handles may be passed between and used by multiple threads with no implicit thread-locks

${"##"} Experimental API Support
Features which are still being considered for inclusion into the "Core" API, 
but require additional experimentation by application vendors before ratification,
are exposed as "Experimental" APIs.

Applications should not rely on experimental APIs in production.
- Experimental APIs may be added and removed from the API at any time; with or without an official API revision.
- Experimental APIs are not gaurenteed to be forward or backward capatible between API versions.
- Experimental APIs are not gaurenteed to be supported in production driver releases; and may appear and disappear from release to release.

An implementation will return ::${X}_RESULT_ERROR_UNSUPPORTED for any experimental API not supported by that driver.

${"#"} <a name="drv">Driver Architecture</a>
The following section provides high-level driver architecture.

![Driver](../images/intro_driver.png?raw=true)  
@image latex intro_driver.png

${"##"} Library
A static library is provided to allow applications to make direct API calls without understanding the underlying driver architecture. 
## --validate=off
For example, C/C++ applications should include "${x}_api.h" (C) or "${x}_api.hpp" (C++11) and link with "${x}_api.lib".
## --validate=on

${"##"} Loader
The loader initiates the loading of the driver(s) and layer(s).
The loader exports all API functions to the static library via per-process API function pointer table(s).
Each driver and layer must below the loader will also export its API/DDI functions via per-process function pointer table(s).
## --validate=off
The export function and table definitions are defined in "${x}_ddi.h".
## --validate=on

## --validate=off
The loader is dynamically linked with the application using the "${x}_loader.dll" (windows) or "${x}_loader.so" (linux).
## --validate=on
The loader is vendor agnostic, but must be aware of the names of vendor-specific device driver names. 
(Note: these are currently hard-coded but a registration method will be adopted when multiple vendors are supported.)

The loader dynamically loads each vendor's device driver(s) present in the system and queries each per-process function pointer table(s).
If only one device driver needs to be loaded, then the loader layer may be entirely bypassed.

The following diagram illustrates the expected loading sequence:  
![Loader](../images/intro_loader.png?raw=true)  
@image latex intro_loader.png

Thus, the loader's internal function pointer table entries may point to:
    + validation layer intercepts (if enabled),
    + instrumentation layer intercepts (if enabled),
    + device driver exports,
    + or any combination of the above

${"##"} Device Drivers
The device driver(s) contain the device-specific implementations of the APIs.

## --validate=off
The device driver(s) are dynamically linked using a _${x}_vendor_type.dll_ (windows) / _${x}_vendor_type.so_ (linux);
where _vendor_ and _type_ are names chosen by the device vendor.
For example, Intel GPUs use the name: "${x}_intc_gpu".
## --validate=on

${"##"} <a name="v0">Validation Layer</a>
The validation layer provides an optional capability for application developers to enable additional API validation while maintaining minimal driver implementation overhead.
- works independent of driver implementation
- works for production / release drivers
- works independent of vendor or device type
- checks for common application errors, such as parameter validation
- provides common application debug tracking, such as object and memory lifetime

The validation layer must be enabled via an environment variable.
Each capability is enabled by additional environment variables.

The validation layer supports the following capabilities:
- <a name="v1">Parameter Validation</a>
    + checks function parameters, such as null pointer parameters, invalid enumerations, uninitialized structures, etc.
    + functions may return ::${X}_RESULT_ERROR_INVALID_ARGUMENT or ::${X}_RESULT_ERROR_UNSUPPORTED
- <a name="v2">Handle Lifetime</a>
    + tracks handle allocations, destruction and usage for leaks and invalid usage (e.g., destruction while still in-use by device)
- <a name="v3">Memory Tracker</a>
    + tracks memory allocations and free for leaks and invalid usage (e.g., non-visible to device)
- <a name="v4">Threading Validation</a>
    + checks multi-threading usage (e.g., functions are not called from simultaneous threads using the same handle)

${"##"} <a name="i0">Instrumentation Layer</a>
The instrumentation layer provides an optional capability for application developers to enable additional profiling API while maintaining minimal driver implementation overhead.
- works independent of driver implementation
- works for production / release drivers
- implements [Tools](#tls) APIs

The instrumentation layer must be enabled via an environment variable.
Each capability is enabled by additional environment variables.

The instrumentation layer supports the following capabilities:
- <a name="i1">API Tracing</a>
    + enables API tracing and profiling APIs; more details in Tools programming guide
- <a name="i1">PIN</a>
    + enables binary instrumentation of programs for profiling; more details in Tools programming guide

${"##"} Environment Variables
The following table documents the supported knobs for overriding default driver behavior.
## --validate=off
| Category            | Name                                        | Values            | Description                                                                       |
|---------------------|---------------------------------------------|-------------------|-----------------------------------------------------------------------------------|
| Device              | [${X}_AFFINITY_MASK](#aff)                  | hex string        | Forces driver to only report devices (and sub-devices) as specified by mask value |
| Memory              | ${X}_SHARED_FORCE_DEVICE_ALLOC              | {**0**, 1}        | Forces all shared allocations into device memory                                  |
| Validation          | [${X}_ENABLE_VALIDATION_LAYER](#v0)         | {**0**, 1}        | Enables validation layer for debugging                                            |
| ^                   | [${X}_ENABLE_PARAMETER_VALIDATION](#v1)     | {**0**, 1}        | Enables the validation level for parameters                                       |
| ^                   | [${X}_ENABLE_HANDLE_LIFETIME](#v2)          | {**0**, 1}        | Enables the validation level for tracking handle lifetime                         |
| ^                   | [${X}_ENABLE_MEMORY_TRACKER](#v3)           | {**0**, 1}        | Enables the validation level for tracking memory lifetime                         |
| ^                   | [${X}_ENABLE_THREADING_VALIDATION](#v4)     | {**0**, 1}        | Enables the validation level for multithreading usage                             |
| Instrumentation     | [${X}_ENABLE_INSTRUMENTATION_LAYER](#i0)    | {**0**, 1}        | Enables instrumentation layer for profiling                                       |
| ^                   | [${X}_ENABLE_API_TRACING](#i1)              | {**0**, 1}        | Enables the instrumentation for API tracing                                       |
| ^                   | [${X}_ENABLE_METRICS](#i2)                  | {**0**, 1}        | Enables the instrumentation for device metrics                                    |
| ^                   | [${X}_ENABLE_PROGRAM_INSTRUMENTATION](#i3)  | {**0**, 1}        | Enables the instrumentation for program instrumentation                           |
| ^                   | [${X}_ENABLE_PROGRAM_DEBUGGING](#i4)        | {**0**, 1}        | Enables the instrumentation for program debugging                                 |
## --validate=on

${"###"} <a name="aff">Affinity Mask</a>
The affinity mask allows an application or tool to restrict which devices (and sub-devices) are visible to 3rd-party libraries or applications in another process, respectively.
The affinity mask is specified via an environment variable as a string of hexadecimal values.
The value is specific to system configuration; e.g., the number of devices and the number of sub-devices for each device.

The following examples demonstrate proper usage:
- "" (empty string) = disabled; i.e. all devices and sub-devices are reported.  This is the default value.
- Two devices, each with four sub-devices
    + "FF" = all devices and sub-devices are reported (same as default)
    + "0F" = only device 0 (with all its sub-devices) is reported
    + "F0" = only device 1 (with all its sub-devices) is reported as device 0
    + "AA" = both device 0 and 1 are reported, however each only has two sub-devices reported as sub-device 0 and 1
- Two devices, device 0 with one sub-device and device 1 with two sub-devices
    + "07" = all devices and sub-devices are reported (same as default)
    + "01" = only device 0 (with all its sub-devices) is reported
    + "06" = only device 1 (with all its sub-devices) is reported as device 0
    + "05" = both device 0 and device 1 are reported, however each only has one sub-device reported as sub-device 0

${"#"} <a name="tls">Tools</a>
Level-Zero APIs specific for supporting 3rd-party tools are separated from "Core" into "Tools" APIs.
The "Tools" APIs are designed to provided low-level access to device capabilities in order to support 3rd-party tools, but are not intended to replace or directly interface 3rd-party tools.
The "Tools" APIs are still available for direct application use.

The following diagram illustrates how 3rd-party tools may utilize the instrumentation layer:  
![Tool](../images/intro_tools.png?raw=true)  
@image latex intro_tools.png

The "Tools" APIs provide the following capabilities for 3rd-party tools:
- Allow for callbacks to be registered, in order to be notified of specific application events.
- Allow for device metrics to be queried, in order to profile application usage.
- Allow for application programs to be instrumented with custom instructions, for low-level code profiling.
- Allow for application programs to be debugged using breakpoints and register access.

See the "Tools" programming guide for more details.
