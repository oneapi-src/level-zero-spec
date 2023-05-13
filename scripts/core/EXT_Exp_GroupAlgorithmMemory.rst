<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_experimental_device_group_algorithm_memory_properties:

========================================================
Group Algorithm Memory Properties Experimental Extension
========================================================

API
----

* Enumerations

    * ${x}_device_group_algorithm_memory_properties_exp_version_t
    * ${x}_group_algorithm_type_exp_t
    * ${x}_group_algorithm_memory_scope_exp_t

* Structures


    * ${x}_device_group_algorithm_memory_exp_properties_t

* Functions


    * ${x}DeviceGetGroupAlgorithmMemoryPropertiesExp


Group Algorithm Memory Properties
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This extension allows applications to query for memory requirements of
the underlying compiler when selecting a particular group algorithm in
their kernels. Specifically, this extension returns the global memory
size and shared local memory size that applications need to allocate
and pass as a parameter to a group algorithm that requires additional
memory.

Three types of algorithms are available:

${X}_GROUP_ALGORITHM_TYPE_EXP_SORT: sorting algorithm

${X}_GROUP_ALGORITHM_TYPE_EXP_SCAN: scan algorithm

${X}_GROUP_ALGORITHM_TYPE_EXP_REDUCE: reduce algorithm

To know what amount of memory, application would call this extension as
follows:

.. parsed-literal::

        ${x}_device_group_algorithm_memory_exp_properties_t groupAlgorithmMemoryProperties {};
        groupAlgorithmMemoryProperties.stype = ${X}_STRUCTURE_TYPE_DEVICE_GROUP_ALGORITHM_MEMORY_EXP_PROPERTIES;
        groupAlgorithmMemoryProperties.algorithm = ${X}_GROUP_ALGORITHM_TYPE_EXP_SORT;
        groupAlgorithmMemoryProperties.memoryScope = ${X}_GROUP_ALGORITHM_MEMORY_SCOPE_EXP_SUBGROUP;

        ${x}_result_t res = ${x}DeviceGetGroupAlgorithmMemoryPropertiesExp(hDevice, numOfElements, &groupAlgorithmMemoryProperties);


Upon return, groupAlgorithmMemoryProperties will contain in
globalMemorySize and sharedLocalMemorySize the global and
shared local memory needed, respectively, for executing the selected
algorithm in the target device.