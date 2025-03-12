<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_device_cache_line_size:

======================================
 Device CacheLine Size Extension
======================================

API
----
* Enumerations


    * ${x}_device_cache_line_size_ext_version_t


* Structures


    * ${x}_device_cache_line_size_ext_t

Device CacheLine Size
~~~~~~~~~~~~~~~~~~~~~

Accelerator devices have a cache line size which is the size of the smallest unit of memory that can be read or written to memory. The ${x}_device_cache_line_size_ext_t struct returned via ${x}DeviceGetCacheProperties contains the cache line size of the device.

.. parsed-literal::
       ...
        ${x}_device_cache_properties_t devCacheProps;
        ${x}_device_cache_line_size_ext_t devCacheLineSize;
        devProps.stype = ${X}_STRUCTURE_TYPE_DEVICE_CACHE_PROPERTIES;
        devProps.pNext = &devCacheLineSize;
        devCacheLineSize.stype = ${X}_STRUCTURE_TYPE_DEVICE_CACHELINE_SIZE_EXT;
        devCacheLineSize.pNext = nullptr;
        uint32_t count = 1;
        // Get the Device Cache Properties and the Device CacheLine Size Properties
        ${x}_result_t result = ${x}DeviceGetCacheProperties(dev, &count, &devProps);
        auto device_cache_line_size = devCacheLineSize.cacheLineSize;
