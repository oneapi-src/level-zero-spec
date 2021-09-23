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
