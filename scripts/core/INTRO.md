${"#"} Introduction

[DO NOT EDIT]: # (generated from /scripts/core/INTRO.md)

The Intel ${Xx} Driver API provides the lowest-level, fine-grain and most explicit control over:
- Memory Allocation and Cross-Process Sharing
- Kernel Submission
- Asynchronous Execution and Scheduling
- Synchronization Primitives
- Metrics Reporting

Most applications should not require the additional control provided by the driver APIs.  
The driver APIs are intended for providing explicit controls needed by higher-level runtime APIs and libraries.

While heavily influenced by other low-level APIs, such as OpenCL, the driver APIs are designed to evolve independently.
While heavily influenced by GPU archtiecture, the driver APIs are designed to be supportable across different device types, such as CPUs or FPGAs.

${"##"} Cross-Device Support
In order to both expose the full capabilities of GPUs and remain supportable by other devices, the API definition is sub-divided into "Core" and "Extended".  
"Core" represents APIs that all fully cross-device while "Extended" represents APIs that are device-specific.
All implementations must support "Core" APIs while "Extended" APIs are optional.
An implementation will return "::${X}_RESULT_ERROR_UNSUPPORTED" for any feature request not supported by that device.

${"##"} Installation
The ${Xx} driver API is implemented within the ${x}.dll, which is copied on the system during installation of the device driver.

${"##"} Naming Convention
- all driver entry points are prefixed with ${x}
- all types follow **${x}_\<name\>_t** convention
- all macros and enumerator values use all caps **${X}_\<SCOPE\>_\<NAME\>** convention
- all functions use **${x}\<Actor\>\<Action\>\<Object\>** convention
- all function input parameters precede output parameters

${"##"} Error Handling
- all functions return ::${x}_result_t.
- all functions are gaurenteed to never throw exceptions or fail silently.

${"##"} Environment Variables
The following table documents the supported knobs for overriding default driver behavior.

| Category | Name     | Values   | Description |
|----------|----------|----------|-------------|
|          |          |          |             |
