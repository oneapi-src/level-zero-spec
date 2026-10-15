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

.. _ZES_extension_device_gpu_topology:

==============================
 Device GPU Topology Extension
==============================

API
----
* Enumerations

    * ${s}_device_gpu_topology_ext_version_t

* Structures

    * ${s}_device_gpu_topology_ext_properties_t

* Macros

    * ${S}_DEVICE_GPU_TOPOLOGY_EXT_NAME

Device GPU Topology Overview
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Device GPU Topology extension provides the ability to query the GPU
topology of the device: the number of slices, Xe Cores, vector engines, matrix
engines, hardware threads and the name of the GPU generation.

An Xe Core is the same hardware unit that earlier GPU generations call a
sub-slice, as in the ``numSubslicesPerSlice`` member of
${x}_device_properties_t, so sub-slices and Xe Cores are the same thing under
different names. Likewise, a vector engine is the same hardware unit that
earlier GPU generations call an execution unit (EU), so ``numVectorEngines``
is the EU count on those generations and no separate EU count is reported.
Note that on those earlier generations a single core refers to an EU rather
than to an Xe Core.

Each slice contains one or more Xe Cores, and each Xe Core contains vector
engines and matrix engines. Every count returned by this extension is a total
across the entire device.

The ``generationName`` member is human-readable text intended for display and
logging purposes only. Its format and content are implementation-defined and
may change between driver releases, so applications should not parse it.
Applications that make decisions based on the device architecture should
instead use an immutable identifier, such as the ``ipVersion`` member of
${x}_device_ip_version_ext_t, the ``deviceId`` member of
${x}_device_properties_t, or the ``uuid`` member of
${s}_device_ext_properties_t.

Applications can retrieve these properties by passing the extension structure
via the pNext chain when calling ${s}DeviceGetProperties.

Querying the GPU Topology
~~~~~~~~~~~~~~~~~~~~~~~~~

The following pseudo-code demonstrates the usage pattern for querying the GPU
topology of the device.

.. parsed-literal::

    // Query device properties with the device GPU topology extension
    ${s}_device_properties_t deviceProps = {};
    deviceProps.stype = ${S}_STRUCTURE_TYPE_DEVICE_PROPERTIES;

    ${s}_device_gpu_topology_ext_properties_t gpuProps = {};
    gpuProps.stype = ${S}_STRUCTURE_TYPE_DEVICE_GPU_TOPOLOGY_EXT_PROPERTIES;
    gpuProps.pNext = nullptr;

    deviceProps.pNext = &gpuProps;

    ${s}DeviceGetProperties(hDevice, &deviceProps);

    output("Number of slices: %u\\n", gpuProps.numSlices);
    output("Number of Xe Cores: %u\\n", gpuProps.numXeCores);
    output("Number of vector engines: %u\\n", gpuProps.numVectorEngines);
    output("Number of matrix engines: %u\\n", gpuProps.numMatrixEngines);
    output("Number of hardware threads: %u\\n", gpuProps.numThreads);
    output("GPU generation name: %s\\n", gpuProps.generationName);
