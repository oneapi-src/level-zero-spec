<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
    s=tags['$s']
    S=s.upper()
%>
:orphan:

.. _ZES_extension_device_state:

============================
 Device State Extension
============================

API
----

* Enumerations
    * ${s}_device_ext_state_version_t
    * ${s}_device_state_ext_flags_t

* Structures

    * ${s}_device_ext_state_t


Device State
~~~~~~~~~~~~~~

This extension provides additional device state information beyond the basic reset and repair status
available through the standard ${s}DeviceGetState API. The extension allows applications to query
extended device states including wedged condition, survivability mode, and flash override status.

The ${s}_device_ext_state_t structure can be passed via the pNext chain of ${s}_device_state_t to
retrieve these additional state flags.

Multiple flags may be set simultaneously if the device is in multiple states.

Usage Example
~~~~~~~~~~~~~

.. parsed-literal::

    // Query basic device state
    ${s}_device_state_t deviceState = {};
    deviceState.stype = ${S}_STRUCTURE_TYPE_DEVICE_STATE;
    deviceState.pNext = nullptr;
    
    // Add extended state structure to pNext chain
    ${s}_device_ext_state_t extendedState = {};
    extendedState.stype = ${S}_STRUCTURE_TYPE_DEVICE_EXT_STATE;
    extendedState.pNext = nullptr;
    deviceState.pNext = &extendedState;
    
    // Get device state including extended flags
    ${s}DeviceGetState(hDevice, &deviceState);
    
    // Check extended device state flags
    if (extendedState.flags & ${S}_DEVICE_EXT_STATE_FLAGS_WEDGED) {
        // Device is wedged - recovery action needed
    }
    
    if (extendedState.flags & ${S}_DEVICE_EXT_STATE_FLAGS_SURVIVABILITY) {
        // Device is in survivability mode
    }
    
    if (extendedState.flags & ${S}_DEVICE_EXT_STATE_FLAGS_FLASH_OVERRIDE) {
        // Device has flash override enabled
    }
