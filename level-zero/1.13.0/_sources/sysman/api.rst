

==============================
Sysman API
==============================
oneAPI Level Zero Specification - Version 1.13.0

 

 

Common
============================================================
* Enumerations


    * :ref:`zes-structure-type-t`

 
* Structures


    * :ref:`zes-base-properties-t`
    * :ref:`zes-base-desc-t`
    * :ref:`zes-base-state-t`
    * :ref:`zes-base-config-t`
    * :ref:`zes-base-capability-t`




Common Enums
------------------------------------------------------------------------------


.. _zes-structure-type-t:

zes_structure_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_structure_type_t
    :project: LevelZero

 
Common Structures
------------------------------------------------------------------------------

.. _zes-base-properties-t:

zes_base_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_base_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-base-desc-t:

zes_base_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_base_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-base-state-t:

zes_base_state_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_base_state_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-base-config-t:

zes_base_config_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_base_config_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-base-capability-t:

zes_base_capability_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_base_capability_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Driver
============================================================
* Functions


    * :ref:`zesInit`
    * :ref:`zesDriverGet`
    * :ref:`zesDriverGetExtensionProperties`
    * :ref:`zesDriverGetExtensionFunctionAddress`

 
* Enumerations


    * :ref:`zes-init-flags-t`

 
* Structures


    * :ref:`zes-driver-extension-properties-t`


Driver Functions
------------------------------------------------------------------------------


.. _zesInit:

zesInit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesInit
    :project: LevelZero


.. _zesDriverGet:

zesDriverGet
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDriverGet
    :project: LevelZero


.. _zesDriverGetExtensionProperties:

zesDriverGetExtensionProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDriverGetExtensionProperties
    :project: LevelZero


.. _zesDriverGetExtensionFunctionAddress:

zesDriverGetExtensionFunctionAddress
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDriverGetExtensionFunctionAddress
    :project: LevelZero



Driver Enums
------------------------------------------------------------------------------


.. _zes-init-flags-t:

zes_init_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_init_flag_t
    :project: LevelZero

 
Driver Structures
------------------------------------------------------------------------------

.. _zes-driver-extension-properties-t:

zes_driver_extension_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_driver_extension_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Device
============================================================
* Functions


    * :ref:`zesDeviceGet`
    * :ref:`zesDeviceGetProperties`
    * :ref:`zesDeviceGetState`
    * :ref:`zesDeviceReset`
    * :ref:`zesDeviceResetExt`
    * :ref:`zesDeviceProcessesGetState`
    * :ref:`zesDevicePciGetProperties`
    * :ref:`zesDevicePciGetState`
    * :ref:`zesDevicePciGetBars`
    * :ref:`zesDevicePciGetStats`

 
* Enumerations


    * :ref:`zes-engine-type-flags-t`
    * :ref:`zes-repair-status-t`
    * :ref:`zes-reset-reason-flags-t`
    * :ref:`zes-reset-type-t`
    * :ref:`zes-device-type-t`
    * :ref:`zes-device-property-flags-t`
    * :ref:`zes-pci-link-status-t`
    * :ref:`zes-pci-link-qual-issue-flags-t`
    * :ref:`zes-pci-link-stab-issue-flags-t`
    * :ref:`zes-pci-bar-type-t`

 
* Structures


    * :ref:`zes-device-state-t`
    * :ref:`zes-reset-properties-t`
    * :ref:`zes-uuid-t`
    * :ref:`zes-device-properties-t`
    * :ref:`zes-device-ext-properties-t`
    * :ref:`zes-process-state-t`
    * :ref:`zes-pci-address-t`
    * :ref:`zes-pci-speed-t`
    * :ref:`zes-pci-properties-t`
    * :ref:`zes-pci-state-t`
    * :ref:`zes-pci-bar-properties-t`
    * :ref:`zes-pci-bar-properties-1-2-t`
    * :ref:`zes-pci-stats-t`


Device Functions
------------------------------------------------------------------------------


.. _zesDeviceGet:

zesDeviceGet
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceGet
    :project: LevelZero


.. _zesDeviceGetProperties:

zesDeviceGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceGetProperties
    :project: LevelZero


.. _zesDeviceGetState:

zesDeviceGetState
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceGetState
    :project: LevelZero


.. _zesDeviceReset:

zesDeviceReset
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceReset
    :project: LevelZero


.. _zesDeviceResetExt:

zesDeviceResetExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceResetExt
    :project: LevelZero


.. _zesDeviceProcessesGetState:

zesDeviceProcessesGetState
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceProcessesGetState
    :project: LevelZero


.. _zesDevicePciGetProperties:

zesDevicePciGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDevicePciGetProperties
    :project: LevelZero


.. _zesDevicePciGetState:

zesDevicePciGetState
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDevicePciGetState
    :project: LevelZero


.. _zesDevicePciGetBars:

zesDevicePciGetBars
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDevicePciGetBars
    :project: LevelZero


.. _zesDevicePciGetStats:

zesDevicePciGetStats
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDevicePciGetStats
    :project: LevelZero



Device Enums
------------------------------------------------------------------------------


.. _zes-engine-type-flags-t:

zes_engine_type_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_engine_type_flag_t
    :project: LevelZero


.. _zes-repair-status-t:

zes_repair_status_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_repair_status_t
    :project: LevelZero


.. _zes-reset-reason-flags-t:

zes_reset_reason_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_reset_reason_flag_t
    :project: LevelZero


.. _zes-reset-type-t:

zes_reset_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_reset_type_t
    :project: LevelZero


.. _zes-device-type-t:

zes_device_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_device_type_t
    :project: LevelZero


.. _zes-device-property-flags-t:

zes_device_property_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_device_property_flag_t
    :project: LevelZero


.. _zes-pci-link-status-t:

zes_pci_link_status_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_pci_link_status_t
    :project: LevelZero


.. _zes-pci-link-qual-issue-flags-t:

zes_pci_link_qual_issue_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_pci_link_qual_issue_flag_t
    :project: LevelZero


.. _zes-pci-link-stab-issue-flags-t:

zes_pci_link_stab_issue_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_pci_link_stab_issue_flag_t
    :project: LevelZero


.. _zes-pci-bar-type-t:

zes_pci_bar_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_pci_bar_type_t
    :project: LevelZero

 
Device Structures
------------------------------------------------------------------------------

.. _zes-device-state-t:

zes_device_state_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_device_state_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-reset-properties-t:

zes_reset_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_reset_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-uuid-t:

zes_uuid_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_uuid_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-device-properties-t:

zes_device_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_device_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-device-ext-properties-t:

zes_device_ext_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_device_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-process-state-t:

zes_process_state_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_process_state_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-pci-address-t:

zes_pci_address_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_pci_address_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-pci-speed-t:

zes_pci_speed_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_pci_speed_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-pci-properties-t:

zes_pci_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_pci_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-pci-state-t:

zes_pci_state_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_pci_state_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-pci-bar-properties-t:

zes_pci_bar_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_pci_bar_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-pci-bar-properties-1-2-t:

zes_pci_bar_properties_1_2_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_pci_bar_properties_1_2_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-pci-stats-t:

zes_pci_stats_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_pci_stats_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Overclock
============================================================
* Functions


    * :ref:`zesDeviceSetOverclockWaiver`
    * :ref:`zesDeviceGetOverclockDomains`
    * :ref:`zesDeviceGetOverclockControls`
    * :ref:`zesDeviceResetOverclockSettings`
    * :ref:`zesDeviceReadOverclockState`
    * :ref:`zesDeviceEnumOverclockDomains`
    * :ref:`zesOverclockGetDomainProperties`
    * :ref:`zesOverclockGetDomainVFProperties`
    * :ref:`zesOverclockGetDomainControlProperties`
    * :ref:`zesOverclockGetControlCurrentValue`
    * :ref:`zesOverclockGetControlPendingValue`
    * :ref:`zesOverclockSetControlUserValue`
    * :ref:`zesOverclockGetControlState`
    * :ref:`zesOverclockGetVFPointValues`
    * :ref:`zesOverclockSetVFPointValues`

 
* Enumerations


    * :ref:`zes-overclock-domain-t`
    * :ref:`zes-overclock-control-t`
    * :ref:`zes-overclock-mode-t`
    * :ref:`zes-control-state-t`
    * :ref:`zes-pending-action-t`
    * :ref:`zes-vf-program-type-t`
    * :ref:`zes-vf-type-t`
    * :ref:`zes-vf-array-type-t`

 
* Structures


    * :ref:`zes-overclock-properties-t`
    * :ref:`zes-control-property-t`
    * :ref:`zes-vf-property-t`


Overclock Functions
------------------------------------------------------------------------------


.. _zesDeviceSetOverclockWaiver:

zesDeviceSetOverclockWaiver
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceSetOverclockWaiver
    :project: LevelZero


.. _zesDeviceGetOverclockDomains:

zesDeviceGetOverclockDomains
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceGetOverclockDomains
    :project: LevelZero


.. _zesDeviceGetOverclockControls:

zesDeviceGetOverclockControls
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceGetOverclockControls
    :project: LevelZero


.. _zesDeviceResetOverclockSettings:

zesDeviceResetOverclockSettings
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceResetOverclockSettings
    :project: LevelZero


.. _zesDeviceReadOverclockState:

zesDeviceReadOverclockState
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceReadOverclockState
    :project: LevelZero


.. _zesDeviceEnumOverclockDomains:

zesDeviceEnumOverclockDomains
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEnumOverclockDomains
    :project: LevelZero


.. _zesOverclockGetDomainProperties:

zesOverclockGetDomainProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesOverclockGetDomainProperties
    :project: LevelZero


.. _zesOverclockGetDomainVFProperties:

zesOverclockGetDomainVFProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesOverclockGetDomainVFProperties
    :project: LevelZero


.. _zesOverclockGetDomainControlProperties:

zesOverclockGetDomainControlProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesOverclockGetDomainControlProperties
    :project: LevelZero


.. _zesOverclockGetControlCurrentValue:

zesOverclockGetControlCurrentValue
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesOverclockGetControlCurrentValue
    :project: LevelZero


.. _zesOverclockGetControlPendingValue:

zesOverclockGetControlPendingValue
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesOverclockGetControlPendingValue
    :project: LevelZero


.. _zesOverclockSetControlUserValue:

zesOverclockSetControlUserValue
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesOverclockSetControlUserValue
    :project: LevelZero


.. _zesOverclockGetControlState:

zesOverclockGetControlState
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesOverclockGetControlState
    :project: LevelZero


.. _zesOverclockGetVFPointValues:

zesOverclockGetVFPointValues
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesOverclockGetVFPointValues
    :project: LevelZero


.. _zesOverclockSetVFPointValues:

zesOverclockSetVFPointValues
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesOverclockSetVFPointValues
    :project: LevelZero



Overclock Enums
------------------------------------------------------------------------------


.. _zes-overclock-domain-t:

zes_overclock_domain_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_overclock_domain_t
    :project: LevelZero


.. _zes-overclock-control-t:

zes_overclock_control_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_overclock_control_t
    :project: LevelZero


.. _zes-overclock-mode-t:

zes_overclock_mode_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_overclock_mode_t
    :project: LevelZero


.. _zes-control-state-t:

zes_control_state_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_control_state_t
    :project: LevelZero


.. _zes-pending-action-t:

zes_pending_action_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_pending_action_t
    :project: LevelZero


.. _zes-vf-program-type-t:

zes_vf_program_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_vf_program_type_t
    :project: LevelZero


.. _zes-vf-type-t:

zes_vf_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_vf_type_t
    :project: LevelZero


.. _zes-vf-array-type-t:

zes_vf_array_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_vf_array_type_t
    :project: LevelZero

 
Overclock Structures
------------------------------------------------------------------------------

.. _zes-overclock-properties-t:

zes_overclock_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_overclock_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-control-property-t:

zes_control_property_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_control_property_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-vf-property-t:

zes_vf_property_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_vf_property_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Diagnostics
============================================================
* Functions


    * :ref:`zesDeviceEnumDiagnosticTestSuites`
    * :ref:`zesDiagnosticsGetProperties`
    * :ref:`zesDiagnosticsGetTests`
    * :ref:`zesDiagnosticsRunTests`

 
* Enumerations


    * :ref:`zes-diag-result-t`

 
* Structures


    * :ref:`zes-diag-test-t`
    * :ref:`zes-diag-properties-t`


Diagnostics Functions
------------------------------------------------------------------------------


.. _zesDeviceEnumDiagnosticTestSuites:

zesDeviceEnumDiagnosticTestSuites
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEnumDiagnosticTestSuites
    :project: LevelZero


.. _zesDiagnosticsGetProperties:

zesDiagnosticsGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDiagnosticsGetProperties
    :project: LevelZero


.. _zesDiagnosticsGetTests:

zesDiagnosticsGetTests
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDiagnosticsGetTests
    :project: LevelZero


.. _zesDiagnosticsRunTests:

zesDiagnosticsRunTests
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDiagnosticsRunTests
    :project: LevelZero



Diagnostics Enums
------------------------------------------------------------------------------


.. _zes-diag-result-t:

zes_diag_result_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_diag_result_t
    :project: LevelZero

 
Diagnostics Structures
------------------------------------------------------------------------------

.. _zes-diag-test-t:

zes_diag_test_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_diag_test_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-diag-properties-t:

zes_diag_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_diag_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Ecc
============================================================
* Functions


    * :ref:`zesDeviceEccAvailable`
    * :ref:`zesDeviceEccConfigurable`
    * :ref:`zesDeviceGetEccState`
    * :ref:`zesDeviceSetEccState`

 
* Enumerations


    * :ref:`zes-device-ecc-state-t`
    * :ref:`zes-device-action-t`

 
* Structures


    * :ref:`zes-device-ecc-desc-t`
    * :ref:`zes-device-ecc-properties-t`


Ecc Functions
------------------------------------------------------------------------------


.. _zesDeviceEccAvailable:

zesDeviceEccAvailable
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEccAvailable
    :project: LevelZero


.. _zesDeviceEccConfigurable:

zesDeviceEccConfigurable
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEccConfigurable
    :project: LevelZero


.. _zesDeviceGetEccState:

zesDeviceGetEccState
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceGetEccState
    :project: LevelZero


.. _zesDeviceSetEccState:

zesDeviceSetEccState
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceSetEccState
    :project: LevelZero



Ecc Enums
------------------------------------------------------------------------------


.. _zes-device-ecc-state-t:

zes_device_ecc_state_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_device_ecc_state_t
    :project: LevelZero


.. _zes-device-action-t:

zes_device_action_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_device_action_t
    :project: LevelZero

 
Ecc Structures
------------------------------------------------------------------------------

.. _zes-device-ecc-desc-t:

zes_device_ecc_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_device_ecc_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-device-ecc-properties-t:

zes_device_ecc_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_device_ecc_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Engine
============================================================
* Functions


    * :ref:`zesDeviceEnumEngineGroups`
    * :ref:`zesEngineGetProperties`
    * :ref:`zesEngineGetActivity`

 
* Enumerations


    * :ref:`zes-engine-group-t`

 
* Structures


    * :ref:`zes-engine-properties-t`
    * :ref:`zes-engine-stats-t`


Engine Functions
------------------------------------------------------------------------------


.. _zesDeviceEnumEngineGroups:

zesDeviceEnumEngineGroups
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEnumEngineGroups
    :project: LevelZero


.. _zesEngineGetProperties:

zesEngineGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesEngineGetProperties
    :project: LevelZero


.. _zesEngineGetActivity:

zesEngineGetActivity
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesEngineGetActivity
    :project: LevelZero



Engine Enums
------------------------------------------------------------------------------


.. _zes-engine-group-t:

zes_engine_group_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_engine_group_t
    :project: LevelZero

 
Engine Structures
------------------------------------------------------------------------------

.. _zes-engine-properties-t:

zes_engine_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_engine_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-engine-stats-t:

zes_engine_stats_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_engine_stats_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Events
============================================================
* Functions


    * :ref:`zesDeviceEventRegister`
    * :ref:`zesDriverEventListen`
    * :ref:`zesDriverEventListenEx`

 
* Enumerations


    * :ref:`zes-event-type-flags-t`

 


Events Functions
------------------------------------------------------------------------------


.. _zesDeviceEventRegister:

zesDeviceEventRegister
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEventRegister
    :project: LevelZero


.. _zesDriverEventListen:

zesDriverEventListen
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDriverEventListen
    :project: LevelZero


.. _zesDriverEventListenEx:

zesDriverEventListenEx
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDriverEventListenEx
    :project: LevelZero



Events Enums
------------------------------------------------------------------------------


.. _zes-event-type-flags-t:

zes_event_type_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_event_type_flag_t
    :project: LevelZero

 

 

Fabric
============================================================
* Functions


    * :ref:`zesDeviceEnumFabricPorts`
    * :ref:`zesFabricPortGetProperties`
    * :ref:`zesFabricPortGetLinkType`
    * :ref:`zesFabricPortGetConfig`
    * :ref:`zesFabricPortSetConfig`
    * :ref:`zesFabricPortGetState`
    * :ref:`zesFabricPortGetThroughput`
    * :ref:`zesFabricPortGetFabricErrorCounters`
    * :ref:`zesFabricPortGetMultiPortThroughput`

 
* Enumerations


    * :ref:`zes-fabric-port-status-t`
    * :ref:`zes-fabric-port-qual-issue-flags-t`
    * :ref:`zes-fabric-port-failure-flags-t`

 
* Structures


    * :ref:`zes-fabric-port-id-t`
    * :ref:`zes-fabric-port-speed-t`
    * :ref:`zes-fabric-port-properties-t`
    * :ref:`zes-fabric-link-type-t`
    * :ref:`zes-fabric-port-config-t`
    * :ref:`zes-fabric-port-state-t`
    * :ref:`zes-fabric-port-throughput-t`
    * :ref:`zes-fabric-port-error-counters-t`


Fabric Functions
------------------------------------------------------------------------------


.. _zesDeviceEnumFabricPorts:

zesDeviceEnumFabricPorts
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEnumFabricPorts
    :project: LevelZero


.. _zesFabricPortGetProperties:

zesFabricPortGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFabricPortGetProperties
    :project: LevelZero


.. _zesFabricPortGetLinkType:

zesFabricPortGetLinkType
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFabricPortGetLinkType
    :project: LevelZero


.. _zesFabricPortGetConfig:

zesFabricPortGetConfig
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFabricPortGetConfig
    :project: LevelZero


.. _zesFabricPortSetConfig:

zesFabricPortSetConfig
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFabricPortSetConfig
    :project: LevelZero


.. _zesFabricPortGetState:

zesFabricPortGetState
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFabricPortGetState
    :project: LevelZero


.. _zesFabricPortGetThroughput:

zesFabricPortGetThroughput
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFabricPortGetThroughput
    :project: LevelZero


.. _zesFabricPortGetFabricErrorCounters:

zesFabricPortGetFabricErrorCounters
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFabricPortGetFabricErrorCounters
    :project: LevelZero


.. _zesFabricPortGetMultiPortThroughput:

zesFabricPortGetMultiPortThroughput
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFabricPortGetMultiPortThroughput
    :project: LevelZero



Fabric Enums
------------------------------------------------------------------------------


.. _zes-fabric-port-status-t:

zes_fabric_port_status_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_fabric_port_status_t
    :project: LevelZero


.. _zes-fabric-port-qual-issue-flags-t:

zes_fabric_port_qual_issue_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_fabric_port_qual_issue_flag_t
    :project: LevelZero


.. _zes-fabric-port-failure-flags-t:

zes_fabric_port_failure_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_fabric_port_failure_flag_t
    :project: LevelZero

 
Fabric Structures
------------------------------------------------------------------------------

.. _zes-fabric-port-id-t:

zes_fabric_port_id_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_fabric_port_id_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-fabric-port-speed-t:

zes_fabric_port_speed_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_fabric_port_speed_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-fabric-port-properties-t:

zes_fabric_port_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_fabric_port_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-fabric-link-type-t:

zes_fabric_link_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_fabric_link_type_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-fabric-port-config-t:

zes_fabric_port_config_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_fabric_port_config_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-fabric-port-state-t:

zes_fabric_port_state_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_fabric_port_state_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-fabric-port-throughput-t:

zes_fabric_port_throughput_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_fabric_port_throughput_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-fabric-port-error-counters-t:

zes_fabric_port_error_counters_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_fabric_port_error_counters_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Fan
============================================================
* Functions


    * :ref:`zesDeviceEnumFans`
    * :ref:`zesFanGetProperties`
    * :ref:`zesFanGetConfig`
    * :ref:`zesFanSetDefaultMode`
    * :ref:`zesFanSetFixedSpeedMode`
    * :ref:`zesFanSetSpeedTableMode`
    * :ref:`zesFanGetState`

 
* Enumerations


    * :ref:`zes-fan-speed-mode-t`
    * :ref:`zes-fan-speed-units-t`

 
* Structures


    * :ref:`zes-fan-speed-t`
    * :ref:`zes-fan-temp-speed-t`
    * :ref:`zes-fan-speed-table-t`
    * :ref:`zes-fan-properties-t`
    * :ref:`zes-fan-config-t`


Fan Functions
------------------------------------------------------------------------------


.. _zesDeviceEnumFans:

zesDeviceEnumFans
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEnumFans
    :project: LevelZero


.. _zesFanGetProperties:

zesFanGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFanGetProperties
    :project: LevelZero


.. _zesFanGetConfig:

zesFanGetConfig
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFanGetConfig
    :project: LevelZero


.. _zesFanSetDefaultMode:

zesFanSetDefaultMode
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFanSetDefaultMode
    :project: LevelZero


.. _zesFanSetFixedSpeedMode:

zesFanSetFixedSpeedMode
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFanSetFixedSpeedMode
    :project: LevelZero


.. _zesFanSetSpeedTableMode:

zesFanSetSpeedTableMode
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFanSetSpeedTableMode
    :project: LevelZero


.. _zesFanGetState:

zesFanGetState
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFanGetState
    :project: LevelZero



Fan Enums
------------------------------------------------------------------------------


.. _zes-fan-speed-mode-t:

zes_fan_speed_mode_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_fan_speed_mode_t
    :project: LevelZero


.. _zes-fan-speed-units-t:

zes_fan_speed_units_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_fan_speed_units_t
    :project: LevelZero

 
Fan Structures
------------------------------------------------------------------------------

.. _zes-fan-speed-t:

zes_fan_speed_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_fan_speed_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-fan-temp-speed-t:

zes_fan_temp_speed_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_fan_temp_speed_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-fan-speed-table-t:

zes_fan_speed_table_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_fan_speed_table_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-fan-properties-t:

zes_fan_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_fan_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-fan-config-t:

zes_fan_config_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_fan_config_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Firmware
============================================================
* Functions


    * :ref:`zesDeviceEnumFirmwares`
    * :ref:`zesFirmwareGetProperties`
    * :ref:`zesFirmwareFlash`
    * :ref:`zesFirmwareGetFlashProgress`
    * :ref:`zesFirmwareGetConsoleLogs`

 

 
* Structures


    * :ref:`zes-firmware-properties-t`


Firmware Functions
------------------------------------------------------------------------------


.. _zesDeviceEnumFirmwares:

zesDeviceEnumFirmwares
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEnumFirmwares
    :project: LevelZero


.. _zesFirmwareGetProperties:

zesFirmwareGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFirmwareGetProperties
    :project: LevelZero


.. _zesFirmwareFlash:

zesFirmwareFlash
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFirmwareFlash
    :project: LevelZero


.. _zesFirmwareGetFlashProgress:

zesFirmwareGetFlashProgress
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFirmwareGetFlashProgress
    :project: LevelZero


.. _zesFirmwareGetConsoleLogs:

zesFirmwareGetConsoleLogs
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFirmwareGetConsoleLogs
    :project: LevelZero



 
Firmware Structures
------------------------------------------------------------------------------

.. _zes-firmware-properties-t:

zes_firmware_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_firmware_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Frequency
============================================================
* Functions


    * :ref:`zesDeviceEnumFrequencyDomains`
    * :ref:`zesFrequencyGetProperties`
    * :ref:`zesFrequencyGetAvailableClocks`
    * :ref:`zesFrequencyGetRange`
    * :ref:`zesFrequencySetRange`
    * :ref:`zesFrequencyGetState`
    * :ref:`zesFrequencyGetThrottleTime`
    * :ref:`zesFrequencyOcGetCapabilities`
    * :ref:`zesFrequencyOcGetFrequencyTarget`
    * :ref:`zesFrequencyOcSetFrequencyTarget`
    * :ref:`zesFrequencyOcGetVoltageTarget`
    * :ref:`zesFrequencyOcSetVoltageTarget`
    * :ref:`zesFrequencyOcSetMode`
    * :ref:`zesFrequencyOcGetMode`
    * :ref:`zesFrequencyOcGetIccMax`
    * :ref:`zesFrequencyOcSetIccMax`
    * :ref:`zesFrequencyOcGetTjMax`
    * :ref:`zesFrequencyOcSetTjMax`

 
* Enumerations


    * :ref:`zes-freq-domain-t`
    * :ref:`zes-freq-throttle-reason-flags-t`
    * :ref:`zes-oc-mode-t`

 
* Structures


    * :ref:`zes-freq-properties-t`
    * :ref:`zes-freq-range-t`
    * :ref:`zes-freq-state-t`
    * :ref:`zes-freq-throttle-time-t`
    * :ref:`zes-oc-capabilities-t`


Frequency Functions
------------------------------------------------------------------------------


.. _zesDeviceEnumFrequencyDomains:

zesDeviceEnumFrequencyDomains
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEnumFrequencyDomains
    :project: LevelZero


.. _zesFrequencyGetProperties:

zesFrequencyGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFrequencyGetProperties
    :project: LevelZero


.. _zesFrequencyGetAvailableClocks:

zesFrequencyGetAvailableClocks
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFrequencyGetAvailableClocks
    :project: LevelZero


.. _zesFrequencyGetRange:

zesFrequencyGetRange
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFrequencyGetRange
    :project: LevelZero


.. _zesFrequencySetRange:

zesFrequencySetRange
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFrequencySetRange
    :project: LevelZero


.. _zesFrequencyGetState:

zesFrequencyGetState
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFrequencyGetState
    :project: LevelZero


.. _zesFrequencyGetThrottleTime:

zesFrequencyGetThrottleTime
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFrequencyGetThrottleTime
    :project: LevelZero


.. _zesFrequencyOcGetCapabilities:

zesFrequencyOcGetCapabilities
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFrequencyOcGetCapabilities
    :project: LevelZero


.. _zesFrequencyOcGetFrequencyTarget:

zesFrequencyOcGetFrequencyTarget
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFrequencyOcGetFrequencyTarget
    :project: LevelZero


.. _zesFrequencyOcSetFrequencyTarget:

zesFrequencyOcSetFrequencyTarget
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFrequencyOcSetFrequencyTarget
    :project: LevelZero


.. _zesFrequencyOcGetVoltageTarget:

zesFrequencyOcGetVoltageTarget
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFrequencyOcGetVoltageTarget
    :project: LevelZero


.. _zesFrequencyOcSetVoltageTarget:

zesFrequencyOcSetVoltageTarget
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFrequencyOcSetVoltageTarget
    :project: LevelZero


.. _zesFrequencyOcSetMode:

zesFrequencyOcSetMode
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFrequencyOcSetMode
    :project: LevelZero


.. _zesFrequencyOcGetMode:

zesFrequencyOcGetMode
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFrequencyOcGetMode
    :project: LevelZero


.. _zesFrequencyOcGetIccMax:

zesFrequencyOcGetIccMax
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFrequencyOcGetIccMax
    :project: LevelZero


.. _zesFrequencyOcSetIccMax:

zesFrequencyOcSetIccMax
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFrequencyOcSetIccMax
    :project: LevelZero


.. _zesFrequencyOcGetTjMax:

zesFrequencyOcGetTjMax
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFrequencyOcGetTjMax
    :project: LevelZero


.. _zesFrequencyOcSetTjMax:

zesFrequencyOcSetTjMax
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFrequencyOcSetTjMax
    :project: LevelZero



Frequency Enums
------------------------------------------------------------------------------


.. _zes-freq-domain-t:

zes_freq_domain_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_freq_domain_t
    :project: LevelZero


.. _zes-freq-throttle-reason-flags-t:

zes_freq_throttle_reason_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_freq_throttle_reason_flag_t
    :project: LevelZero


.. _zes-oc-mode-t:

zes_oc_mode_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_oc_mode_t
    :project: LevelZero

 
Frequency Structures
------------------------------------------------------------------------------

.. _zes-freq-properties-t:

zes_freq_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_freq_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-freq-range-t:

zes_freq_range_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_freq_range_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-freq-state-t:

zes_freq_state_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_freq_state_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-freq-throttle-time-t:

zes_freq_throttle_time_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_freq_throttle_time_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-oc-capabilities-t:

zes_oc_capabilities_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_oc_capabilities_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Led
============================================================
* Functions


    * :ref:`zesDeviceEnumLeds`
    * :ref:`zesLedGetProperties`
    * :ref:`zesLedGetState`
    * :ref:`zesLedSetState`
    * :ref:`zesLedSetColor`

 

 
* Structures


    * :ref:`zes-led-properties-t`
    * :ref:`zes-led-color-t`
    * :ref:`zes-led-state-t`


Led Functions
------------------------------------------------------------------------------


.. _zesDeviceEnumLeds:

zesDeviceEnumLeds
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEnumLeds
    :project: LevelZero


.. _zesLedGetProperties:

zesLedGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesLedGetProperties
    :project: LevelZero


.. _zesLedGetState:

zesLedGetState
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesLedGetState
    :project: LevelZero


.. _zesLedSetState:

zesLedSetState
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesLedSetState
    :project: LevelZero


.. _zesLedSetColor:

zesLedSetColor
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesLedSetColor
    :project: LevelZero



 
Led Structures
------------------------------------------------------------------------------

.. _zes-led-properties-t:

zes_led_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_led_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-led-color-t:

zes_led_color_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_led_color_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-led-state-t:

zes_led_state_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_led_state_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Memory
============================================================
* Functions


    * :ref:`zesDeviceEnumMemoryModules`
    * :ref:`zesMemoryGetProperties`
    * :ref:`zesMemoryGetState`
    * :ref:`zesMemoryGetBandwidth`

 
* Enumerations


    * :ref:`zes-mem-type-t`
    * :ref:`zes-mem-loc-t`
    * :ref:`zes-mem-health-t`

 
* Structures


    * :ref:`zes-mem-properties-t`
    * :ref:`zes-mem-state-t`
    * :ref:`zes-mem-bandwidth-t`
    * :ref:`zes-mem-ext-bandwidth-t`


Memory Functions
------------------------------------------------------------------------------


.. _zesDeviceEnumMemoryModules:

zesDeviceEnumMemoryModules
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEnumMemoryModules
    :project: LevelZero


.. _zesMemoryGetProperties:

zesMemoryGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesMemoryGetProperties
    :project: LevelZero


.. _zesMemoryGetState:

zesMemoryGetState
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesMemoryGetState
    :project: LevelZero


.. _zesMemoryGetBandwidth:

zesMemoryGetBandwidth
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesMemoryGetBandwidth
    :project: LevelZero



Memory Enums
------------------------------------------------------------------------------


.. _zes-mem-type-t:

zes_mem_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_mem_type_t
    :project: LevelZero


.. _zes-mem-loc-t:

zes_mem_loc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_mem_loc_t
    :project: LevelZero


.. _zes-mem-health-t:

zes_mem_health_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_mem_health_t
    :project: LevelZero

 
Memory Structures
------------------------------------------------------------------------------

.. _zes-mem-properties-t:

zes_mem_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_mem_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-mem-state-t:

zes_mem_state_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_mem_state_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-mem-bandwidth-t:

zes_mem_bandwidth_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_mem_bandwidth_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-mem-ext-bandwidth-t:

zes_mem_ext_bandwidth_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_mem_ext_bandwidth_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Performance
============================================================
* Functions


    * :ref:`zesDeviceEnumPerformanceFactorDomains`
    * :ref:`zesPerformanceFactorGetProperties`
    * :ref:`zesPerformanceFactorGetConfig`
    * :ref:`zesPerformanceFactorSetConfig`

 

 
* Structures


    * :ref:`zes-perf-properties-t`


Performance Functions
------------------------------------------------------------------------------


.. _zesDeviceEnumPerformanceFactorDomains:

zesDeviceEnumPerformanceFactorDomains
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEnumPerformanceFactorDomains
    :project: LevelZero


.. _zesPerformanceFactorGetProperties:

zesPerformanceFactorGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesPerformanceFactorGetProperties
    :project: LevelZero


.. _zesPerformanceFactorGetConfig:

zesPerformanceFactorGetConfig
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesPerformanceFactorGetConfig
    :project: LevelZero


.. _zesPerformanceFactorSetConfig:

zesPerformanceFactorSetConfig
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesPerformanceFactorSetConfig
    :project: LevelZero



 
Performance Structures
------------------------------------------------------------------------------

.. _zes-perf-properties-t:

zes_perf_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_perf_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Power
============================================================
* Functions


    * :ref:`zesDeviceEnumPowerDomains`
    * :ref:`zesDeviceGetCardPowerDomain`
    * :ref:`zesPowerGetProperties`
    * :ref:`zesPowerGetEnergyCounter`
    * :ref:`zesPowerGetLimits`
    * :ref:`zesPowerSetLimits`
    * :ref:`zesPowerGetEnergyThreshold`
    * :ref:`zesPowerSetEnergyThreshold`

 
* Enumerations


    * :ref:`zes-power-domain-t`
    * :ref:`zes-power-level-t`
    * :ref:`zes-power-source-t`
    * :ref:`zes-limit-unit-t`

 
* Structures


    * :ref:`zes-power-properties-t`
    * :ref:`zes-power-energy-counter-t`
    * :ref:`zes-power-sustained-limit-t`
    * :ref:`zes-power-burst-limit-t`
    * :ref:`zes-power-peak-limit-t`
    * :ref:`zes-energy-threshold-t`


Power Functions
------------------------------------------------------------------------------


.. _zesDeviceEnumPowerDomains:

zesDeviceEnumPowerDomains
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEnumPowerDomains
    :project: LevelZero


.. _zesDeviceGetCardPowerDomain:

zesDeviceGetCardPowerDomain
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceGetCardPowerDomain
    :project: LevelZero


.. _zesPowerGetProperties:

zesPowerGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesPowerGetProperties
    :project: LevelZero


.. _zesPowerGetEnergyCounter:

zesPowerGetEnergyCounter
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesPowerGetEnergyCounter
    :project: LevelZero


.. _zesPowerGetLimits:

zesPowerGetLimits
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesPowerGetLimits
    :project: LevelZero


.. _zesPowerSetLimits:

zesPowerSetLimits
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesPowerSetLimits
    :project: LevelZero


.. _zesPowerGetEnergyThreshold:

zesPowerGetEnergyThreshold
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesPowerGetEnergyThreshold
    :project: LevelZero


.. _zesPowerSetEnergyThreshold:

zesPowerSetEnergyThreshold
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesPowerSetEnergyThreshold
    :project: LevelZero



Power Enums
------------------------------------------------------------------------------


.. _zes-power-domain-t:

zes_power_domain_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_power_domain_t
    :project: LevelZero


.. _zes-power-level-t:

zes_power_level_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_power_level_t
    :project: LevelZero


.. _zes-power-source-t:

zes_power_source_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_power_source_t
    :project: LevelZero


.. _zes-limit-unit-t:

zes_limit_unit_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_limit_unit_t
    :project: LevelZero

 
Power Structures
------------------------------------------------------------------------------

.. _zes-power-properties-t:

zes_power_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_power_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-power-energy-counter-t:

zes_power_energy_counter_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_power_energy_counter_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-power-sustained-limit-t:

zes_power_sustained_limit_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_power_sustained_limit_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-power-burst-limit-t:

zes_power_burst_limit_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_power_burst_limit_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-power-peak-limit-t:

zes_power_peak_limit_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_power_peak_limit_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-energy-threshold-t:

zes_energy_threshold_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_energy_threshold_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Psu
============================================================
* Functions


    * :ref:`zesDeviceEnumPsus`
    * :ref:`zesPsuGetProperties`
    * :ref:`zesPsuGetState`

 
* Enumerations


    * :ref:`zes-psu-voltage-status-t`

 
* Structures


    * :ref:`zes-psu-properties-t`
    * :ref:`zes-psu-state-t`


Psu Functions
------------------------------------------------------------------------------


.. _zesDeviceEnumPsus:

zesDeviceEnumPsus
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEnumPsus
    :project: LevelZero


.. _zesPsuGetProperties:

zesPsuGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesPsuGetProperties
    :project: LevelZero


.. _zesPsuGetState:

zesPsuGetState
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesPsuGetState
    :project: LevelZero



Psu Enums
------------------------------------------------------------------------------


.. _zes-psu-voltage-status-t:

zes_psu_voltage_status_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_psu_voltage_status_t
    :project: LevelZero

 
Psu Structures
------------------------------------------------------------------------------

.. _zes-psu-properties-t:

zes_psu_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_psu_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-psu-state-t:

zes_psu_state_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_psu_state_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Ras
============================================================
* Functions


    * :ref:`zesDeviceEnumRasErrorSets`
    * :ref:`zesRasGetProperties`
    * :ref:`zesRasGetConfig`
    * :ref:`zesRasSetConfig`
    * :ref:`zesRasGetState`

 
* Enumerations


    * :ref:`zes-ras-error-type-t`
    * :ref:`zes-ras-error-cat-t`

 
* Structures


    * :ref:`zes-ras-properties-t`
    * :ref:`zes-ras-state-t`
    * :ref:`zes-ras-config-t`


Ras Functions
------------------------------------------------------------------------------


.. _zesDeviceEnumRasErrorSets:

zesDeviceEnumRasErrorSets
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEnumRasErrorSets
    :project: LevelZero


.. _zesRasGetProperties:

zesRasGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesRasGetProperties
    :project: LevelZero


.. _zesRasGetConfig:

zesRasGetConfig
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesRasGetConfig
    :project: LevelZero


.. _zesRasSetConfig:

zesRasSetConfig
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesRasSetConfig
    :project: LevelZero


.. _zesRasGetState:

zesRasGetState
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesRasGetState
    :project: LevelZero



Ras Enums
------------------------------------------------------------------------------


.. _zes-ras-error-type-t:

zes_ras_error_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_ras_error_type_t
    :project: LevelZero


.. _zes-ras-error-cat-t:

zes_ras_error_cat_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_ras_error_cat_t
    :project: LevelZero

 
Ras Structures
------------------------------------------------------------------------------

.. _zes-ras-properties-t:

zes_ras_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_ras_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-ras-state-t:

zes_ras_state_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_ras_state_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-ras-config-t:

zes_ras_config_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_ras_config_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Scheduler
============================================================
* Functions


    * :ref:`zesDeviceEnumSchedulers`
    * :ref:`zesSchedulerGetProperties`
    * :ref:`zesSchedulerGetCurrentMode`
    * :ref:`zesSchedulerGetTimeoutModeProperties`
    * :ref:`zesSchedulerGetTimesliceModeProperties`
    * :ref:`zesSchedulerSetTimeoutMode`
    * :ref:`zesSchedulerSetTimesliceMode`
    * :ref:`zesSchedulerSetExclusiveMode`
    * :ref:`zesSchedulerSetComputeUnitDebugMode`

 
* Enumerations


    * :ref:`zes-sched-mode-t`

 
* Structures


    * :ref:`zes-sched-properties-t`
    * :ref:`zes-sched-timeout-properties-t`
    * :ref:`zes-sched-timeslice-properties-t`


Scheduler Functions
------------------------------------------------------------------------------


.. _zesDeviceEnumSchedulers:

zesDeviceEnumSchedulers
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEnumSchedulers
    :project: LevelZero


.. _zesSchedulerGetProperties:

zesSchedulerGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesSchedulerGetProperties
    :project: LevelZero


.. _zesSchedulerGetCurrentMode:

zesSchedulerGetCurrentMode
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesSchedulerGetCurrentMode
    :project: LevelZero


.. _zesSchedulerGetTimeoutModeProperties:

zesSchedulerGetTimeoutModeProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesSchedulerGetTimeoutModeProperties
    :project: LevelZero


.. _zesSchedulerGetTimesliceModeProperties:

zesSchedulerGetTimesliceModeProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesSchedulerGetTimesliceModeProperties
    :project: LevelZero


.. _zesSchedulerSetTimeoutMode:

zesSchedulerSetTimeoutMode
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesSchedulerSetTimeoutMode
    :project: LevelZero


.. _zesSchedulerSetTimesliceMode:

zesSchedulerSetTimesliceMode
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesSchedulerSetTimesliceMode
    :project: LevelZero


.. _zesSchedulerSetExclusiveMode:

zesSchedulerSetExclusiveMode
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesSchedulerSetExclusiveMode
    :project: LevelZero


.. _zesSchedulerSetComputeUnitDebugMode:

zesSchedulerSetComputeUnitDebugMode
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesSchedulerSetComputeUnitDebugMode
    :project: LevelZero



Scheduler Enums
------------------------------------------------------------------------------


.. _zes-sched-mode-t:

zes_sched_mode_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_sched_mode_t
    :project: LevelZero

 
Scheduler Structures
------------------------------------------------------------------------------

.. _zes-sched-properties-t:

zes_sched_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_sched_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-sched-timeout-properties-t:

zes_sched_timeout_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_sched_timeout_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-sched-timeslice-properties-t:

zes_sched_timeslice_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_sched_timeslice_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Standby
============================================================
* Functions


    * :ref:`zesDeviceEnumStandbyDomains`
    * :ref:`zesStandbyGetProperties`
    * :ref:`zesStandbyGetMode`
    * :ref:`zesStandbySetMode`

 
* Enumerations


    * :ref:`zes-standby-type-t`
    * :ref:`zes-standby-promo-mode-t`

 
* Structures


    * :ref:`zes-standby-properties-t`


Standby Functions
------------------------------------------------------------------------------


.. _zesDeviceEnumStandbyDomains:

zesDeviceEnumStandbyDomains
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEnumStandbyDomains
    :project: LevelZero


.. _zesStandbyGetProperties:

zesStandbyGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesStandbyGetProperties
    :project: LevelZero


.. _zesStandbyGetMode:

zesStandbyGetMode
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesStandbyGetMode
    :project: LevelZero


.. _zesStandbySetMode:

zesStandbySetMode
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesStandbySetMode
    :project: LevelZero



Standby Enums
------------------------------------------------------------------------------


.. _zes-standby-type-t:

zes_standby_type_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_standby_type_t
    :project: LevelZero


.. _zes-standby-promo-mode-t:

zes_standby_promo_mode_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_standby_promo_mode_t
    :project: LevelZero

 
Standby Structures
------------------------------------------------------------------------------

.. _zes-standby-properties-t:

zes_standby_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_standby_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Temperature
============================================================
* Functions


    * :ref:`zesDeviceEnumTemperatureSensors`
    * :ref:`zesTemperatureGetProperties`
    * :ref:`zesTemperatureGetConfig`
    * :ref:`zesTemperatureSetConfig`
    * :ref:`zesTemperatureGetState`

 
* Enumerations


    * :ref:`zes-temp-sensors-t`

 
* Structures


    * :ref:`zes-temp-properties-t`
    * :ref:`zes-temp-threshold-t`
    * :ref:`zes-temp-config-t`


Temperature Functions
------------------------------------------------------------------------------


.. _zesDeviceEnumTemperatureSensors:

zesDeviceEnumTemperatureSensors
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEnumTemperatureSensors
    :project: LevelZero


.. _zesTemperatureGetProperties:

zesTemperatureGetProperties
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesTemperatureGetProperties
    :project: LevelZero


.. _zesTemperatureGetConfig:

zesTemperatureGetConfig
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesTemperatureGetConfig
    :project: LevelZero


.. _zesTemperatureSetConfig:

zesTemperatureSetConfig
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesTemperatureSetConfig
    :project: LevelZero


.. _zesTemperatureGetState:

zesTemperatureGetState
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesTemperatureGetState
    :project: LevelZero



Temperature Enums
------------------------------------------------------------------------------


.. _zes-temp-sensors-t:

zes_temp_sensors_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_temp_sensors_t
    :project: LevelZero

 
Temperature Structures
------------------------------------------------------------------------------

.. _zes-temp-properties-t:

zes_temp_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_temp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-temp-threshold-t:

zes_temp_threshold_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_temp_threshold_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-temp-config-t:

zes_temp_config_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_temp_config_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

Eccstate
============================================================
* Enumerations


    * :ref:`zes-device-ecc-default-properties-ext-version-t`

 
* Structures


    * :ref:`zes-device-ecc-default-properties-ext-t`




Eccstate Enums
------------------------------------------------------------------------------


.. _zes-device-ecc-default-properties-ext-version-t:

zes_device_ecc_default_properties_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_device_ecc_default_properties_ext_version_t
    :project: LevelZero

 
Eccstate Structures
------------------------------------------------------------------------------

.. _zes-device-ecc-default-properties-ext-t:

zes_device_ecc_default_properties_ext_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_device_ecc_default_properties_ext_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Powerlimits
============================================================
* Functions


    * :ref:`zesPowerGetLimitsExt`
    * :ref:`zesPowerSetLimitsExt`

 
* Enumerations


    * :ref:`zes-power-limits-ext-version-t`

 
* Structures


    * :ref:`zes-power-limit-ext-desc-t`
    * :ref:`zes-power-ext-properties-t`


Powerlimits Functions
------------------------------------------------------------------------------


.. _zesPowerGetLimitsExt:

zesPowerGetLimitsExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesPowerGetLimitsExt
    :project: LevelZero


.. _zesPowerSetLimitsExt:

zesPowerSetLimitsExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesPowerSetLimitsExt
    :project: LevelZero



Powerlimits Enums
------------------------------------------------------------------------------


.. _zes-power-limits-ext-version-t:

zes_power_limits_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_power_limits_ext_version_t
    :project: LevelZero

 
Powerlimits Structures
------------------------------------------------------------------------------

.. _zes-power-limit-ext-desc-t:

zes_power_limit_ext_desc_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_power_limit_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-power-ext-properties-t:

zes_power_ext_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_power_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Engineactivity
============================================================
* Functions


    * :ref:`zesEngineGetActivityExt`

 
* Enumerations


    * :ref:`zes-engine-activity-ext-version-t`

 
* Structures


    * :ref:`zes-engine-ext-properties-t`


Engineactivity Functions
------------------------------------------------------------------------------


.. _zesEngineGetActivityExt:

zesEngineGetActivityExt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesEngineGetActivityExt
    :project: LevelZero



Engineactivity Enums
------------------------------------------------------------------------------


.. _zes-engine-activity-ext-version-t:

zes_engine_activity_ext_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_engine_activity_ext_version_t
    :project: LevelZero

 
Engineactivity Structures
------------------------------------------------------------------------------

.. _zes-engine-ext-properties-t:

zes_engine_ext_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_engine_ext_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Rasstate
============================================================
* Functions


    * :ref:`zesRasGetStateExp`
    * :ref:`zesRasClearStateExp`

 
* Enumerations


    * :ref:`zes-ras-state-exp-version-t`
    * :ref:`zes-ras-error-category-exp-t`

 
* Structures


    * :ref:`zes-ras-state-exp-t`


Rasstate Functions
------------------------------------------------------------------------------


.. _zesRasGetStateExp:

zesRasGetStateExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesRasGetStateExp
    :project: LevelZero


.. _zesRasClearStateExp:

zesRasClearStateExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesRasClearStateExp
    :project: LevelZero



Rasstate Enums
------------------------------------------------------------------------------


.. _zes-ras-state-exp-version-t:

zes_ras_state_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_ras_state_exp_version_t
    :project: LevelZero


.. _zes-ras-error-category-exp-t:

zes_ras_error_category_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_ras_error_category_exp_t
    :project: LevelZero

 
Rasstate Structures
------------------------------------------------------------------------------

.. _zes-ras-state-exp-t:

zes_ras_state_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_ras_state_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

Mempageofflinestate
============================================================
* Enumerations


    * :ref:`zes-mem-page-offline-state-exp-version-t`

 
* Structures


    * :ref:`zes-mem-page-offline-state-exp-t`




Mempageofflinestate Enums
------------------------------------------------------------------------------


.. _zes-mem-page-offline-state-exp-version-t:

zes_mem_page_offline_state_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_mem_page_offline_state_exp_version_t
    :project: LevelZero

 
Mempageofflinestate Structures
------------------------------------------------------------------------------

.. _zes-mem-page-offline-state-exp-t:

zes_mem_page_offline_state_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_mem_page_offline_state_exp_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

Memorybwcountervalidbits
============================================================
* Enumerations


    * :ref:`zes-mem-bandwidth-counter-bits-exp-version-t`

 
* Structures


    * :ref:`zes-mem-bandwidth-counter-bits-exp-properties-t`




Memorybwcountervalidbits Enums
------------------------------------------------------------------------------


.. _zes-mem-bandwidth-counter-bits-exp-version-t:

zes_mem_bandwidth_counter_bits_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_mem_bandwidth_counter_bits_exp_version_t
    :project: LevelZero

 
Memorybwcountervalidbits Structures
------------------------------------------------------------------------------

.. _zes-mem-bandwidth-counter-bits-exp-properties-t:

zes_mem_bandwidth_counter_bits_exp_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_mem_bandwidth_counter_bits_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

 

Powerdomainproperties
============================================================
* Enumerations


    * :ref:`zes-power-domain-properties-exp-version-t`

 
* Structures


    * :ref:`zes-power-domain-exp-properties-t`




Powerdomainproperties Enums
------------------------------------------------------------------------------


.. _zes-power-domain-properties-exp-version-t:

zes_power_domain_properties_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_power_domain_properties_exp_version_t
    :project: LevelZero

 
Powerdomainproperties Structures
------------------------------------------------------------------------------

.. _zes-power-domain-exp-properties-t:

zes_power_domain_exp_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_power_domain_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Firmwaresecurityversion
============================================================
* Functions


    * :ref:`zesFirmwareGetSecurityVersionExp`
    * :ref:`zesFirmwareSetSecurityVersionExp`

 
* Enumerations


    * :ref:`zes-firmware-security-exp-version-t`

 


Firmwaresecurityversion Functions
------------------------------------------------------------------------------


.. _zesFirmwareGetSecurityVersionExp:

zesFirmwareGetSecurityVersionExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFirmwareGetSecurityVersionExp
    :project: LevelZero


.. _zesFirmwareSetSecurityVersionExp:

zesFirmwareSetSecurityVersionExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesFirmwareSetSecurityVersionExp
    :project: LevelZero



Firmwaresecurityversion Enums
------------------------------------------------------------------------------


.. _zes-firmware-security-exp-version-t:

zes_firmware_security_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_firmware_security_exp_version_t
    :project: LevelZero

 

 

Sysmandevicemapping
============================================================
* Functions


    * :ref:`zesDeviceGetSubDevicePropertiesExp`
    * :ref:`zesDriverGetDeviceByUuidExp`

 
* Enumerations


    * :ref:`zes-sysman-device-mapping-exp-version-t`

 
* Structures


    * :ref:`zes-subdevice-exp-properties-t`


Sysmandevicemapping Functions
------------------------------------------------------------------------------


.. _zesDeviceGetSubDevicePropertiesExp:

zesDeviceGetSubDevicePropertiesExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceGetSubDevicePropertiesExp
    :project: LevelZero


.. _zesDriverGetDeviceByUuidExp:

zesDriverGetDeviceByUuidExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDriverGetDeviceByUuidExp
    :project: LevelZero



Sysmandevicemapping Enums
------------------------------------------------------------------------------


.. _zes-sysman-device-mapping-exp-version-t:

zes_sysman_device_mapping_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_sysman_device_mapping_exp_version_t
    :project: LevelZero

 
Sysmandevicemapping Structures
------------------------------------------------------------------------------

.. _zes-subdevice-exp-properties-t:

zes_subdevice_exp_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_subdevice_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


 

Virtualfunctionmanagement
============================================================
* Functions


    * :ref:`zesDeviceEnumActiveVFExp`
    * :ref:`zesVFManagementGetVFPropertiesExp`
    * :ref:`zesVFManagementGetVFMemoryUtilizationExp`
    * :ref:`zesVFManagementGetVFEngineUtilizationExp`
    * :ref:`zesVFManagementSetVFTelemetryModeExp`
    * :ref:`zesVFManagementSetVFTelemetrySamplingIntervalExp`
    * :ref:`zesDeviceEnumEnabledVFExp`
    * :ref:`zesVFManagementGetVFCapabilitiesExp`
    * :ref:`zesVFManagementGetVFMemoryUtilizationExp2`
    * :ref:`zesVFManagementGetVFEngineUtilizationExp2`
    * :ref:`zesVFManagementGetVFCapabilitiesExp2`

 
* Enumerations


    * :ref:`zes-vf-management-exp-version-t`
    * :ref:`zes-vf-info-mem-type-exp-flags-t`
    * :ref:`zes-vf-info-util-exp-flags-t`

 
* Structures


    * :ref:`zes-vf-exp-properties-t`
    * :ref:`zes-vf-util-mem-exp-t`
    * :ref:`zes-vf-util-engine-exp-t`
    * :ref:`zes-vf-exp-capabilities-t`
    * :ref:`zes-vf-exp2-capabilities-t`
    * :ref:`zes-vf-util-mem-exp2-t`
    * :ref:`zes-vf-util-engine-exp2-t`


Virtualfunctionmanagement Functions
------------------------------------------------------------------------------


.. _zesDeviceEnumActiveVFExp:

zesDeviceEnumActiveVFExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEnumActiveVFExp
    :project: LevelZero


.. _zesVFManagementGetVFPropertiesExp:

zesVFManagementGetVFPropertiesExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesVFManagementGetVFPropertiesExp
    :project: LevelZero


.. _zesVFManagementGetVFMemoryUtilizationExp:

zesVFManagementGetVFMemoryUtilizationExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesVFManagementGetVFMemoryUtilizationExp
    :project: LevelZero


.. _zesVFManagementGetVFEngineUtilizationExp:

zesVFManagementGetVFEngineUtilizationExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesVFManagementGetVFEngineUtilizationExp
    :project: LevelZero


.. _zesVFManagementSetVFTelemetryModeExp:

zesVFManagementSetVFTelemetryModeExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesVFManagementSetVFTelemetryModeExp
    :project: LevelZero


.. _zesVFManagementSetVFTelemetrySamplingIntervalExp:

zesVFManagementSetVFTelemetrySamplingIntervalExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesVFManagementSetVFTelemetrySamplingIntervalExp
    :project: LevelZero


.. _zesDeviceEnumEnabledVFExp:

zesDeviceEnumEnabledVFExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesDeviceEnumEnabledVFExp
    :project: LevelZero


.. _zesVFManagementGetVFCapabilitiesExp:

zesVFManagementGetVFCapabilitiesExp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesVFManagementGetVFCapabilitiesExp
    :project: LevelZero


.. _zesVFManagementGetVFMemoryUtilizationExp2:

zesVFManagementGetVFMemoryUtilizationExp2
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesVFManagementGetVFMemoryUtilizationExp2
    :project: LevelZero


.. _zesVFManagementGetVFEngineUtilizationExp2:

zesVFManagementGetVFEngineUtilizationExp2
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesVFManagementGetVFEngineUtilizationExp2
    :project: LevelZero


.. _zesVFManagementGetVFCapabilitiesExp2:

zesVFManagementGetVFCapabilitiesExp2
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: zesVFManagementGetVFCapabilitiesExp2
    :project: LevelZero



Virtualfunctionmanagement Enums
------------------------------------------------------------------------------


.. _zes-vf-management-exp-version-t:

zes_vf_management_exp_version_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_vf_management_exp_version_t
    :project: LevelZero


.. _zes-vf-info-mem-type-exp-flags-t:

zes_vf_info_mem_type_exp_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_vf_info_mem_type_exp_flag_t
    :project: LevelZero


.. _zes-vf-info-util-exp-flags-t:

zes_vf_info_util_exp_flags_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: zes_vf_info_util_exp_flag_t
    :project: LevelZero

 
Virtualfunctionmanagement Structures
------------------------------------------------------------------------------

.. _zes-vf-exp-properties-t:

zes_vf_exp_properties_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_vf_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-vf-util-mem-exp-t:

zes_vf_util_mem_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_vf_util_mem_exp_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-vf-util-engine-exp-t:

zes_vf_util_engine_exp_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_vf_util_engine_exp_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-vf-exp-capabilities-t:

zes_vf_exp_capabilities_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_vf_exp_capabilities_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-vf-exp2-capabilities-t:

zes_vf_exp2_capabilities_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_vf_exp2_capabilities_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-vf-util-mem-exp2-t:

zes_vf_util_mem_exp2_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_vf_util_mem_exp2_t
    :project: LevelZero
    :members:
    :undoc-members:

.. _zes-vf-util-engine-exp2-t:

zes_vf_util_engine_exp2_t
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: zes_vf_util_engine_exp2_t
    :project: LevelZero
    :members:
    :undoc-members:


