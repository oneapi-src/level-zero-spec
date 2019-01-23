# Introduction

[DO NOT EDIT]: # (generated from /scripts/core/INTRO.md)

The Intel Xe Driver API provides the lowest-level, fine-grain and most explicit control over:
- Memory Allocation and Cross-Process Sharing
- Kernel Submission
- Asynchronous Execution and Scheduling
- Synchronization Primitives
- Metrics Reporting

Most applications should not require the additional control provided by the driver APIs.  
The driver APIs are intended for providing explicit controls needed by higher-level runtime APIs and libraries.

While heavily influenced by other low-level APIs, such as OpenCL, the driver APIs are designed to evolve independently.
While heavily influenced by GPU archtiecture, the driver APIs are designed to be supportable across different device types, such as FPGAs.

## Cross-Device Support
In order to both expose the full capabilities of GPUs and remain supportable by other devices, the API definition is sub-divided into "Core" and "Extended".  
"Core" represents APIs that all fully cross-device while "Extended" represents APIs that are device-specific.
All implementations must support "Core" APIs while "Extended" APIs are optional.
An implementation will return "::XE_RESULT_ERROR_UNSUPPORTED" for any feature request not supported by that device.

## Installation
The Xe driver API is implemented within the xe.dll, which is copied on the system during installation of the device driver.

## Naming Convention
- all driver entry points are prefixed with xe
- all types follow **xe_\<name\>_t** convention
- all macros and enumerator values use all caps **XE_\<SCOPE\>_\<NAME\>** convention
- all functions use **xe\<Actor\>\<Action\>\<Object\>** convention
- all function input parameters precede output parameters

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
- all functions return ::xe_result_t.
- all functions are gaurenteed to never throw exceptions or fail silently.

## Environment Variables
The following table documents the supported knobs for overriding default driver behavior.

| Category            | Name                                    | Values                 | Description                                           |
|---------------------|-----------------------------------------|------------------------|-------------------------------------------------------|
| Memory              | @todo XE_MANAGED_FORCE_DEVICE_ALLOC   | {**0**, 1}             | Forces all managed allocations into device memory     |
| Programs            | @todo XE_PROGRAM_CACHE_DISABLE        | {**0**, 1}             | Disables the disk caching of compiled programs        |
| Cache               | @todo XE_PROGRAM_MOCS_INDEX           | {}                     | Overrides the Memory Object Control State (MOCS) index used for programs, scratch space, and arguments. |
|||||
