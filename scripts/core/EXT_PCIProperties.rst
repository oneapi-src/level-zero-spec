<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_pci_properties:

======================================
 PCI Properties Extension
======================================

API
----

* Functions


    * ${x}DevicePciGetPropertiesExt


* Enumerations


    * ${x}_pci_properties_ext_version_t


* Structures


    * ${x}_pci_ext_properties_t
    * ${x}_pci_address_ext_t
    * ${x}_pci_speed_ext_t

PCI Properties
~~~~~~~~~~~~~~~~~~

Accelerator devices connected to the host CPU over a PCI root complex can be located in the PCI switch fabric using the BDF address. This is useful, e.g., to determine which PCI devices are located *close* to each other in the PCI switch fabric. The ${x}_pci_address_ext_t struct returned via ${x}_pci_ext_properties_t by the call to ${x}DevicePciGetPropertiesExt contains the BDF address of the device.

The choice of the optimal algorithm to use for a given computation may be dependent on the access speed, i.e., bandwidth at which data can be transferred over PCI to the device. The ${x}_pci_speed_ext_t struct returned via ${x}_pci_ext_properties_t by the call to ${x}DevicePciGetPropertiesExt contains the theoretical PCI BW for accessing the device.

The following psuedo-code demonstrates a sequence for obtaining the BDF address & PCI BW of a device:

.. parsed-literal::

       ...
       // Create a PCI address struct
       {x}_pci_address_ext_t devAddr = {
           0, // domain
           0, // bus
           0, // device
           0  // function
       };
       // Create a PCI speed struct
       ${x}_pci_speed_ext_t devSpeed = {
           0, // gen
           0, // width
           0  // maxBandwidth
       };

       // Create a PCI Properties struct
       ${x}_pci_ext_properties_t devPCIProps = {
           ${X}_STRUCTURE_TYPE_PCI_EXT_PROPERTIES,
           nullptr,
           devAddr,
           devSpeed
       };

       // Get the PCI Address & Speed
       ${x}_result_t result = ${x}DevicePciGetPropertiesExt(dev, &devPCIProps);
