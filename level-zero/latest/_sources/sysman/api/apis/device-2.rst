============================================================
Device
============================================================
oneAPI Level Zero Specification - Version 1.21.26




Device Functions
================


.. _zesDeviceEccConfigurable:

zesDeviceEccConfigurable
------------------------

.. rst-class:: api-version

*Added in version 1.4*

.. doxygenfunction:: zesDeviceEccConfigurable
    :project: LevelZero


.. _zesDeviceGetEccState:

zesDeviceGetEccState
--------------------

.. rst-class:: api-version

*Added in version 1.4*

.. doxygenfunction:: zesDeviceGetEccState
    :project: LevelZero


.. _zesDeviceSetEccState:

zesDeviceSetEccState
--------------------

.. rst-class:: api-version

*Added in version 1.4*

.. doxygenfunction:: zesDeviceSetEccState
    :project: LevelZero


.. _zesDeviceGet:

zesDeviceGet
------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenfunction:: zesDeviceGet
    :project: LevelZero


.. _zesDeviceSetOverclockWaiver:

zesDeviceSetOverclockWaiver
---------------------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenfunction:: zesDeviceSetOverclockWaiver
    :project: LevelZero


.. _zesDeviceGetOverclockDomains:

zesDeviceGetOverclockDomains
----------------------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenfunction:: zesDeviceGetOverclockDomains
    :project: LevelZero


.. _zesDeviceGetOverclockControls:

zesDeviceGetOverclockControls
-----------------------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenfunction:: zesDeviceGetOverclockControls
    :project: LevelZero


.. _zesDeviceResetOverclockSettings:

zesDeviceResetOverclockSettings
-------------------------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenfunction:: zesDeviceResetOverclockSettings
    :project: LevelZero


.. _zesDeviceReadOverclockState:

zesDeviceReadOverclockState
---------------------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenfunction:: zesDeviceReadOverclockState
    :project: LevelZero


.. _zesDeviceEnumOverclockDomains:

zesDeviceEnumOverclockDomains
-----------------------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenfunction:: zesDeviceEnumOverclockDomains
    :project: LevelZero



Device Enums
============


.. _zes-engine-type-flags-t:

zes_engine_type_flags_t
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zes-process-state-t`, :ref:`zes-perf-properties-t`, :ref:`zes-sched-properties-t`

.. doxygentypedef:: zes_engine_type_flags_t
    :project: LevelZero

.. doxygenenum:: zes_engine_type_flag_t
    :project: LevelZero


.. _zes-repair-status-t:

zes_repair_status_t
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zes-device-state-t`

.. doxygenenum:: zes_repair_status_t
    :project: LevelZero


.. _zes-reset-reason-flags-t:

zes_reset_reason_flags_t
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zes-device-state-t`

.. doxygentypedef:: zes_reset_reason_flags_t
    :project: LevelZero

.. doxygenenum:: zes_reset_reason_flag_t
    :project: LevelZero


.. _zes-reset-type-t:

zes_reset_type_t
----------------

.. rst-class:: api-version

*Added in version 1.7*

.. container:: api-usage

   | **Member of:** :ref:`zes-reset-properties-t`

.. doxygenenum:: zes_reset_type_t
    :project: LevelZero


.. _zes-device-type-t:

zes_device_type_t
-----------------

.. rst-class:: api-version

*Added in version 1.7*

.. container:: api-usage

   | **Member of:** :ref:`zes-device-ext-properties-t`

.. doxygenenum:: zes_device_type_t
    :project: LevelZero


.. _zes-device-property-flags-t:

zes_device_property_flags_t
---------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. container:: api-usage

   | **Member of:** :ref:`zes-device-ext-properties-t`

.. doxygentypedef:: zes_device_property_flags_t
    :project: LevelZero

.. doxygenenum:: zes_device_property_flag_t
    :project: LevelZero


.. _zes-pci-link-status-t:

zes_pci_link_status_t
---------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zes-pci-state-t`, :ref:`zes-driver-pci-device-properties-t`

.. doxygenenum:: zes_pci_link_status_t
    :project: LevelZero


.. _zes-pci-link-qual-issue-flags-t:

zes_pci_link_qual_issue_flags_t
-------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zes-pci-state-t`

.. doxygentypedef:: zes_pci_link_qual_issue_flags_t
    :project: LevelZero

.. doxygenenum:: zes_pci_link_qual_issue_flag_t
    :project: LevelZero


.. _zes-pci-link-stab-issue-flags-t:

zes_pci_link_stab_issue_flags_t
-------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zes-pci-state-t`

.. doxygentypedef:: zes_pci_link_stab_issue_flags_t
    :project: LevelZero

.. doxygenenum:: zes_pci_link_stab_issue_flag_t
    :project: LevelZero


.. _zes-pci-bar-type-t:

zes_pci_bar_type_t
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zes-pci-bar-properties-t`, :ref:`zes-pci-bar-properties-1-2-t`

.. doxygenenum:: zes_pci_bar_type_t
    :project: LevelZero


.. _zes-overclock-domain-t:

zes_overclock_domain_t
----------------------

.. rst-class:: api-version

*Added in version 1.5*

.. container:: api-usage

   | **Used by:** :ref:`zesDeviceGetOverclockControls`
   | **Member of:** :ref:`zes-overclock-properties-t`

.. doxygenenum:: zes_overclock_domain_t
    :project: LevelZero


.. _zes-device-ecc-state-t:

zes_device_ecc_state_t
----------------------

.. rst-class:: api-version

*Added in version 1.4*

.. container:: api-usage

   | **Member of:** :ref:`zes-device-ecc-desc-t`, :ref:`zes-device-ecc-properties-t`, :ref:`zes-device-ecc-default-properties-ext-t`

.. doxygenenum:: zes_device_ecc_state_t
    :project: LevelZero


.. _zes-device-action-t:

zes_device_action_t
-------------------

.. rst-class:: api-version

*Added in version 1.4*

.. container:: api-usage

   | **Used by:** :ref:`zesDevicePciLinkSpeedUpdateExt`
   | **Member of:** :ref:`zes-device-ecc-properties-t`

.. doxygenenum:: zes_device_action_t
    :project: LevelZero


.. _zes-freq-domain-t:

zes_freq_domain_t
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zes-freq-properties-t`

.. doxygenenum:: zes_freq_domain_t
    :project: LevelZero


.. _zes-sched-mode-t:

zes_sched_mode_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesSchedulerGetCurrentMode`

.. doxygenenum:: zes_sched_mode_t
    :project: LevelZero


.. _zes-pci-link-speed-flags-t:

zes_pci_link_speed_flags_t
--------------------------

.. rst-class:: api-version

*Added in version 1.20*

.. container:: api-usage

   | **Member of:** :ref:`zes-pci-config-properties-t`

.. doxygentypedef:: zes_pci_link_speed_flags_t
    :project: LevelZero

.. doxygenenum:: zes_pci_link_speed_flag_t
    :project: LevelZero


 
Device Structures
=================


.. _zes-uuid-t:

zes_uuid_t
----------

.. rst-class:: api-version

*Added in version 1.7*

.. container:: api-usage

   | **Used by:** :ref:`zesDriverGetDeviceByUuidExp`
   | **Member of:** :ref:`zes-driver-properties-t`, :ref:`zes-device-ext-properties-t`, :ref:`zes-subdevice-exp-properties-t`, :ref:`zes-vf-exp-properties-t`, :ref:`zes-info-log-metadata-ext-t`, :ref:`zes-device-soc-uid-ext-properties-t`

.. doxygenstruct:: zes_uuid_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-device-state-t:

zes_device_state_t
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesDeviceGetState`
   | **pNext may point to:** :ref:`zes-device-ext-state-t`

.. doxygenstruct:: zes_device_state_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-reset-properties-t:

zes_reset_properties_t
----------------------

.. rst-class:: api-version

*Added in version 1.7*

.. container:: api-usage

   | **Used by:** :ref:`zesDeviceResetExt`

.. doxygenstruct:: zes_reset_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-device-properties-t:

zes_device_properties_t
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesDeviceGetProperties`
   | **pNext may point to:** :ref:`zes-device-soc-uid-ext-properties-t`, :ref:`zes-device-ext-properties-t`, :ref:`zes-device-index-ext-properties-t`, :ref:`zes-oem-serial-id-ext-properties-t`, :ref:`zes-device-gpu-topology-ext-properties-t`

.. doxygenstruct:: zes_device_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-process-state-t:

zes_process_state_t
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesDeviceProcessesGetState`

.. doxygenstruct:: zes_process_state_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-pci-address-t:

zes_pci_address_t
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zes-pci-properties-t`, :ref:`zes-vf-exp-properties-t`, :ref:`zes-vf-exp-capabilities-t`, :ref:`zes-vf-exp2-capabilities-t`, :ref:`zes-info-log-metadata-ext-t`, :ref:`zes-driver-pci-device-properties-t`

.. doxygenstruct:: zes_pci_address_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-pci-speed-t:

zes_pci_speed_t
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zes-pci-properties-t`, :ref:`zes-pci-state-t`, :ref:`zes-pci-stats-t`, :ref:`zes-driver-pci-device-properties-t`

.. doxygenstruct:: zes_pci_speed_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-pci-properties-t:

zes_pci_properties_t
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesDevicePciGetProperties`
   | **pNext may point to:** :ref:`zes-pci-link-speed-downgrade-ext-properties-t`, :ref:`zes-pci-config-properties-t`

.. doxygenstruct:: zes_pci_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-pci-state-t:

zes_pci_state_t
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesDevicePciGetState`
   | **pNext may point to:** :ref:`zes-pci-link-speed-downgrade-ext-state-t`

.. doxygenstruct:: zes_pci_state_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-pci-bar-properties-t:

zes_pci_bar_properties_t
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesDevicePciGetBars`

.. doxygenstruct:: zes_pci_bar_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-pci-bar-properties-1-2-t:

zes_pci_bar_properties_1_2_t
----------------------------

.. rst-class:: api-version

*Added in version 1.2*

.. doxygenstruct:: zes_pci_bar_properties_1_2_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-pci-stats-t:

zes_pci_stats_t
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesDevicePciGetStats`

.. doxygenstruct:: zes_pci_stats_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-device-ecc-desc-t:

zes_device_ecc_desc_t
---------------------

.. rst-class:: api-version

*Added in version 1.4*

.. container:: api-usage

   | **Used by:** :ref:`zesDeviceSetEccState`

.. doxygenstruct:: zes_device_ecc_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-device-ecc-properties-t:

zes_device_ecc_properties_t
---------------------------

.. rst-class:: api-version

*Added in version 1.4*

.. container:: api-usage

   | **Used by:** :ref:`zesDeviceGetEccState`, :ref:`zesDeviceSetEccState`
   | **pNext may point to:** :ref:`zes-device-ecc-default-properties-ext-t`

.. doxygenstruct:: zes_device_ecc_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-sched-timeout-properties-t:

zes_sched_timeout_properties_t
------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesSchedulerGetTimeoutModeProperties`, :ref:`zesSchedulerSetTimeoutMode`

.. doxygenstruct:: zes_sched_timeout_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-sched-timeslice-properties-t:

zes_sched_timeslice_properties_t
--------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesSchedulerGetTimesliceModeProperties`, :ref:`zesSchedulerSetTimesliceMode`

.. doxygenstruct:: zes_sched_timeslice_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-pci-config-properties-t:

zes_pci_config_properties_t
---------------------------

.. rst-class:: api-version

*Added in version 1.20*

.. container:: api-usage

   | **Member of:** :ref:`zes-driver-pci-device-properties-t`
   | **Goes in pNext of:** :ref:`zes-pci-properties-t`

.. doxygenstruct:: zes_pci_config_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. raw:: html

   <nav class="api-pager" aria-label="Page navigation"><a class="prev" href="device.html">&lsaquo; Prev</a><a href="device.html">1</a><strong class="current">2</strong><span class="next disabled">Next &rsaquo;</span></nav>
