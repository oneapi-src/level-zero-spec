
:orphan:

.. _ZE_extension_mutable_command_list:

===============================
 Mutable Command List Extension
===============================

.. rst-class:: ext-version

*Introduced in Level Zero version 1.20*

API
----

* Enumerations

    * :ref:`ze-mutable-command-list-ext-version-t`
    * :ref:`ze-mutable-command-ext-flags-t`
    * :ref:`ze-mutable-command-list-ext-flags-t`

* Structures

    * :ref:`ze-mutable-command-id-ext-desc-t`
    * :ref:`ze-mutable-command-list-ext-properties-t`
    * :ref:`ze-mutable-command-list-ext-desc-t`
    * :ref:`ze-mutable-commands-ext-desc-t`
    * :ref:`ze-mutable-kernel-argument-ext-desc-t`
    * :ref:`ze-mutable-group-count-ext-desc-t`
    * :ref:`ze-mutable-group-size-ext-desc-t`
    * :ref:`ze-mutable-global-offset-ext-desc-t`

    * :ref:`ze-mutable-graph-argument-ext-desc-t`

* Functions

    * :ref:`zeCommandListGetNextCommandIdExt`
    * :ref:`zeCommandListGetNextCommandIdWithKernelsExt`
    * :ref:`zeCommandListUpdateMutableCommandsExt`
    * :ref:`zeCommandListUpdateMutableCommandSignalEventExt`
    * :ref:`zeCommandListUpdateMutableCommandWaitEventsExt`
    * :ref:`zeCommandListUpdateMutableCommandKernelsExt`


======================
 Mutable Command List
======================

- A mutable command list is created by supplying a :ref:`ze-mutable-command-list-ext-desc-t` object via the `pNext` member of :ref:`ze-command-list-desc-t`\.
- Mutable command lists support mutation to **identified** commands *after* being closed with :ref:`zeCommandListClose`\.
- Implementation support for mutable commands may be discovered by providing a :ref:`ze-mutable-command-list-ext-properties-t` object in the `pNext` member of :ref:`ze-device-properties-t` in a call to :ref:`zeDeviceGetProperties`\.

.. parsed-literal::

    // Discover mutable command list properties
    :ref:`ze-mutable-command-list-ext-properties-t` mutCmdListProps = {
        :ref:`ZE_STRUCTURE_TYPE_MUTABLE_COMMAND_LIST_EXT_PROPERTIES <ze-structure-type-t>`\,      // stype
        nullptr,                                                    // pNext
        0,                                                          // mutableCommandListFlags
        0                                                           // mutableCommandFlags
    };

    :ref:`ze-device-properties-t` deviceProps = {
        :ref:`ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES_1_2 <ze-structure-type-t>`   // :ref:`ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES <ze-structure-type-t>` deprecated since 1.17
    };
    deviceProps.pNext = &mutCmdListProps;

    :ref:`zeDeviceGetProperties`\(hDevice, &deviceProps);

    // ...

    // Create a mutable command list
    :ref:`ze-mutable-command-list-ext-desc-t` mutCmdListDesc = {
        :ref:`ZE_STRUCTURE_TYPE_MUTABLE_COMMAND_LIST_EXT_DESC <ze-structure-type-t>`\,
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
    :ref:`ze-mutable-command-id-ext-desc-t` cmdIdDesc = {
        :ref:`ZE_STRUCTURE_TYPE_MUTABLE_COMMAND_ID_EXT_DESC <ze-structure-type-t>`\,      // stype
        nullptr,                                            // pNext
        0                                                   // flags
    };

    uint64_t commandId = 0;
    :ref:`zeCommandListGetNextCommandIdExt`\(hCommandList, &cmdIdDesc, &commandId);

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

    :ref:`ze-mutable-group-count-ext-desc-t` groupCountDesc = {
        :ref:`ZE_STRUCTURE_TYPE_MUTABLE_GROUP_COUNT_EXT_DESC <ze-structure-type-t>`\,         // stype
        nullptr,                                                // pNext
        commandId,                                              // commandId
        &groupCount                                             // pGroupCount
    };

    // Prepare to modify Kernel Argument
    int argValue = 1;

    :ref:`ze-mutable-kernel-argument-ext-desc-t` krnlArgDesc = {
        :ref:`ZE_STRUCTURE_TYPE_MUTABLE_KERNEL_ARGUMENT_EXT_DESC <ze-structure-type-t>`\,     // stype
        &groupCountDesc,                                        // pNext
        commandId,                                              // commandId
        0,                                                      // argIndex
        sizeof(int),                                            // argSize
        &argValue                                               // pArgValue
    };

    // Prepare to update mutable commands
    :ref:`ze-mutable-commands-ext-desc-t` desc = {
        :ref:`ZE_STRUCTURE_TYPE_MUTABLE_COMMANDS_EXT_DESC <ze-structure-type-t>`\,            // stype
        &krnlArgDesc,                                           // pNext
        0                                                       // flags
    };

    // Synchronize command list execution
    :ref:`zeFenceHostSynchronize`\(hFence, UINT64_MAX);

    // Update mutable commands
    :ref:`zeCommandListUpdateMutableCommandsExt`\(hCommandList, &desc);

    // Update signal event for the launch kernel command
    :ref:`zeCommandListUpdateMutableCommandSignalEventExt`\(hCommandList, commandId, hNewLaunchKernelSignalEvent);

    // Update the wait events for the launch kernel command
    :ref:`zeCommandListUpdateMutableCommandWaitEventsExt`\(hCommandList, commandId, 1, &hNewLaunchKernelWaitEvent);

    // Close the command list
    :ref:`zeCommandListClose`\(hCommandList);

    // ...


Note, the command list must be explicitly closed after updating mutable commands and events. This informs the implementation that the application has finished with updates and is ready to submit the command list.
In preparation for kernel mutation user must provide all possible kernels for the command.

.. parsed-literal::

    // define all possible kernels
    ze_kernel_handle_t addKernel;
    ze_kernel_handle_t mulKernel;

    ze_kernel_handle_t kernels[] = {addKernel, mulKernel};

    // when users want kernel mutation, they need to explicitly state this, as 0 does not include kernel instruction mutation by default
    :ref:`ze-mutable-command-ext-flags-t` mutationFlags =
        :ref:`ZE_MUTABLE_COMMAND_EXT_FLAG_KERNEL_ARGUMENTS <ze-mutable-command-ext-flags-t>` |
        :ref:`ZE_MUTABLE_COMMAND_EXT_FLAG_GROUP_COUNT <ze-mutable-command-ext-flags-t>` |
        :ref:`ZE_MUTABLE_COMMAND_EXT_FLAG_GROUP_SIZE <ze-mutable-command-ext-flags-t>` |
        :ref:`ZE_MUTABLE_COMMAND_EXT_FLAG_KERNEL_INSTRUCTION <ze-mutable-command-ext-flags-t>`\;

    // Get next command identifier
    :ref:`ze-mutable-command-id-ext-desc-t` cmdIdDesc = {
        :ref:`ZE_STRUCTURE_TYPE_MUTABLE_COMMAND_ID_EXT_DESC <ze-structure-type-t>`\,      // stype
        nullptr,                                            // pNext
        mutationFlags                                       // flags
    };

    // retrieve id for the append operation and provide all possible kernels for this command
    uint64_t mutableKernelCommandId = 0;
    :ref:`zeCommandListGetNextCommandIdWithKernelsExt`\(hCommandList, &cmdIdDesc, &mutableKernelCommandId, 2, kernels);

    // Encode command into command list
    :ref:`zeCommandListAppendLaunchKernel`\(hCommandList, addKernel, &groupSize, nullptr, 0, nullptr);

    // Close the command list
    :ref:`zeCommandListClose`\(hCommandList);

Mutation of kernels must obey two rules:
- kernel handle mutation function must be called as first for a given command id
- kernel mutation invalidates all kernel arguments and dispatch parameters, these must be provided for the new kernel

.. parsed-literal::

    // Update mutable kernel for the command, switch from `addKernel` to `mulKernel`
    :ref:`zeCommandListUpdateMutableCommandKernelsExt`\(hCommandList, 1, &mutableKernelCommandId, &mulKernel);

    // modify group count
    :ref:`ze-group-count-t` groupCount = {
        32,                                                     // groupCountX
        1,                                                      // groupCountY
        1                                                       // groupCountZ
    };

    :ref:`ze-mutable-group-count-ext-desc-t` groupCountDesc = {
        :ref:`ZE_STRUCTURE_TYPE_MUTABLE_GROUP_COUNT_EXT_DESC <ze-structure-type-t>`\,         // stype
        nullptr,                                                // pNext
        mutableKernelCommandId,                                 // commandId
        &groupCount                                             // pGroupCount
    };

    :ref:`ze-mutable-group-size-ext-desc-t` groupSizeDesc = {
        :ref:`ZE_STRUCTURE_TYPE_MUTABLE_GROUP_SIZE_EXT_DESC <ze-structure-type-t>`\,          // stype
        &groupCountDesc,                                        // pNext
        mutableKernelCommandId,                                 // commandId
        32,                                                     // groupSizeX
        1,                                                      // groupSizeY
        1,                                                      // groupSizeZ
    };

    // Prepare to modify Kernel Argument
    int argValue = 1;
    void ``*``\usmPointer;

    :ref:`ze-mutable-kernel-argument-ext-desc-t` krnlArgMemoryDesc = {
        :ref:`ZE_STRUCTURE_TYPE_MUTABLE_KERNEL_ARGUMENT_EXT_DESC <ze-structure-type-t>`\,     // stype
        &groupSizeDesc,                                         // pNext
        mutableKernelCommandId,                                 // commandId
        0,                                                      // argIndex
        sizeof(void ``*``\),                                         // argSize
        &usmPointer                                             // pArgValue
    };

    :ref:`ze-mutable-kernel-argument-ext-desc-t` krnlArgScalarDesc = {
        :ref:`ZE_STRUCTURE_TYPE_MUTABLE_KERNEL_ARGUMENT_EXT_DESC <ze-structure-type-t>`\,     // stype
        &krnlArgMemoryDesc,                                     // pNext
        mutableKernelCommandId,                                 // commandId
        1,                                                      // argIndex
        sizeof(int),                                            // argSize
        &argValue                                               // pArgValue
    };

    // Prepare to update mutable commands
    :ref:`ze-mutable-commands-ext-desc-t` desc = {
        :ref:`ZE_STRUCTURE_TYPE_MUTABLE_COMMANDS_EXT_DESC <ze-structure-type-t>`\,            // stype
        &krnlArgScalarDesc,                                     // pNext
        0                                                       // flags
    };

    // Update mutable kernel arguments and dispatch parameters for the command
    :ref:`zeCommandListUpdateMutableCommandsExt`\(hCommandList, &desc);

    // Close the command list
    :ref:`zeCommandListClose`\(hCommandList);


The command list must be explicitly closed after updating mutable commands.
