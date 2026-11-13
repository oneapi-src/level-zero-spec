
:orphan:

.. _ZES_extension_device_index:

=============================
 Device Index Extension
=============================

.. rst-class:: ext-version

*Introduced in Level Zero version 1.20*

API
----
* Enumerations

    * :ref:`zes-device-index-ext-version-t`

* Structures

    * :ref:`zes-device-index-ext-properties-t`

* Macros

    * ZES_DEVICE_INDEX_EXT_NAME

Device Index Overview
~~~~~~~~~~~~~~~~~~~~~

The Device Index extension provides the ability to query the device index (GPU ID),
an integer identifier for a Sysman device handle.

Applications can retrieve the device index by passing the extension structure via
the pNext chain when querying device properties.

The device index is set at :ref:`zesInit`\(), subsequent calls may add new devices but will
not change existing indexes. To identify a device across processes or reboots, it is
recommended that devices be looked up by their PCI IDs or UUID.

The following pseudo-code demonstrates the usage pattern for querying the device index.

**Querying Device Index**

.. parsed-literal::

    // Query device properties with device index extension
    :ref:`zes-device-properties-t` deviceProps = {};
    deviceProps.stype = :ref:`ZES_STRUCTURE_TYPE_DEVICE_PROPERTIES <zes-structure-type-t>`\;

    :ref:`zes-device-index-ext-properties-t` deviceIndexProps = {};
    deviceIndexProps.stype = :ref:`ZES_STRUCTURE_TYPE_DEVICE_INDEX_EXT_PROPERTIES <zes-structure-type-t>`\;
    deviceIndexProps.pNext = nullptr;

    deviceProps.pNext = &deviceIndexProps;

    if (:ref:`zesDeviceGetProperties`\(hDevice, &deviceProps) == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\) {
        output("Device Index: %u\\n", deviceIndexProps.deviceIndex);
    }
