
:orphan:

.. _ZES_extension_device_state:

============================
 Device State Extension
============================

API
----

* Enumerations
    * :ref:`zes-device-ext-state-version-t`
    * :ref:`zes-device-state-ext-flags-t`

* Structures

    * :ref:`zes-device-ext-state-t`


Device State
~~~~~~~~~~~~~~

This extension provides additional device state information beyond the basic reset and repair status
available through the standard :ref:`zesDeviceGetState` API. The extension allows applications to query
extended device states including wedged condition, survivability mode, and flash override status.

The :ref:`zes-device-ext-state-t` structure can be passed via the pNext chain of :ref:`zes-device-state-t` to
retrieve these additional state flags.

Multiple flags may be set simultaneously if the device is in multiple states.

Usage Example
~~~~~~~~~~~~~

.. parsed-literal::

    // Query basic device state
    :ref:`zes-device-state-t` deviceState = {};
    deviceState.stype = :ref:`ZES_STRUCTURE_TYPE_DEVICE_STATE <zes-structure-type-t>`\;
    deviceState.pNext = nullptr;
    
    // Add extended state structure to pNext chain
    :ref:`zes-device-ext-state-t` extendedState = {};
    extendedState.stype = :ref:`ZES_STRUCTURE_TYPE_DEVICE_EXT_STATE <zes-structure-type-t>`\;
    extendedState.pNext = nullptr;
    deviceState.pNext = &extendedState;
    
    // Get device state including extended flags
    :ref:`zesDeviceGetState`\(hDevice, &deviceState);
    
    // Check extended device state flags
    if (extendedState.flags & :ref:`ZES_DEVICE_STATE_EXT_FLAG_WEDGED <zes-device-state-ext-flags-t>`\) {
        // Device is wedged - recovery action needed
    }
    
    if (extendedState.flags & :ref:`ZES_DEVICE_STATE_EXT_FLAG_SURVIVABILITY <zes-device-state-ext-flags-t>`\) {
        // Device is in survivability mode
    }
    
    if (extendedState.flags & :ref:`ZES_DEVICE_STATE_EXT_FLAG_FLASH_OVERRIDE <zes-device-state-ext-flags-t>`\) {
        // Device has flash override enabled
    }
