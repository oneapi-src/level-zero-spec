# Introduction
The Intel Xe Driver API provides the lowest-level, fine-grain and most explicit control over:
- Memory Allocation and Cross-Process Sharing
- Kernel Submission
- Asynchronous Execution and Scheduling
- Synchronization Primitives
- Metrics Reporting

The Xe driver API is implemented within the xe.dll, which is copied on the system during installation of the device driver.

Most applications should not require the additional control provided by the driver APIs.  
The driver APIs are intended for providing explicit controls needed by higher-level runtime APIs and libraries.

## Naming Convention
- all driver entry points are prefixed with xe
- all types follow **xe_\<name\>_t** convention
- all macros and enumerator values use all caps **XE_\<SCOPE\>_\<NAME\>** convention
- all functions use **xe\<Actor\>\<Action\>\<Object\>** convention
- all function input parameters precede output parameters

## Error Handling
- all functions return ::xe_result_t.
- all functions are gaurenteed to never throw exceptions or fail silently.

## Environment Variables
The following table documents the supported knobs for overriding default driver behavior.

| Category | Name     | Values   | Description |
|----------|----------|----------|-------------|
|          |          |          |             |
