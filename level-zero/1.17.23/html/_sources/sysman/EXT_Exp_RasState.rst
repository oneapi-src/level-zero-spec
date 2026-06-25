
:orphan:

.. _ZES_extension_ras_state:

========================
 RAS Get State Extension
========================

API
----

* Functions

    * :ref:`zesRasGetStateExp`
    * :ref:`zesRasClearStateExp`
    * :ref:`zesRasGetSupportedCategoriesExp`
    * :ref:`zesRasGetStateExp2`

* Enumerations

    * :ref:`zes-ras-state-exp-version-t`
    * :ref:`zes-ras-error-category-exp-t`

* Structures

    * :ref:`zes-ras-state-exp-t`
    * :ref:`zes-ras-state-exp2-t`


RAS State
~~~~~~~~~~~

Reliability, Availability, Serviceability (RAS) is a standard mechanism to report HW errors.
In L0 Sysman, we report these errors via RAS API and organized into Correctable or Uncorrectable
errors. Furthermore, the errors can be grouped by category so that source of the error
is easily identifiable.

This extension is defined with intent to provide an extensible interface to the user for discovering
these errors. A separate function is provided to allow users to clear the error counters.
This functionality extends and is intended to eventually replace existing mechanism via :ref:`zesRasGetState`\.

To that end, this extension also adds new enumerator for RAS error categories. The list of error categories
include existing ones (refer to the Sysman Programming guide) and also additional ones which are defined here.
The additional error categories are listed below: 

================================================================================== ============================================================= =======================================
Error category                                                                     :ref:`ZES_RAS_ERROR_TYPE_CORRECTABLE <zes-ras-error-type-t>`   :ref:`ZES_RAS_ERROR_TYPE_UNCORRECTABLE <zes-ras-error-type-t>`
================================================================================== ============================================================= =======================================
 :ref:`ZES_RAS_ERROR_CATEGORY_EXP_MEMORY_ERRORS <zes-ras-error-category-exp-t>`        Number of ECC correctable errors                            Number of ECC uncorrectable errors
                                                  that have occurred in memory -                              that have occurred in memory -
                                                  GDDR/HBM.                                                   GDDR/HBM.
 :ref:`ZES_RAS_ERROR_CATEGORY_EXP_SCALE_ERRORS <zes-ras-error-category-exp-t>`         Number of correctable errors                                Number of ECC uncorrectable errors
                                                  that have occurred in scale IP                              that have occurred in scale IP
 :ref:`ZES_RAS_ERROR_CATEGORY_EXP_L3FABRIC_ERRORS <zes-ras-error-category-exp-t>`      Number of ECC correctable errors                            Number of ECC uncorrectable errors
                                                  that have occurred in L3 fabric                             that have occurred in L3 fabric
================================================================================== ============================================================= =======================================

The following pseudo-code demonstrates a sequence for querying the number of error categories
supported by a platform and for obtaining the error counters for these categories.

RAS Get Supported Categories
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The :ref:`zesRasGetSupportedCategoriesExp` function provides a way to query which RAS error categories
are supported by the platform. This allows applications to discover available error categories
before attempting to retrieve error counters.

The following pseudo-code demonstrates how to query supported categories:

Usage Example
~~~~~~~~~~~~~

.. parsed-literal::

    // Query for number of supported categories
    uint32_t categoryCount = 0;
    {s}RasGetSupportedCategoriesExp(rasHandle, &categoryCount, nullptr);

    :ref:`zes-ras-error-category-exp-t`\* categories = (:ref:`zes-ras-error-category-exp-t`\*) allocate(categoryCount * sizeof(:ref:`zes-ras-error-category-exp-t`\));

    // Retrieve supported categories
    {s}RasGetSupportedCategoriesExp(rasHandle, &categoryCount, categories);

    // Print supported categories
    for(uint32_t i = 0; i < categoryCount; i++) {
        output("Supported category: %d\\n", categories[i]);
    }


RAS Get State 
~~~~~~~~~~~~~

:ref:`zesRasGetStateExp2` takes a separate input array of error categories, allowing selective querying of specific error categories to query error counters.

Usage Example
~~~~~~~~~~~~~

.. parsed-literal::

    // Step 1: Discover supported categories
    uint32_t categoryCount = 0;
    {s}RasGetSupportedCategoriesExp(rasHandle, &categoryCount, nullptr);
    
    :ref:`zes-ras-error-category-exp-t`\* categories = (:ref:`zes-ras-error-category-exp-t`\*) 
        allocate(categoryCount * sizeof(:ref:`zes-ras-error-category-exp-t`\));
    
    {s}RasGetSupportedCategoriesExp(rasHandle, &categoryCount, categories);
    
    // Step 2: Prepare output state structures
    :ref:`zes-ras-state-exp2-t`\* rasStates = (:ref:`zes-ras-state-exp2-t`\*) 
        allocate(categoryCount * sizeof(:ref:`zes-ras-state-exp2-t`\));
    
    for(uint32_t i = 0; i < categoryCount; i++) {
        rasStates[i].stype = :ref:`ZES_STRUCTURE_TYPE_RAS_STATE_EXP2 <zes-structure-type-t>`\;
        rasStates[i].pNext = nullptr;
    }
    
    // Step 3: Retrieve error states (all categories are supported)
    ze_result_t result = {s}RasGetStateExp2(rasHandle, categoryCount, categories, rasStates);
    
    // Step 4: Process results
    if (result == ZE_RESULT_SUCCESS) {
        for(uint32_t i = 0; i < categoryCount; i++) {
            output("Category %d: %llu errors\\n", 
                   categories[i], rasStates[i].errorCounter);
        }
    }
    
    free(categories);
    free(rasStates);
