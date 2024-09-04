<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_experimental_mutable_command_list:

================================
 Mutable Command List Extension
================================

API
----

* Enumerations

    * ${x}_mutable_command_list_exp_version_t
    * ${x}_mutable_command_exp_flags_t
    * ${x}_mutable_command_list_exp_flags_t

* Structures

    * ${x}_mutable_command_id_exp_desc_t
    * ${x}_mutable_command_list_exp_properties_t
    * ${x}_mutable_command_list_exp_desc_t
    * ${x}_mutable_commands_exp_desc_t
    * ${x}_mutable_kernel_argument_exp_desc_t
    * ${x}_mutable_group_count_exp_desc_t
    * ${x}_mutable_group_size_exp_desc_t
    * ${x}_mutable_global_offset_exp_desc_t

    * ${x}_mutable_graph_argument_exp_desc_t

* Functions

    * ${x}CommandListGetNextCommandIdExp
    * ${x}CommandListGetNextCommandIdWithKernelsExp
    * ${x}CommandListUpdateMutableCommandsExp
    * ${x}CommandListUpdateMutableCommandSignalEventExp
    * ${x}CommandListUpdateMutableCommandWaitEventsExp
    * ${x}CommandListUpdateMutableCommandKernelsExp


======================
 Mutable Command List
======================

- A mutable command list is created by supplying a ${x}_mutable_command_list_exp_desc_t object via the `pNext` member of ${x}_command_list_desc_t.
- Mutable command lists support mutation to **identified** commands *after* being closed with ${x}CommandListClose.
- Implementation support for mutable commands may be discovered by providing a ${x}_mutable_command_list_exp_properties_t object in the `pNext` member of ${x}_device_properties_t in a call to ${x}DeviceGetProperties.

.. parsed-literal::

    // Discover mutable command list properties
    ${x}_mutable_command_list_exp_properties_t mutCmdListProps = {
        ${X}_STRUCTURE_TYPE_MUTABLE_COMMAND_LIST_EXP_PROPERTIES,      // stype
        nullptr,                                                    // pNext
        0,                                                          // mutableCommandListFlags
        0                                                           // mutableCommandFlags
    };

    ${x}_device_properties_t deviceProps = {
        ${X}_STRUCTURE_TYPE_DEVICE_PROPERTIES
    };
    deviceProps.pNext = &mutCmdListProps;

    ${x}DeviceGetProperties(hDevice, &deviceProps);

    // ...

    // Create a mutable command list
    ${x}_mutable_command_list_exp_desc_t mutCmdListDesc = {
        ${X}_STRUCTURE_TYPE_MUTABLE_COMMAND_LIST_EXP_DESC,
        nullptr,
        0 // flags
    };

    ${x}_command_list_desc_t commandListDesc = {
        ${X}_STRUCTURE_TYPE_COMMAND_LIST_DESC,
        &mutCmdListDesc,
        0,
        0 // flags
    };

    ${x}_command_list_handle_t hCommandList = nullptr;
    ${x}CommandListCreate(hContext, hDevice, &commandListDesc, &hCommandList);

    // [ ...create fence, signal event and wait event objects... ]
    // This example assumes hFence, hSignalEvent and hWaitEvent have been created.

    // Create kernel from module
    ${x}_kernel_desc_t kernelDesc = {
        ${X}_STRUCTURE_TYPE_KERNEL_DESC,
        0,
        "example"
    };
    ${x}_kernel_handle_t hKernel = nullptr;
    ${x}_result_t result = ${x}KernelCreate(hModule, &kernelDesc, &hKernel);

    // Set the kernel arguments
    ${x}_group_count_t groupSize = {};
    ${x}KernelSuggestGroupSize(hKernel, 1024, 1024, 1, &groupSize.groupCountX, &groupSize.groupCountY, &groupSize.groupCountZ);

    int defaultValue = 0;
    ${x}KernelSetArgumentValue(hKernel, 0, sizeof(int), &defaultValue);

    // Get next command identifier
    ${x}_mutable_command_id_exp_desc_t cmdIdDesc = {
        ${X}_STRUCTURE_TYPE_MUTABLE_COMMAND_ID_EXP_DESC,      // stype
        nullptr,                                            // pNext
        0                                                   // flags
    };

    uint64_t commandId = 0;
    ${x}CommandListGetNextCommandIdExp(hCommandList, &cmdIdDesc, &commandId);

    // Encode command into command list
    ${x}CommandListAppendLaunchKernel(hCommandList, hKernel, &groupSize, hSignalEvent, 1, &hWaitEvent);

    // Close the command list
    ${x}CommandListClose(hCommandList);

    // ...

    // Execute the command list
    zeCommandQueueExecuteCommandLists(hCommandQueue, 1, &hCommandList, hFence);

    // ...


The application may subsequently mutate specific commands, as follows:

.. parsed-literal::

    // Prepare to modify group count
    ${x}_group_count_t groupCount = {
        256,                                                    // groupCountX
        256,                                                    // groupCountY
        1                                                       // groupCountZ
    };

    ${x}_mutable_group_count_exp_desc_t groupCountDesc = {
        ${X}_STRUCTURE_TYPE_MUTABLE_GROUP_COUNT_EXP_DESC,         // stype
        nullptr,                                                // pNext
        commandId,                                              // commandId
        &groupCount                                             // pGroupCount
    };

    // Prepare to modify Kernel Argument
    int argValue = 1;

    ${x}_mutable_kernel_argument_exp_desc_t krnlArgDesc = {
        ${X}_STRUCTURE_TYPE_MUTABLE_KERNEL_ARGUMENT_EXP_DESC,     // stype
        &groupCountDesc,                                        // pNext
        commandId,                                              // commandId
        0,                                                      // argIndex
        sizeof(int),                                            // argSize
        &argValue                                               // pArgValue
    };

    // Prepare to update mutable commands
    ${x}_mutable_commands_exp_desc_t desc = {
        ${X}_STRUCTURE_TYPE_MUTABLE_COMMANDS_EXP_DESC,            // stype
        &krnlArgDesc,                                           // pNext
        0                                                       // flags
    };

    // Synchronize command list execution
    ${x}FenceHostSynchronize(hFence, UINT64_MAX);

    // Update mutable commands
    ${x}CommandListUpdateMutableCommandsExp(hCommandList, &desc);

    // Update signal event for the launch kernel command
    ${x}CommandListUpdateMutableCommandSignalEventExp(hCommandList, commandId, hNewLaunchKernelSignalEvent);

    // Update the wait events for the launch kernel command
    ${x}CommandListUpdateMutableCommandWaitEventsExp(hCommandList, commandId, 1, &hNewLaunchKernelWaitEvent);

    // Close the command list
    ${x}CommandListClose(hCommandList);

    // ...


Note, the command list must be explicitly closed after updating mutable commands and events. This informs the implementation that the application has finished with updates and is ready to submit the command list.
In preparation for kernel mutation user must provide all possible kernels for the command.

.. parsed-literal::

    // define all possible kernels
    ${x}_kernel_handle_t addKernel;
    ${x}_kernel_handle_t mulKernel;

    ${x}_kernel_handle_t kernels[] = {addKernel, mulKernel};

    // when users want kernel mutation, they need to explicitly state this, as 0 does not include kernel instruction mutation by default
    ${x}_mutable_command_exp_flags_t mutationFlags =
        ${X}_MUTABLE_COMMAND_EXP_FLAG_KERNEL_ARGUMENTS |
        ${X}_MUTABLE_COMMAND_EXP_FLAG_GROUP_COUNT |
        ${X}_MUTABLE_COMMAND_EXP_FLAG_GROUP_SIZE |
        ${X}_MUTABLE_COMMAND_EXP_FLAG_KERNEL_INSTRUCTION;

    // Get next command identifier
    ${x}_mutable_command_id_exp_desc_t cmdIdDesc = {
        ${X}_STRUCTURE_TYPE_MUTABLE_COMMAND_ID_EXP_DESC,      // stype
        nullptr,                                            // pNext
        mutationFlags                                       // flags
    };

    // retrieve id for the append operation and provide all possible kernels for this command
    uint64_t mutableKernelCommandId = 0;
    ${x}CommandListGetNextCommandIdWithKernelsExp(hCommandList, &cmdIdDesc, &mutableKernelCommandId, 2, kernels);

    // Encode command into command list
    ${x}CommandListAppendLaunchKernel(hCommandList, addKernel, &groupSize, nullptr, 0, nullptr);

    // Close the command list
    ${x}CommandListClose(hCommandList);

Mutation of kernels must obey two rules:
- kernel handle mutation function must be called as first for a given command id
- kernel mutation invalidates all kernel arguments and dispatch parameters, these must be provided for the new kernel

.. parsed-literal::

    // Update mutable kernel for the command, switch from `addKernel` to `mulKernel`
    ${x}CommandListUpdateMutableCommandKernelsExp(hCommandList, 1, &mutableKernelCommandId, &mulKernel);

    // modify group count
    ${x}_group_count_t groupCount = {
        32,                                                     // groupCountX
        1,                                                      // groupCountY
        1                                                       // groupCountZ
    };

    ${x}_mutable_group_count_exp_desc_t groupCountDesc = {
        ${X}_STRUCTURE_TYPE_MUTABLE_GROUP_COUNT_EXP_DESC,         // stype
        nullptr,                                                // pNext
        mutableKernelCommandId,                                 // commandId
        &groupCount                                             // pGroupCount
    };

    ${x}_mutable_group_size_exp_desc_t groupSizeDesc = {
        ${X}_STRUCTURE_TYPE_MUTABLE_GROUP_SIZE_EXP_DESC,          // stype
        &groupCountDesc,                                        // pNext
        mutableKernelCommandId,                                 // commandId
        32,                                                     // groupSizeX
        1,                                                      // groupSizeY
        1,                                                      // groupSizeZ
    };

    // Prepare to modify Kernel Argument
    int argValue = 1;
    void *usmPointer;

    ${x}_mutable_kernel_argument_exp_desc_t krnlArgMemoryDesc = {
        ${X}_STRUCTURE_TYPE_MUTABLE_KERNEL_ARGUMENT_EXP_DESC,     // stype
        &groupSizeDesc,                                         // pNext
        mutableKernelCommandId,                                 // commandId
        0,                                                      // argIndex
        sizeof(void *),                                         // argSize
        &usmPointer                                             // pArgValue
    };

    ${x}_mutable_kernel_argument_exp_desc_t krnlArgScalarDesc = {
        ${X}_STRUCTURE_TYPE_MUTABLE_KERNEL_ARGUMENT_EXP_DESC,     // stype
        &krnlArgMemoryDesc,                                     // pNext
        mutableKernelCommandId,                                 // commandId
        1,                                                      // argIndex
        sizeof(int),                                            // argSize
        &argValue                                               // pArgValue
    };

    // Prepare to update mutable commands
    ${x}_mutable_commands_exp_desc_t desc = {
        ${X}_STRUCTURE_TYPE_MUTABLE_COMMANDS_EXP_DESC,            // stype
        &krnlArgScalarDesc,                                     // pNext
        0                                                       // flags
    };

    // Update mutable kernel arguments and dispatch parameters for the command
    ${x}CommandListUpdateMutableCommandsExp(hCommandList, &desc);

    // Close the command list
    ${x}CommandListClose(hCommandList);


The command list must be explicitly closed after updating mutable commands.
