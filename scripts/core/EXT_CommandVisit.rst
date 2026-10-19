<%
from templates import helper as th
%><%
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_command_visit:

=============================
 Command Visit Extension
=============================

API
----

* Functions

    * ${x}CommandListVisitExt
    * ${x}GraphVisitExt

* Enumerations

    * ${x}_command_visit_ext_version_t
    * ${x}_command_visit_ext_default_op_t

* Callback Functions

    * ${x}_command_visit_ext_default_op_callback_t

* Structures

    * ${x}_command_visit_ext_desc_t
    * ${x}_concrete_visitor_ext_desc_t

Command Visit
~~~~~~~~~~~~~

This extension introduces APIs for visiting commands recorded in a command list or graph and applying custom behavior to each visited command.

Semantics and Behavior
~~~~~~~~~~~~~~~~~~~~~~

1. ${x}CommandListVisitExt traverses command list commands in recording order. The command list must be created with ${X}_COMMAND_LIST_FLAG_ENABLE_COMMAND_VISIT.
2. ${x}GraphVisitExt traverses graph commands in recording order. Graphs do not require an explicit opt-in flag.
3. Concrete visitors are provided by chaining one or more ${x}_concrete_visitor_ext_desc_t structures to the `pNext` chain of ${x}_command_visit_ext_desc_t, one per API function. Each `fname` must be unique within the chain. The implementation executes the concrete callback whose `fname` matches the current command API.
4. If no concrete callback is provided for a command, the implementation applies `defaultOp` from ${x}_command_visit_ext_desc_t.
5. For each command without a concrete callback, the implementation invokes, in order: `beforeDefaultOpClb` (if not null), `defaultOp`, `afterDefaultOpClb` (if not null). For commands with a concrete callback, only the concrete callback is invoked.
6. `beforeDefaultOpClb` and `afterDefaultOpClb` may inspect or modify synchronization parameters (wait events and signal event) used by the default operation, e.g. to remap event lists without modifying the command itself.

Concrete visitor callbacks have the same signature as the visited API, with `userData` appended as the last parameter and the ${X}_VISITOR_CCONV calling convention. For example, a concrete visitor for ${x}CommandListAppendLaunchKernel has the following prototype:

.. parsed-literal::

    ${x}_result_t ${X}_VISITOR_CCONV myLaunchKernelVisitor(
        ${x}_command_list_handle_t hCommandList,
        ${x}_kernel_handle_t hKernel,
        const ${x}_group_count_t* pLaunchFuncArgs,
        ${x}_event_handle_t hSignalEvent,
        uint32_t numWaitEvents,
        ${x}_event_handle_t* phWaitEvents,
        void* userData);

.. parsed-literal::

    // Create a source command list with command visit enabled
    ${x}_command_list_desc_t srcDesc = {
        ${X}_STRUCTURE_TYPE_COMMAND_LIST_DESC,                // stype
        nullptr,                                              // pNext
        0,                                                    // commandQueueGroupOrdinal
        ${X}_COMMAND_LIST_FLAG_ENABLE_COMMAND_VISIT           // flags
    };
    ${x}_command_list_handle_t hCommandList;
    ${x}CommandListCreate(hContext, hDevice, &srcDesc, &hCommandList);

    // ... record commands into hCommandList ...

    // Create a target command list that will receive re-appended commands
    ${x}_command_list_desc_t dstDesc = {
        ${X}_STRUCTURE_TYPE_COMMAND_LIST_DESC,                // stype
        nullptr,                                              // pNext
        0,                                                    // commandQueueGroupOrdinal
        0                                                     // flags
    };
    ${x}_command_list_handle_t hTargetCommandList;
    ${x}CommandListCreate(hContext, hDevice, &dstDesc, &hTargetCommandList);

    // Register a concrete visitor for kernel launches
    ${x}_concrete_visitor_ext_desc_t launchVisitor = {
        ${X}_STRUCTURE_TYPE_CONCRETE_VISITOR_EXT_DESC,       // stype
        nullptr,                                              // pNext
## --validate=off
        "${x}CommandListAppendLaunchKernel",                 // fname
## --validate=on
        (void*)myLaunchKernelVisitor                          // callback
    };

    // Configure default command visit behavior
    ${x}_command_visit_ext_desc_t visitDesc = {
        ${X}_STRUCTURE_TYPE_COMMAND_VISIT_EXT_DESC,            // stype
        &launchVisitor,                                       // pNext
        userData,                                             // userData
        hTargetCommandList,                                   // hReappendTargetCommandList
        beforeDefaultCallback,                                // beforeDefaultOpClb
        ${X}_COMMAND_VISIT_EXT_DEFAULT_OP_REAPPEND,           // defaultOp
        afterDefaultCallback                                  // afterDefaultOpClb
    };

    // Visit a command list
    ${x}CommandListVisitExt(hCommandList, &visitDesc);

    // Visit a graph
    ${x}GraphVisitExt(hGraph, &visitDesc);
