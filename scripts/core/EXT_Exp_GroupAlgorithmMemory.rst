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