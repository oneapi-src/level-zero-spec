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

.. _ZES_extension_device_health:

===========================
 Device Health Extension
===========================

API
----

* Enumerations

    * ${s}_device_health_status_ext_t
    * ${s}_device_health_ext_version_t

* Functions

    * ${s}DeviceGetHealthStatusExt
    * ${s}DeviceSetHealthStatusExt

Device Health Overview
~~~~~~~~~~~~~~~~~~~~~~

Device health represents a comprehensive assessment of a device's reliability and expected performance in upcoming operations. 
The health status is stored in non-volatile memory (NVM) and persists across device resets and firmware updates.

Example Usage
~~~~~~~~~~~~~

**Query Current Health Status:**

.. parsed-literal::

    ${s}_device_health_status_ext_t health;
    ${x}_result_t result = ${s}DeviceGetHealthStatusExt(hDevice, &health);
    
    if (result == ${X}_RESULT_SUCCESS) {
        switch (health) {
            case ${S}_DEVICE_HEALTH_STATUS_EXT_OK:
                // Device is healthy with no known issues
                break;
            case ${S}_DEVICE_HEALTH_STATUS_EXT_WARNING:
                // Device may have issues, diagnostics recommended
                break;
            case ${S}_DEVICE_HEALTH_STATUS_EXT_CRITICAL:
                // Device should not be used until maintenance is performed
                break;
            case ${S}_DEVICE_HEALTH_STATUS_EXT_FAILED:
                // Permanent non-recoverable failure; FRU replacement required
                break;
        }
    }

**Set Health Status:**

.. parsed-literal::

    // After running diagnostics and confirming device is healthy
    ${x}_result_t result = ${s}DeviceSetHealthStatusExt(hDevice, ${S}_DEVICE_HEALTH_STATUS_EXT_OK);
    
    if (result == ${X}_RESULT_ERROR_INSUFFICIENT_PERMISSIONS) {
        // User does not have permissions to set health status
    }