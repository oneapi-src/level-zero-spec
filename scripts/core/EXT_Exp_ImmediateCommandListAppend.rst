<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_experimental_immediate_command_list_append:

=========================================
 Immediate Command List Append Extension
=========================================

API
----

* Enumerations

    * ${x}_immediate_command_list_append_exp_version_t

* Functions

    * ${x}CommandListImmediateAppendCommandListsExp

===============================
 Immediate Command List Append
===============================

This extension allows an application to append one or more command lists to an immediate command list for dispatch.
