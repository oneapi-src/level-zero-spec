
:orphan:

.. _ZES_extension_memory_vendor_info:

=============================
 Memory Vendor Info Extension
=============================

.. rst-class:: ext-version

*Introduced in Level Zero version 1.18*

API
----
* Enumerations

    * :ref:`zes-memory-vendor-info-ext-version-t`
   
* Structures

    * :ref:`zes-memory-vendor-info-ext-properties-t`

* Macros

    * ZES_MEMORY_VENDOR_INFO_EXT_NAME
    * ZES_MEMORY_VENDOR_NAME_EXT_SIZE

Memory Vendor Info Overview
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Memory Vendor Info extension provides the ability to query the memory vendor
ID and the memory vendor name.

Applications can retrieve both the memory vendor ID and the memory vendor name by
passing the extension structure via the pNext chain when calling
:ref:`zesMemoryGetProperties`\. The two are reported independently: if the vendor ID
cannot be determined, the vendor ID will be 0, and if the vendor name cannot be
determined, the length will be 0 and the name will not be populated.

Checking Extension Support
~~~~~~~~~~~~~~~~~~~~~~~~~~

Query extension support via :ref:`zesDriverGetExtensionProperties` before use:

.. parsed-literal::

    uint32_t count = 0;
    :ref:`zesDriverGetExtensionProperties`\(hDriver, &count, NULL);

    :ref:`zes-driver-extension-properties-t`\* props =
        malloc(count * sizeof(:ref:`zes-driver-extension-properties-t`\));
    :ref:`zesDriverGetExtensionProperties`\(hDriver, &count, props);

    bool supported = false;
    for (uint32_t i = 0; i < count; i++) {
        if (strcmp(props[i].name, ZES_MEMORY_VENDOR_INFO_EXT_NAME) == 0) {
            supported = true;
            break;
        }
    }
    free(props);

If the extension is not reported, the driver ignores the extension structure in
the ``pNext`` chain and the values returned in
:ref:`zes-memory-vendor-info-ext-properties-t` are not modified.

Querying the Vendor ID and Vendor Name
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following pseudo-code demonstrates the usage pattern for querying the memory
vendor ID and the memory vendor name.

.. parsed-literal::

    // Query memory properties with memory vendor info extension to retrieve
    // both the vendor ID and the vendor name
    :ref:`zes-mem-properties-t` memProps = {};
    memProps.stype = :ref:`ZES_STRUCTURE_TYPE_MEM_PROPERTIES <zes-structure-type-t>`\;
    
    :ref:`zes-memory-vendor-info-ext-properties-t` vendorInfoProps = {};
    vendorInfoProps.stype = :ref:`ZES_STRUCTURE_TYPE_MEMORY_VENDOR_INFO_EXT_PROPERTIES <zes-structure-type-t>`\;
    vendorInfoProps.pNext = nullptr;
    
    memProps.pNext = &vendorInfoProps;
    
    :ref:`zesMemoryGetProperties`\(hMemory, &memProps);
    
    // Check if vendor ID was successfully retrieved
    if (vendorInfoProps.vendorId != 0) {
        output("Memory Vendor ID: 0x%x\\n", vendorInfoProps.vendorId);
    } else {
        output("Memory vendor ID not available for this device\\n");
    }

    // Check if vendor name was successfully retrieved
    if (vendorInfoProps.length != 0) {
        output("Memory Vendor Name: %s\\n", vendorInfoProps.vendorName);
        output("Memory Vendor Name Length: %u\\n", vendorInfoProps.length);
    } else {
        output("Memory vendor name not available for this device\\n");
    }
