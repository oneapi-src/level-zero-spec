/**************************************************************************//**
*
* INTEL CONFIDENTIAL
* Copyright 2019
* Intel Corporation All Rights Reserved.
*
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
*
* @file xe_module.cpp
*
* @brief Intel Xe Driver APIs for Module
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/module.yml
* @endcond
*
******************************************************************************/
#include "../include/xe_module.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates module object from an input IL or native binary.
/// 
/// @details
///     - This function may be called from simultaneous threads.
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + nullptr for desc
///         + invalid desc->format
///         + nullptr for desc->pInputModule
///         + nullptr for desc->phModule
///         + 0 for desc->inputSize
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceCreateModule(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_module_desc_t* desc,                   ///< [in] pointer to module descriptor
    xe_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
    xe_module_build_log_handle_t* phBuildLog        ///< [out][optional] pointer to handle of module's build log.
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_device_handle_t() == hDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == desc, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(XE_MODULE_DESC_VERSION <= desc->version, XE_RESULT_ERROR_UNSUPPORTED);
    // @todo: check_return(nullptr == phModule, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys module
/// 
/// @details
///     - The application is responsible for making sure the GPU is not
///       currently referencing the event before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this module
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuModuleUnload**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hModule
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeModuleDestroy(
    xe_module_handle_t hModule                      ///< [in] handle of the module
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_module_handle_t() == hModule, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys module build log object
/// 
/// @details
///     - The application is responsible for making sure the GPU is not
///       currently referencing the event before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this object
///     - The implementation of this function should be lock-free.
///     - This function can be called before or after ::xeModuleDestroy for the
///       associated module.
/// 
/// @remarks
///   _Analogues_
///     - 
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hBuildLog
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeModuleBuildLogDestroy(
    xe_module_build_log_handle_t hBuildLog          ///< [in] handle of the module build log object.
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_module_build_log_handle_t() == hBuildLog, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves text string for build log.
/// 
/// @details
///     - This function may be called from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr for hBuildLog
///         + nullptr for pSize
///         + nullptr for pBuildLog
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeModuleBuildLogGetString(
    xe_module_build_log_handle_t hBuildLog,         ///< [in] handle of the module build log object.
    uint32_t* pSize,                                ///< [out] size of native binary.
    char** pBuildLog                                ///< [out] string pointer to log.
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_module_build_log_handle_t() == hBuildLog, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pSize, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pBuildLog, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve native binary from Module.
/// 
/// @details
///     - This function may be called from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - The memory for the native binary output is associated with the module.
///       The output pointer should not be accessed after a module has been
///       destroyed.
///     - The native binary output can be cached to disk and new modules can be
///       later constructed from the cached copy.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + invalid format
///         + nullptr for pInputModule
///         + nullptr for phModule
///         + 0 for inputSize
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeModuleGetNativeBinary(
    xe_module_handle_t hModule,                     ///< [in] handle of the device
    uint32_t* pSize,                                ///< [out] size of native binary.
    char** pModuleNativeBinary                      ///< [out] pointer to native binary
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_module_handle_t() == hModule, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pSize, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pModuleNativeBinary, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Create Function object from Module by name
/// 
/// @details
///     - This function may be called from simultaneous threads.
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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hModule
///         + nullptr for desc
///         + nullptr for desc->pFunctionName
///         + invalid name for desc->pFunctionName
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeModuleCreateFunction(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const xe_function_desc_t* desc,                 ///< [in] pointer to function descriptor
    xe_function_handle_t* phFunction                ///< [out] handle of the Function object
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_module_handle_t() == hModule, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == desc, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(XE_FUNCTION_DESC_VERSION <= desc->version, XE_RESULT_ERROR_UNSUPPORTED);
    // @todo: check_return(nullptr == phFunction, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys Function object
/// 
/// @details
///     - The application is responsible for making sure the GPU is not
///       currently referencing the event before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this function
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hFunction
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeFunctionDestroy(
    xe_function_handle_t hFunction                  ///< [in] handle of the function object
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_function_handle_t() == hFunction, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Create Function arguments needed to pass arguments to a function.
/// 
/// @details
///     - This function may be called from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - FunctionArgs objects must be used with the Function object it was
///       created for.
///     - Use ::xeFunctionArgsSetValue to setup arguments for dispatch.
///     - FunctionArgs can updated and used across multiple dispatches for the
///       same function.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hFunction
///         + nullptr for phFunctionArgs
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeFunctionCreateFunctionArgs(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function
    xe_function_args_handle_t* phFunctionArgs       ///< [out] handle of the Function arguments object
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_function_handle_t() == hFunction, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == phFunctionArgs, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys Function arguments object
/// 
/// @details
///     - The application is responsible for making sure the GPU is not
///       currently referencing the event before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this function args
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hFunctionArgs
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeFunctionArgsDestroy(
    xe_function_args_handle_t hFunctionArgs         ///< [in] handle of the function arguments buffer object
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_function_args_handle_t() == hFunctionArgs, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set function arguments within arguments buffer.
/// 
/// @details
///     - This function may **not** be called from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuCtxCreate**
///     - cuCtxGetCurrent
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hFunctionArgs
///         + invalid argument index
///         + nullptr for pArgValue
///         + invalid size specified
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeFunctionArgsSetValue(
    xe_function_args_handle_t hFunctionArgs,        ///< [in/out] handle of the function args object.
    uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
    size_t argSize,                                 ///< [in] size of argument type
    const void* pArgValue                           ///< [in] argument value represented as matching arg type
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_function_args_handle_t() == hFunctionArgs, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pArgValue, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets a function argument attribute
/// 
/// @details
///     - This function may **not** be called from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clSetKernelExecInfo**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hFunctionArgs
///         + invalid value for attr
///         + invalid value for value
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeFunctionArgsSetAttribute(
    xe_function_args_handle_t hFunctionArgs,        ///< [in/out] handle of the function args object.
    xe_function_argument_attribute_t attr,          ///< [in] attribute to set
    uint32_t value                                  ///< [in] attribute value to set
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_function_args_handle_t() == hFunctionArgs, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Query a function attribute.
/// 
/// @details
///     - This function may be called from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuFuncGetAttribute**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hFunction
///         + invalid value for attr
///         + nullptr for pValue
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeFunctionQueryAttribute(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    xe_function_attribute_t attr,                   ///< [in] attribute to query
    uint32_t* pValue                                ///< [out] returned attribute value
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_function_handle_t() == hFunction, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pValue, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Dispatch command over one or more work groups.
/// 
/// @details
///     - This function may **not** be called from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuLaunchKernel**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandQueue
///         + invalid handle for hFunction
///         + nullptr for function arguments buffer
///         + invalid group count range for dispatch
///         + invalid dispatch count range for dispatch
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandListEncodeDispatchFunction(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    xe_function_args_handle_t hFunctionArgs,        ///< [in] handle to function arguments buffer.
    uint32_t groupSizeX,                            ///< [in] group size for X dimension
    uint32_t groupSizeY,                            ///< [in] group size for Y dimension
    uint32_t groupSizeZ,                            ///< [in] group size for Z dimension
    uint32_t groupCountX,                           ///< [in] width of group dispatches in X dimension
    uint32_t groupCountY,                           ///< [in] width of group dispatches in Y dimension
    uint32_t groupCountZ,                           ///< [in] width of group dispatches in Z dimension
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_command_list_handle_t() == hCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(xe_function_handle_t() == hFunction, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(xe_function_args_handle_t() == hFunctionArgs, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Dispatch command over one or more work groups using indirect dispatch
///        arguments.
/// 
/// @details
///     - This function may **not** be called from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - The dispatch arguments need to be device visible.
///     - The dispatch arguments buffer may not be reusued until dispatch has
///       completed on the device.
/// 
/// @remarks
///   _Analogues_
///     - **cuLaunchKernel**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandQueue
///         + invalid handle for hFunction
///         + invalid handle for hFunctionArgs.
///         + nullptr for dispatch arguments buffer
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandListEncodeDispatchFunctionIndirect(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    xe_function_args_handle_t hFunctionArgs,        ///< [in] handle to function arguments buffer.
    const xe_dispatch_function_arguments_t* pDispatchArgumentsBuffer,   ///< [in] Pointer to buffer that will contain dispatch arguments.
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_command_list_handle_t() == hCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(xe_function_handle_t() == hFunction, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(xe_function_args_handle_t() == hFunctionArgs, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pDispatchArgumentsBuffer, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Query a suggested group size for function. If the function has an
///        embedded group size then this will be returned. Otherwise, one will be
///        suggested.
/// 
/// @details
///     - This function may be called from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - 
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hFunction
///         + invalid number of threads.
/*@todo: __declspec(dllexport)*/
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
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_function_handle_t() == hFunction, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == groupSizeX, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == groupSizeY, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == groupSizeZ, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

