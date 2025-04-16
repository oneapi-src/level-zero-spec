
:orphan:

.. _ZE_experimental_command_list_clone:

==============================
 Command List Clone Extension
==============================

API
----

* Enumerations

    * :ref:`ze-command-list-clone-exp-version-t`

* Functions

    * :ref:`zeCommandListCreateCloneExp`


====================
 Command List Clone
====================

A command list created with the cloneable flag may be cloned only after it has been closed.

.. parsed-literal::

    // Create a command list that may be cloned
    :ref:`ze-command-list-desc-t` commandListDesc = {
        :ref:`ZE_STRUCTURE_TYPE_COMMAND_LIST_DESC <ze-structure-type-t>`\,
        nullptr,
        0,
        :ref:`ZE_COMMAND_LIST_FLAG_EXP_CLONEABLE <ze-command-list-flags-t>`
    };
    ze_command_list_handle_t hCommandList = nullptr;
    :ref:`zeCommandListCreate`\(hContext, hDevice, &commandListDesc, &hCommandList);

    // { ...[construct command list]... }

    // Close the command list
    :ref:`zeCommandListClose`\(hCommandList);

    // Execute the command list
    zeCommandQueueExecuteCommandLists(hCommandQueue, 1, &hCommandList, nullptr);

    // Clone the command list, no synchronization required
    ze_command_list_handle_t hClonedCommandList = nullptr;
    :ref:`zeCommandListCreateCloneExp`\(hCommandList, &hClonedCommandList);

    // ...

