
:orphan:

.. _ZES_extension_engine_activity:

==========================
 Engine Activity Extension
==========================

API
----

* Functions

    * :ref:`zesEngineGetActivityExt`

* Structures

    * :ref:`zes-engine-ext-properties-t`

Engine Activity
~~~~~~~~~~~~~~~~~~

This extension provides capability to user to gather the activity stats for each Virtual Function (VF) associated with engine group.
Intended use case of the feature is to query utilization stats from Physical Function (PF) interface. However, the extension
may return error code :ref:`ZE_RESULT_ERROR_UNSUPPORTED_FEATURE <ze-result-t>` if an environment does not support it.
If VF has no activity value to report, then implementation shall reflect that appropriately in :ref:`zes-engine-stats-t` struct so that percentage
calculation results in value of 0.
If PF has no activity value to report, then implementation shall reflect that appropriately in :ref:`zes-engine-stats-t` struct which is
at index 0 of the output vector such that utilization calculation results in value of 0.

The following pseudo-code demonstrates a sequence for obtaining the engine activity for all Virtual Functions from Physical Function environment:

.. parsed-literal::

    // Query for engine properties and gather number of virtual function instances by passing extension structure.
    // Number of VFs is per engine handle and equates to number of VFs actively using
    // the resource represented by the engine handle.
    // Together with pCount from GetActivityExt, user can gather the full view of engine
    // utilization for all VFs and PF as shown below

    :ref:`zes-engine-properties-t` engineProps;
    :ref:`zes-engine-ext-properties-t` engineExtProps;
    engineProps.stype = ZES_STRUCTURE_TYPE_ENGINE_PROPERTIES;
    engineProps.pNext = &engineExtProps;
    engineExtProps.stype = ZES_STRUCTURE_TYPE_ENGINE_EXT_PROPERTIES;

    :ref:`zesEngineGetProperties`\(hEngine, &engineProps);

    // Query count of engine stats to gather
    // this count is inclusive of PF and N number of VFs
    // i.e. if engineStatCount = 4, then this implies, one PF engine stat at index 0
    //      of output vector followed by engine stats for 3 VFs
    uint32_t engineStatCount = 0;
    {s}EngineGetActivityExt(hEngine, &engineStatCount, nullptr);

    // Gather engine stats for all VFs and PF.
    // Gather two snapshots of engine activity and calculate percentage
    // utilization per formula in :ref:`zes-engine-stats-t`
    :ref:`zes-engine-stats-t`\* engineStats0 = (:ref:`zes-engine-stats-t`\*) allocate(engineStatCount * sizeof(:ref:`zes-engine-stats-t`\));
    {s}EngineGetActivityExt(hEngine, &engineStatCount, engineStats0);
    sleep(1);
    :ref:`zes-engine-stats-t`\* engineStats1 = (:ref:`zes-engine-stats-t`\*) allocate(engineStatCount * sizeof(:ref:`zes-engine-stats-t`\));
    {s}EngineGetActivityExt(hEngine, &engineStatCount, engineStats1);

    for (uint32_t idx = 0; idx < engineStatCount; ++idx) {
        double utilization = (engineStats1[idx].activeTime - engineStats0[idx].activeTime)/(engineStats1[idx].timestamp - engineStats0[idx].timestamp);
        output("%s Utilization of engine type pertaining to this handle = %.2f\n", (idx == 0) ? "PF" : "VF", utilization);
    }
