
:orphan:

.. _ZES_extension_device_ecc_default_properties:

=========================================
 Device-ECC default properties Extension
=========================================

API
----

* Structures

    * :ref:`zes-device-ecc-default-properties-ext-t`

Device-ECC properties
~~~~~~~~~~~~~~~~~~~~~

By default, {s}DeviceGetEccState returns the current state of the ECC counters.

Additionally to get default ECC state, pass :ref:`zes-device-ecc-default-properties-ext-t` to {s}DeviceGetEccState as pNext member of :ref:`zes-device-ecc-properties-t`\.

.. parsed-literal::

    :ref:`zes-device-ecc-properties-t` getState = {:ref:`ZES_STRUCTURE_TYPE_DEVICE_ECC_PROPERTIES <zes-structure-type-t>`\};
    :ref:`zes-device-ecc-default-properties-ext-t` ext = {:ref:`ZES_STRUCTURE_TYPE_DEVICE_ECC_DEFAULT_PROPERTIES_EXT <zes-structure-type-t>`\};
    getState.pNext = &ext;
    :ref:`ze-result-t` = :ref:`zesDeviceGetEccState`\(device, &getState);

