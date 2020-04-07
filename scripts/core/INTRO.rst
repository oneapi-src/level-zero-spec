
<%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
==========
 Overview
==========

Objective
=========

The objective of the ${OneApi} Level-Zero API is to provide
direct-to-metal interfaces to offload accelerator devices. It is a
programming interface that can be published at a cadence that better
matches Intel hardware releases and can be tailored to any device needs.
It can be adapted to support broader set of languages features, such as
function pointers, virtual functions, unified memory, and I/O
capabilities.

.. image:: ../images/one_api_sw_stack.png

The Level-Zero API provides the lowest-level, fine-grain and most explicit control over:

- Device Discovery
- Memory Allocation
- Peer-to-Peer Communication
- Inter-Process Sharing
- Kernel Submission
- Asynchronous Execution and Scheduling
- Synchronization Primitives
- Metrics Reporting
- System Management Interface

Most applications should not require the additional control provided by
the Level-Zero API. The Level-Zero API is intended for providing
explicit controls needed by higher-level runtime APIs and libraries.

While initially influenced by other low-level APIs, such as OpenCL and Vulkan,
the Level-Zero APIs are designed to evolve independently. While initially
influenced by GPU architecture, the Level-Zero APIs are designed to be supportable
across different compute device architectures, such as FPGAs, CSAs, etc.

Devices
-------

The API architecture exposes both physical and logical abstraction of
the underlying devices capabilities. The device, sub device and memory
are exposed at physical level while command queues, events and
synchronization methods are defined as logical entities. All logical
entities will be bound to device level physical capabilities.

Device discovery APIs enumerate the accelerators functional features.
These APIs provide interface to query information like compute unit
count within the device or sub device, available memory and affinity to
the compute, user managed cache size and work submission command queues.

Memory & Caches
---------------

Memory is visible to the upper-level software stack as unified memory
with a single virtual address space covering both the Host and a
specific device.

For GPUs, the API exposes two levels of the device memory hierarchy:

1. Local Device Memory: can be managed at the device and/or sub device level.
2. Device Cache(s):

    + Last Level Cache (L3) can be controlled through memory allocation APIs.
    + Low Level Cache (L1) can be controlled through program language intrinsics.

The API allows allocation of buffers and images at device and sub device
granularity with full cacheablity hints.

- Buffers are transparent memory accessed through virtual address pointers
- Images are opaque objects accessed through handles

The memory APIs provide allocation methods to allocate either device,
host or shared memory. The APIs enable both implicit and explicit
management of the resources by the application or runtimes. The
interface also provides query capabilities for all memory objects.

Subdevice Support
-----------------

The API supports sub-devices and there are functions to query
and obtain a sub-device. A sub-device can represent a physical or
logical partition of the device. Outside of these functions there are no
distinction between sub-devices and devices. For example, a sub-device
can be used with memory allocation and tasks and allow placement and
submission to a specific sub-device.

Peer-to-Peer Communication
--------------------------

Peer to Peer API's provide capabilities to marshall data across Host to
Device, Device to Host and Device to Device. The data marshalling API
can be scheduled as asynchronous operations or can be synchronized with
kernel execution through command queues. Data coherency is maintained by
the driver without any explicit involvement from the application.

Inter-Process Communication
---------------------------

The API allows sharing of memory objects across different device
processes. Since each process has its own virtual address space, there
is no guarantee that the same virtual address will be available when the
memory object is shared in new process. There are a set of APIs that
makes it easier to share the memory objects with ease.

System Management
-----------------

The API provides in-band ability to query the performance, power and
health of accelerator resources. It also enables controlling the
performance and power profile of these resources. Finally, it provides
access to maintenance facilities such as performing hardware diagnostics
or updating firmware.

API Specification
=================

The following section provides high-level design philosophy of the APIs.
For more detailed information, refer to the programming guides and
detailed specification pages.

Header files can be found at: https://github.com/oneapi-src/level-zero

Terminology
-----------

  This specification uses key words based on
  `RFC2119 <https://www.ietf.org/rfc/rfc2119.txt>`__ to indicate
  requirement level. In particular, the following words are used to
  describe the actions of an implementation of this specification:
  
  - **May** - the word *may*, or the adjective *optional*, mean that conforming implementations are permitted to, but need not behave as described.
  - **Should** - the word *should*, or the adjective *recommended*, mean that there could be reasons for an implementations to deviate from the behavior described, but that such deviation should be avoided.
  - **Must** - the word *must*, or the term *required* or *shall*, mean that the behavior described is an absolute requirement of the specification.

Naming Convention
-----------------

The following naming conventions are followed in order to avoid
conflicts within the API, or with other APIs and libraries:
## --validate=off
- all driver entry points are prefixed with ${x}
- all types follow \**${x}_<name>_t*\* convention
- all macros and enumerator values use all caps \**${X}_<SCOPE>_<NAME>*\* convention
- all functions use camel case **${x}<Object><Action>** convention - exception: since "driver" functions use implicit <Object>, it is omitted
- all structure members and function parameters use camel case convention
## --validate=on

In addition, the following coding standards are followed:
- all function input parameters precede output parameters
- all functions return ::${x}_result_t

Versioning
----------

There are multiple versions that should be used by the application to determine compatibility:

**API Version** - this is the version of the API supported by the device.

  - This is typically used to determine if the device supports the minimum set of APIs required by the application.
  - There is a single API version that represents a collection of APIs.
  - The value is determined from calling ::${x}DriverGetApiVersion
  - The value returned will be the minimum of the ::${x}_api_version_t supported by the device and known by the driver.

**Structure Version** - these are the versions of the structures passed-by-pointer to the driver.

  - These are typically used by the driver to support applications written to older versions of the API.
  - They are provided as the first member of every structure passed to the driver.

**Driver Version** - this is the version of the driver installed in the system.

  - This is typically used to mitigate driver implementation issues for a feature.
  - The value is determined from calling ::${x}DriverGetProperties

Error Handling
--------------

The following design philosophies are adopted in order to reduce Host-side overhead:

* By default, the driver implementation does no parameter validation of any kind

   * This can be enabled via environment variables, described below

* By default, neither the driver nor device provide any protection against the following:

   * Invalid API programming
   * Invalid function arguments
   * Function infinite loops or recursions
   * Synchronization primitive deadlocks
   * Non-visible memory access by the Host or device
   * Non-resident memory access by the device

* The driver implementation is **not** required to perform API validation of any kind

   * The driver should ensure well-behaved applications are not burdened with the overhead needed for non-behaving applications
   * Unless otherwise specified, the driver behavior is undefined when APIs are improperly used
   * For debug purposes, API validation can be enabled via the [Validation Layers](#v0)

* All API functions return ::${x}_result_t

   * This enumeration contains error codes for the core APIs and validation layers
   * This allows for a consistent pattern on the application side for catching errors; especially when validation layer(s) are enabled

Multithreading and Concurrency
------------------------------

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
    + no implicit garabage collection is supported by the driver

In general, the API is designed to be free-threaded rather than thread-safe.
This provides multithreaded applications with complete 
control over both threading and locks. This also eliminates unnecessary
driver overhead for single threaded applications and/or very low latency
usages.

The exception to this rule is that all memory allocation APIs are
thread-safe since they allocate from a single global memory pool. If an
application needs lock-free memory allocation, then it could allocate a
per-thread pool and implement its own sub-allocator.

An application is in direct control over all Host thread creation and
usage. The driver should never implicitly create threads. If there is a
need for an implementation to use a background thread, then that thread
should be create and provided by the application.

Each API function must document details on the multithreading
requirements for that call.

The primary usage-models enabled by these rules is:

- multiple, simultaneous threads may operate on independent driver objects with no implicit thread-locks
- driver object handles may be passed between and used by multiple threads with no implicit thread-locks

Extension Support
-----------------

Features which are device- or vendor-specific can be exposed as extensions.
The list of extensions supported by the driver implementation can be queried using ::${x}DriverGetExtensionProperties.

"Experimental" extensions require additional experimentation and feedback from application vendors
before ratification, therefore applications should not rely on experimental extensions in production.

- Experimental extensions may be added and removed from the driver at any time.
- Experimental extensions are not guaranteed to be forward or backward compatible between versions.
- Experimental extensions are not guaranteed to be supported in production driver releases; and may appear and disappear from release to release.

Import Library
--------------

A static import library shall be provided to allow applications
to make direct API calls without understanding the underlying
driver interfaces. 

## --validate=off
C/C++ applications may include "${x}_api.h" and link with "${x}_api.lib".
## --validate=on

.. _Tools:

Tools
=====

Level-Zero APIs specific for supporting 3rd-party tools are separated
from "Core" into "Tools" APIs. The "Tools" APIs are designed to provided
low-level access to device capabilities in order to support 3rd-party
tools, but are not intended to replace or directly interface 3rd-party
tools. The "Tools" APIs are still available for direct application use.

The "Tools" APIs provide the following capabilities for 3rd-party tools:

- Allow for callbacks to be registered, in order to be notified of specific application events.
- Allow for device metrics to be queried, in order to profile application usage.
- Allow for application programs to be instrumented with custom instructions, for low-level code profiling.
- Allow for application programs to be debugged using breakpoints and register access.

See the "Tools" programming guide for more details.

.. _system-management-1:

System Management
=================

All global management of accelerator resources are separated from "Core" into the "Sysman" API.

The "Sysman" API provides in-band access to the following features for each accelerator device:

- Query inventory information
- Query information about host processes using the device
- Change the accelerator workload scheduling policies
- Query and control frequency/voltage/power
- Query temperature sensors
- Query load on various accelerator engines (overall, media, compute, copy)
- Query device memory bandwidth and health
- Query PCI bandwidth and health
- Query high-speed Fabric bandwidth and health
- Control the standby policy of the device
- Query ECC/RAS status of various components on the device
- Query power supply status
- Control LEDs
- Control fans
- Perform overclocking/under-voltage changes where appropriate
- Listen for events (temperature excursion, frequency throttling, RAS errors)
- Flash firmware
- Run diagnostics
- Reset the device

By default, only administrator users have permissions to perform control
operations on resources. Most queries are available to any user with the
exception of those that could be used for side-channel attacks. The
systems administrator can tighten/relax the default permissions.

See the "Sysman" programming guide for more details.

