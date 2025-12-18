<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
    s=tags['$s']
    S=s.upper()
%>
:orphan:

.. _ZES_extension_pci_link_speed_downgrade:

=======================================
 PCI Link Speed Downgrade Extension
=======================================

API
----

* Functions

    * ${s}DevicePciLinkSpeedUpdateExt

* Enumerations

    * ${s}_pci_link_speed_downgrade_ext_version_t

* Structures

    * ${s}_pci_link_speed_downgrade_ext_state_t
    * ${s}_pci_link_speed_downgrade_ext_properties_t

PCI Link Speed Downgrade
~~~~~~~~~~~~~~~~~~~~~~~~~

This extension provides the ability to query and update PCIe link speed, enabling downgrade or upgrade (restore to its default speed) of the connection between the device and the host.

Query PCI Link Speed Downgrade Capability
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To check if the device supports PCIe link speed downgrade capability, pass ${s}_pci_link_speed_downgrade_ext_properties_t to ${s}DevicePciGetProperties as pNext member of ${s}_pci_properties_t.

.. parsed-literal:

    ${s}_pci_properties_t pciProperties = {${S}_STRUCTURE_TYPE_PCI_PROPERTIES};
    ${s}_pci_link_speed_downgrade_ext_properties_t extProperties = {${S}_PCI_LINK_SPEED_DOWNGRADE_EXT_PROPERTIES};
    pciProperties.pNext = &extProperties;
    ${x}_result_t result = ${s}DevicePciGetProperties(hDevice, &pciProperties);
    
    if (extProperties.pciLinkSpeedUpdateCapable) {
        // Device supports PCIe link speed update
        // maxPciGenSupported indicates the maximum PCIe generation supported
    }

Query PCI Link Speed Downgrade Status
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To check the current PCIe downgrade status, pass ${s}_pci_link_speed_downgrade_ext_state_t to ${s}DevicePciGetState as pNext member of ${s}_pci_state_t.

.. parsed-literal:

    ${s}_pci_state_t pciState = {${S}_STRUCTURE_TYPE_PCI_STATE};
    ${s}_pci_link_speed_downgrade_ext_state_t extState = {${S}_PCI_LINK_SPEED_DOWNGRADE_EXT_STATE};
    pciState.pNext = &extState;
    ${x}_result_t result = ${s}DevicePciGetState(hDevice, &pciState);
    
    if (extState.pciLinkSpeedDowngradeStatus) {
        // PCIe link is currently downgraded
    } else {
        // PCIe link is operating at normal speed
    }

Update PCI Link Speed
~~~~~~~~~~~~~~~~~~~~~

To downgrade or set to the default PCIe link speed, use ${s}DevicePciLinkSpeedUpdateExt function.

.. parsed-literal::

    ${s}_device_action_t pendingAction;
    ${x}_bool_t shouldDowngrade = true;  // true for downgrade
    
    ${x}_result_t result = ${s}DevicePciLinkSpeedUpdateExt(hDevice, shouldDowngrade, &pendingAction);

Example Usage
~~~~~~~~~~~~~

The following pseudo-code demonstrates an example Usage for managing PCIe link speed:

.. parsed-literal::

    // Step 1: Check if device supports PCIe link speed update
    ${s}_pci_properties_t pciProperties = {${S}_STRUCTURE_TYPE_PCI_PROPERTIES};
    ${s}_pci_link_speed_downgrade_ext_properties_t extProperties = {${S}_PCI_LINK_SPEED_DOWNGRADE_EXT_PROPERTIES};
    pciProperties.pNext = &extProperties;
    
    if (${s}DevicePciGetProperties(hDevice, &pciProperties) == ${X}_RESULT_SUCCESS) {
        if (!extProperties.pciLinkSpeedUpdateCapable) {
            // Device does not support PCIe link speed update
            return;
        }
        
        printf("Max PCIe Gen Supported: %d\\n", extProperties.maxPciGenSupported);
    }
    
    // Step 2: Check current downgrade status
    ${s}_pci_state_t pciState = {${S}_STRUCTURE_TYPE_PCI_STATE};
    ${s}_pci_link_speed_downgrade_ext_state_t extState = {${S}_PCI_LINK_SPEED_DOWNGRADE_EXT_STATE};
    pciState.pNext = &extState;
    
    if (${s}DevicePciGetState(hDevice, &pciState) == ${X}_RESULT_SUCCESS) {
        printf("Current downgrade status: %s\\n", 
               extState.pciLinkSpeedDowngradeStatus ? "Downgraded" : "Normal");
    }
    
    // Step 3: Perform downgrade
    ${s}_device_action_t pendingAction;
    ${x}_result_t result = ${s}DevicePciLinkSpeedUpdateExt(hDevice, true, &pendingAction);
    
    if (result == ${X}_RESULT_SUCCESS) {
        printf("PCIe link speed downgrade initiated\\n");
        printf("Required action: %d\\n", pendingAction);
    }
