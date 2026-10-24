
:orphan:

.. _ZE_extension_command_visit:

=============================
 Command Visit Extension
=============================

.. rst-class:: ext-version

*Introduced in Level Zero version 1.20*

API
----

* Functions

    * :ref:`zeCommandListVisitExt`
    * :ref:`zeGraphVisitExt`

* Enumerations

    * :ref:`ze-command-visit-ext-version-t`
    * :ref:`ze-command-visit-ext-default-op-t`

* Callback Functions

    * ze_command_visit_ext_default_op_callback_t

* Structures

    * :ref:`ze-command-visit-ext-desc-t`
    * :ref:`ze-concrete-visitor-ext-desc-t`

Command Visit
~~~~~~~~~~~~~

This extension introduces APIs for visiting commands recorded in a command list or graph and applying custom behavior to each visited command.

Semantics and Behavior
~~~~~~~~~~~~~~~~~~~~~~

1. :ref:`zeCommandListVisitExt` traverses command list commands in recording order. The command list must be created with :ref:`ZE_COMMAND_LIST_FLAG_ENABLE_COMMAND_VISIT <ze-command-list-flags-t>`\.
2. :ref:`zeGraphVisitExt` traverses graph commands in recording order. Graphs do not require an explicit opt-in flag.
3. Concrete visitors are provided by chaining one or more :ref:`ze-concrete-visitor-ext-desc-t` structures to the `pNext` chain of :ref:`ze-command-visit-ext-desc-t`\, one per API function. Each `fname` must be unique within the chain. The implementation executes the concrete callback whose `fname` matches the current command API.
4. If no concrete callback is provided for a command, the implementation applies `defaultOp` from :ref:`ze-command-visit-ext-desc-t`\.
5. For each command without a concrete callback, the implementation invokes, in order: `beforeDefaultOpClb` (if not null), `defaultOp`, `afterDefaultOpClb` (if not null). For commands with a concrete callback, only the concrete callback is invoked.
6. `beforeDefaultOpClb` and `afterDefaultOpClb` may inspect or modify synchronization parameters (wait events and signal event) used by the default operation, e.g. to remap event lists without modifying the command itself.

Concrete visitor callbacks have the same signature as the visited API, with `userData` appended as the last parameter and the ZE_VISITOR_CCONV calling convention. For example, a concrete visitor for :ref:`zeCommandListAppendLaunchKernel` has the following prototype:

.. parsed-literal::

    :ref:`ze-result-t` ZE_VISITOR_CCONV myLaunchKernelVisitor(
        ze_command_list_handle_t hCommandList,
        ze_kernel_handle_t hKernel,
        const :ref:`ze-group-count-t`\* pLaunchFuncArgs,
        ze_event_handle_t hSignalEvent,
        uint32_t numWaitEvents,
        ze_event_handle_t* phWaitEvents,
        void* userData);

.. parsed-literal::

    // Create a source command list with command visit enabled
    :ref:`ze-command-list-desc-t` srcDesc = {
        :ref:`ZE_STRUCTURE_TYPE_COMMAND_LIST_DESC <ze-structure-type-t>`\,                // stype
        nullptr,                                              // pNext
        0,                                                    // commandQueueGroupOrdinal
        :ref:`ZE_COMMAND_LIST_FLAG_ENABLE_COMMAND_VISIT <ze-command-list-flags-t>`           // flags
    };
    ze_command_list_handle_t hCommandList;
    :ref:`zeCommandListCreate`\(hContext, hDevice, &srcDesc, &hCommandList);

    // ... record commands into hCommandList ...

    // Create a target command list that will receive re-appended commands
    :ref:`ze-command-list-desc-t` dstDesc = {
        :ref:`ZE_STRUCTURE_TYPE_COMMAND_LIST_DESC <ze-structure-type-t>`\,                // stype
        nullptr,                                              // pNext
        0,                                                    // commandQueueGroupOrdinal
        0                                                     // flags
    };
    ze_command_list_handle_t hTargetCommandList;
    :ref:`zeCommandListCreate`\(hContext, hDevice, &dstDesc, &hTargetCommandList);

    // Register a concrete visitor for kernel launches
    :ref:`ze-concrete-visitor-ext-desc-t` launchVisitor = {
        :ref:`ZE_STRUCTURE_TYPE_CONCRETE_VISITOR_EXT_DESC <ze-structure-type-t>`\,       // stype
        nullptr,                                              // pNext
        "zeCommandListAppendLaunchKernel",                 // fname
        (void*)myLaunchKernelVisitor                          // callback
    };

    // Configure default command visit behavior
    :ref:`ze-command-visit-ext-desc-t` visitDesc = {
        :ref:`ZE_STRUCTURE_TYPE_COMMAND_VISIT_EXT_DESC <ze-structure-type-t>`\,            // stype
        &launchVisitor,                                       // pNext
        userData,                                             // userData
        hTargetCommandList,                                   // hReappendTargetCommandList
        beforeDefaultCallback,                                // beforeDefaultOpClb
        :ref:`ZE_COMMAND_VISIT_EXT_DEFAULT_OP_REAPPEND <ze-command-visit-ext-default-op-t>`\,           // defaultOp
        afterDefaultCallback                                  // afterDefaultOpClb
    };

    // Visit a command list
    :ref:`zeCommandListVisitExt`\(hCommandList, &visitDesc);

    // Visit a graph
    :ref:`zeGraphVisitExt`\(hGraph, &visitDesc);
