
:orphan:

.. _ZES_extension_oem_serial_id:

=============================
 OEM Serial ID Extension
=============================

API
----
* Enumerations

    * :ref:`zes-oem-serial-id-ext-version-t`
   
* Structures

    * :ref:`zes-oem-serial-id-ext-properties-t`

* Macros

    * ZES_OEM_SERIAL_ID_SIZE

OEM Serial ID Overview
~~~~~~~~~~~~~~~~~~~~~~

The OEM Serial ID extension provides the ability to query the OEM-assigned serial ID
of the device. This serial ID is typically programmed during device manufacturing and
uniquely identifies the specific device hardware.

Applications can retrieve the OEM serial ID by passing the extension structure via the 
pNext chain when querying device properties. If the serial ID cannot be determined,
the string will not be populated and the length will be 0.

The following pseudo-code demonstrates the usage pattern for querying the OEM serial ID.

**Querying OEM Serial ID**

.. parsed-literal::

    // Query device properties with OEM serial ID extension
    :ref:`zes-device-properties-t` deviceProps = {};
    deviceProps.stype = :ref:`ZES_STRUCTURE_TYPE_DEVICE_PROPERTIES <zes-structure-type-t>`\;
    
    :ref:`zes-oem-serial-id-ext-properties-t` serialIdProps = {};
    serialIdProps.stype = :ref:`ZES_STRUCTURE_TYPE_OEM_SERIAL_ID_EXT_PROPERTIES <zes-structure-type-t>`\;
    serialIdProps.pNext = nullptr;
    
    deviceProps.pNext = &serialIdProps;
    
    :ref:`zesDeviceGetProperties`\(hDevice, &deviceProps);
    
    // Check if serial ID was successfully retrieved
    if (serialIdProps.length != 0) {
        output("OEM Serial ID: %s\\n", serialIdProps.oemSerialId);
        output("Serial ID Length: %u\\n", serialIdProps.length);
    } else {
        output("OEM serial ID not available for this device\\n");
    }