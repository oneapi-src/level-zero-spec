<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_device_npu_properties:

================================================
 NPU Device Properties Extension
================================================

API
----

* Macros

    * ${X}_DEVICE_NPU_PROPERTIES_EXT_NAME

* Enumerations

    * ${x}_device_npu_properties_ext_version_t

* Structures

    * ${x}_device_npu_properties_ext_t

NPU Device Properties
~~~~~~~~~~~~~~~~~~~~~~

${x}_device_npu_properties_ext_t exposes NPU-native device properties with
no clean analogue in the GPU-oriented ${x}_device_properties_t base struct.
It is returned via the ``pNext`` member of ${x}_device_properties_t from
${x}DeviceGetProperties, and applies only when
${x}_device_properties_t.type is ${X}_DEVICE_TYPE_VPU.

The base ${x}_device_properties_t fields remain populated for backward
compatibility. New consumers should prefer the NPU-native fields in this
extension.

``int8x8MacsPerTile`` reports MACs per tile at INT8×INT8 baseline precision.
Throughput at other precisions: 2× for INT8×INT4, 0.5× for FP16×FP16,
0.5× for INT16×INT8, 1× for INT16×INT4.

``timestampFreqHz`` gives the device timestamp counter frequency in Hz,
used to convert raw device tick counts from ${x}DeviceGetGlobalTimestamps
and ${x}CommandListAppendWriteGlobalTimestamp into time durations.

The following pseudo-code demonstrates querying NPU device properties:

.. parsed-literal::

       ${x}_device_npu_properties_ext_t npuProps = {};
       npuProps.stype = ${X}_STRUCTURE_TYPE_DEVICE_NPU_PROPERTIES_EXT;
       npuProps.pNext = nullptr;

       ${x}_device_properties_t devProps = {};
       devProps.stype = ${X}_STRUCTURE_TYPE_DEVICE_PROPERTIES;
       devProps.pNext = &npuProps;

       ${x}DeviceGetProperties(hDevice, &devProps);

       // NPU-native fields are now populated in npuProps
