<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_device_vector_sizes:

=======================================================
 Device Vector Sizes Query Extension
=======================================================

API
----

* Enumerations
    * ${x}_device_vector_sizes_ext_version_t

* Structures
    * ${x}_device_vector_width_properties_ext_t

* Functions
    * ${x}DeviceGetVectorWidthPropertiesExt

Summary:
~~~~~~~~~~~~~~~~~~~~~~

This extension provides a mechanism to query all the supported vector sizes for the given device. Users can use this query to allow them to choose the best vector size for each data type for their kernels.
The call to ${x}DeviceGetVectorWidthPropertiesExt returns list(s) of preferred/native vector sizes matched with the vector width supported on the device.
The first index in the array for the vector sizes will be for the largest vector width supported by the device. 
Example: a device with SIMD support of 16, 8, will report the preferred vector sizes for 16 first and then 8.

Example usecase:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. parsed-literal::
    ${x}DeviceGetVectorWidthPropertiesExt(hDevice, &pCount, nullptr);
    std::vector<${x}_device_vector_width_properties_ext_t> vectorWidthProps(pCount);
    for (auto& vectorWidthProp : vectorWidthProps) {
        vectorWidthProp.stype = ${X}_STRUCTURE_TYPE_DEVICE_VECTOR_WIDTH_PROPERTIES_EXT;
        vectorWidthProp.pNext = nullptr;
    }
    ${x}DeviceGetVectorWidthPropertiesExt(hDevice, &pCount, vectorWidthProps.data());
