<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_experimental_command_list_clone:

==============================
 Command List Clone Extension
==============================

API
----

* Enumerations

    * ${x}_command_list_clone_exp_version_t

* Functions

    * ${x}CommandListCreateCloneExp


====================
 Command List Clone
====================

A command list created with the cloneable flag may be cloned only after it has been closed.

.. parsed-literal::

    // Create a command list that may be cloned
    ${x}_command_list_desc_t commandListDesc = {
        ${X}_STRUCTURE_TYPE_COMMAND_LIST_DESC,
        nullptr,
        0,
        ${X}_COMMAND_LIST_FLAG_EXP_CLONEABLE
    };
    ${x}_command_list_handle_t hCommandList = nullptr;
    ${x}CommandListCreate(hContext, hDevice, &commandListDesc, &hCommandList);

    // { ...[construct command list]... }

    // Close the command list
    ${x}CommandListClose(hCommandList);

    // Execute the command list
    zeCommandQueueExecuteCommandLists(hCommandQueue, 1, &hCommandList, nullptr);

    // Clone the command list, no synchronization required
    ${x}_command_list_handle_t hClonedCommandList = nullptr;
    ${x}CommandListCreateCloneExp(hCommandList, &hClonedCommandList);

    // ...

