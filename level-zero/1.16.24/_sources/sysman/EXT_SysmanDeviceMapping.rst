
:orphan:

.. _ZES_experimental_sysman_device_mapping:

=====================================
 Sysman Device mapping Extension
=====================================

API
----

* Functions

    * :ref:`zesDriverGetDeviceByUuidExp`
    * :ref:`zesDeviceGetSubDevicePropertiesExp`

* Enumerations

    * :ref:`zes-sysman-device-mapping-exp-version-t`

* Structures

    * :ref:`zes-subdevice-exp-properties-t`


Sysman Device Mapping
~~~~~~~~~~~~~~~~~~~~~

Three types of device hierarchy models FLAT, COMPOSITE and COMBINED are exposed by Level Zero driver implementation.
Core could use any model it needs for better performance, while SYSMAN keeps a uniform view of the system.

This extension is defined with intent to provide an interface to the user for mapping core device 
handle to sysman device or vice versa using UUID. 


The following pseudo-code demonstrates a sequence for querying the sub device properties
and also how to query sysman device handle from the UUID.

.. parsed-literal::

    // Query Sysman device handle corresponding to given UUID
    uint32_t subDeviceId = 0;
    bool onSubDevice = false;
    :ref:`zes-uuid-t` coreDeviceUuid;
    zes_device_handle_t* phDevice = (zes_device_handle_t*)allocate(sizeof(zes_device_handle_t));
    :ref:`zesDriverGetDeviceByUuidExp`\(pSysmanDriverHandle, coreDeviceUuid, phDevice, &subDeviceId, &onSubDevice);

    // Query for number of sub devices of the sysman device
    uint32_t subDeviceCount = 0;
    :ref:`zesDeviceGetSubDevicePropertiesExp`\(pSysmanDeviceHandle, &subDeviceCount, nullptr);

    :ref:`zes-subdevice-exp-properties-t`\* subDeviceProperties = (:ref:`zes-subdevice-exp-properties-t`\*) allocate(subDeviceCount * sizeof(:ref:`zes-subdevice-exp-properties-t`\));

    //Query sub device properties
    :ref:`zesDeviceGetSubDevicePropertiesExp`\(pSysmanDeviceHandle, &subDeviceCount, subDeviceProperties);

    // Print sub device property details
    for(uint32_t i = 0; i < subDeviceCount; i++) {
        output(" Sub Device Id : %lu \\n", subDeviceProperties[i]->subdeviceId);
        output("UUID : \\n");
        for (uint32_t j = 0; j < ZE_MAX_UUID_SIZE; j++) {
             output("%x  ",subDeviceProperties[i]->uuid.id[j]);
        }
        output("\\n");
    }

