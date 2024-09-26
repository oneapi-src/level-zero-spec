
:orphan:

.. _ZES_experimental_virtual_function_management:

========================================
 Virtual Function Management Extension
========================================

API
----

* Functions

    * :ref:`zesDeviceEnumEnabledVFExp`
    * :ref:`zesVFManagementGetVFCapabilitiesExp`
    * :ref:`zesVFManagementGetVFMemoryUtilizationExp`
    * :ref:`zesVFManagementGetVFEngineUtilizationExp`

* Enumerations

    * :ref:`zes-vf-management-exp-version-t`
   
* Structures

    * :ref:`zes-vf-exp-capabilities-t`
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
    :ref:`zes-vf-exp-capabilities-t` vfProps {};
    :ref:`zesDeviceEnumEnabledVFExp`\(hDevice, &numVf, nullptr);

    // Allocate memory for vf handles and call back in to gather handles
    std::vector<zes_vf_handle_t> vfs(numVf, nullptr);
    :ref:`zesDeviceEnumEnabledVFExp`\(hDevice, &numVf, vfs.data());

    // Gather VF properties
    std::vector <:ref:`zes-vf-exp-capabilities-t`\> vfProps(numVf);
    for (uint32_t i = 0; i < numVf; i++) {
        :ref:`zesVFManagementGetVFCapabilitiesExp`\(vfs[i], &vfProps[i]);
    }

    // Detect the info types a particular VF supports

    // Using VF# 0 to demonstrate how to detect engine info type and query engine util info
    zes_vf_handle_t activeVf = vfs[0];
    uint32_t engineStatCount = 0;
    
    :ref:`zesVFManagementGetVFEngineUtilizationExp`\(activeVf, &engineStatCount, nullptr);
    // Allocate memory for vf engine stats
    :ref:`zes-vf-util-engine-exp-t`\* engineStats0 = (:ref:`zes-vf-util-engine-exp-t`\*) allocate(engineStatCount * sizeof(:ref:`zes-vf-util-engine-exp-t`\));
    :ref:`zesVFManagementGetVFEngineUtilizationExp`\(activeVf, &engineStatCount, engineStats0);
    sleep(1)
    :ref:`zes-vf-util-engine-exp-t`\* engineStats1 = (:ref:`zes-vf-util-engine-exp-t`\*) allocate(engineStatCount * sizeof(:ref:`zes-vf-util-engine-exp-t`\));
    :ref:`zesVFManagementGetVFEngineUtilizationExp`\(activeVf, &engineStatCount, &engineStats1);