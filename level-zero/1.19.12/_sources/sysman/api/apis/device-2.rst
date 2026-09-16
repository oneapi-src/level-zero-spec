============================================================
Device
============================================================
oneAPI Level Zero Specification - Version 1.19.12


Device Functions
================


.. _zesDeviceEccAvailable:

zesDeviceEccAvailable
---------------------

.. rst-class:: api-version

*Added in version 1.4*

.. doxygenfunction:: zesDeviceEccAvailable
    :project: LevelZero


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

.. doxygenenum:: zes_engine_type_flag_t
    :project: LevelZero


.. _zes-repair-status-t:

zes_repair_status_t
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenenum:: zes_repair_status_t
    :project: LevelZero


.. _zes-reset-reason-flags-t:

zes_reset_reason_flags_t
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenenum:: zes_reset_reason_flag_t
    :project: LevelZero


.. _zes-reset-type-t:

zes_reset_type_t
----------------

.. rst-class:: api-version

*Added in version 1.7*

.. doxygenenum:: zes_reset_type_t
    :project: LevelZero


.. _zes-device-type-t:

zes_device_type_t
-----------------

.. rst-class:: api-version

*Added in version 1.7*

.. doxygenenum:: zes_device_type_t
    :project: LevelZero


.. _zes-device-property-flags-t:

zes_device_property_flags_t
---------------------------

.. rst-class:: api-version

*Added in version 1.7*

.. doxygenenum:: zes_device_property_flag_t
    :project: LevelZero


.. _zes-pci-link-status-t:

zes_pci_link_status_t
---------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenenum:: zes_pci_link_status_t
    :project: LevelZero


.. _zes-pci-link-qual-issue-flags-t:

zes_pci_link_qual_issue_flags_t
-------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenenum:: zes_pci_link_qual_issue_flag_t
    :project: LevelZero


.. _zes-pci-link-stab-issue-flags-t:

zes_pci_link_stab_issue_flags_t
-------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenenum:: zes_pci_link_stab_issue_flag_t
    :project: LevelZero


.. _zes-pci-bar-type-t:

zes_pci_bar_type_t
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenenum:: zes_pci_bar_type_t
    :project: LevelZero


.. _zes-overclock-domain-t:

zes_overclock_domain_t
----------------------

.. rst-class:: api-version

*Added in version 1.5*

.. doxygenenum:: zes_overclock_domain_t
    :project: LevelZero


.. _zes-device-ecc-state-t:

zes_device_ecc_state_t
----------------------

.. rst-class:: api-version

*Added in version 1.4*

.. doxygenenum:: zes_device_ecc_state_t
    :project: LevelZero


.. _zes-device-action-t:

zes_device_action_t
-------------------

.. rst-class:: api-version

*Added in version 1.4*

.. doxygenenum:: zes_device_action_t
    :project: LevelZero


.. _zes-freq-domain-t:

zes_freq_domain_t
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenenum:: zes_freq_domain_t
    :project: LevelZero


.. _zes-sched-mode-t:

zes_sched_mode_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenenum:: zes_sched_mode_t
    :project: LevelZero

 
Device Structures
=================


.. _zes-uuid-t:

zes_uuid_t
----------

.. rst-class:: api-version

*Added in version 1.7*

.. doxygenstruct:: zes_uuid_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-device-state-t:

zes_device_state_t
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenstruct:: zes_device_state_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-reset-properties-t:

zes_reset_properties_t
----------------------

.. rst-class:: api-version

*Added in version 1.7*

.. doxygenstruct:: zes_reset_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-device-properties-t:

zes_device_properties_t
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenstruct:: zes_device_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-process-state-t:

zes_process_state_t
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenstruct:: zes_process_state_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-pci-address-t:

zes_pci_address_t
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenstruct:: zes_pci_address_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-pci-speed-t:

zes_pci_speed_t
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenstruct:: zes_pci_speed_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-pci-properties-t:

zes_pci_properties_t
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenstruct:: zes_pci_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-pci-state-t:

zes_pci_state_t
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenstruct:: zes_pci_state_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-pci-bar-properties-t:

zes_pci_bar_properties_t
------------------------

.. rst-class:: api-version

*Added in version 1.0*

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

.. doxygenstruct:: zes_pci_stats_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-device-ecc-desc-t:

zes_device_ecc_desc_t
---------------------

.. rst-class:: api-version

*Added in version 1.4*

.. doxygenstruct:: zes_device_ecc_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-device-ecc-properties-t:

zes_device_ecc_properties_t
---------------------------

.. rst-class:: api-version

*Added in version 1.4*

.. doxygenstruct:: zes_device_ecc_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-sched-timeout-properties-t:

zes_sched_timeout_properties_t
------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenstruct:: zes_sched_timeout_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-sched-timeslice-properties-t:

zes_sched_timeslice_properties_t
--------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenstruct:: zes_sched_timeslice_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. raw:: html

   <nav class="api-pager" aria-label="Page navigation"><a class="prev" href="device.html">&lsaquo; Prev</a><a href="device.html">1</a><strong class="current">2</strong><span class="next disabled">Next &rsaquo;</span></nav>
