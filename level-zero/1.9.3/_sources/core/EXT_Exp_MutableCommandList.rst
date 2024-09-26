
:orphan:

.. _ZE_experimental_mutable_command_list:

================================
 Mutable Command List Extension
================================

API
----

* Enumerations

    * :ref:`ze-mutable-command-list-exp-version-t`
    * :ref:`ze-mutable-command-exp-flags-t`
    * :ref:`ze-mutable-command-list-exp-flags-t`

* Structures

    * :ref:`ze-mutable-command-id-exp-desc-t`
    * :ref:`ze-mutable-command-list-exp-properties-t`
    * :ref:`ze-mutable-command-list-exp-desc-t`
    * :ref:`ze-mutable-commands-exp-desc-t`
    * :ref:`ze-mutable-kernel-argument-exp-desc-t`
    * :ref:`ze-mutable-group-count-exp-desc-t`
    * :ref:`ze-mutable-group-size-exp-desc-t`
    * :ref:`ze-mutable-global-offset-exp-desc-t`

* Functions

    * :ref:`zeCommandListGetNextCommandIdExp`
    * :ref:`zeCommandListUpdateMutableCommandsExp`
    * :ref:`zeCommandListUpdateMutableCommandSignalEventExp`
    * :ref:`zeCommandListUpdateMutableCommandWaitEventsExp`


======================
 Mutable Command List
======================

- A mutable command list is created by supplying a :ref:`ze-mutable-command-list-exp-desc-t` object via the `pNext` member of :ref:`ze-command-list-desc-t`\.
- Mutable command lists support mutation to **identified** commands *after* being closed with :ref:`zeCommandListClose`\.
- Implementation support for mutable commands may be discovered by providing a :ref:`ze-mutable-command-list-exp-properties-t` object in the `pNext` member of :ref:`ze-device-properties-t` in a call to :ref:`zeDeviceGetProperties`\.

.. parsed-literal::

    // Discover mutable command list properties
    :ref:`ze-mutable-command-list-exp-properties-t` mutCmdListProps = {
        :ref:`ZE_STRUCTURE_TYPE_MUTABLE_COMMAND_LIST_EXP_PROPERTIES <ze-structure-type-t>`\,      // stype
        nullptr,                                                    // pNext
        0,                                                          // mutableCommandListFlags
        0                                                           // mutableCommandFlags
    };

    :ref:`ze-device-properties-t` deviceProps = {
        :ref:`ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES <ze-structure-type-t>`
    };
    deviceProps.pNext = &mutCmdListProps;

    :ref:`zeDeviceGetProperties`\(hDevice, &deviceProps);

    // ...

    // Create a mutable command list
    :ref:`ze-mutable-command-list-exp-desc-t` mutCmdListDesc = {
        :ref:`ZE_STRUCTURE_TYPE_MUTABLE_COMMAND_LIST_EXP_DESC <ze-structure-type-t>`\,
        nullptr,
        0 // flags
    };

    :ref:`ze-command-list-desc-t` commandListDesc = {
        :ref:`ZE_STRUCTURE_TYPE_COMMAND_LIST_DESC <ze-structure-type-t>`\,
        &mutCmdListDesc,
        0,
        0 // flags
    };

    ze_command_list_handle_t hCommandList = nullptr;
    :ref:`zeCommandListCreate`\(hContext, hDevice, &commandListDesc, &hCommandList);

    // [ ...create fence, signal event and wait event objects... ]
    // This example assumes hFence, hSignalEvent and hWaitEvent have been created.

    // Create kernel from module
    :ref:`ze-kernel-desc-t` kernelDesc = {
        :ref:`ZE_STRUCTURE_TYPE_KERNEL_DESC <ze-structure-type-t>`\,
        0,
        "example"
    };
    ze_kernel_handle_t hKernel = nullptr;
    :ref:`ze-result-t` result = :ref:`zeKernelCreate`\(hModule, &kernelDesc, &hKernel);

    // Set the kernel arguments
    :ref:`ze-group-count-t` groupSize = {};
    :ref:`zeKernelSuggestGroupSize`\(hKernel, 1024, 1024, 1, &groupSize.groupCountX, &groupSize.groupCountY, &groupSize.groupCountZ);

    int defaultValue = 0;
    :ref:`zeKernelSetArgumentValue`\(hKernel, 0, sizeof(int), &defaultValue);

    // Get next command identifier
    :ref:`ze-mutable-command-id-exp-desc-t` cmdIdDesc = {
        :ref:`ZE_STRUCTURE_TYPE_MUTABLE_COMMAND_ID_EXP_DESC <ze-structure-type-t>`       // stype
        nullptr,                                            // pNext
        0                                                   // flags
    };

    uint64_t commandId = 0;
    :ref:`zeCommandListGetNextCommandIdExp`\(hCommandList, &cmdIdDesc, &commandId);

    // Encode command into command list
    :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, hKernel, &groupSize, hSignalEvent, 1, &hWaitEvent);

    // Close the command list
    :ref:`zeCommandListClose`\(hCommandList);

    // ...

    // Execute the command list
    zeCommandQueueExecuteCommandLists(hCommandQueue, 1, &hCommandList, hFence);

    // ...


The application may subsequently mutate specific commands, as follows:

.. parsed-literal::

    // Prepare to modify group count
    :ref:`ze-group-count-t` groupCount = {
        256,                                                    // groupCountX
        256,                                                    // groupCountY
        1                                                       // groupCountZ
    };

    :ref:`ze-mutable-group-count-exp-desc-t` groupCountDesc = {
        :ref:`ZE_STRUCTURE_TYPE_MUTABLE_GROUP_COUNT_EXP_DESC <ze-structure-type-t>`\,         // stype
        nullptr,                                                // pNext
        commandId,                                              // commandId
        &groupCount                                             // pGroupCount
    };

    // Prepare to modify Kernel Argument
    int argValue = 1;

    :ref:`ze-mutable-kernel-argument-exp-desc-t` krnlArgDesc = {
        :ref:`ZE_STRUCTURE_TYPE_MUTABLE_KERNEL_ARGUMENT_EXP_DESC <ze-structure-type-t>`\,     // stype
        &groupCountDesc,                                        // pNext
        commandId,                                              // commandId
        0,                                                      // argIndex
        sizeof(int),                                            // argSize
        &argValue                                               // pArgValue
    };

    // Prepare to update mutable commands
    :ref:`ze-mutable-commands-exp-desc-t` desc = {
        :ref:`ZE_STRUCTURE_TYPE_MUTABLE_COMMANDS_EXP_DESC <ze-structure-type-t>`\,            // stype
        &krnlArgDesc,                                           // pNext
        0                                                       // flags
    };

    // Synchronize command list execution
    :ref:`zeFenceHostSynchronize`\(hFence, UINT64_MAX);

    // Update mutable commands
    :ref:`zeCommandListUpdateMutableCommandsExp`\(hCommandList, &desc);

    // Update signal event for the launch kernel command
    :ref:`zeCommandListUpdateMutableCommandSignalEventExp`\(hCommandList, commandId, hNewLaunchKernelSignalEvent);

    // Update the wait events for the launch kernel command
    :ref:`zeCommandListUpdateMutableCommandWaitEventsExp`\(hCommandList, commandId, 1, &hNewLaunchKernelWaitEvent);

    // Close the command list
    :ref:`zeCommandListClose`\(hCommandList);

    // ...


Note, the command list must be explicitly closed after updating mutable commands and events. This informs the implementation that the application has finished with updates and is ready to submit the command list.
