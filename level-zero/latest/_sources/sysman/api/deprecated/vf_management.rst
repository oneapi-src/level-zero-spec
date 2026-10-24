============================================================
VF Management - Deprecated
============================================================
oneAPI Level Zero Specification - Version 1.20.41


VF Management - Deprecated Functions
====================================


.. _zesVFManagementGetVFPropertiesExp:

zesVFManagementGetVFPropertiesExp
---------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.11. No longer supported. Use :ref:`zesVFManagementGetVFCapabilitiesExp2` instead.

.. doxygenfunction:: zesVFManagementGetVFPropertiesExp
    :project: LevelZero


.. _zesVFManagementGetVFMemoryUtilizationExp:

zesVFManagementGetVFMemoryUtilizationExp
----------------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.11. No longer supported. Use :ref:`zesVFManagementGetVFMemoryUtilizationExp2` instead.

.. doxygenfunction:: zesVFManagementGetVFMemoryUtilizationExp
    :project: LevelZero


.. _zesVFManagementGetVFEngineUtilizationExp:

zesVFManagementGetVFEngineUtilizationExp
----------------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.11. No longer supported. Use :ref:`zesVFManagementGetVFEngineUtilizationExp2` instead.

.. doxygenfunction:: zesVFManagementGetVFEngineUtilizationExp
    :project: LevelZero


.. _zesVFManagementSetVFTelemetryModeExp:

zesVFManagementSetVFTelemetryModeExp
------------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.11. Utilization telemetry needs no enabling; query it directly (memory: zesVFManagementGetVFMemoryUtilizationExp2). Related: :ref:`zesVFManagementGetVFEngineUtilizationExp2`.

.. doxygenfunction:: zesVFManagementSetVFTelemetryModeExp
    :project: LevelZero


.. _zesVFManagementSetVFTelemetrySamplingIntervalExp:

zesVFManagementSetVFTelemetrySamplingIntervalExp
------------------------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.11. Utilization telemetry needs no sampling setup; query it directly (memory: zesVFManagementGetVFMemoryUtilizationExp2). Related: :ref:`zesVFManagementGetVFEngineUtilizationExp2`.

.. doxygenfunction:: zesVFManagementSetVFTelemetrySamplingIntervalExp
    :project: LevelZero


.. _zesVFManagementGetVFCapabilitiesExp:

zesVFManagementGetVFCapabilitiesExp
-----------------------------------

.. rst-class:: api-version

*Added in version 1.10*

.. rst-class:: api-deprecated

**Deprecated** since 1.12. No longer supported. Use :ref:`zesVFManagementGetVFCapabilitiesExp2` instead.

.. doxygenfunction:: zesVFManagementGetVFCapabilitiesExp
    :project: LevelZero



VF Management - Deprecated Enums
================================


.. _zes-vf-info-mem-type-exp-flags-t:

zes_vf_info_mem_type_exp_flags_t
--------------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.10. Use :ref:`zes-mem-loc-t` instead.

.. doxygenenum:: zes_vf_info_mem_type_exp_flag_t
    :project: LevelZero


.. _zes-vf-info-util-exp-flags-t:

zes_vf_info_util_exp_flags_t
----------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.10. The Exp2 utilization queries report what is available: memory by zes_mem_loc_t, engines by zes_engine_group_t. Related: :ref:`zesVFManagementGetVFEngineUtilizationExp2`.

.. doxygenenum:: zes_vf_info_util_exp_flag_t
    :project: LevelZero

 
VF Management - Deprecated Structures
=====================================


.. _zes-vf-exp-properties-t:

zes_vf_exp_properties_t
-----------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.10. Use :ref:`zes-vf-exp2-capabilities-t` instead.

.. doxygenstruct:: zes_vf_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-vf-util-mem-exp-t:

zes_vf_util_mem_exp_t
---------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.10. Use :ref:`zes-vf-util-mem-exp2-t` instead.

.. doxygenstruct:: zes_vf_util_mem_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-vf-util-engine-exp-t:

zes_vf_util_engine_exp_t
------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. rst-class:: api-deprecated

**Deprecated** since 1.10. Use :ref:`zes-vf-util-engine-exp2-t` instead.

.. doxygenstruct:: zes_vf_util_engine_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-vf-exp-capabilities-t:

zes_vf_exp_capabilities_t
-------------------------

.. rst-class:: api-version

*Added in version 1.10*

.. rst-class:: api-deprecated

**Deprecated** since 1.12. Use :ref:`zes-vf-exp2-capabilities-t` instead.

.. doxygenstruct:: zes_vf_exp_capabilities_t
    :project: LevelZero
    :members:
    :undoc-members:

