.. SPDX-FileCopyrightText: 2021 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

===============================
 oneAPI Specification Releases
===============================


The oneapi spec has moved to `oneAPI Spec`_. Level Zero continues to
be available at this site. All other specs have been archived. For any
questions, file an issue at `level-zero-spec issues`_.

.. _`oneAPI Spec`: https://oneapi-spec.uxlfoundation.org/
.. _`level-zero-spec issues`: https://github.com/oneapi-src/level-zero-spec/issues



Level Zero
==========

.. list-table::
  :widths: 30 20 50
  :header-rows: 1

  * - Version
    - Date
    - View
  * - `Level Zero v1.11.8`_
    - 2024-11-13
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.11.8/index.html>`__  
  * - `Level Zero v1.11`_
    - 2024-10-03
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.11/index.html>`__  	
  * - `Level Zero v1.10`_
    - 2024-09-06
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.10/index.html>`__  	
  * - `Level Zero v1.9.3`_
    - 2024-05-03
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.9.3/index.html>`__  
  * - `Level Zero v1.9.2`_
    - 2024-02-20
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.9.2/index.html>`__
  * - `Level Zero v1.9.1`_
    - 2024-02-09
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.9.1/index.html>`__
  * - `Level Zero v1.9.0`_
    - 2024-02-02
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.9.0/index.html>`__
  * - `Level Zero v1.8.0`_
    - 2023-10-13
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.8.0/index.html>`__
  * - `Level Zero v1.7.8`_
    - 2023-8-28
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.7.8/index.html>`__
  * - `Level Zero v1.7.0`_
    - 2023-7-9
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.7.0/index.html>`__
  * - `Level Zero v1.6.10`_
    - 2023-5-19
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.6.10/index.html>`__
  * - `Level Zero v1.6.3`_
    - 2023-4-25
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.6.3/index.html>`__
  * - `Level Zero v1.6.0`_
    - 2023-3-31
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.6.0/index.html>`__
  * - `Level Zero v1.5.17`_
    - 2023-3-2
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.5.17/index.html>`__
  * - `Level Zero v1.5.16`_
    - 2023-2-28
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.5.16/index.html>`__
  * - `Level Zero v1.5.8`_
    - 2023-1-19
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.5.8/index.html>`__
  * - `Level Zero v1.5.0`_
    - 2023-1-11
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.5.0/index.html>`__
  * - `Level Zero v1.4.8`_
    - 2022-07-22
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.4.8/index.html>`__
  * - `Level Zero v1.4`_
    - 2022-05-05
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.4.0/index.html>`__
  * - `Level Zero v1.3`_
    - 2021-11-27
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.3.7/index.html>`__
  * - `Level Zero v1.2`_
    - 2021-05-11
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.2.43/index.html>`__
  * - `Level Zero v1.1`_
    - 2021-02-04
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.1.2/index.html>`__
  * - `Level Zero v1.0`_
    - 2020-10-02
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/1.0.4/index.html>`__
  * - `Level Zero v0.95`_
    - 2020-05-28
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/0.95/index.html>`__
  * - `Level Zero v0.91`_
    - 2020-03-04
    - `HTML <https://oneapi-src.github.io/level-zero-spec/level-zero/0.91/index.html>`__

Release Notes
-------------

Level Zero v1.11.8
~~~~~~~~~~~~~~~~~~

* Patches to v1.11 release:

	- Fixing ABI compatibility issues with v1.11.
	- Fix metric types for new experimental types.
	- Scripts updated to raise a proper exception when parse errors occur.
	- Fix zeKernelGetBinaryExp's inclusion.
	- Update documentation on Init and add deprecation comments for init changes.  

Level Zero v1.11
~~~~~~~~~~~~~~~~~~

* Updated Features:

	- zePhysicalMemCreate to support physical system memory.
	- Added a new error code in GetGlobalTimestamps function.
	- Add support for metrics and groups to export memory.
	- Add API specification to retrieve kernel binary program data.

* Patches to v1.10 release:

	- Addressed level-zero loader ABI breakage issue with spec v1.10.
	- Documentation update to spec to relax restriction to allow driver to create internal threads.
	- rename Programmable1Exp to ProgrammableExp2.
	
Level Zero v1.10
~~~~~~~~~~~~~~~~~~

* Updated Features

	- Supports new single API for Level Zero Init and Driver Retrieval
	- Support for concurrent Metric group query
	- Supports experimental extension for metric tracer
	- Support to specify fp64 range to metric_value_info
	- Support zetCreateMetricGroupsFromMetricsExp programmable API
	- Support for new temperature sensor types
	- Support for ZE_API_VERSION_CURRENT_M macro for compile time version validation.
	- Supports version 1.1 of mutable commands extension
	- Support for NPU graph support for MCL extension
	- Support for new ELF memory space for debugger
	- Support for Metric Tracer Decode support for sub-devices
	- Support for byte normalized programmable type
	- Added updates to virtual management API

* Patches to v1.9.3 release

	- Added description to replace C string parameter type
	- Fixed metricprogrammable spec issues
	- Update documentation on zesInit Usage
	- Remove VF experimental interfaces
	- fix metrics names in tracer
	

Level Zero v1.9.3
~~~~~~~~~~~~~~~~~~

* Patches to v1.9.2 release

    - Misc infrastructure updates 
    - Fix typo in for device property 
    - Update support for sampled bindless images 
    - Update new image formats

Level Zero v1.9.2
~~~~~~~~~~~~~~~~~~

* Patch v1.9 to fix API version enum

Level Zero v1.9.1
~~~~~~~~~~~~~~~~~~

* Misc. patches to v1.9.0 release

    - Add missing enumerations to programming guides
    - Add numWaitEvents parameter to mutable command list update wait events API (needed for loader)
    - Add range to phCommandLists description in append command lists extension
    - Fix spelling error in sysman subdevice properties structure type name
    - Fix immediate command list append API parameter description to work around script limitation
    - Convert fixed-length character array parameters to constant pointers in programmable metrics and firmware secuirty version extensions

Level Zero v1.9.0
~~~~~~~~~~~~~~~~~~

* Core

  - Fix device hierarchy environment variable value in docs
  - Add experimental extension for immediate command list append command lists
  - Add experimental extension to clone a command list
  - Add experimental extension for mutable command lists
  - Add experimental extension for bindless images
  - Add introspection APIs
  - Add invalid argument error code to zeContextMakeMemoryResident

* Sysman

  - Fixes to Memory Bandwidth Extensions
  - Add SURVIVABILITY_MODE_DETECTED event type
  - Clarify engine stats details
  - Add clarification for setting frequency defaults
  - New firmware API for logging
  - Add extension to support Flat device model
  - Add experimental extension to access firmware security version
  - Add experimental extension for VF telemetry

* Tools

  - Add support for programmable metrics

Level Zero v1.8.0
~~~~~~~~~~~~~~~~~~

* Core

  - Add API Versions 1.7, 1.8
  - Add experimental extension for counter-based events
  - Clarify usage of IPC event pools

* Sysman

  - Add RasClearState to extension listing
  - Add MEMORY power domain
  - Add GPU power domain
  - Clarify that the time units for engine activity counters are implementation specific
  - Describe extension discovery
  - Added GPU Board Temperature Metric
  - Add power domain properties extension
  - Deprecate unused APIs and/or APIs with enhanced replacements
  - Deprecate compute unit debug mode
  - Add memory timestamp valid bits experimental extension
  - Add flash progress API
  - Added Memory Page Offline Metrics

Level Zero v1.7.8
~~~~~~~~~~~~~~~~~~

* Core

  - Fix timestamps results parameter attributes

* Sysman

  - Add extension mechanism for dynamically discovering RAS error states
  - Move engine activity extension to separate extension file
  - Add clarifications to board and serial number descriptions
  - Clarify description for multi-port throughput

* Tools

  - Clarify metric streamer desc member descriptions

Level Zero v1.7.0
~~~~~~~~~~~~~~~~~~

* Core

  - Fix a spelling error in the core programming guide command queues section
  - Minor fix to kernel timestamp example in programming guide
  - Some fixes for kernel max group size extension
  - Add clarification to immediate command lists execution
  - Add system memory hint for memory advise
  - Add API to set atomic properties of a shared allocation
  - Add support for in-order lists
  - Add support for flexible device hierarchy model
  - Add ray tracing acceleration structure build experimental extension

* Sysman

  - Various updates for engine, fabric, device and memory
  - Added Fabric Error Counters and API
  - Update engine group descriptions
  - Fixes to GetFabricPortMultiThroughput

* Tools

  - Minor formatting fix for metric export data
  - Fix sample code for MetricGroupGetExportDataExp
  - Promote ZET_METRIC_TYPE_IP_EXP out of experimental
  - Fix ZET typo to conform to naming convention

Level Zero v1.6.10
~~~~~~~~~~~~~~~~~~

* Core

  - Clarify documentation on build logs lifetime
  - Set pNext pointer to NULL in programming guide

* Sysman

  - Add support for machine independent calculation for metrics data
  - Update metrics timer resolution to cycle/sec

* Tools

  - Fix html generation of metric export data example code
  - Fix base type for zet_metric_global_timestamps_resolution_exp_t

* Infrastructure (Scripts)

  - Misc. formatting and infrastructure fixes

Level Zero v1.6.3
~~~~~~~~~~~~~~~~~

* Core

  - Import SECURITY.md

* Sysman

  - Revert RAS Category and Fabric API changes, restoring backwards compatibility.

* Infrastructure (Scripts)

  - Update copyright year for publication.

Level Zero v1.6.0
~~~~~~~~~~~~~~~~~

* Core Changes

  - Add zeMemPutIpcHandle and zeEventPoolPutIpcHandle
  - Add helper functions for IPC handle
  - Add zeDriverGetLastResultString
  - Add zeCommandListHostSynchronize
  - Module build option clarification
  - Introduce extension to query normalized kernel event timestamps
  - Clarify image buffers format/layout restrictions

* Sysman

  - Extend the SYSMAN Frequency Domain list to include a MEDIA Domain

* Infrastructure (Scripts)

  - Fixup extension references and substitutions
  - Fixup parser versions (add newer point releases to all_versions)

Level Zero v1.5.17
~~~~~~~~~~~~~~~~~~

* Tool Changes

  - Add missing version to global metrics timestamps extension

Level Zero v1.5.16
~~~~~~~~~~~~~~~~~~

* Core Changes

  - Clarify intended interpretation of 32-bit device id
  - Clarify that zeContextMakeMemoryResident is a cross-platform API
  - Clarify language for pString parameter of zeKernelGetSourceAttributes
  - Add an extension to get the kernel max group size properties
  - Fixup typo in PCI Properties extension example

* Tool Changes

  - Add extension for global metrics timestamps

* Sysman Changes

  - Explicitly state the timestamp unit for the memory bandwidth API
  - Update value of ZES_MAX_RAS_ERROR_CATEGORY_COUNT macro

Level Zero v1.5.8
~~~~~~~~~~~~~~~~~

* Infrastructure (Scripts)

  - Remove nullptr error code from params with mbz trait
  - Fix handling of mbz attributes
  - Fix ze_device_properties_t in samples

Level Zero v1.5.0
~~~~~~~~~~~~~~~~~

* Core Changes

  - Clarify that a context can also be used by sub-devices of devices
  - Add an extension for bfloat16 conversions
  - Relax restriction and allow ipc events with timestamps
  - Add an extension to return the device IP version
  - Move image view extension to standard
  - Fix off-by-one error for maximum memory allocation size
  - Add host support for IPC allocations
  - Add sub-allocations properties extensions
  - Clarify commands in an immediate command list may execute synchronously
  - Add additional default errors
  
* Tool Changes

  - Add a deprecation message for ZET_ENABLE_API_TRACING_EXP

* Sysman Changes

  - RAS Category and Fabric API
  - Remove out-of-date Sysman object hierarchy diagram
  - Mark zesPowerGetLimits and zesPowerSetLimits as deprecated
  - Separate APIs for initializing and enumerating sysman
  - Correct documentation for zesMemoryGetBandwidth


Level Zero v1.4.8
~~~~~~~~~~~~~~~~~

* Core Changes

  - Fix naming for some fabric extension function args.

* Sysman Changes

  - Remove const for _zes_power_limit_ext_desc_t ouput params.
  - Modify zes_power_level_t desc entry.
  - Add missing structure type enums.

Level Zero v1.4
~~~~~~~~~~~~~~~

* Core Changes

  - Fabric Topology Discovery API extension added.
  - Add detail to allocation access capabilities
  - Add an extension to the Core API for obtaining memory BW
  - Add clarifications for printf
  - Add extension for querying device locally unique identifier
  - Fix reordering of stypes
  - Standardize use of desc in SetEccState

Level Zero v1.3
~~~~~~~~~~~~~~~

* Core Changes

  - Add EU count extension.
  - Add clarification that link log may contain unresolved symbols
    after dynamic linking.
  - Add documentation for dynamic linking.
  - Add extension for linkage inspection.
  - Add extension for obtaining PCI BDF address.
  - Clarify programming guide section on command queues & command lists.
  - Correct documentation regarding maxMemoryFillPatternSize.
  - Clarify that pNext should be nullptr as default.
  - Clarify that unsupported structure types in pNext are ignored.
  - Add extension for image copy to/from memory that permits pitch
    within the memory buffer.
  - Add support for sRGB.
  - Clarify that zeInit needs to be called after forking processes.
  - Clarify barrier execution semantics for zeCommandListAppendBarrier.
  - Add an extension for querying image allocation properties.
  - Add an experimental extension to supply compression hints.

* Tools Changes

  - Add experimental extension for calculating multiple metrics.

Level Zero v1.2
~~~~~~~~~~~~~~~

* Core Changes

  - Added alloc flags for device and host initial placement.
  - Fix spec references.
  - Add clarification that SPIR-V import and export linkage types are
    used.
  - Add VPU to ze_device_type_t and ze_init_flags_t.
  - Add -ze-opt-level build option.
  - Add kernel scheduling hints experimental extension.
  - Add extended subgroups extension.
  - Add image view planar extension.
  - Add image view extension.
  - Add additional kernel preferred group size properties.
  - Add SPIR-V extension for linkonce-odr.
  - Add cache biasing flags for IPC handles.
  - Add documentation pages for extensions.
  - Add kernel scheduling hints for thread arbitration policy.
  - Add image memory properties experimental extension.
  - Add Event Query Timestamps experimental extension.
  - Fix compatibility issue device time resolution.
  - Add RGBP and BRGP image formats.

* Sysman

  - New return codes for low power state.

Level Zero v1.1
~~~~~~~~~~~~~~~

* Core Changes

  - Add code example for interop sharing, importing Linux dma_buf as
    an external memory handle for device allocation.
  - Clarify zeInit behavior regarding multiple calls with different
    flags or environment variables.
  - Add experimental extension for global work offset property to be
    set on kernel.
  - Update timeResolution units to double in device properties.
  - Added zeDeviceGetGlobalTimestamps to return synchronized host and
    device global timestamps.
  - Clarification on non-standard extensions via
    zeDriverGetExtensionFunctionAddress.
  - Clarifications for execution behavior for submitting multiple
    command lists
  - Add zeContextCreateEx to support context visibility for one or
    more device objects.
  - Specify that kernel state is not stored in thread-local storage by
    implementation.
  - Add float atomics extension to support additional floating point
    atomics capabilities.
  - Add extension to relax allocation limits and allow for allocations
    > 4GB.

* Sysman

  - Fix bug in fan spec. The fan configuration zes_fan_config_t should
    point to the table structure zes_fan_table_t instead of one
    temp/speed pair.

* Tools

  - Add page fault debug event ZE_DEBUG_EVENT_TYPE_PAGE_FAULT.
  - Clarification for metric group properties.
  - Remove phWaitEvents parameters from zetCommandListAppendMetricQueryEnd.
  
Level Zero v1.0
~~~~~~~~~~~~~~~

* Core Changes

  - Update command queue group properties to indicate numQueues is
    number of physical engines.
  - Clarify 'Get' parameters such that the pCount description is more
    clear to what is return in array.
  - Clarify metrics flag in ze_command_queue_group_property_flags_t.
  - Fix API documentation to indicate that pIpcProperties argument is
    [in,out] for GetIpcProperties.
  - Add experimental extension "ze_experimental_module_program" to
    support compiling and linking multiple SPIR-V modules together.
  - Updates to Raytracing extension.
  - Clean up Introduction documentation to remove reference to CSA and
    update ABI compatibility.
  - Fix PG documentation error for -g build flag in Module Build
    Options section.
  - Clarify in PG the default signal / wait event behavior.
  - Add cooperative kernel launch code snippet in PG.
  - Clarify that app must ensure the location in the pool is not being
    used by another event in zeEventCreate.

* Sysman

  - Update PG to describe that both min and max temperatures across
    sensors will be included in temp components.
  - Clarify fan configuration comment to indicate that fan temp/speeds
    are passed back as table.
  - Fixed comment showing how to calculate %allocated and %free memory
    in memory state structure.
  - Clean up ambiguous comments in the function and structures for
    scheduler and memory components.

* Tools

  - Fix wrong type in pseudo-code for API Tracing documentation.

Level Zero v0.95
~~~~~~~~~~~~~~~~

* Updates from implementation team.

Level Zero v0.91
~~~~~~~~~~~~~~~~

* Initial release
