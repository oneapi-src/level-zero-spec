<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_device_compute_dotproduct_ext_properties:

================================================
Device Compute Dot Product Capability Extension 
================================================

API
----

* Enumerations


    * ${x}_device_compute_dotproduct_properties_ext_version_t


* Structures

    * ${x}_device_compute_dotproduct_ext_properties_t


Extended Device Properties
~~~~~~~~~~~~~~~~~~~~~~~~~~~

User may query support for compute capabilty support on the device using the compute dot product capabilty extension supported under device compute properties(${x}_device_compute_properties_t).

The following psuedo-code demonstrates a sequence for obtaining extended information about the device compute dot product capability:

.. parsed-literal::

       ...
        // Discover properties on device
        //Driver handle ze_driver_handle_t Driverh obtained through previous call to zeInitDrivers
        //Obtain Device handle ze_device_handle_t Deviceh
        //zeDeviceGet(Driverh, 1, Deviceh);

        ze_device_compute_properties_t devComputeProp{};
        ${x}_device_compute_dotproduct_ext_properties_t* pDpDeviceCaps = allocate(sizeof(${x}_device_compute_dotproduct_ext_properties_t));

        pDpDeviceCaps.stype =  ZE_STRUCTURE_TYPE_DEVICE_COMPUTE_DOTPRODUCT_EXT_PROPERTIES;
        devComputeProp.stype = ZE_STRUCTURE_TYPE_DEVICE_COMPUTEPROPERTIES;
        devComputeProp.pNext = pDpDeviceCaps;

        //obtain device and extended memory properties
        zeDeviceGetComputeProperties(Deviceh, &devComputeProp);
       ...



