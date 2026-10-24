
:orphan:

.. _ZE_extension_device_npu_properties:

================================================
 NPU Device Properties Extension
================================================

.. rst-class:: ext-version

*Introduced in Level Zero version 1.18*

API
----

* Macros

    * ZE_DEVICE_NPU_PROPERTIES_EXT_NAME

* Enumerations

    * :ref:`ze-device-npu-properties-ext-version-t`

* Structures

    * :ref:`ze-device-npu-properties-ext-t`

NPU Device Properties
~~~~~~~~~~~~~~~~~~~~~~

:ref:`ze-device-npu-properties-ext-t` exposes NPU-native device properties with
no clean analogue in the GPU-oriented :ref:`ze-device-properties-t` base struct.
It is returned via the ``pNext`` member of :ref:`ze-device-properties-t` from
:ref:`zeDeviceGetProperties`\, and applies only when
:ref:`ze-device-properties-t`\.type is :ref:`ZE_DEVICE_TYPE_VPU <ze-device-type-t>`\.

The base :ref:`ze-device-properties-t` fields remain populated for backward
compatibility. New consumers should prefer the NPU-native fields in this
extension.

``int8x8MacsPerTile`` reports MACs per tile at INT8×INT8 baseline precision.
Throughput at other precisions: 2× for INT8×INT4, 0.5× for FP16×FP16,
0.5× for INT16×INT8, 1× for INT16×INT4.

``timestampFreqHz`` gives the device timestamp counter frequency in Hz,
used to convert raw device tick counts from :ref:`zeDeviceGetGlobalTimestamps`
and :ref:`zeCommandListAppendWriteGlobalTimestamp` into time durations.

``compilerVersion`` is packed with ``ZE_MAKE_VERSION``. Use
``ZE_MAJOR_VERSION`` and ``ZE_MINOR_VERSION`` to extract its components.

The following pseudo-code demonstrates querying NPU device properties:

.. parsed-literal::

       :ref:`ze-device-npu-properties-ext-t` npuProps = {};
       npuProps.stype = :ref:`ZE_STRUCTURE_TYPE_DEVICE_NPU_PROPERTIES_EXT <ze-structure-type-t>`\;
       npuProps.pNext = nullptr;

       :ref:`ze-device-properties-t` devProps = {};
       devProps.stype = :ref:`ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES <ze-structure-type-t>`\;
       devProps.pNext = &npuProps;

       :ref:`zeDeviceGetProperties`\(hDevice, &devProps);

       // NPU-native fields are now populated in npuProps
