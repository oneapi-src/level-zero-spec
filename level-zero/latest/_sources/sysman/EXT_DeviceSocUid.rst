
:orphan:

.. _ZES_extension_device_soc_uid:

===================================
 Device SOC Unique ID Extension
===================================

.. rst-class:: ext-version

*Introduced in Level Zero version 1.21*

API
----
* Enumerations

    * :ref:`zes-device-soc-uid-ext-version-t`

* Structures

    * :ref:`zes-device-soc-uid-ext-properties-t`

* Macros

    * ZES_DEVICE_SOC_UID_EXT_NAME

Device SOC Unique ID Overview
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Device SOC Unique ID extension provides the ability to query the unique ID
of the SOC on which the device resides.

Applications can retrieve this property by passing the extension structure via
the pNext chain when calling :ref:`zesDeviceGetProperties`\. If the SOC unique ID
cannot be determined for the device, it will be set to all zeroes.

Querying the SOC Unique ID
~~~~~~~~~~~~~~~~~~~~~~~~~~

The following pseudo-code demonstrates the usage pattern for querying the SOC
unique ID of the device.

.. parsed-literal::

    // Query device properties with the device SOC unique ID extension
    :ref:`zes-device-properties-t` deviceProps = {};
    deviceProps.stype = :ref:`ZES_STRUCTURE_TYPE_DEVICE_PROPERTIES <zes-structure-type-t>`\;

    :ref:`zes-device-soc-uid-ext-properties-t` socUidProps = {};
    socUidProps.stype = :ref:`ZES_STRUCTURE_TYPE_DEVICE_SOC_UID_EXT_PROPERTIES <zes-structure-type-t>`\;
    socUidProps.pNext = nullptr;

    deviceProps.pNext = &socUidProps;

    :ref:`zesDeviceGetProperties`\(hDevice, &deviceProps);

    output("SOC unique ID: ");
    for (uint32_t i = 0; i < ZES_MAX_UUID_SIZE; i++) {
        output("%02x", socUidProps.socUid.id[i]);
    }
    output("\\n");
