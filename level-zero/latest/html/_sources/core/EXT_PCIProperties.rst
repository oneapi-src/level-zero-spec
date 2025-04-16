
:orphan:

.. _ZE_extension_pci_properties:

======================================
 PCI Properties Extension
======================================

API
----

* Functions


    * :ref:`zeDevicePciGetPropertiesExt`


* Enumerations


    * :ref:`ze-pci-properties-ext-version-t`


* Structures


    * :ref:`ze-pci-ext-properties-t`
    * :ref:`ze-pci-address-ext-t`
    * :ref:`ze-pci-speed-ext-t`

PCI Properties
~~~~~~~~~~~~~~~~~~

Accelerator devices connected to the host CPU over a PCI root complex can be located in the PCI switch fabric using a bus:device:function (BDF) address. This is useful, e.g., to determine which PCI devices are located *close* to each other in the PCI switch fabric. The :ref:`ze-pci-address-ext-t` struct returned via :ref:`ze-pci-ext-properties-t` by the call to :ref:`zeDevicePciGetPropertiesExt` contains the BDF address of the device.

The choice of the optimal algorithm to use for a given computation may be dependent on the access speed, i.e., bandwidth at which data can be transferred over PCI to the device. The :ref:`ze-pci-speed-ext-t` struct returned via :ref:`ze-pci-ext-properties-t` by the call to :ref:`zeDevicePciGetPropertiesExt` contains the theoretical PCI BW for accessing the device.

The following psuedo-code demonstrates a sequence for obtaining the BDF address & PCI BW of a device:

.. parsed-literal::

       ...
       // Create a PCI address struct
       :ref:`ze-pci-address-ext-t` devAddr = {
           0, // domain
           0, // bus
           0, // device
           0  // function
       };
       // Create a PCI speed struct
       :ref:`ze-pci-speed-ext-t` devSpeed = {
           0, // gen
           0, // width
           0  // maxBandwidth
       };

       // Create a PCI Properties struct
       :ref:`ze-pci-ext-properties-t` devPCIProps = {
           :ref:`ZE_STRUCTURE_TYPE_PCI_EXT_PROPERTIES <ze-structure-type-t>`\,
           nullptr,
           devAddr,
           devSpeed
       };

       // Get the PCI Address & Speed
       :ref:`ze-result-t` result = :ref:`zeDevicePciGetPropertiesExt`\(dev, &devPCIProps);
