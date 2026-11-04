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

User may query support for compute capability support on the device using the compute dot product capability extension supported under device compute properties(${x}_device_compute_properties_t).

Dot-product paths
^^^^^^^^^^^^^^^^^

The extension exposes up to three independent dot-product / matrix-multiply paths on the device.
A path is advertised by one or more bits of ``dp_caps``; the legal input and output data types for
that path are advertised by the corresponding ``*_input_types`` / ``*_output_types`` members.
A member value of ``0`` means "no supported data types for this path"; non-zero values are the
bitwise-OR of the supported data-type bits.

.. list-table::
   :header-rows: 1
   :widths: 15 55 30

   * - Path
     - ``dp_caps`` bit(s)
     - Member fields
   * - **DP4A**
       (non-systolic vector dot product)
     - ``DEVICE_NON_SYSTOLIC_DPA4_SIMD_ALL``
     - ``dpv4_input_types``,
       ``dpv4_output_types``
   * - **DPAS**
       (systolic dot-product accumulate)
     - ``DEVICE_SYSTOLIC_DPAS_SIMD8``,
       ``DEVICE_SYSTOLIC_DPAS_SIMD16``,
       ``DEVICE_SYSTOLIC_DPAS_DEPTH4``,
       ``DEVICE_SYSTOLIC_DPAS_DEPTH8``
     - ``dpas_input_types``,
       ``dpas_output_types``
   * - **BDPAS**
       (block-scaled systolic dot-product)
     - ``DEVICE_SYSTOLIC_BDPAS_SIMD16``,
       ``DEVICE_SYSTOLIC_BDPAS_DEPTH8``
     - ``bdpas_input_types``,
       ``bdpas_output_types``

The ``DEVICE_SYSTOLIC_OUTPUT_MATRIX_ROWCOUNT_UPTO8`` and ``DEVICE_SYSTOLIC_OUTPUT_MATRIX_ROWCOUNT_FIXED8`` bits are
output-shape modifiers for the systolic path. They qualify the DPAS/BDPAS output row count, but do not, on their own,
advertise DPAS or BDPAS support — a driver must also set at least one of the ``DEVICE_SYSTOLIC_DPAS_*`` or
``DEVICE_SYSTOLIC_BDPAS_*`` bits.

The ``dpv4_*`` members describe the modalities of **DP4A** instruction. The ``DEVICE_INPUT_DATA_SCALING_*`` bits only carry meaning when set in
``bdpas_input_types``.

The following pseudo-code demonstrates a sequence for obtaining extended information about the device compute dot product capability:

.. parsed-literal::

       ...
        // Discover properties on device
        //Driver handle ze_driver_handle_t Driverh obtained through previous call to zeInitDrivers
        //Obtain Device handle ze_device_handle_t Deviceh
        //zeDeviceGet(Driverh, 1, Deviceh);

        ze_device_compute_properties_t devComputeProp{};
        ${x}_device_compute_dotproduct_ext_properties_t* pDpDeviceCaps = allocate(sizeof(${x}_device_compute_dotproduct_ext_properties_t));

        pDpDeviceCaps.stype =  ZE_STRUCTURE_TYPE_DEVICE_COMPUTE_DOTPRODUCT_EXT_PROPERTIES;
        devComputeProp.stype = ZE_STRUCTURE_TYPE_DEVICE_COMPUTE_PROPERTIES;
        devComputeProp.pNext = pDpDeviceCaps;

        //obtain device extended compute properties
        zeDeviceGetComputeProperties(Deviceh, &devComputeProp);
       ...



