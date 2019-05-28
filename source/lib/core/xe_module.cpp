/**************************************************************************//**
* INTEL CONFIDENTIAL  
* Copyright 2019  
* Intel Corporation All Rights Reserved.  
*
* @cond DEV
* The source code contained or described herein and all documents related to the  
* source code ("Material") are owned by Intel Corporation or its suppliers or  
* licensors. Title to the Material remains with Intel Corporation or its suppliers  
* and licensors. The Material contains trade secrets and proprietary and confidential  
* information of Intel or its suppliers and licensors. The Material is protected by  
* worldwide copyright and trade secret laws and treaty provisions. No part of the  
* Material may be used, copied, reproduced, modified, published, uploaded, posted  
* transmitted, distributed, or disclosed in any way without Intel's prior express  
* written permission.  
*
* No license under any patent, copyright, trade secret or other intellectual  
* property right is granted to or conferred upon you by disclosure or delivery  
* of the Materials, either expressly, by implication, inducement, estoppel  
* or otherwise. Any license under such intellectual property rights must be  
* express and approved by Intel in writing.  
* @endcond
*
* @file xe_module.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Module
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/module.yml
* @endcond
*
******************************************************************************/
#include "xe_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates module object from an input IL or native binary.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - This function will create and compile the module object.
///     - A build log can optionally be returned to the caller. Caller is
///       responsible for destroying build log using ::xeModuleBuildLogDestroy
///     - Device memory will be allocated for module during creation.
///     - A module can be created directly from native binary format.
///     - A native binary object can be retrieved from a module using
///       ::xeModuleGetNativeBinary. This can be cached to disk and to create
///       new modules.
///     - The following build options are supported:
///         + "-xe-opt-disable" - Disable optimizations
///         + "-xe-opt-greater-than-4GB-buffer-required" - Use 64-bit offset
///           calculations for buffers.
///         + "-xe-opt-large-register-file" - Increase number of registers
///           available to threads.
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
///         + nullptr == pDesc
///         + nullptr == phModule
///         + invalid pDesc->format
///         + nullptr == pDesc->pInputModule
///         + nullptr == pDesc->phModule
///         + 0 == pDesc->inputSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_MODULE_DESC_VERSION_CURRENT < pDesc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::XE_RESULT_ERROR_MODULE_BUILD_FAILURE
///         + Failure to build module. See build log for more details.
xe_result_t __xecall
xeModuleCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_module_desc_t* pDesc,                  ///< [in] pointer to module descriptor
    xe_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
    xe_module_build_log_handle_t* phBuildLog        ///< [in,out][optional] pointer to handle of module's build log.
    )
{
    auto pfnCreate = xe_lib::lib.ddiTable.Module.pfnCreate;

#if _DEBUG
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnCreate( hDevice, pDesc, phModule, phBuildLog );
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
    xe_module_handle_t hModule                      ///< [in] handle of the module
    )
{
    auto pfnDestroy = xe_lib::lib.ddiTable.Module.pfnDestroy;

#if _DEBUG
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnDestroy( hModule );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys module build log object
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the build log before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this object
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
    xe_module_build_log_handle_t hModuleBuildLog    ///< [in] handle of the module build log object.
    )
{
    auto pfnDestroy = xe_lib::lib.ddiTable.ModuleBuildLog.pfnDestroy;

#if _DEBUG
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnDestroy( hModuleBuildLog );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves text string for build log.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - The caller must provide memory for build log.
///     - The caller can pass nullptr for pBuildLog when querying only for size.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModuleBuildLog
///         + nullptr == pSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeModuleBuildLogGetString(
    xe_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
    size_t* pSize,                                  ///< [in,out] size of build log string.
    char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
    )
{
    auto pfnGetString = xe_lib::lib.ddiTable.ModuleBuildLog.pfnGetString;

#if _DEBUG
    if( nullptr == pfnGetString )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetString( hModuleBuildLog, pSize, pBuildLog );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve native binary from Module.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - The caller can pass nullptr for pModuleNativeBinary when querying only
///       for size.
///     - The implementation will copy the native binary into a buffer supplied
///       by the caller.
///     - The memory for the native binary output is associated with the module.
///     - The native binary output can be cached to disk and new modules can be
///       later constructed from the cached copy.
///     - The native binary will retain debugging information that is associated
///       with a module.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModule
///         + nullptr == pSize
///         + invalid format
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeModuleGetNativeBinary(
    xe_module_handle_t hModule,                     ///< [in] handle of the device
    size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
    uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
    )
{
    auto pfnGetNativeBinary = xe_lib::lib.ddiTable.Module.pfnGetNativeBinary;

#if _DEBUG
    if( nullptr == pfnGetNativeBinary )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

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
///         + nullptr == pPtr
///         + invalid name
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeModuleGetGlobalPointer(
    xe_module_handle_t hModule,                     ///< [in] handle of the device
    const char* pGlobalName,                        ///< [in] name of function in global
    void** pPtr                                     ///< [out] device visible pointer
    )
{
    auto pfnGetGlobalPointer = xe_lib::lib.ddiTable.Module.pfnGetGlobalPointer;

#if _DEBUG
    if( nullptr == pfnGetGlobalPointer )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetGlobalPointer( hModule, pGlobalName, pPtr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Create Function object from Module by name
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - Function objects should be destroyed before the Module is destroyed.
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
///         + nullptr == pDesc
///         + nullptr == phFunction
///         + nullptr == pDesc->pFunctionName
///         + invalid value for pDesc->pFunctionName
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_FUNCTION_DESC_VERSION_CURRENT < pDesc->version
xe_result_t __xecall
xeFunctionCreate(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const xe_function_desc_t* pDesc,                ///< [in] pointer to function descriptor
    xe_function_handle_t* phFunction                ///< [out] handle of the Function object
    )
{
    auto pfnCreate = xe_lib::lib.ddiTable.Function.pfnCreate;

#if _DEBUG
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnCreate( hModule, pDesc, phFunction );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys Function object
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the function before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this function
///     - The application may **not** call this function from simultaneous
///       threads with the same function handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFunction
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeFunctionDestroy(
    xe_function_handle_t hFunction                  ///< [in] handle of the function object
    )
{
    auto pfnDestroy = xe_lib::lib.ddiTable.Function.pfnDestroy;

#if _DEBUG
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnDestroy( hFunction );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve function pointer from Module by name
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - Function pointer is no longer valid if Module is destroyed.
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
    auto pfnGetFunctionPointer = xe_lib::lib.ddiTable.Module.pfnGetFunctionPointer;

#if _DEBUG
    if( nullptr == pfnGetFunctionPointer )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetFunctionPointer( hModule, pFunctionName, pfnFunction );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set group size for Function.
/// 
/// @details
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this function
///     - The implementation of this function should be lock-free.
///     - This can be called multiple times. The driver copies the group size
///       information when appending functions into a command list.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFunction
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeFunctionSetGroupSize(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this function.
    uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this function.
    uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this function.
    )
{
    auto pfnSetGroupSize = xe_lib::lib.ddiTable.Function.pfnSetGroupSize;

#if _DEBUG
    if( nullptr == pfnSetGroupSize )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnSetGroupSize( hFunction, groupSizeX, groupSizeY, groupSizeZ );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Query a suggested group size for function given a global size for each
///        dimension.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - This function ignores the group size that is set using
///       ::xeFunctionSetGroupSize.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFunction
///         + nullptr == groupSizeX
///         + nullptr == groupSizeY
///         + nullptr == groupSizeZ
///         + invalid number of threads.
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeFunctionSuggestGroupSize(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    uint32_t globalSizeX,                           ///< [in] global width for X dimension.
    uint32_t globalSizeY,                           ///< [in] global width for Y dimension.
    uint32_t globalSizeZ,                           ///< [in] global width for Z dimension.
    uint32_t* groupSizeX,                           ///< [out] recommended size of group for X dimension.
    uint32_t* groupSizeY,                           ///< [out] recommended size of group for Y dimension.
    uint32_t* groupSizeZ                            ///< [out] recommended size of group for Z dimension.
    )
{
    auto pfnSuggestGroupSize = xe_lib::lib.ddiTable.Function.pfnSuggestGroupSize;

#if _DEBUG
    if( nullptr == pfnSuggestGroupSize )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnSuggestGroupSize( hFunction, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set function argument used on function launch.
/// 
/// @details
///     - This function may **not** be called from simultaneous threads with the
///       same function handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFunction
///         + invalid argument index
///         + invalid size specified
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeFunctionSetArgumentValue(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function args object.
    uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
    size_t argSize,                                 ///< [in] size of argument type
    const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                    ///< null then argument value is considered null.
    )
{
    auto pfnSetArgumentValue = xe_lib::lib.ddiTable.Function.pfnSetArgumentValue;

#if _DEBUG
    if( nullptr == pfnSetArgumentValue )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnSetArgumentValue( hFunction, argIndex, argSize, pArgValue );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets a function attribute
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
///         + nullptr == hFunction
///         + invalid value for attr
///         + invalid value for value
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeFunctionSetAttribute(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function.
    xe_function_set_attribute_t attr,               ///< [in] attribute to set
    uint32_t value                                  ///< [in] attribute value to set
    )
{
    auto pfnSetAttribute = xe_lib::lib.ddiTable.Function.pfnSetAttribute;

#if _DEBUG
    if( nullptr == pfnSetAttribute )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnSetAttribute( hFunction, attr, value );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Query a function attribute.
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
///         + nullptr == hFunction
///         + nullptr == pValue
///         + invalid value for attr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeFunctionGetAttribute(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    xe_function_get_attribute_t attr,               ///< [in] attribute to query
    uint32_t* pValue                                ///< [out] returned attribute value
    )
{
    auto pfnGetAttribute = xe_lib::lib.ddiTable.Function.pfnGetAttribute;

#if _DEBUG
    if( nullptr == pfnGetAttribute )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetAttribute( hFunction, attr, pValue );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch function over one or more work groups.
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
///         + nullptr == hFunction
///         + nullptr == pLaunchFuncArgs
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendLaunchFunction(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    const xe_thread_group_dimensions_t* pLaunchFuncArgs,///< [in] launch function arguments.
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    auto pfnAppendLaunchFunction = xe_lib::lib.ddiTable.CommandList.pfnAppendLaunchFunction;

#if _DEBUG
    if( nullptr == pfnAppendLaunchFunction )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnAppendLaunchFunction( hCommandList, hFunction, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch function over one or more work groups using indirect arguments.
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
///         + nullptr == hFunction
///         + nullptr == pLaunchArgumentsBuffer
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendLaunchFunctionIndirect(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    const xe_thread_group_dimensions_t* pLaunchArgumentsBuffer, ///< [in] pointer to device buffer that will contain launch arguments
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    auto pfnAppendLaunchFunctionIndirect = xe_lib::lib.ddiTable.CommandList.pfnAppendLaunchFunctionIndirect;

#if _DEBUG
    if( nullptr == pfnAppendLaunchFunctionIndirect )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnAppendLaunchFunctionIndirect( hCommandList, hFunction, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch multiple functions over one or more work groups using an array
///        of indirect arguments.
/// 
/// @details
///     - The array of launch arguments need to be device visible.
///     - The array of launch arguments buffer may not be reusued until the
///       function has completed on the device.
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
///         + nullptr == phFunctions
///         + nullptr == pNumLaunchArguments
///         + nullptr == pLaunchArgumentsBuffer
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendLaunchMultipleFunctionsIndirect(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numFunctions,                          ///< [in] maximum number of functions to launch
    xe_function_handle_t* phFunctions,              ///< [in][range(0, numFunctions)] handles of the function objects
    const uint32_t* pNumLaunchArguments,            ///< [in] pointer to device memory location that will contain the actual
                                                    ///< number of launch arguments; value must be less-than or equal-to
                                                    ///< numFunctions
    const xe_thread_group_dimensions_t* pLaunchArgumentsBuffer, ///< [in][range(0, numFunctions)] pointer to device buffer that will
                                                    ///< contain a contiguous array of launch arguments
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    auto pfnAppendLaunchMultipleFunctionsIndirect = xe_lib::lib.ddiTable.CommandList.pfnAppendLaunchMultipleFunctionsIndirect;

#if _DEBUG
    if( nullptr == pfnAppendLaunchMultipleFunctionsIndirect )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnAppendLaunchMultipleFunctionsIndirect( hCommandList, numFunctions, phFunctions, pNumLaunchArguments, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
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
    auto pfnAppendLaunchHostFunction = xe_lib::lib.ddiTable.CommandList.pfnAppendLaunchHostFunction;

#if _DEBUG
    if( nullptr == pfnAppendLaunchHostFunction )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnAppendLaunchHostFunction( hCommandList, pfnHostFunc, pUserData, hSignalEvent, numWaitEvents, phWaitEvents );
}

} // extern "C"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    Module::Module( 
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t& desc                              ///< [in] descriptor of the module object
        ) :
        m_pDevice( pDevice ),
        m_desc( desc )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    ModuleBuildLog::ModuleBuildLog( 
        Module* pModule                                 ///< [in] pointer to owner object
        ) :
        m_pModule( pModule )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    Function::Function( 
        Module* pModule,                                ///< [in] pointer to owner object
        const desc_t& desc                              ///< [in] descriptor of the function object
        ) :
        m_pModule( pModule ),
        m_desc( desc )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates module object from an input IL or native binary.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    ///     - This function will create and compile the module object.
    ///     - A build log can optionally be returned to the caller. Caller is
    ///       responsible for destroying build log using ::ModuleBuildLogDestroy
    ///     - Device memory will be allocated for module during creation.
    ///     - A module can be created directly from native binary format.
    ///     - A native binary object can be retrieved from a module using
    ///       ::ModuleGetNativeBinary. This can be cached to disk and to create new
    ///       modules.
    ///     - The following build options are supported:
    ///         + "--opt-disable" - Disable optimizations
    ///         + "--opt-greater-than-4GB-buffer-required" - Use 64-bit offset
    ///           calculations for buffers.
    ///         + "--opt-large-register-file" - Increase number of registers
    ///           available to threads.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuModuleLoad**
    /// 
    /// @returns
    ///     - Module: pointer to handle of module object created
    /// 
    /// @throws result_t
    Module* __xecall
    Module::Create(
        Device* pDevice,                                ///< [in] pointer to the device
        const desc_t* pDesc,                            ///< [in] pointer to module descriptor
        ModuleBuildLog* phBuildLog                      ///< [in,out][optional] pointer to pointer to module's build log.
        )
    {
        result_t result = result_t::SUCCESS;

        // auto result = ::xeModuleCreate( handle, pDevice, pDesc, phBuildLog );
        if( result_t::SUCCESS != result ) throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Module::Create" );

        return (Module*)0;
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
        Module* pModule                                 ///< [in] pointer to the module
        )
    {
        result_t result = result_t::SUCCESS;

        // auto result = ::xeModuleDestroy( handle, pModule );
        if( result_t::SUCCESS != result ) throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Module::Destroy" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys module build log object
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the build log before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this object
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same build log handle.
    ///     - The implementation of this function should be lock-free.
    ///     - This function can be called before or after ::ModuleDestroy for the
    ///       associated module.
    /// 
    /// @throws result_t
    void __xecall
    ModuleBuildLog::Destroy(
        ModuleBuildLog* pModuleBuildLog                 ///< [in] pointer to the module build log object.
        )
    {
        result_t result = result_t::SUCCESS;

        // auto result = ::xeModuleBuildLogDestroy( handle, pModuleBuildLog );
        if( result_t::SUCCESS != result ) throw exception_t( result, __FILE__, STRING(__LINE__), "xe::ModuleBuildLog::Destroy" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves text string for build log.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    ///     - The caller must provide memory for build log.
    ///     - The caller can pass nullptr for pBuildLog when querying only for size.
    /// 
    /// @throws result_t
    void __xecall
    ModuleBuildLog::GetString(
        size_t* pSize,                                  ///< [in,out] size of build log string.
        char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
        )
    {
        result_t result = result_t::SUCCESS;

        // auto result = ::xeModuleBuildLogGetString( handle, pSize, pBuildLog );
        if( result_t::SUCCESS != result ) throw exception_t( result, __FILE__, STRING(__LINE__), "xe::ModuleBuildLog::GetString" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve native binary from Module.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    ///     - The caller can pass nullptr for pModuleNativeBinary when querying only
    ///       for size.
    ///     - The implementation will copy the native binary into a buffer supplied
    ///       by the caller.
    ///     - The memory for the native binary output is associated with the module.
    ///     - The native binary output can be cached to disk and new modules can be
    ///       later constructed from the cached copy.
    ///     - The native binary will retain debugging information that is associated
    ///       with a module.
    /// 
    /// @throws result_t
    void __xecall
    Module::GetNativeBinary(
        size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
        uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
        )
    {
        result_t result = result_t::SUCCESS;

        // auto result = ::xeModuleGetNativeBinary( handle, pSize, pModuleNativeBinary );
        if( result_t::SUCCESS != result ) throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Module::GetNativeBinary" );
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
        const char* pGlobalName                         ///< [in] name of function in global
        )
    {
        result_t result = result_t::SUCCESS;

        // auto result = ::xeModuleGetGlobalPointer( handle, pGlobalName );
        if( result_t::SUCCESS != result ) throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Module::GetGlobalPointer" );

        return (void*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Create Function object from Module by name
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    ///     - Function objects should be destroyed before the Module is destroyed.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuModuleGetFunction**
    /// 
    /// @returns
    ///     - Function: handle of the Function object
    /// 
    /// @throws result_t
    Function* __xecall
    Function::Create(
        Module* pModule,                                ///< [in] pointer to the module
        const desc_t* pDesc                             ///< [in] pointer to function descriptor
        )
    {
        result_t result = result_t::SUCCESS;

        // auto result = ::xeFunctionCreate( handle, pModule, pDesc );
        if( result_t::SUCCESS != result ) throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Function::Create" );

        return (Function*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys Function object
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the function before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this function
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same function handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Function::Destroy(
        Function* pFunction                             ///< [in] pointer to the function object
        )
    {
        result_t result = result_t::SUCCESS;

        // auto result = ::xeFunctionDestroy( handle, pFunction );
        if( result_t::SUCCESS != result ) throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Function::Destroy" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve function pointer from Module by name
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    ///     - Function pointer is no longer valid if Module is destroyed.
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
        result_t result = result_t::SUCCESS;

        // auto result = ::xeModuleGetFunctionPointer( handle, pFunctionName );
        if( result_t::SUCCESS != result ) throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Module::GetFunctionPointer" );

        return (void*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set group size for Function.
    /// 
    /// @details
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this function
    ///     - The implementation of this function should be lock-free.
    ///     - This can be called multiple times. The driver copies the group size
    ///       information when appending functions into a command list.
    /// 
    /// @throws result_t
    void __xecall
    Function::SetGroupSize(
        uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this function.
        uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this function.
        uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this function.
        )
    {
        result_t result = result_t::SUCCESS;

        // auto result = ::xeFunctionSetGroupSize( handle, groupSizeX, groupSizeY, groupSizeZ );
        if( result_t::SUCCESS != result ) throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Function::SetGroupSize" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Query a suggested group size for function given a global size for each
    ///        dimension.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    ///     - This function ignores the group size that is set using
    ///       ::FunctionSetGroupSize.
    /// 
    /// @returns
    ///     - uint32_t: recommended size of group for X dimension.
    ///     - uint32_t: recommended size of group for Y dimension.
    ///     - uint32_t: recommended size of group for Z dimension.
    /// 
    /// @throws result_t
    std::tuple<uint32_t, uint32_t, uint32_t> __xecall
    Function::SuggestGroupSize(
        uint32_t globalSizeX,                           ///< [in] global width for X dimension.
        uint32_t globalSizeY,                           ///< [in] global width for Y dimension.
        uint32_t globalSizeZ                            ///< [in] global width for Z dimension.
        )
    {
        result_t result = result_t::SUCCESS;

        // auto result = ::xeFunctionSuggestGroupSize( handle, globalSizeX, globalSizeY, globalSizeZ );
        if( result_t::SUCCESS != result ) throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Function::SuggestGroupSize" );

        return std::tuple<uint32_t, uint32_t, uint32_t>{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set function argument used on function launch.
    /// 
    /// @details
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same function handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Function::SetArgumentValue(
        uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
        size_t argSize,                                 ///< [in] size of argument type
        const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                        ///< null then argument value is considered null.
        )
    {
        result_t result = result_t::SUCCESS;

        // auto result = ::xeFunctionSetArgumentValue( handle, argIndex, argSize, pArgValue );
        if( result_t::SUCCESS != result ) throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Function::SetArgumentValue" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sets a function attribute
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
    Function::SetAttribute(
        set_attribute_t attr,                           ///< [in] attribute to set
        uint32_t value                                  ///< [in] attribute value to set
        )
    {
        result_t result = result_t::SUCCESS;

        // auto result = ::xeFunctionSetAttribute( handle, attr, value );
        if( result_t::SUCCESS != result ) throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Function::SetAttribute" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Query a function attribute.
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
    Function::GetAttribute(
        get_attribute_t attr                            ///< [in] attribute to query
        )
    {
        result_t result = result_t::SUCCESS;

        // auto result = ::xeFunctionGetAttribute( handle, attr );
        if( result_t::SUCCESS != result ) throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Function::GetAttribute" );

        return uint32_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch function over one or more work groups.
    /// 
    /// @details
    ///     - This may **not** be called for a command list created with
    ///       ::COMMAND_LIST_FLAG_COPY_ONLY.
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
    CommandList::AppendLaunchFunction(
        Function* pFunction,                            ///< [in] pointer to the function object
        const thread_group_dimensions_t* pLaunchFuncArgs,   ///< [in] launch function arguments.
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        Event* phWaitEvents                             ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        result_t result = result_t::SUCCESS;

        // auto result = ::xeCommandListAppendLaunchFunction( handle, pFunction, pLaunchFuncArgs, pSignalEvent, numWaitEvents, phWaitEvents );
        if( result_t::SUCCESS != result ) throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendLaunchFunction" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch function over one or more work groups using indirect arguments.
    /// 
    /// @details
    ///     - The launch arguments need to be device visible.
    ///     - The launch arguments buffer may not be reusued until the function has
    ///       completed on the device.
    ///     - This may **not** be called for a command list created with
    ///       ::COMMAND_LIST_FLAG_COPY_ONLY.
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
    CommandList::AppendLaunchFunctionIndirect(
        Function* pFunction,                            ///< [in] pointer to the function object
        const thread_group_dimensions_t* pLaunchArgumentsBuffer,///< [in] pointer to device buffer that will contain launch arguments
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        Event* phWaitEvents                             ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        result_t result = result_t::SUCCESS;

        // auto result = ::xeCommandListAppendLaunchFunctionIndirect( handle, pFunction, pLaunchArgumentsBuffer, pSignalEvent, numWaitEvents, phWaitEvents );
        if( result_t::SUCCESS != result ) throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendLaunchFunctionIndirect" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch multiple functions over one or more work groups using an array
    ///        of indirect arguments.
    /// 
    /// @details
    ///     - The array of launch arguments need to be device visible.
    ///     - The array of launch arguments buffer may not be reusued until the
    ///       function has completed on the device.
    ///     - This may **not** be called for a command list created with
    ///       ::COMMAND_LIST_FLAG_COPY_ONLY.
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
    CommandList::AppendLaunchMultipleFunctionsIndirect(
        uint32_t numFunctions,                          ///< [in] maximum number of functions to launch
        Function* phFunctions,                          ///< [in][range(0, numFunctions)] handles of the function objects
        const uint32_t* pNumLaunchArguments,            ///< [in] pointer to device memory location that will contain the actual
                                                        ///< number of launch arguments; value must be less-than or equal-to
                                                        ///< numFunctions
        const thread_group_dimensions_t* pLaunchArgumentsBuffer,///< [in][range(0, numFunctions)] pointer to device buffer that will
                                                        ///< contain a contiguous array of launch arguments
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        Event* phWaitEvents                             ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        result_t result = result_t::SUCCESS;

        // auto result = ::xeCommandListAppendLaunchMultipleFunctionsIndirect( handle, numFunctions, phFunctions, pNumLaunchArguments, pLaunchArgumentsBuffer, pSignalEvent, numWaitEvents, phWaitEvents );
        if( result_t::SUCCESS != result ) throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendLaunchMultipleFunctionsIndirect" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch host function. All work after this command in the command list
    ///        will block until host function completes.
    /// 
    /// @details
    ///     - This may **not** be called for a command list created with
    ///       ::COMMAND_LIST_FLAG_COPY_ONLY.
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
        Event* phWaitEvents                             ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        result_t result = result_t::SUCCESS;

        // auto result = ::xeCommandListAppendLaunchHostFunction( handle, pfnHostFunc, pUserData, pSignalEvent, numWaitEvents, phWaitEvents );
        if( result_t::SUCCESS != result ) throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendLaunchHostFunction" );
    }

} // namespace xe

#ifdef _DEBUG
///////////////////////////////////////////////////////////////////////////////
/// @brief Converts Module::desc_version_t to std::string
std::string to_string( xe::Module::desc_version_t val )
{
    switch( val )
    {
    case xe::Module::desc_version_t::CURRENT:
        return std::string("xe::Module::desc_version_t::CURRENT");
    };
    return std::string("xe::Module::desc_version_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts Module::format_t to std::string
std::string to_string( xe::Module::format_t val )
{
    switch( val )
    {
    case xe::Module::format_t::IL_SPIRV:
        return std::string("xe::Module::format_t::IL_SPIRV");
    case xe::Module::format_t::NATIVE:
        return std::string("xe::Module::format_t::NATIVE");
    };
    return std::string("xe::Module::format_t::?");
}



///////////////////////////////////////////////////////////////////////////////
/// @brief Converts Function::desc_version_t to std::string
std::string to_string( xe::Function::desc_version_t val )
{
    switch( val )
    {
    case xe::Function::desc_version_t::CURRENT:
        return std::string("xe::Function::desc_version_t::CURRENT");
    };
    return std::string("xe::Function::desc_version_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts Function::flag_t to std::string
std::string to_string( xe::Function::flag_t val )
{
    switch( val )
    {
    case xe::Function::flag_t::NONE:
        return std::string("xe::Function::flag_t::NONE");
    case xe::Function::flag_t::FORCE_RESIDENCY:
        return std::string("xe::Function::flag_t::FORCE_RESIDENCY");
    };
    return std::string("xe::Function::flag_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts Function::set_attribute_t to std::string
std::string to_string( xe::Function::set_attribute_t val )
{
    switch( val )
    {
    case xe::Function::set_attribute_t::FUNCTION_SET_ATTR_INDIRECT_HOST_ACCESS:
        return std::string("xe::Function::set_attribute_t::FUNCTION_SET_ATTR_INDIRECT_HOST_ACCESS");
    case xe::Function::set_attribute_t::FUNCTION_SET_ATTR_INDIRECT_DEVICE_ACCESS:
        return std::string("xe::Function::set_attribute_t::FUNCTION_SET_ATTR_INDIRECT_DEVICE_ACCESS");
    case xe::Function::set_attribute_t::FUNCTION_SET_ATTR_INDIRECT_SHARED_ACCESS:
        return std::string("xe::Function::set_attribute_t::FUNCTION_SET_ATTR_INDIRECT_SHARED_ACCESS");
    };
    return std::string("xe::Function::set_attribute_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts Function::get_attribute_t to std::string
std::string to_string( xe::Function::get_attribute_t val )
{
    switch( val )
    {
    case xe::Function::get_attribute_t::FUNCTION_GET_ATTR_MAX_REGS_USED:
        return std::string("xe::Function::get_attribute_t::FUNCTION_GET_ATTR_MAX_REGS_USED");
    case xe::Function::get_attribute_t::FUNCTION_GET_ATTR_NUM_THREAD_DIMENSIONS:
        return std::string("xe::Function::get_attribute_t::FUNCTION_GET_ATTR_NUM_THREAD_DIMENSIONS");
    case xe::Function::get_attribute_t::FUNCTION_GET_ATTR_MAX_SHARED_MEM_SIZE:
        return std::string("xe::Function::get_attribute_t::FUNCTION_GET_ATTR_MAX_SHARED_MEM_SIZE");
    case xe::Function::get_attribute_t::FUNCTION_GET_ATTR_HAS_SPILL_FILL:
        return std::string("xe::Function::get_attribute_t::FUNCTION_GET_ATTR_HAS_SPILL_FILL");
    case xe::Function::get_attribute_t::FUNCTION_GET_ATTR_HAS_BARRIERS:
        return std::string("xe::Function::get_attribute_t::FUNCTION_GET_ATTR_HAS_BARRIERS");
    case xe::Function::get_attribute_t::FUNCTION_GET_ATTR_HAS_DPAS:
        return std::string("xe::Function::get_attribute_t::FUNCTION_GET_ATTR_HAS_DPAS");
    };
    return std::string("xe::Function::get_attribute_t::?");
}


#endif // _DEBUG
