# Introduction

[DO NOT EDIT]: # (generated from /scripts/core/INTRO.md)

## Table of Contents
* [Objective](#obj)
* [API Specification](#spec)
* [Drivers](#drv)

# <a name="obj">Objective</a>
The objective of the Level-Zero APIs to provide direct-to-metal interfaces to offload accelerator devices.

The Intel Xe Driver API provides the lowest-level, fine-grain and most explicit control over:
- Memory Allocation and Cross-Process Sharing
- Kernel Submission
- Asynchronous Execution and Scheduling
- Synchronization Primitives
- Metrics Reporting

Most applications should not require the additional control provided by the driver APIs.
The driver APIs are intended for providing explicit controls needed by higher-level runtime APIs and libraries.

While heavily influenced by other low-level APIs, such as OpenCL, the driver APIs are designed to evolve independently.
While heavily influenced by GPU archtiecture, the driver APIs are designed to be supportable across different compute device architectures, such as FPGAs, CSAs, etc.

## Devices
The API architecture exposes both physical and logical abstraction of the underlying devices capabilities. 
The Device, sub device and memory are exposed at physical level and command queues, events and synchronization methods are defined as logical entities. 
All logical entities will be bound to device level physical capabilities.
Device discovery APIs enumerate the accelerators functional features. 
These APIs provide interface to query information like compute unit count within the device or sub device, 
available memory and affinity to the compute, user managed cache size and work submission command queues.

## Memory
Memory is visible to upper level stack as unified memory with single VA space covering both GPU and specific device type (e.g GPU or FPGA). 
For GPU the API exposed 2 levels (potentially 3 levels) of memory hierarchy. 
The local memory available per device / sub device and user managed shared memory cache size (L1 cache). 
@todo [**Murali**] Determine the need to expose the last level (L3) cache on GPU, given it is configurable at the very high (buffer or image) level granularity in the HW.  
The Level 0 application interface allows allocation of buffers and images at device and sub device granularity. 
The memory APIs allow 3 kinds of allocation methods and enable implicit and explicit management of the resources by the application or runtimes
@todo [**Ankur**] add cache capabilities of the device, e.g. max SLM size, L2$ size, L3$ controls
@todo [**Ben**] SPIR-V has semantics within the kernels to declare cache requests, what about outside of kernels?  Add per-Resource L3$ _HINTS_, overrided by kernels.

## Cross-Device Support
In order to both expose the full capabilities of GPUs and remain supportable by other devices, the API definition is sub-divided into "Core" and "Extended".  
"Core" represents APIs that all fully cross-device while "Extended" represents APIs that are device-specific.
All implementations must support "Core" APIs while "Extended" APIs are optional.
An implementation will return ::XE_RESULT_ERROR_UNSUPPORTED for any feature request not supported by that device.

## Multi-Die Device Support
GPUs are typically built with multiple dies, also called as "Tiles" with in the package. 
Each Tile is interconnected with neighboring tile using high bandwidth link. 
Even though, tiles have direct connection to its own memory, the high band width link allows each tile to access its neighboring tile's memory at very low latency. 
The cross-tile memory is stacked within package allowing applications to access all the device memory with the single continuous view.

@todo [**Ben/Zack**] add support for sub-devices and memory, command queue affinity, etc.

## Peer-to-Peer Communication
@todo [**Murali**] add high-level goals for P2P

## Inter-Process Communication
@todo [**Murali**] add high-level goals for IPC.

# <a name="spec">API Specification</a>
The following section provides high-level design philosophy of the APIs.
For more detailed information, refer to the programming guides and detailed specification pages.

## Naming Convention
The following naming convention is followed in order to avoid conflicts within the API, or with other APIs and libraries:
- all driver entry points are prefixed with xe
- all types follow **xe_\<name\>_t** convention
- all macros and enumerator values use all caps **XE_\<SCOPE\>_\<NAME\>** convention
- all functions use **xe\<Actor\>\<Action\>\<Object\>** convention
- all function input parameters precede output parameters

## Terminology
This specification uses key words based on [RFC2119](https://www.ietf.org/rfc/rfc2119.txt) to indicate requirement level. 
In particular, the following words are used to describe the actions of an implementation of this specification:
- **May**: the word _may_, or the adjective _optional_, mean that conforming implementations are permitted to, but need not behave as described.
- **Should**: the word _should_, or the adjective _recommended_, mean that there could be reasons for an implementations to deviate from the behavior described, but that such deviation should be avoided.  
- **Must**: the word _must_, or the term _required_ or _shall_, mean that the behavior described is an absolute requirement of the specification.

## Versioning
There are multiple versions that can be used by the application to determine compatibility:
1. Header Version - this is the version of the header files included by the application.
    - This is typically used to determine whether the application is using the latest version of the API header files.
    - It is determined from ::XE_UMD_HEADER_VERSION.
2. API Version - this is the version of the API features supported by the device.
    - This is typically used to determine if the device supports the minimum set of features required by the application.
    - It is determined from calling ::xeDeviceGetApiVersion
3. Driver Version - this is the version of the driver installed in the system.
    - This is typically used to mitigate driver implementation issues for a feature.
    - It is determined from calling ::xeDriverGetVersion
4. Structure Version - these are the versions of the structures passed-by-pointer to the driver.
    - These are typically used by the driver to support applications written to older versions of the API.
    - They are provided as the first member of every structure passed to the driver.

## Error Handling
The following rules are followed in order to maximize robustness and security:
- all functions are gaurenteed to never throw exceptions or fail silently.
- all functions return ::xe_result_t.
- all function parameters are validated prior to execution to ensure implementation compatibility.

## Multithreading
In order to eliminate the usage of thread-locks by the implementation, the following design philosophies are adopted:
- work submission occurs exclusively by enqueing command lists into a command queue
- work submission into a command queue is free-threaded
- multiple, simulateneous threads may encode multiple command lists independently
- the application is responsible for ensuring multiple, simultaneous threads are not modifying mutable objects;
such as command queues and command lists
- the application is responsible for ensuring the GPU is not accessing objects before they are modified, resued or destroyed;
such as memory, images and command lists
- there is no implicit garbage collection performed by the implementation

# <a name="drv">Drivers</a>
## Installation
The Xe driver API is implemented within the xe<name>.dll, which is copied on the system during installation of the device driver;
where <name> is a name chosen by the device vendor.

This API does not define an Installable Client Driver (ICD), however it is expected that users of this API would prefer to implement
their own device abstraction layer and communicate directly with the device-driver.

## Environment Variables
The following table documents the supported knobs for overriding default driver behavior.

@todo [**Brandon**] add driver validation levels e.g., {low, **medium**, high}

| Category            | Name                                    | Values                 | Description                                           |
|---------------------|-----------------------------------------|------------------------|-------------------------------------------------------|
| Memory              | XE_SHARED_FORCE_DEVICE_ALLOC          | {**0**, 1}             | Forces all shared allocations into device memory     |

