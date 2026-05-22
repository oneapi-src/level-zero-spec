
:orphan:

.. _ZES_extension_pci_link_speed_downgrade:

=======================================
 PCI Link Speed Downgrade Extension
=======================================

API
----

* Functions

    * :ref:`zesDevicePciLinkSpeedUpdateExt`

* Enumerations

    * :ref:`zes-pci-link-speed-downgrade-ext-version-t`

* Structures

    * :ref:`zes-pci-link-speed-downgrade-ext-state-t`
    * :ref:`zes-pci-link-speed-downgrade-ext-properties-t`

PCI Link Speed Downgrade
~~~~~~~~~~~~~~~~~~~~~~~~~

This extension provides the ability to query and update PCIe link speed, enabling downgrade or upgrade (restore to its default speed) of the connection between the device and the host.

Query PCI Link Speed Downgrade Capability
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To check if the device supports PCIe link speed downgrade capability, pass :ref:`zes-pci-link-speed-downgrade-ext-properties-t` to :ref:`zesDevicePciGetProperties` as pNext member of :ref:`zes-pci-properties-t`\.

.. parsed-literal:

    :ref:`zes-pci-properties-t` pciProperties = {:ref:`ZES_STRUCTURE_TYPE_PCI_PROPERTIES <zes-structure-type-t>`\};
    :ref:`zes-pci-link-speed-downgrade-ext-properties-t` extProperties = {:ref:`ZES_STRUCTURE_TYPE_PCI_LINK_SPEED_DOWNGRADE_EXT_PROPERTIES <zes-structure-type-t>`\};
    pciProperties.pNext = &extProperties;
    :ref:`ze-result-t` result = :ref:`zesDevicePciGetProperties`\(hDevice, &pciProperties);
    
    if (extProperties.pciLinkSpeedUpdateCapable) {
        // Device supports PCIe link speed update
        // maxPciGenSupported indicates the maximum PCIe generation supported
    }

Query PCI Link Speed Downgrade Status
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To check the current PCIe downgrade status, pass :ref:`zes-pci-link-speed-downgrade-ext-state-t` to :ref:`zesDevicePciGetState` as pNext member of :ref:`zes-pci-state-t`\.

.. parsed-literal:

    :ref:`zes-pci-state-t` pciState = {:ref:`ZES_STRUCTURE_TYPE_PCI_STATE <zes-structure-type-t>`\};
    :ref:`zes-pci-link-speed-downgrade-ext-state-t` extState = {:ref:`ZES_STRUCTURE_TYPE_PCI_LINK_SPEED_DOWNGRADE_EXT_STATE <zes-structure-type-t>`\};
    pciState.pNext = &extState;
    :ref:`ze-result-t` result = :ref:`zesDevicePciGetState`\(hDevice, &pciState);
    
    if (extState.pciLinkSpeedDowngradeStatus) {
        // PCIe link is currently downgraded
    } else {
        // PCIe link is operating at normal speed
    }

Update PCI Link Speed
~~~~~~~~~~~~~~~~~~~~~

To downgrade or set to the default PCIe link speed, use :ref:`zesDevicePciLinkSpeedUpdateExt` function.

.. parsed-literal::

    :ref:`zes-device-action-t` pendingAction;
    ze_bool_t shouldDowngrade = true;  // true for downgrade
    
    :ref:`ze-result-t` result = :ref:`zesDevicePciLinkSpeedUpdateExt`\(hDevice, shouldDowngrade, &pendingAction);

Example Usage
~~~~~~~~~~~~~

The following pseudo-code demonstrates an example Usage for managing PCIe link speed:

.. parsed-literal::

    // Step 1: Check if device supports PCIe link speed update
    :ref:`zes-pci-properties-t` pciProperties = {:ref:`ZES_STRUCTURE_TYPE_PCI_PROPERTIES <zes-structure-type-t>`\};
    :ref:`zes-pci-link-speed-downgrade-ext-properties-t` extProperties = {:ref:`ZES_STRUCTURE_TYPE_PCI_LINK_SPEED_DOWNGRADE_EXT_PROPERTIES <zes-structure-type-t>`\};
    pciProperties.pNext = &extProperties;
    
    if (:ref:`zesDevicePciGetProperties`\(hDevice, &pciProperties) == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\) {
        if (!extProperties.pciLinkSpeedUpdateCapable) {
            // Device does not support PCIe link speed update
            return;
        }
        
        printf("Max PCIe Gen Supported: %d\\n", extProperties.maxPciGenSupported);
    }
    
    // Step 2: Check current downgrade status
    :ref:`zes-pci-state-t` pciState = {:ref:`ZES_STRUCTURE_TYPE_PCI_STATE <zes-structure-type-t>`\};
    :ref:`zes-pci-link-speed-downgrade-ext-state-t` extState = {:ref:`ZES_STRUCTURE_TYPE_PCI_LINK_SPEED_DOWNGRADE_EXT_STATE <zes-structure-type-t>`\};
    pciState.pNext = &extState;
    
    if (:ref:`zesDevicePciGetState`\(hDevice, &pciState) == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\) {
        printf("Current downgrade status: %s\\n", 
               extState.pciLinkSpeedDowngradeStatus ? "Downgraded" : "Normal");
    }
    
    // Step 3: Perform downgrade
    :ref:`zes-device-action-t` pendingAction;
    :ref:`ze-result-t` result = :ref:`zesDevicePciLinkSpeedUpdateExt`\(hDevice, true, &pendingAction);
    
    if (result == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\) {
        printf("PCIe link speed downgrade initiated\\n");
        printf("Required action: %d\\n", pendingAction);
    }
