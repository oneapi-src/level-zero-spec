============================================================
Module
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Module Handles
==============


.. _ze-module-handle-t:

ze_module_handle_t
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zeModuleCreate`, :ref:`zeKernelGetModuleHandle`
   | **Used by:** :ref:`zeModuleDestroy`, :ref:`zeModuleDynamicLink`, :ref:`zeModuleGetNativeBinary`, :ref:`zeModuleGetGlobalPointer`, :ref:`zeModuleGetKernelNames`, :ref:`zeModuleGetProperties`, :ref:`zeModuleGetDeviceHandle`, :ref:`zeKernelCreate`, :ref:`zeModuleGetFunctionPointer`, :ref:`zeModuleInspectLinkageExt`
   | **Member of:** :ref:`ze-runtime-requirements-module-desc-t`
   | **See also:** :ref:`Modules (Programming Guide) <Modules>`

.. cpp:type:: ze_module_handle_t

    Handle of driver's module object.



Module Functions
================


.. _zeModuleCreate:

zeModuleCreate
--------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeModuleCreate
    :project: LevelZero


.. _zeModuleDestroy:

zeModuleDestroy
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeModuleDestroy
    :project: LevelZero


.. _zeModuleDynamicLink:

zeModuleDynamicLink
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeModuleDynamicLink
    :project: LevelZero


.. _zeModuleGetNativeBinary:

zeModuleGetNativeBinary
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeModuleGetNativeBinary
    :project: LevelZero


.. _zeModuleGetGlobalPointer:

zeModuleGetGlobalPointer
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeModuleGetGlobalPointer
    :project: LevelZero


.. _zeModuleGetKernelNames:

zeModuleGetKernelNames
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeModuleGetKernelNames
    :project: LevelZero


.. _zeModuleGetProperties:

zeModuleGetProperties
---------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeModuleGetProperties
    :project: LevelZero


.. _zeModuleGetFunctionPointer:

zeModuleGetFunctionPointer
--------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeModuleGetFunctionPointer
    :project: LevelZero


.. _zeModuleGetDeviceHandle:

zeModuleGetDeviceHandle
-----------------------

.. rst-class:: api-version

*Added in version 1.18*

.. doxygenfunction:: zeModuleGetDeviceHandle
    :project: LevelZero



Module Enums
============


.. _ze-module-format-t:

ze_module_format_t
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-module-desc-t`

.. doxygenenum:: ze_module_format_t
    :project: LevelZero


.. _ze-module-property-flags-t:

ze_module_property_flags_t
--------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-module-properties-t`

.. doxygentypedef:: ze_module_property_flags_t
    :project: LevelZero

.. doxygenenum:: ze_module_property_flag_t
    :project: LevelZero


 
Module Structures
=================


.. _ze-module-constants-t:

ze_module_constants_t
---------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-module-desc-t`, :ref:`ze-module-program-exp-desc-t`

.. doxygenstruct:: ze_module_constants_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-module-desc-t:

ze_module_desc_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeModuleCreate`

.. doxygenstruct:: ze_module_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-module-properties-t:

ze_module_properties_t
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeModuleGetProperties`

.. doxygenstruct:: ze_module_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

