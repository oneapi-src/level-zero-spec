============================================================
Context
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Context Handles
===============


.. _ze-context-handle-t:

ze_context_handle_t
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zeDriverGetDefaultContext`, :ref:`zeContextCreate`, :ref:`zeContextCreateEx`, :ref:`zeCommandListGetContextHandle`, :ref:`zeEventPoolGetContextHandle`
   | **Used by:** :raw-html:`<span class="api-usage-fold"><input type="checkbox" id="usage-ze-context-handle-t-3"><span class="api-usage-links">` :ref:`zeContextDestroy`, :ref:`zeContextGetStatus`, :ref:`zeCommandQueueCreate`, :ref:`zeCommandListCreate`, :ref:`zeCommandListCreateImmediate`, :ref:`zeContextSystemBarrier`, :ref:`zeCommandListAppendMemoryCopyFromContext`, :ref:`zeEventPoolCreate`, :ref:`zeEventCounterBasedCreate`, :ref:`zeEventPoolPutIpcHandle`, :ref:`zeEventPoolOpenIpcHandle`, :ref:`zeEventCounterBasedOpenIpcHandle`, :ref:`zeImageCreate`, :ref:`zeMemAllocShared`, :ref:`zeMemAllocDevice`, :ref:`zeMemAllocHost`, :ref:`zeMemFree`, :ref:`zeMemGetAllocProperties`, :ref:`zeMemGetAddressRange`, :ref:`zeMemGetIpcHandle`, :ref:`zeMemGetIpcHandleFromFileDescriptorExp`, :ref:`zeMemGetFileDescriptorFromIpcHandleExp`, :ref:`zeMemPutIpcHandle`, :ref:`zeMemOpenIpcHandle`, :ref:`zeMemCloseIpcHandle`, :ref:`zeMemSetAtomicAccessAttributeExp`, :ref:`zeMemGetAtomicAccessAttributeExp`, :ref:`zeModuleCreate`, :ref:`zeContextMakeMemoryResident`, :ref:`zeContextEvictMemory`, :ref:`zeContextMakeImageResident`, :ref:`zeContextEvictImage`, :ref:`zeSamplerCreate`, :ref:`zeVirtualMemReserve`, :ref:`zeVirtualMemFree`, :ref:`zeVirtualMemQueryPageSize`, :ref:`zePhysicalMemGetProperties`, :ref:`zePhysicalMemCreate`, :ref:`zePhysicalMemDestroy`, :ref:`zeVirtualMemMap`, :ref:`zeVirtualMemUnmap`, :ref:`zeVirtualMemSetAccessAttribute`, :ref:`zeVirtualMemGetAccessAttribute`, :ref:`zeImageViewCreateExt`, :ref:`zeImageViewCreateExp`, :ref:`zeImageGetAllocPropertiesExt`, :ref:`zeMemFreeExt`, :ref:`zeMemGetPitchFor2dImage`, :ref:`zeMemGetIpcHandleWithProperties`, :ref:`zeGraphCreateExt` :raw-html:`</span><label for="usage-ze-context-handle-t-3"><span class="more">Show all 50</span><span class="less">Show less</span></label></span>`
   | **See also:** `Contexts (Programming Guide) <../../PROG.html#contexts>`__

.. cpp:type:: ze_context_handle_t

    Handle of driver's context object.



Context Functions
=================


.. _zeContextCreate:

zeContextCreate
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeContextCreate
    :project: LevelZero


.. _zeContextDestroy:

zeContextDestroy
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeContextDestroy
    :project: LevelZero


.. _zeContextGetStatus:

zeContextGetStatus
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeContextGetStatus
    :project: LevelZero


.. _zeContextSystemBarrier:

zeContextSystemBarrier
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeContextSystemBarrier
    :project: LevelZero


.. _zeContextMakeMemoryResident:

zeContextMakeMemoryResident
---------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeContextMakeMemoryResident
    :project: LevelZero


.. _zeContextEvictMemory:

zeContextEvictMemory
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeContextEvictMemory
    :project: LevelZero


.. _zeContextMakeImageResident:

zeContextMakeImageResident
--------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeContextMakeImageResident
    :project: LevelZero


.. _zeContextEvictImage:

zeContextEvictImage
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeContextEvictImage
    :project: LevelZero


.. _zeContextCreateEx:

zeContextCreateEx
-----------------

.. rst-class:: api-version

*Added in version 1.1*

.. doxygenfunction:: zeContextCreateEx
    :project: LevelZero



Context Enums
=============


.. _ze-context-flags-t:

ze_context_flags_t
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-context-desc-t`

.. doxygentypedef:: ze_context_flags_t
    :project: LevelZero

.. doxygenenum:: ze_context_flag_t
    :project: LevelZero


 
Context Structures
==================


.. _ze-context-desc-t:

ze_context_desc_t
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeContextCreate`, :ref:`zeContextCreateEx`

.. doxygenstruct:: ze_context_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

