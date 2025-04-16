
:orphan:

.. _ZE_extension_device_vector_sizes:

=======================================================
 Device Vector Sizes Query Extension
=======================================================

API
----

* Enumerations
    * :ref:`ze-device-vector-sizes-ext-version-t`

* Structures
    * :ref:`ze-device-vector-width-properties-ext-t`

* Functions
    * :ref:`zeDeviceGetVectorWidthPropertiesExt`

Summary:
~~~~~~~~~~~~~~~~~~~~~~

This extension provides a mechanism to query all the supported vector sizes for the given device. Users can use this query to allow them to choose the best vector size for each data type for their kernels.
The call to :ref:`zeDeviceGetVectorWidthPropertiesExt` returns list(s) of preferred/native vector sizes matched with the vector width supported on the device.
The first index in the array for the vector sizes will be for the largest vector width supported by the device. 
Example: a device with SIMD support of 16, 8, will report the preferred vector sizes for 16 first and then 8.

Example usecase:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. parsed-literal::
    :ref:`zeDeviceGetVectorWidthPropertiesExt`\(hDevice, &pCount, nullptr);
    std::vector<:ref:`ze-device-vector-width-properties-ext-t`\> vectorWidthProps(pCount);
    for (auto& vectorWidthProp : vectorWidthProps) {
        vectorWidthProp.stype = :ref:`ZE_STRUCTURE_TYPE_DEVICE_VECTOR_WIDTH_PROPERTIES_EXT <ze-structure-type-t>`\;
        vectorWidthProp.pNext = nullptr;
    }
    :ref:`zeDeviceGetVectorWidthPropertiesExt`\(hDevice, &pCount, vectorWidthProps.data());
