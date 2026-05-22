
:orphan:

.. _ZE_extension_device_memory_properties:

======================================
 Device Memory Properties Extension
======================================

API
----

* Enumerations


    * :ref:`ze-device-memory-properties-ext-version-t`
    * :ref:`ze-device-memory-ext-type-t`


* Structures


    * :ref:`ze-device-memory-ext-properties-t`

Extended Device Memory Properties
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Users may wish to build a cost model for computation on accelerators exposed through 'oneAPI' Level-Zero. Such cost models require detailed information about the properties of the accelerator such as memory bandwidth. This extension provides extended information about the memories exposed as part of a device. The extension introduces the :ref:`ze-device-memory-ext-properties-t` struct which can be passed to :ref:`zeDeviceGetMemoryProperties` via the `pNext` member of :ref:`ze-device-memory-properties-t`\.

The following psuedo-code demonstrates a sequence for obtaining extended information about the memory properties of a memory module exposed as part of a device:

.. parsed-literal::

       ...
       // Discover memories on device
       uint32_t memCount = 0;
       :ref:`zeDeviceGetMemoryProperties`\(hDevice, &memCount, nullptr);

       // Allocate properties structs
       :ref:`ze-device-memory-properties-t`\* pMemProps = allocate(memCount*sizeof(:ref:`ze-device-memory-properties-t`\));
       :ref:`ze-device-memory-ext-properties-t`\* pExtMemProps = allocate(memCount*sizeof(:ref:`ze-device-memory-ext-properties-t`\));

       // Make pNext in memProps point at corresponding extMemProps
       for (uint32_t i = 0; i < memCount; ++i) {
         pMemProps[i].stype = :ref:`ZE_STRUCTURE_TYPE_DEVICE_MEMORY_PROPERTIES <ze-structure-type-t>`\;
         pMemProps[i].pNext = &pExtMemProps[i];
         pExtMemProps[i].stype = :ref:`ZE_STRUCTURE_TYPE_DEVICE_MEMORY_EXT_PROPERTIES <ze-structure-type-t>`\;
         pExtMemProps[i].pNext = nullptr;
       }

       // Obtain memory & extended memory properties
       :ref:`zeDeviceGetMemoryProperties`\(hDevice, &memCount, pMemProps);
