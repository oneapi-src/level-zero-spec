
:orphan:

.. _ZE_extension_device_cache_line_size:

======================================
 Device CacheLine Size Extension
======================================

API
----
* Enumerations


    * :ref:`ze-device-cache-line-size-ext-version-t`


* Structures


    * :ref:`ze-device-cache-line-size-ext-t`

Device CacheLine Size
~~~~~~~~~~~~~~~~~~~~~

Accelerator devices have a cache line size which is the size of the smallest unit of memory that can be read or written to memory. The :ref:`ze-device-cache-line-size-ext-t` struct returned via :ref:`zeDeviceGetCacheProperties` contains the cache line size of the device.

.. parsed-literal::
       ...
        :ref:`ze-device-cache-properties-t` devCacheProps;
        :ref:`ze-device-cache-line-size-ext-t` devCacheLineSize;
        devProps.stype = :ref:`ZE_STRUCTURE_TYPE_DEVICE_CACHE_PROPERTIES <ze-structure-type-t>`\;
        devProps.pNext = &devCacheLineSize;
        devCacheLineSize.stype = :ref:`ZE_STRUCTURE_TYPE_DEVICE_CACHELINE_SIZE_EXT <ze-structure-type-t>`\;
        devCacheLineSize.pNext = nullptr;
        uint32_t count = 1;
        // Get the Device Cache Properties and the Device CacheLine Size Properties
        :ref:`ze-result-t` result = :ref:`zeDeviceGetCacheProperties`\(dev, &count, &devProps);
        auto device_cache_line_size = devCacheLineSize.cacheLineSize;
