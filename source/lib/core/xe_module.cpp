/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_module.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Module
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/module.yml
 * @endcond
 *
 */
#include "xe_lib.h"
#include <sstream>

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates module object from an input IL or native binary.
/// 
/// @details
///     - Compiles the module for execution on the device.
///     - The module can only be used on the device on which it was created.
///     - The module can be copied to other devices within the same driver
///       instance by using ::xeModuleGetNativeBinary.
///     - The following build options are supported:
///         + "-xe-opt-disable" - Disable optimizations
///         + "-xe-opt-greater-than-4GB-buffer-required" - Use 64-bit offset
///           calculations for buffers.
///         + "-xe-opt-large-register-file" - Increase number of registers
///           available to threads.
///     - A build log can optionally be returned to the caller. The caller is
///       responsible for destroying build log using ::xeModuleBuildLogDestroy.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuModuleLoad**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == desc
///         + nullptr == phModule
///         + invalid pDesc->format
///         + nullptr == pDesc->pInputModule
///         + nullptr == pDesc->phModule
///         + 0 == pDesc->inputSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_MODULE_DESC_VERSION_CURRENT < desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::XE_RESULT_ERROR_MODULE_BUILD_FAILURE
///         + Failure to build module. See build log for more details.
xe_result_t __xecall
xeModuleCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_module_desc_t* desc,                   ///< [in] pointer to module descriptor
    xe_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
    xe_module_build_log_handle_t* phBuildLog        ///< [out][optional] pointer to handle of module's build log.
    )
{
    auto pfnCreate = xe_lib::context.ddiTable.Module.pfnCreate;
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnCreate( hDevice, desc, phModule, phBuildLog );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys module
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the module before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this module
///     - The application may **not** call this function from simultaneous
///       threads with the same module handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuModuleUnload**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModule
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeModuleDestroy(
    xe_module_handle_t hModule                      ///< [in][release] handle of the module
    )
{
    auto pfnDestroy = xe_lib::context.ddiTable.Module.pfnDestroy;
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnDestroy( hModule );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys module build log object
/// 
/// @details
///     - The implementation of this function will immediately free all Host
///       allocations associated with this object
///     - The application may **not** call this function from simultaneous
///       threads with the same build log handle.
///     - The implementation of this function should be lock-free.
///     - This function can be called before or after ::xeModuleDestroy for the
///       associated module.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModuleBuildLog
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeModuleBuildLogDestroy(
    xe_module_build_log_handle_t hModuleBuildLog    ///< [in][release] handle of the module build log object.
    )
{
    auto pfnDestroy = xe_lib::context.ddiTable.ModuleBuildLog.pfnDestroy;
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnDestroy( hModuleBuildLog );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves text string for build log.
/// 
/// @details
///     - The caller can pass nullptr for pBuildLog when querying only for size.
///     - The caller must provide memory for build log.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModuleBuildLog
///         + nullptr == pSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeModuleBuildLogGetString(
    xe_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
    size_t* pSize,                                  ///< [in,out] size of build log string.
    char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
    )
{
    auto pfnGetString = xe_lib::context.ddiTable.ModuleBuildLog.pfnGetString;
    if( nullptr == pfnGetString )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetString( hModuleBuildLog, pSize, pBuildLog );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve native binary from Module.
/// 
/// @details
///     - The native binary output can be cached to disk and new modules can be
///       later constructed from the cached copy.
///     - The native binary will retain debugging information that is associated
///       with a module.
///     - The caller can pass nullptr for pModuleNativeBinary when querying only
///       for size.
///     - The implementation will copy the native binary into a buffer supplied
///       by the caller.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModule
///         + nullptr == pSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeModuleGetNativeBinary(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
    uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
    )
{
    auto pfnGetNativeBinary = xe_lib::context.ddiTable.Module.pfnGetNativeBinary;
    if( nullptr == pfnGetNativeBinary )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetNativeBinary( hModule, pSize, pModuleNativeBinary );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve global variable pointer from Module.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModule
///         + nullptr == pGlobalName
///         + nullptr == pptr
///         + invalid name
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeModuleGetGlobalPointer(
    xe_module_handle_t hModule,                     ///< [in] handle of the device
    const char* pGlobalName,                        ///< [in] name of global variable in module
    void** pptr                                     ///< [out] device visible pointer
    )
{
    auto pfnGetGlobalPointer = xe_lib::context.ddiTable.Module.pfnGetGlobalPointer;
    if( nullptr == pfnGetGlobalPointer )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetGlobalPointer( hModule, pGlobalName, pptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Create a kernel object from a module by name
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuModuleGetFunction**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModule
///         + nullptr == desc
///         + nullptr == phKernel
///         + nullptr == pDesc->pKernelName
///         + invalid value for pDesc->pKernelName
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_KERNEL_DESC_VERSION_CURRENT < desc->version
xe_result_t __xecall
xeKernelCreate(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const xe_kernel_desc_t* desc,                   ///< [in] pointer to kernel descriptor
    xe_kernel_handle_t* phKernel                    ///< [out] handle of the Function object
    )
{
    auto pfnCreate = xe_lib::context.ddiTable.Kernel.pfnCreate;
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnCreate( hModule, desc, phKernel );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a kernel object
/// 
/// @details
///     - All kernels must be destroyed before the module is destroyed.
///     - The application is responsible for making sure the device is not
///       currently referencing the kernel before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this kernel
///     - The application may **not** call this function from simultaneous
///       threads with the same kernel handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hKernel
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeKernelDestroy(
    xe_kernel_handle_t hKernel                      ///< [in][release] handle of the kernel object
    )
{
    auto pfnDestroy = xe_lib::context.ddiTable.Kernel.pfnDestroy;
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnDestroy( hKernel );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve a function pointer from a module by name
/// 
/// @details
///     - The function pointer is unique for the device on which the module was
///       created.
///     - The function pointer is no longer valid if module is destroyed.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModule
///         + nullptr == pFunctionName
///         + nullptr == pfnFunction
///         + invalid value pFunctionName. Function name must exist in Module.
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeModuleGetFunctionPointer(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
    void** pfnFunction                              ///< [out] pointer to function.
    )
{
    auto pfnGetFunctionPointer = xe_lib::context.ddiTable.Module.pfnGetFunctionPointer;
    if( nullptr == pfnGetFunctionPointer )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetFunctionPointer( hModule, pFunctionName, pfnFunction );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set group size for a kernel
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same function handle.
///     - The implementation of this function should be lock-free.
///     - The implementation will copy the group size information into a command
///       list when the function is appended.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hKernel
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeKernelSetGroupSize(
    xe_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this kernel
    uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this kernel
    uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this kernel
    )
{
    auto pfnSetGroupSize = xe_lib::context.ddiTable.Kernel.pfnSetGroupSize;
    if( nullptr == pfnSetGroupSize )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetGroupSize( hKernel, groupSizeX, groupSizeY, groupSizeZ );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Query a suggested group size for a kernel given a global size for each
///        dimension.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - This function ignores the group size that is set using
///       ::xeKernelSetGroupSize.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hKernel
///         + nullptr == groupSizeX
///         + nullptr == groupSizeY
///         + nullptr == groupSizeZ
///         + invalid global width
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeKernelSuggestGroupSize(
    xe_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    uint32_t globalSizeX,                           ///< [in] global width for X dimension
    uint32_t globalSizeY,                           ///< [in] global width for Y dimension
    uint32_t globalSizeZ,                           ///< [in] global width for Z dimension
    uint32_t* groupSizeX,                           ///< [out] recommended size of group for X dimension
    uint32_t* groupSizeY,                           ///< [out] recommended size of group for Y dimension
    uint32_t* groupSizeZ                            ///< [out] recommended size of group for Z dimension
    )
{
    auto pfnSuggestGroupSize = xe_lib::context.ddiTable.Kernel.pfnSuggestGroupSize;
    if( nullptr == pfnSuggestGroupSize )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSuggestGroupSize( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Query a suggested max group count a cooperative kernel.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hKernel
///         + nullptr == groupCountX
///         + nullptr == groupCountY
///         + nullptr == groupCountZ
///         + invalid number of threads.
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeKernelSuggestMaxCooperativeGroupCount(
    xe_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    uint32_t* groupCountX,                          ///< [out] recommend group count X dimension.
    uint32_t* groupCountY,                          ///< [out] recommend group count Y dimension.
    uint32_t* groupCountZ                           ///< [out] recommend group count Z dimension.
    )
{
    auto pfnSuggestMaxCooperativeGroupCount = xe_lib::context.ddiTable.Kernel.pfnSuggestMaxCooperativeGroupCount;
    if( nullptr == pfnSuggestMaxCooperativeGroupCount )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSuggestMaxCooperativeGroupCount( hKernel, groupCountX, groupCountY, groupCountZ );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set kernel argument used on kernel launch.
/// 
/// @details
///     - This function may **not** be called from simultaneous threads with the
///       same function handle.
///     - The implementation of this function should be lock-free.
///     - The implementation will copy the arguments into a command list when
///       the function is appended.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hKernel
///         + invalid argument index
///         + invalid size specified
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeKernelSetArgumentValue(
    xe_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
    size_t argSize,                                 ///< [in] size of argument type
    const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                    ///< null then argument value is considered null.
    )
{
    auto pfnSetArgumentValue = xe_lib::context.ddiTable.Kernel.pfnSetArgumentValue;
    if( nullptr == pfnSetArgumentValue )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetArgumentValue( hKernel, argIndex, argSize, pArgValue );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets a kernel attribute
/// 
/// @details
///     - This function may **not** be called from simultaneous threads with the
///       same function handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clSetKernelExecInfo**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hKernel
///         + invalid value for attr
///         + invalid value for value
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeKernelSetAttribute(
    xe_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    xe_kernel_set_attribute_t attr,                 ///< [in] attribute to set
    uint32_t value                                  ///< [in] attribute value to set
    )
{
    auto pfnSetAttribute = xe_lib::context.ddiTable.Kernel.pfnSetAttribute;
    if( nullptr == pfnSetAttribute )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnSetAttribute( hKernel, attr, value );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Query a kernel attribute.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuFuncGetAttribute**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hKernel
///         + nullptr == pValue
///         + invalid value for attr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeKernelGetAttribute(
    xe_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    xe_kernel_get_attribute_t attr,                 ///< [in] attribute to query
    uint32_t* pValue                                ///< [out] returned attribute value
    )
{
    auto pfnGetAttribute = xe_lib::context.ddiTable.Kernel.pfnGetAttribute;
    if( nullptr == pfnGetAttribute )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetAttribute( hKernel, attr, pValue );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch kernel over one or more work groups.
/// 
/// @details
///     - This may **not** be called for a command list created with
///       ::XE_COMMAND_LIST_FLAG_COPY_ONLY.
///     - This function may **not** be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuLaunchKernel**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hKernel
///         + nullptr == pLaunchFuncArgs
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendLaunchKernel(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    const xe_thread_group_dimensions_t* pLaunchFuncArgs,///< [in] thread group launch arguments
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    auto pfnAppendLaunchKernel = xe_lib::context.ddiTable.CommandList.pfnAppendLaunchKernel;
    if( nullptr == pfnAppendLaunchKernel )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendLaunchKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch kernel cooperatively over one or more work groups.
/// 
/// @details
///     - This may **not** be called for a command list created with
///       ::XE_COMMAND_LIST_FLAG_COPY_ONLY.
///     - This may only be used for a command list that are submitted to command
///       queue with cooperative flag set.
///     - This function may **not** be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
///     - Use ::xeKernelSuggestMaxCooperativeGroupCount to recommend max group
///       count for device for cooperative functions that device supports.
/// 
/// @remarks
///   _Analogues_
///     - **cudaLaunchCooperativeKernel**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hKernel
///         + nullptr == pLaunchFuncArgs
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendLaunchCooperativeKernel(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    const xe_thread_group_dimensions_t* pLaunchFuncArgs,///< [in] thread group launch arguments
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    auto pfnAppendLaunchCooperativeKernel = xe_lib::context.ddiTable.CommandList.pfnAppendLaunchCooperativeKernel;
    if( nullptr == pfnAppendLaunchCooperativeKernel )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendLaunchCooperativeKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch kernel over one or more work groups using indirect arguments.
/// 
/// @details
///     - The launch arguments need to be device visible.
///     - The launch arguments buffer may not be reusued until the function has
///       completed on the device.
///     - This may **not** be called for a command list created with
///       ::XE_COMMAND_LIST_FLAG_COPY_ONLY.
///     - This function may **not** be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuLaunchKernel**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hKernel
///         + nullptr == pLaunchArgumentsBuffer
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendLaunchKernelIndirect(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    const xe_thread_group_dimensions_t* pLaunchArgumentsBuffer, ///< [in] pointer to device buffer that will contain thread group launch
                                                    ///< arguments
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    auto pfnAppendLaunchKernelIndirect = xe_lib::context.ddiTable.CommandList.pfnAppendLaunchKernelIndirect;
    if( nullptr == pfnAppendLaunchKernelIndirect )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendLaunchKernelIndirect( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch multiple kernels over one or more work groups using an array of
///        indirect arguments.
/// 
/// @details
///     - The array of launch arguments need to be device visible.
///     - The array of launch arguments buffer may not be reused until the
///       kernel has completed on the device.
///     - This may **not** be called for a command list created with
///       ::XE_COMMAND_LIST_FLAG_COPY_ONLY.
///     - This function may **not** be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuLaunchKernel**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == phKernels
///         + nullptr == pCountBuffer
///         + nullptr == pLaunchArgumentsBuffer
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendLaunchMultipleKernelsIndirect(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numKernels,                            ///< [in] maximum number of kernels to launch
    xe_kernel_handle_t* phKernels,                  ///< [in][range(0, numKernels)] handles of the kernel objects
    const uint32_t* pCountBuffer,                   ///< [in] pointer to device memory location that will contain the actual
                                                    ///< number of kernels to launch; value must be less-than or equal-to
                                                    ///< numKernels
    const xe_thread_group_dimensions_t* pLaunchArgumentsBuffer, ///< [in][range(0, numKernels)] pointer to device buffer that will contain
                                                    ///< a contiguous array of thread group launch arguments
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    auto pfnAppendLaunchMultipleKernelsIndirect = xe_lib::context.ddiTable.CommandList.pfnAppendLaunchMultipleKernelsIndirect;
    if( nullptr == pfnAppendLaunchMultipleKernelsIndirect )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendLaunchMultipleKernelsIndirect( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch host function. All work after this command in the command list
///        will block until host function completes.
/// 
/// @details
///     - This may **not** be called for a command list created with
///       ::XE_COMMAND_LIST_FLAG_COPY_ONLY.
///     - This function may **not** be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuLaunchHostFunc**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == pUserData
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendLaunchHostFunction(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_host_pfn_t pfnHostFunc,                      ///< [in] pointer to host function.
    void* pUserData,                                ///< [in] pointer to user data to pass to host function.
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    auto pfnAppendLaunchHostFunction = xe_lib::context.ddiTable.CommandList.pfnAppendLaunchHostFunction;
    if( nullptr == pfnAppendLaunchHostFunction )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendLaunchHostFunction( hCommandList, pfnHostFunc, pUserData, hSignalEvent, numWaitEvents, phWaitEvents );
}

} // extern "C"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    Module::Module( 
        module_handle_t handle,                         ///< [in] handle of module object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the module object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    ModuleBuildLog::ModuleBuildLog( 
        module_build_log_handle_t handle,               ///< [in] handle of the buildlog object
        Module* pModule                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pModule( pModule )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    Kernel::Kernel( 
        kernel_handle_t handle,                         ///< [in] handle of kernel object
        Module* pModule,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the kernel object
        ) :
        m_handle( handle ),
        m_pModule( pModule ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates module object from an input IL or native binary.
    /// 
    /// @details
    ///     - Compiles the module for execution on the device.
    ///     - The module can only be used on the device on which it was created.
    ///     - The module can be copied to other devices within the same driver
    ///       instance by using ::xeModuleGetNativeBinary.
    ///     - The following build options are supported:
    ///         + "-xe-opt-disable" - Disable optimizations
    ///         + "-xe-opt-greater-than-4GB-buffer-required" - Use 64-bit offset
    ///           calculations for buffers.
    ///         + "-xe-opt-large-register-file" - Increase number of registers
    ///           available to threads.
    ///     - A build log can optionally be returned to the caller. The caller is
    ///       responsible for destroying build log using ::xeModuleBuildLogDestroy.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuModuleLoad**
    /// 
    /// @returns
    ///     - Module*: pointer to handle of module object created
    ///     - ModuleBuildLog*: pointer to handle of module's build log.
    /// 
    /// @throws result_t
    Module* __xecall
    Module::Create(
        Device* pDevice,                                ///< [in] pointer to the device
        const desc_t* desc,                             ///< [in] pointer to module descriptor
        ModuleBuildLog** ppBuildLog                     ///< [out][optional] pointer to pointer to module's build log.
        )
    {
        xe_module_handle_t hModule;

        xe_module_build_log_handle_t hBuildLog;

        auto result = static_cast<result_t>( ::xeModuleCreate(
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const xe_module_desc_t*>( desc ),
            &hModule,
            ( ppBuildLog ) ? &hBuildLog : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Module::Create" );

        Module* pModule = nullptr;

        try
        {
            pModule = new Module( reinterpret_cast<module_handle_t>( hModule ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pModule;
            pModule = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xe::Module::Create" );
        }

        if( ppBuildLog )
            *ppBuildLog =  nullptr;

        try
        {
            if( ppBuildLog )
                *ppBuildLog =  new ModuleBuildLog( reinterpret_cast<module_build_log_handle_t>( hBuildLog ), pModule );
        }
        catch( std::bad_alloc& )
        {
            if( ppBuildLog )
            {
                delete *ppBuildLog;
                *ppBuildLog =  nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xe::Module::Create" );
        }

        return pModule;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys module
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the module before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this module
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same module handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuModuleUnload**
    /// 
    /// @throws result_t
    void __xecall
    Module::Destroy(
        Module* pModule                                 ///< [in][release] pointer to the module
        )
    {
        auto result = static_cast<result_t>( ::xeModuleDestroy(
            reinterpret_cast<xe_module_handle_t>( pModule->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Module::Destroy" );

        delete pModule;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys module build log object
    /// 
    /// @details
    ///     - The implementation of this function will immediately free all Host
    ///       allocations associated with this object
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same build log handle.
    ///     - The implementation of this function should be lock-free.
    ///     - This function can be called before or after ::xeModuleDestroy for the
    ///       associated module.
    /// 
    /// @throws result_t
    void __xecall
    ModuleBuildLog::Destroy(
        ModuleBuildLog* pModuleBuildLog                 ///< [in][release] pointer to the module build log object.
        )
    {
        auto result = static_cast<result_t>( ::xeModuleBuildLogDestroy(
            reinterpret_cast<xe_module_build_log_handle_t>( pModuleBuildLog->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::ModuleBuildLog::Destroy" );

        delete pModuleBuildLog;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves text string for build log.
    /// 
    /// @details
    ///     - The caller can pass nullptr for pBuildLog when querying only for size.
    ///     - The caller must provide memory for build log.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    ModuleBuildLog::GetString(
        size_t* pSize,                                  ///< [in,out] size of build log string.
        char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
        )
    {
        auto result = static_cast<result_t>( ::xeModuleBuildLogGetString(
            reinterpret_cast<xe_module_build_log_handle_t>( getHandle() ),
            pSize,
            pBuildLog ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::ModuleBuildLog::GetString" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve native binary from Module.
    /// 
    /// @details
    ///     - The native binary output can be cached to disk and new modules can be
    ///       later constructed from the cached copy.
    ///     - The native binary will retain debugging information that is associated
    ///       with a module.
    ///     - The caller can pass nullptr for pModuleNativeBinary when querying only
    ///       for size.
    ///     - The implementation will copy the native binary into a buffer supplied
    ///       by the caller.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Module::GetNativeBinary(
        size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
        uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
        )
    {
        auto result = static_cast<result_t>( ::xeModuleGetNativeBinary(
            reinterpret_cast<xe_module_handle_t>( getHandle() ),
            pSize,
            pModuleNativeBinary ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Module::GetNativeBinary" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve global variable pointer from Module.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - void*: device visible pointer
    /// 
    /// @throws result_t
    void* __xecall
    Module::GetGlobalPointer(
        const char* pGlobalName                         ///< [in] name of global variable in module
        )
    {
        void* pptr;

        auto result = static_cast<result_t>( ::xeModuleGetGlobalPointer(
            reinterpret_cast<xe_module_handle_t>( getHandle() ),
            pGlobalName,
            &pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Module::GetGlobalPointer" );

        return pptr;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Create a kernel object from a module by name
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuModuleGetFunction**
    /// 
    /// @returns
    ///     - Kernel*: handle of the Function object
    /// 
    /// @throws result_t
    Kernel* __xecall
    Kernel::Create(
        Module* pModule,                                ///< [in] pointer to the module
        const desc_t* desc                              ///< [in] pointer to kernel descriptor
        )
    {
        xe_kernel_handle_t hKernel;

        auto result = static_cast<result_t>( ::xeKernelCreate(
            reinterpret_cast<xe_module_handle_t>( pModule->getHandle() ),
            reinterpret_cast<const xe_kernel_desc_t*>( desc ),
            &hKernel ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Kernel::Create" );

        Kernel* pKernel = nullptr;

        try
        {
            pKernel = new Kernel( reinterpret_cast<kernel_handle_t>( hKernel ), pModule, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pKernel;
            pKernel = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xe::Kernel::Create" );
        }

        return pKernel;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys a kernel object
    /// 
    /// @details
    ///     - All kernels must be destroyed before the module is destroyed.
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the kernel before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this kernel
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same kernel handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Kernel::Destroy(
        Kernel* pKernel                                 ///< [in][release] pointer to the kernel object
        )
    {
        auto result = static_cast<result_t>( ::xeKernelDestroy(
            reinterpret_cast<xe_kernel_handle_t>( pKernel->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Kernel::Destroy" );

        delete pKernel;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve a function pointer from a module by name
    /// 
    /// @details
    ///     - The function pointer is unique for the device on which the module was
    ///       created.
    ///     - The function pointer is no longer valid if module is destroyed.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - void*: pointer to function.
    /// 
    /// @throws result_t
    void* __xecall
    Module::GetFunctionPointer(
        const char* pFunctionName                       ///< [in] Name of function to retrieve function pointer for.
        )
    {
        void* pfnFunction;

        auto result = static_cast<result_t>( ::xeModuleGetFunctionPointer(
            reinterpret_cast<xe_module_handle_t>( getHandle() ),
            pFunctionName,
            &pfnFunction ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Module::GetFunctionPointer" );

        return pfnFunction;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set group size for a kernel
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same function handle.
    ///     - The implementation of this function should be lock-free.
    ///     - The implementation will copy the group size information into a command
    ///       list when the function is appended.
    /// 
    /// @throws result_t
    void __xecall
    Kernel::SetGroupSize(
        uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this kernel
        uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this kernel
        uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this kernel
        )
    {
        auto result = static_cast<result_t>( ::xeKernelSetGroupSize(
            reinterpret_cast<xe_kernel_handle_t>( getHandle() ),
            groupSizeX,
            groupSizeY,
            groupSizeZ ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Kernel::SetGroupSize" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Query a suggested group size for a kernel given a global size for each
    ///        dimension.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    ///     - This function ignores the group size that is set using
    ///       ::xeKernelSetGroupSize.
    /// 
    /// @returns
    ///     - uint32_t: recommended size of group for X dimension
    ///     - uint32_t: recommended size of group for Y dimension
    ///     - uint32_t: recommended size of group for Z dimension
    /// 
    /// @throws result_t
    std::tuple<uint32_t, uint32_t, uint32_t> __xecall
    Kernel::SuggestGroupSize(
        uint32_t globalSizeX,                           ///< [in] global width for X dimension
        uint32_t globalSizeY,                           ///< [in] global width for Y dimension
        uint32_t globalSizeZ                            ///< [in] global width for Z dimension
        )
    {
        uint32_t groupSizeX;

        uint32_t groupSizeY;

        uint32_t groupSizeZ;

        auto result = static_cast<result_t>( ::xeKernelSuggestGroupSize(
            reinterpret_cast<xe_kernel_handle_t>( getHandle() ),
            globalSizeX,
            globalSizeY,
            globalSizeZ,
            &groupSizeX,
            &groupSizeY,
            &groupSizeZ ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Kernel::SuggestGroupSize" );

        return std::make_tuple( groupSizeX, groupSizeY, groupSizeZ );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Query a suggested max group count a cooperative kernel.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - uint32_t: recommend group count X dimension.
    ///     - uint32_t: recommend group count Y dimension.
    ///     - uint32_t: recommend group count Z dimension.
    /// 
    /// @throws result_t
    std::tuple<uint32_t, uint32_t, uint32_t> __xecall
    Kernel::SuggestMaxCooperativeGroupCount(
        void
        )
    {
        uint32_t groupCountX;

        uint32_t groupCountY;

        uint32_t groupCountZ;

        auto result = static_cast<result_t>( ::xeKernelSuggestMaxCooperativeGroupCount(
            reinterpret_cast<xe_kernel_handle_t>( getHandle() ),
            &groupCountX,
            &groupCountY,
            &groupCountZ ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Kernel::SuggestMaxCooperativeGroupCount" );

        return std::make_tuple( groupCountX, groupCountY, groupCountZ );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set kernel argument used on kernel launch.
    /// 
    /// @details
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same function handle.
    ///     - The implementation of this function should be lock-free.
    ///     - The implementation will copy the arguments into a command list when
    ///       the function is appended.
    /// 
    /// @throws result_t
    void __xecall
    Kernel::SetArgumentValue(
        uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
        size_t argSize,                                 ///< [in] size of argument type
        const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                        ///< null then argument value is considered null.
        )
    {
        auto result = static_cast<result_t>( ::xeKernelSetArgumentValue(
            reinterpret_cast<xe_kernel_handle_t>( getHandle() ),
            argIndex,
            argSize,
            pArgValue ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Kernel::SetArgumentValue" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sets a kernel attribute
    /// 
    /// @details
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same function handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clSetKernelExecInfo**
    /// 
    /// @throws result_t
    void __xecall
    Kernel::SetAttribute(
        set_attribute_t attr,                           ///< [in] attribute to set
        uint32_t value                                  ///< [in] attribute value to set
        )
    {
        auto result = static_cast<result_t>( ::xeKernelSetAttribute(
            reinterpret_cast<xe_kernel_handle_t>( getHandle() ),
            static_cast<xe_kernel_set_attribute_t>( attr ),
            value ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Kernel::SetAttribute" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Query a kernel attribute.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuFuncGetAttribute**
    /// 
    /// @returns
    ///     - uint32_t: returned attribute value
    /// 
    /// @throws result_t
    uint32_t __xecall
    Kernel::GetAttribute(
        get_attribute_t attr                            ///< [in] attribute to query
        )
    {
        uint32_t value;

        auto result = static_cast<result_t>( ::xeKernelGetAttribute(
            reinterpret_cast<xe_kernel_handle_t>( getHandle() ),
            static_cast<xe_kernel_get_attribute_t>( attr ),
            &value ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Kernel::GetAttribute" );

        return value;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch kernel over one or more work groups.
    /// 
    /// @details
    ///     - This may **not** be called for a command list created with
    ///       ::XE_COMMAND_LIST_FLAG_COPY_ONLY.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuLaunchKernel**
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendLaunchKernel(
        Kernel* pKernel,                                ///< [in] pointer to the kernel object
        const thread_group_dimensions_t* pLaunchFuncArgs,   ///< [in] thread group launch arguments
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<xe_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<xe_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::xeCommandListAppendLaunchKernel(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ),
            reinterpret_cast<xe_kernel_handle_t>( pKernel->getHandle() ),
            reinterpret_cast<const xe_thread_group_dimensions_t*>( pLaunchFuncArgs ),
            ( pSignalEvent ) ? reinterpret_cast<xe_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendLaunchKernel" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch kernel cooperatively over one or more work groups.
    /// 
    /// @details
    ///     - This may **not** be called for a command list created with
    ///       ::XE_COMMAND_LIST_FLAG_COPY_ONLY.
    ///     - This may only be used for a command list that are submitted to command
    ///       queue with cooperative flag set.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    ///     - Use ::xeKernelSuggestMaxCooperativeGroupCount to recommend max group
    ///       count for device for cooperative functions that device supports.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cudaLaunchCooperativeKernel**
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendLaunchCooperativeKernel(
        Kernel* pKernel,                                ///< [in] pointer to the kernel object
        const thread_group_dimensions_t* pLaunchFuncArgs,   ///< [in] thread group launch arguments
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<xe_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<xe_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::xeCommandListAppendLaunchCooperativeKernel(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ),
            reinterpret_cast<xe_kernel_handle_t>( pKernel->getHandle() ),
            reinterpret_cast<const xe_thread_group_dimensions_t*>( pLaunchFuncArgs ),
            ( pSignalEvent ) ? reinterpret_cast<xe_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendLaunchCooperativeKernel" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch kernel over one or more work groups using indirect arguments.
    /// 
    /// @details
    ///     - The launch arguments need to be device visible.
    ///     - The launch arguments buffer may not be reusued until the function has
    ///       completed on the device.
    ///     - This may **not** be called for a command list created with
    ///       ::XE_COMMAND_LIST_FLAG_COPY_ONLY.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuLaunchKernel**
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendLaunchKernelIndirect(
        Kernel* pKernel,                                ///< [in] pointer to the kernel object
        const thread_group_dimensions_t* pLaunchArgumentsBuffer,///< [in] pointer to device buffer that will contain thread group launch
                                                        ///< arguments
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<xe_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<xe_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::xeCommandListAppendLaunchKernelIndirect(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ),
            reinterpret_cast<xe_kernel_handle_t>( pKernel->getHandle() ),
            reinterpret_cast<const xe_thread_group_dimensions_t*>( pLaunchArgumentsBuffer ),
            ( pSignalEvent ) ? reinterpret_cast<xe_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendLaunchKernelIndirect" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch multiple kernels over one or more work groups using an array of
    ///        indirect arguments.
    /// 
    /// @details
    ///     - The array of launch arguments need to be device visible.
    ///     - The array of launch arguments buffer may not be reused until the
    ///       kernel has completed on the device.
    ///     - This may **not** be called for a command list created with
    ///       ::XE_COMMAND_LIST_FLAG_COPY_ONLY.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuLaunchKernel**
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendLaunchMultipleKernelsIndirect(
        uint32_t numKernels,                            ///< [in] maximum number of kernels to launch
        Kernel** ppKernels,                             ///< [in][range(0, numKernels)] handles of the kernel objects
        const uint32_t* pCountBuffer,                   ///< [in] pointer to device memory location that will contain the actual
                                                        ///< number of kernels to launch; value must be less-than or equal-to
                                                        ///< numKernels
        const thread_group_dimensions_t* pLaunchArgumentsBuffer,///< [in][range(0, numKernels)] pointer to device buffer that will contain
                                                        ///< a contiguous array of thread group launch arguments
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<xe_kernel_handle_t> hKernels;
        hKernels.resize( 0 );
        hKernels.reserve( numKernels );
        for( uint32_t i = 0; i < numKernels; ++i )
            hKernels.emplace_back( reinterpret_cast<xe_kernel_handle_t>( ppKernels[ i ]->getHandle() ) );

        thread_local std::vector<xe_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<xe_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::xeCommandListAppendLaunchMultipleKernelsIndirect(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ),
            numKernels,
            hKernels.data(),
            pCountBuffer,
            reinterpret_cast<const xe_thread_group_dimensions_t*>( pLaunchArgumentsBuffer ),
            ( pSignalEvent ) ? reinterpret_cast<xe_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendLaunchMultipleKernelsIndirect" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch host function. All work after this command in the command list
    ///        will block until host function completes.
    /// 
    /// @details
    ///     - This may **not** be called for a command list created with
    ///       ::XE_COMMAND_LIST_FLAG_COPY_ONLY.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuLaunchHostFunc**
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendLaunchHostFunction(
        host_pfn_t pfnHostFunc,                         ///< [in] pointer to host function.
        void* pUserData,                                ///< [in] pointer to user data to pass to host function.
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<xe_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<xe_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::xeCommandListAppendLaunchHostFunction(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ),
            static_cast<xe_host_pfn_t>( pfnHostFunc ),
            pUserData,
            ( pSignalEvent ) ? reinterpret_cast<xe_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendLaunchHostFunction" );
    }

} // namespace xe

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::desc_version_t to std::string
    std::string to_string( const Module::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Module::desc_version_t::CURRENT:
            str = "Module::desc_version_t::CURRENT";
            break;

        default:
            str = "Module::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::format_t to std::string
    std::string to_string( const Module::format_t val )
    {
        std::string str;

        switch( val )
        {
        case Module::format_t::IL_SPIRV:
            str = "Module::format_t::IL_SPIRV";
            break;

        case Module::format_t::NATIVE:
            str = "Module::format_t::NATIVE";
            break;

        default:
            str = "Module::format_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::desc_t to std::string
    std::string to_string( const Module::desc_t val )
    {
        std::string str;
        
        str += "Module::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Module::desc_t::format : ";
        str += to_string(val.format);
        str += "\n";
        
        str += "Module::desc_t::inputSize : ";
        str += std::to_string(val.inputSize);
        str += "\n";
        
        str += "Module::desc_t::pInputModule : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pInputModule);
            str += ss.str();
        }
        str += "\n";
        
        str += "Module::desc_t::pBuildFlags : ";
        str += val.pBuildFlags;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::desc_version_t to std::string
    std::string to_string( const Kernel::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Kernel::desc_version_t::CURRENT:
            str = "Kernel::desc_version_t::CURRENT";
            break;

        default:
            str = "Kernel::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::flag_t to std::string
    std::string to_string( const Kernel::flag_t val )
    {
        std::string str;

        switch( val )
        {
        case Kernel::flag_t::NONE:
            str = "Kernel::flag_t::NONE";
            break;

        case Kernel::flag_t::FORCE_RESIDENCY:
            str = "Kernel::flag_t::FORCE_RESIDENCY";
            break;

        default:
            str = "Kernel::flag_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::set_attribute_t to std::string
    std::string to_string( const Kernel::set_attribute_t val )
    {
        std::string str;

        switch( val )
        {
        case Kernel::set_attribute_t::KERNEL_SET_ATTR_INDIRECT_HOST_ACCESS:
            str = "Kernel::set_attribute_t::KERNEL_SET_ATTR_INDIRECT_HOST_ACCESS";
            break;

        case Kernel::set_attribute_t::KERNEL_SET_ATTR_INDIRECT_DEVICE_ACCESS:
            str = "Kernel::set_attribute_t::KERNEL_SET_ATTR_INDIRECT_DEVICE_ACCESS";
            break;

        case Kernel::set_attribute_t::KERNEL_SET_ATTR_INDIRECT_SHARED_ACCESS:
            str = "Kernel::set_attribute_t::KERNEL_SET_ATTR_INDIRECT_SHARED_ACCESS";
            break;

        default:
            str = "Kernel::set_attribute_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::get_attribute_t to std::string
    std::string to_string( const Kernel::get_attribute_t val )
    {
        std::string str;

        switch( val )
        {
        case Kernel::get_attribute_t::KERNEL_GET_ATTR_MAX_REGS_USED:
            str = "Kernel::get_attribute_t::KERNEL_GET_ATTR_MAX_REGS_USED";
            break;

        case Kernel::get_attribute_t::KERNEL_GET_ATTR_NUM_THREAD_DIMENSIONS:
            str = "Kernel::get_attribute_t::KERNEL_GET_ATTR_NUM_THREAD_DIMENSIONS";
            break;

        case Kernel::get_attribute_t::KERNEL_GET_ATTR_MAX_SHARED_MEM_SIZE:
            str = "Kernel::get_attribute_t::KERNEL_GET_ATTR_MAX_SHARED_MEM_SIZE";
            break;

        case Kernel::get_attribute_t::KERNEL_GET_ATTR_HAS_SPILL_FILL:
            str = "Kernel::get_attribute_t::KERNEL_GET_ATTR_HAS_SPILL_FILL";
            break;

        case Kernel::get_attribute_t::KERNEL_GET_ATTR_HAS_BARRIERS:
            str = "Kernel::get_attribute_t::KERNEL_GET_ATTR_HAS_BARRIERS";
            break;

        case Kernel::get_attribute_t::KERNEL_GET_ATTR_HAS_DPAS:
            str = "Kernel::get_attribute_t::KERNEL_GET_ATTR_HAS_DPAS";
            break;

        default:
            str = "Kernel::get_attribute_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::desc_t to std::string
    std::string to_string( const Kernel::desc_t val )
    {
        std::string str;
        
        str += "Kernel::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Kernel::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Kernel::desc_t::pKernelName : ";
        str += val.pKernelName;
        str += "\n";

        return str;
    }

} // namespace xe
