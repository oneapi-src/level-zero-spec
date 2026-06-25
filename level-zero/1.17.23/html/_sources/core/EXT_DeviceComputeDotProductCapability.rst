
:orphan:

.. _ZE_extension_device_compute_dotproduct_ext_properties:

================================================
Device Compute Dot Product Capability Extension 
================================================

API
----

* Enumerations


    * :ref:`ze-device-compute-dotproduct-properties-ext-version-t`


* Structures

    * :ref:`ze-device-compute-dotproduct-ext-properties-t`


Extended Device Properties
~~~~~~~~~~~~~~~~~~~~~~~~~~~

User may query support for compute capabilty support on the device using the compute dot product capabilty extension supported under device compute properties(:ref:`ze-device-compute-properties-t`\).

The following psuedo-code demonstrates a sequence for obtaining extended information about the device compute dot product capability:

.. parsed-literal::

       ...
        // Discover properties on device
        //Driver handle ze_driver_handle_t Driverh obtained through previous call to zeInitDrivers
        //Obtain Device handle ze_device_handle_t Deviceh
        //zeDeviceGet(Driverh, 1, Deviceh);

        ze_device_compute_properties_t devComputeProp{};
        :ref:`ze-device-compute-dotproduct-ext-properties-t`\* pDpDeviceCaps = allocate(sizeof(:ref:`ze-device-compute-dotproduct-ext-properties-t`\));

        pDpDeviceCaps.stype =  ZE_STRUCTURE_TYPE_DEVICE_COMPUTE_DOTPRODUCT_EXT_PROPERTIES;
        devComputeProp.stype = ZE_STRUCTURE_TYPE_DEVICE_COMPUTEPROPERTIES;
        devComputeProp.pNext = pDpDeviceCaps;

        //obtain device and extended memory properties
        zeDeviceGetComputeProperties(Deviceh, &devComputeProp);
       ...



