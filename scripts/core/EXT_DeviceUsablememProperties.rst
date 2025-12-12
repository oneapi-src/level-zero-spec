<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_device_usablemem_size_properties:

======================================
 Device Usable Memory Size Properties Extension
======================================

API
----

* Enumerations


    * ${x}_device_usablemem_size_properties_ext_version_t


* Structures

    * ${x}_device_usablemem_size_ext_properties_t


Extended Device Properties
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Users may wish get the status of the available allocatable/usable memory. Since this is a transient information based on the overall state of the device usage, user would need to invoke the extension to obtain the information at each point of interest. This extension provides extended information about the usable memory size available as part of the device. The extension introduces the ${x}_device_usablemem_size_ext_properties_t struct which can be passed to $xDeviceGetProperties via the `pNext` member of $x_device_properties_t.

The following psuedo-code demonstrates a sequence for obtaining extended information about the usable memory size 

.. parsed-literal::

       ...
        // Discover properties on device
        //Driver handle ze_driver_handle_t Driverh obtained through previous call to zeInitDrivers
        //Obtain Device handle ze_device_handle_t Deviceh
        //zeDeviceGet(Driverh, 1, Deviceh);

        ze_device_properties_t deviceProperties {};
        ${x}_device_usablemem_size_ext_properties_t* pUsablememProps = allocate(sizeof(${x}_device_usablemem_size_ext_properties_t));

        pUsablememProps.stype =  ZE_STRUCTURE_TYPE_DEVICE_USABLEMEM_SIZE_EXT_PROPERTIES;
        deviceProperties.stype = ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES;
        deviceProperties.pNext = pUsablememProps;
        
        //obtain device and extended memory properties
        zeDeviceGetProperties(Deviceh, &deviceProperties);



