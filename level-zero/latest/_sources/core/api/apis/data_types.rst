============================================================
Data Types
============================================================
oneAPI Level Zero Specification - Version 1.21.26






Data Types Enums
================


.. _ze-result-t:

ze_result_t
-----------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenenum:: ze_result_t
    :project: LevelZero


.. _ze-structure-type-t:

ze_structure_type_t
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenenum:: ze_structure_type_t
    :project: LevelZero


.. _ze-external-memory-type-flags-t:

ze_external_memory_type_flags_t
-------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-device-external-memory-properties-t`, :ref:`ze-external-memory-export-desc-t`, :ref:`ze-external-memory-import-fd-t`, :ref:`ze-external-memory-export-fd-t`, :ref:`ze-external-memory-import-win32-handle-t`, :ref:`ze-external-memory-export-win32-handle-t`

.. doxygentypedef:: ze_external_memory_type_flags_t
    :project: LevelZero

.. doxygenenum:: ze_external_memory_type_flag_t
    :project: LevelZero


.. _ze-bandwidth-unit-t:

ze_bandwidth_unit_t
-------------------

.. rst-class:: api-version

*Added in version 1.4*

.. container:: api-usage

   | **Member of:** :ref:`ze-device-p2p-bandwidth-exp-properties-t`, :ref:`ze-copy-bandwidth-exp-properties-t`, :ref:`ze-fabric-edge-exp-properties-t`, :ref:`ze-device-memory-ext-properties-t`

.. doxygenenum:: ze_bandwidth_unit_t
    :project: LevelZero


.. _ze-latency-unit-t:

ze_latency_unit_t
-----------------

.. rst-class:: api-version

*Added in version 1.4*

.. container:: api-usage

   | **Member of:** :ref:`ze-device-p2p-bandwidth-exp-properties-t`, :ref:`ze-fabric-edge-exp-properties-t`

.. doxygenenum:: ze_latency_unit_t
    :project: LevelZero


.. _ze-device-ip-version-version-t:

ze_device_ip_version_version_t
------------------------------

.. rst-class:: api-version

*Added in version 1.5*

.. container:: api-usage

   | **Extension:** :ref:`ZE_extension_device_ip_version`

.. doxygenenum:: ze_device_ip_version_version_t
    :project: LevelZero


.. _ze-device-compiler-info-t:

ze_device_compiler_info_t
-------------------------

.. rst-class:: api-version

*Added in version 1.18*

.. container:: api-usage

   | **Used by:** :ref:`zeDeviceGetCompilerInfo`, :ref:`zeDeviceGetCompilerInfoSupported`

.. doxygenenum:: ze_device_compiler_info_t
    :project: LevelZero


Data Types Typedefs
===================


.. _ze-bool-t:

ze_bool_t
---------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygentypedef:: ze_bool_t
    :project: LevelZero

 
Data Types Structures
=====================


.. _ze-ipc-mem-handle-t:

ze_ipc_mem_handle_t
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zeMemGetIpcHandle`, :ref:`zeMemGetIpcHandleFromFileDescriptorExp`, :ref:`zeMemGetIpcHandleWithProperties`
   | **Used by:** :ref:`zeMemGetFileDescriptorFromIpcHandleExp`, :ref:`zeMemPutIpcHandle`, :ref:`zeMemOpenIpcHandle`

.. doxygenstruct:: ze_ipc_mem_handle_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-ipc-event-pool-handle-t:

ze_ipc_event_pool_handle_t
--------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zeEventPoolGetIpcHandle`
   | **Used by:** :ref:`zeEventPoolPutIpcHandle`, :ref:`zeEventPoolOpenIpcHandle`

.. doxygenstruct:: ze_ipc_event_pool_handle_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-uuid-t:

ze_uuid_t
---------

.. rst-class:: api-version

*Added in version 1.4*

.. container:: api-usage

   | **Member of:** :ref:`ze-fabric-vertex-exp-properties-t`, :ref:`ze-fabric-edge-exp-properties-t`

.. doxygenstruct:: ze_uuid_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-base-cb-params-t:

ze_base_cb_params_t
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenstruct:: ze_base_cb_params_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-base-properties-t:

ze_base_properties_t
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenstruct:: ze_base_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-base-desc-t:

ze_base_desc_t
--------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeCommandListAppendSignalEventWithParameters`, :ref:`zeCommandListAppendWaitOnEventsWithParameters`, :ref:`zeCommandListAppendLaunchKernelWithParameters`, :ref:`zeCommandListAppendLaunchKernelWithArguments`

.. doxygenstruct:: ze_base_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-ipc-event-counter-based-handle-t:

ze_ipc_event_counter_based_handle_t
-----------------------------------

.. rst-class:: api-version

*Added in version 1.15*

.. container:: api-usage

   | **Obtained from:** :ref:`zeEventCounterBasedGetIpcHandle`
   | **Used by:** :ref:`zeEventCounterBasedOpenIpcHandle`

.. doxygenstruct:: ze_ipc_event_counter_based_handle_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-driver-uuid-t:

ze_driver_uuid_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-driver-properties-t`

.. doxygenstruct:: ze_driver_uuid_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-device-uuid-t:

ze_device_uuid_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-device-properties-t`

.. doxygenstruct:: ze_device_uuid_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-kernel-uuid-t:

ze_kernel_uuid_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-kernel-properties-t`

.. doxygenstruct:: ze_kernel_uuid_t
    :project: LevelZero
    :members:
    :undoc-members:

