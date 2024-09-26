
:orphan:

.. _ZES_experimental_virtual_function_management:

========================================
 Virtual Function Management Extension
========================================

API
----

* Functions

    * :ref:`zesDeviceEnumActiveVFExp`
    * :ref:`zesVFManagementGetVFPropertiesExp`
    * :ref:`zesVFManagementGetVFMemoryUtilizationExp`
    * :ref:`zesVFManagementGetVFEngineUtilizationExp`
    * :ref:`zesVFManagementSetVFTelemetryModeExp`
    * :ref:`zesVFManagementSetVFTelemetrySamplingIntervalExp`

* Enumerations

    * :ref:`zes-vf-management-exp-version-t`
    * :ref:`zes-vf-info-mem-type-exp-flags-t`
    * :ref:`zes-vf-info-util-exp-flags-t`
   
* Structures

    * :ref:`zes-vf-exp-properties-t`
    * :ref:`zes-vf-util-mem-exp-t`
    * :ref:`zes-vf-util-engine-exp-t`
   
Virtual Function Management
~~~~~~~~~~~~~~~~~~~~~~~~~~~
This feature adds the ability to retrieve telemetry from PF domain for monitoring per VF memory and engine utilization. 
This telemetry is used to determine if a VM has oversubscribed GPU memory or observe engine business for a targeted workload.
If VF has no activity value to report, then implementation shall reflect that appropriately in :ref:`zes-vf-util-engine-exp-t` struct so that percentage
calculation results in value of 0.

The following pseudo-code demonstrates a sequence for obtaining the engine activity for all Virtual Functions from Physical Function environment:

.. parsed-literal::

    // Gather count of VF handles
    uint32_t numVf = 0;
    :ref:`zes-vf-exp-properties-t` vfProps {};
    :ref:`zesDeviceEnumActiveVFExp`\(hDevice, &numVf, nullptr);

    // Allocate memory for vf handles and call back in to gather handles
    std::vector<zes_vf_handle_t> vfs(numVf, nullptr);
    :ref:`zesDeviceEnumActiveVFExp`\(hDevice, &numVf, vfs.data());

    // Gather VF properties
    std::vector <:ref:`zes-vf-exp-properties-t`\> vfProps(numVf);
    for (uint32_t i = 0; i < numVf; i++) {
        :ref:`zesVFManagementGetVFPropertiesExp`\(vfs[i], &vfProps[i]);
    }

    // Detect the info types a particular VF supports

    // Using VF# 0 to demonstrate how to detect engine info type and query engine util info
    zes_vf_handle_t activeVf = vfs[0];
    uint32_t count = 1;
    if (vfProps[0].flags & ZES_VF_INFO_ENGINE) {
        :ref:`zes-vf-util-engine-exp-t` engineUtil0 = {};
        :ref:`zesVFManagementGetVFEngineUtilizationExp`\(activeVf, &count, &engineUtil0);
        sleep(1)
        :ref:`zes-vf-util-engine-exp-t` engineUtil1 = {};
        :ref:`zesVFManagementGetVFEngineUtilizationExp`\(activeVf, &count, &engineUtil1);
        // Use formula to calculate engine utilization % based on the 2 snapshots above
    }

    // Demonstrate using setter to switch off Engine telemetry for VF0 and then check if Getter returns INVALID
    :ref:`zesVFManagementSetVFTelemetryModeExp`\(activeVf,  ZES_VF_INFO_ENGINE, false); 
    :ref:`ze-result-t` res = :ref:`zesVFManagementGetVFEngineUtilizationExp`\(activeVf, &count, &engineUtil0);
    if (res != ZES_RESULT_SUCCESS) {
        printf("Engine utilization successfully disabled for VF");
    }
