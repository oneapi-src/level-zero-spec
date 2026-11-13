============================================================
Kernel
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Kernel Handles
==============


.. _ze-kernel-handle-t:

ze_kernel_handle_t
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zeKernelCreate`
   | **Used by:** :raw-html:`<span class="api-usage-fold"><input type="checkbox" id="usage-ze-kernel-handle-t-3"><span class="api-usage-links">` :ref:`zeKernelDestroy`, :ref:`zeKernelSetGroupSize`, :ref:`zeKernelSuggestGroupSize`, :ref:`zeKernelSuggestMaxCooperativeGroupCount`, :ref:`zeKernelSetArgumentValue`, :ref:`zeKernelSetIndirectAccess`, :ref:`zeKernelGetIndirectAccess`, :ref:`zeKernelGetSourceAttributes`, :ref:`zeKernelSetCacheConfig`, :ref:`zeKernelGetProperties`, :ref:`zeKernelGetName`, :ref:`zeKernelGetModuleHandle`, :ref:`zeCommandListAppendLaunchKernel`, :ref:`zeCommandListAppendLaunchKernelWithParameters`, :ref:`zeCommandListAppendLaunchKernelWithArguments`, :ref:`zeCommandListAppendLaunchCooperativeKernel`, :ref:`zeCommandListAppendLaunchKernelIndirect`, :ref:`zeCommandListAppendLaunchMultipleKernelsIndirect`, :ref:`zeKernelSetGlobalOffsetExp`, :ref:`zeKernelSchedulingHintExp`, :ref:`zeCommandListGetNextCommandIdWithKernelsExp`, :ref:`zeCommandListUpdateMutableCommandKernelsExp`, :ref:`zeKernelGetBinaryExp`, :ref:`zeKernelGetAllocationPropertiesExp`, :ref:`zeCommandListGetNextCommandIdWithKernelsExt`, :ref:`zeCommandListUpdateMutableCommandKernelsExt` :raw-html:`</span><label for="usage-ze-kernel-handle-t-3"><span class="more">Show all 26</span><span class="less">Show less</span></label></span>`
   | **See also:** :ref:`Kernels (Programming Guide) <Kernels>`

.. cpp:type:: ze_kernel_handle_t

    Handle of driver's kernel object.



Kernel Functions
================


.. _zeKernelCreate:

zeKernelCreate
--------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeKernelCreate
    :project: LevelZero


.. _zeKernelDestroy:

zeKernelDestroy
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeKernelDestroy
    :project: LevelZero


.. _zeKernelSetCacheConfig:

zeKernelSetCacheConfig
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeKernelSetCacheConfig
    :project: LevelZero


.. _zeKernelSetGroupSize:

zeKernelSetGroupSize
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeKernelSetGroupSize
    :project: LevelZero


.. _zeKernelSuggestGroupSize:

zeKernelSuggestGroupSize
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeKernelSuggestGroupSize
    :project: LevelZero


.. _zeKernelSuggestMaxCooperativeGroupCount:

zeKernelSuggestMaxCooperativeGroupCount
---------------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeKernelSuggestMaxCooperativeGroupCount
    :project: LevelZero


.. _zeKernelSetArgumentValue:

zeKernelSetArgumentValue
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeKernelSetArgumentValue
    :project: LevelZero


.. _zeKernelSetIndirectAccess:

zeKernelSetIndirectAccess
-------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeKernelSetIndirectAccess
    :project: LevelZero


.. _zeKernelGetIndirectAccess:

zeKernelGetIndirectAccess
-------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeKernelGetIndirectAccess
    :project: LevelZero


.. _zeKernelGetSourceAttributes:

zeKernelGetSourceAttributes
---------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeKernelGetSourceAttributes
    :project: LevelZero


.. _zeKernelGetProperties:

zeKernelGetProperties
---------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeKernelGetProperties
    :project: LevelZero


.. _zeKernelGetName:

zeKernelGetName
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeKernelGetName
    :project: LevelZero


.. _zeKernelGetModuleHandle:

zeKernelGetModuleHandle
-----------------------

.. rst-class:: api-version

*Added in version 1.18*

.. doxygenfunction:: zeKernelGetModuleHandle
    :project: LevelZero



Kernel Enums
============


.. _ze-kernel-flags-t:

ze_kernel_flags_t
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-kernel-desc-t`

.. doxygentypedef:: ze_kernel_flags_t
    :project: LevelZero

.. doxygenenum:: ze_kernel_flag_t
    :project: LevelZero


.. _ze-kernel-indirect-access-flags-t:

ze_kernel_indirect_access_flags_t
---------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeKernelSetIndirectAccess`, :ref:`zeKernelGetIndirectAccess`

.. doxygentypedef:: ze_kernel_indirect_access_flags_t
    :project: LevelZero

.. doxygenenum:: ze_kernel_indirect_access_flag_t
    :project: LevelZero


.. _ze-cache-config-flags-t:

ze_cache_config_flags_t
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeKernelSetCacheConfig`

.. doxygentypedef:: ze_cache_config_flags_t
    :project: LevelZero

.. doxygenenum:: ze_cache_config_flag_t
    :project: LevelZero


 
Kernel Structures
=================


.. _ze-kernel-desc-t:

ze_kernel_desc_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeKernelCreate`

.. doxygenstruct:: ze_kernel_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-kernel-properties-t:

ze_kernel_properties_t
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeKernelGetProperties`
   | **pNext may point to:** :ref:`ze-kernel-preferred-group-size-properties-t`, :ref:`ze-kernel-max-group-size-properties-ext-t`

.. doxygenstruct:: ze_kernel_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-kernel-preferred-group-size-properties-t:

ze_kernel_preferred_group_size_properties_t
-------------------------------------------

.. rst-class:: api-version

*Added in version 1.2*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-kernel-properties-t`

.. doxygenstruct:: ze_kernel_preferred_group_size_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

