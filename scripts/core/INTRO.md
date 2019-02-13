${"#"} Introduction

[DO NOT EDIT]: # (generated from /scripts/core/INTRO.md)

${"##"} Table of Contents
* [Objective](#obj)
* [API Specification](#spec)
* [Drivers](#drv)

${"#"} <a name="obj">Objective</a>
The objective of the Level-Zero API is to provide direct-to-metal interfaces to offload accelerator devices. 
It is a programming interface that can be published at a cadence that better matches Intel hardware releases and can be tailored to any hardware needs. 
It can be adapted to support broader set of languages features, such as function pointers, virtual functions, unified memory, and  I/O capabilities.

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
For example, a sub-device can be used with memory allocation and tasks dispatch functions and allow placement and dispatch to a specific sub-device.

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

${"##"} Cross-Device Support
In order to both expose the full capabilities of GPUs and remain supportable by other devices, the API definition is sub-divided into "Core" and "Extended".  
"Core" represents APIs that all fully cross-device while "Extended" represents APIs that are device-specific.
All implementations must support "Core" APIs while "Extended" APIs are optional.
An implementation will return ::${X}_RESULT_ERROR_UNSUPPORTED for any feature request not supported by that device.

Note: currently all APIs are defined as part of the "Core" specification until they are determined to not be supportable by other devices.

${"##"} Naming Convention
The following naming convention is followed in order to avoid conflicts within the API, or with other APIs and libraries:
- all driver entry points are prefixed with ${x}
- all types follow **${x}_\<name\>_t** convention
- all macros and enumerator values use all caps **${X}_\<SCOPE\>_\<NAME\>** convention
- all functions use camel case **${x}\<Actor\>\<Action\>\<Object\>** convention
- all structure members and function parameters use camel case convention
- all function input parameters precede output parameters

Note: "${Xx}" is a placeholder until One-API branding is decided.

${"##"} Terminology
This specification uses key words based on [RFC2119](https://www.ietf.org/rfc/rfc2119.txt) to indicate requirement level. 
In particular, the following words are used to describe the actions of an implementation of this specification:
- **May**: the word _may_, or the adjective _optional_, mean that conforming implementations are permitted to, but need not behave as described.
- **Should**: the word _should_, or the adjective _recommended_, mean that there could be reasons for an implementations to deviate from the behavior described, but that such deviation should be avoided.  
- **Must**: the word _must_, or the term _required_ or _shall_, mean that the behavior described is an absolute requirement of the specification.

${"##"} Versioning
There are multiple versions that should be used by the application to determine compatibility:
1. Header Version - this is the version of the header files included by the application.
    - This is typically used to determine whether the application is using the latest version of the API header files.
    - It is determined from ::${X}_API_HEADER_VERSION.
2. API Version - this is the version of the API supported by the device.
    - This is typically used to determine if the device supports the minimum set of features required by the application.
    - There is a single API version that represents a collection of features.
    - The value is determined from calling ::${x}DeviceGetApiVersion
    - The value returned will be the minimum of the ::${X}_API_HEADER_VERSION supported by the device and known by the driver.
3. Structure Version - these are the versions of the structures passed-by-pointer to the driver.
    - These are typically used by the driver to support applications written to older versions of the API.
    - They are provided as the first member of every structure passed to the driver.
4. Driver Version - this is the version of the driver installed in the system.
    - This is typically used to mitigate driver implementation issues for a feature.
    - The value is determined from calling ::${x}DriverGetVersion

${"##"} Error Handling
The following rules must be followed in order to maximize robustness and security:
- all functions must return ::${x}_result_t.
- functions must never throw unhandled exceptions
- functions must never fail silently; i.e. return ::{$X}_RETURN_SUCCESS 
- function parameters should be validated prior to execution to ensure implementation compatibility, such as structure version.

${"##"} Multithreading and Concurrency
The following design philosophies are adopted in order to maximize Host thread concurrency:
- APIs are free-threaded when the "Actor" is different.
    + the driver should avoid thread-locks for these API calls
- APIs are not thread-safe when the "Actor" is the same, except when explicitly noted.
    + the application is responsible for ensuring multiple threads do not enter an API when the "Actor" is the same
- APIs are not thread-safe with other APIs that use the same "Actor"
    + the application is responsible for ensuring multiple threads do not enter these APIs when the "Actor" is the same
- the application is responsible for freeing handles and memory, no implcit garabage collection is supported by the driver

Each API function must document details on the multithreading requirements for that call.

The primary usage-model enabled by these rules is:
- work submission occurs exclusively by enqueing command lists into a command queue
- work submission into a command queue is free-threaded
- multiple, simulateneous threads may encode multiple command lists independently

${"#"} <a name="drv">Drivers</a>
${"##"} Installation
The Level-Zero API is implemented within a _${x}_vendor_device.dll_ (windows) / _${x}_vendor_device.so_ (linux), which is copied on the system during installation of the device driver;
where _vendor_ and _device_ are names chosen by the device vendor.  For Intel GPUs, the name would be "${x}_intc_gpu".

This API does not define an Installable Client Driver (ICD), as it is expected that users of this API would prefer to implement
their own device abstraction layer and communicate directly with the device-driver.

${"##"} Environment Variables
The following table documents the supported knobs for overriding default driver behavior.

| Category            | Name                                    | Values                 | Description                                           |
|---------------------|-----------------------------------------|------------------------|-------------------------------------------------------|
| Memory              | ${X}_SHARED_FORCE_DEVICE_ALLOC          | {**0**, 1}             | Forces all shared allocations into device memory      |
| Validation          | ${X}_DRIVER_PARAMETER_VALIDATION_LEVEL  | {0, **1**, 2}          | Controls the validation level used by the driver for parameters.<br>0 = disabled, no checks<br>1 = pointer and overflow checks only [default]<br>2 = values and states<br> |

