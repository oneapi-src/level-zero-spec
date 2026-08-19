
:orphan:

.. _ZES_extension_device_health:

===========================
 Device Health Extension
===========================

.. rst-class:: ext-version

*Introduced in Level Zero version 1.18*

API
----

* Enumerations

    * :ref:`zes-device-health-status-ext-t`
    * :ref:`zes-device-health-ext-version-t`

* Functions

    * :ref:`zesDeviceGetHealthStatusExt`
    * :ref:`zesDeviceSetHealthStatusExt`

Device Health Overview
~~~~~~~~~~~~~~~~~~~~~~

Device health represents a comprehensive assessment of a device's reliability and expected performance in upcoming operations. 
The health status is stored in non-volatile memory (NVM) and persists across device resets and firmware updates.

Example Usage
~~~~~~~~~~~~~

**Query Current Health Status:**

.. parsed-literal::

    :ref:`zes-device-health-status-ext-t` health;
    :ref:`ze-result-t` result = :ref:`zesDeviceGetHealthStatusExt`\(hDevice, &health);
    
    if (result == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\) {
        switch (health) {
            case :ref:`ZES_DEVICE_HEALTH_STATUS_EXT_OK <zes-device-health-status-ext-t>`\:
                // Device is healthy with no known issues
                break;
            case :ref:`ZES_DEVICE_HEALTH_STATUS_EXT_WARNING <zes-device-health-status-ext-t>`\:
                // Device may have issues, diagnostics recommended
                break;
            case :ref:`ZES_DEVICE_HEALTH_STATUS_EXT_CRITICAL <zes-device-health-status-ext-t>`\:
                // Device should not be used until maintenance is performed
                break;
            case :ref:`ZES_DEVICE_HEALTH_STATUS_EXT_FAILED <zes-device-health-status-ext-t>`\:
                // Permanent non-recoverable failure; FRU replacement required
                break;
        }
    }

**Set Health Status:**

.. parsed-literal::

    // After running diagnostics and confirming device is healthy
    :ref:`ze-result-t` result = :ref:`zesDeviceSetHealthStatusExt`\(hDevice, :ref:`ZES_DEVICE_HEALTH_STATUS_EXT_OK <zes-device-health-status-ext-t>`\);
    
    if (result == :ref:`ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS <ze-result-t>`\) {
        // User does not have permissions to set health status
    }