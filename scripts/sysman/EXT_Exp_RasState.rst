<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    s=tags['$s']
    S=s.upper()
%>
:orphan:

.. _ZES_extension_ras_state:

========================
 RAS Get State Extension
========================

API
----

* Functions

    * ${s}RasGetStateExp

* Enumerations

    * ${s}_ras_state_exp_version_t
    * ${s}_ras_error_category_exp_t

* Structures

    * ${s}_ras_state_exp_t


RAS State
~~~~~~~~~~~

Reliability, Availability, Serviceability (RAS) is a standard mechanism to report HW errors.
In L0 Sysman, we report these errors via RAS API and organized into Correctable or Uncorrectable
errors. Furthermore, the errors can be grouped by category so that source of the error
is easily identifiable.

This extension is defined with intent to provide an extensible interface to the user for discovering
these errors. A separate function is provided to allow users to clear the error counters.
This functionality extends and is intended to eventually replace existing mechanism via ${s}RasGetState.

To that end, this extension also adds new enumerator for RAS error categories. The list of error categories
include existing ones (refer to the Sysman Programming guide) and also additional ones which are defined here.
The additional error categories are listed below: 

================================================================================== ============================================================= =======================================
Error category                                                                     ${S}_RAS_ERROR_TYPE_CORRECTABLE   ${S}_RAS_ERROR_TYPE_UNCORRECTABLE
================================================================================== ============================================================= =======================================
 ${S}_RAS_ERROR_CATEGORY_EXP_MEMORY_ERRORS        Number of ECC correctable errors                            Number of ECC uncorrectable errors
                                                  that have occurred in memory -                              that have occurred in memory -
                                                  GDDR/HBM.                                                   GDDR/HBM.
 ${S}_RAS_ERROR_CATEGORY_EXP_SCALE_ERRORS         Number of correctable errors                                Number of ECC uncorrectable errors
                                                  that have occurred in scale IP                              that have occurred in scale IP
 ${S}_RAS_ERROR_CATEGORY_EXP_L3FABRIC_ERRORS      Number of ECC correctable errors                            Number of ECC uncorrectable errors
                                                  that have occurred in L3 fabric                             that have occurred in L3 fabric
================================================================================== ============================================================= =======================================

The following pseudo-code demonstrates a sequence for querying the number of error categories
supported by a platform and for obtaining the error counters for these categories.

.. parsed-literal::

    // Query for number of error categories supported by platform
    uint32_t rasCategoryCount = 0;
    {s}RasGetStateExp(rasHandle, &rasCategoryCount, nullptr);

    ${s}_ras_state_exp_t* rasStates = (${s}_ras_state_exp_t*) allocate(rasCategoryCount * sizeof(${s}_ras_state_exp_t));

    //Gather error states
    {s}RasGetStateExp(rasHandle, &rasCategoryCount, rasStates);

    // Print error details
    for(uint32_t i = 0; i < rasCategoryCount; i++) {
        output(" Error category: %d, Error count: %llun \n", rasStates[i]->category, rasStates[i]->errorCounter);
    }

    // Clear error counter for specific category, for example PROGRAMMING_ERRORS
    {s}RasClearStateExp(rasHandle, ZES_RAS_ERROR_CAT_PROGRAMMING_ERRORS);
