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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == desc
///         + nullptr == phModule
///         + invalid desc->format
///         + nullptr for desc->pInputModule
///         + nullptr for desc->phModule
///         + 0 for desc->inputSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_MODULE_DESC_VERSION <= desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::XE_RESULT_ERROR_MODULE_BUILD_FAILURE - "Failure to build module. See build log for more details."
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
    // @todo: check_return(nullptr == hDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == desc, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == phModule, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(XE_MODULE_DESC_VERSION <= desc->version, XE_RESULT_ERROR_UNSUPPORTED);
    /// @begin {9eb829c1441842e279f9be96688eeb91e18798a1c6f1c8383d0a3ac86bfd4809}

    // @todo: insert <code> here

    /// @end   {9eb829c1441842e279f9be96688eeb91e18798a1c6f1c8383d0a3ac86bfd4809}
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hModule
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeModuleDestroy(
    xe_module_handle_t hModule                      ///< [in] handle of the module
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hModule, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {349b769d72d44bcbeb8306573eb07e65478f28d404576327cdd45381da9e8b96}

    // @todo: insert <code> here

    /// @end   {349b769d72d44bcbeb8306573eb07e65478f28d404576327cdd45381da9e8b96}
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
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hBuildLog
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeModuleBuildLogDestroy(
    xe_module_build_log_handle_t hBuildLog          ///< [in] handle of the module build log object.
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hBuildLog, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {f3094b9ab0cf409ea4c6bc63c2ec39ad88091a8ee9fe684c984e877f61548d00}

    // @todo: insert <code> here

    /// @end   {f3094b9ab0cf409ea4c6bc63c2ec39ad88091a8ee9fe684c984e877f61548d00}
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hBuildLog
///         + nullptr == pSize
///         + nullptr == pBuildLog
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeModuleBuildLogGetString(
    xe_module_build_log_handle_t hBuildLog,         ///< [in] handle of the module build log object.
    uint32_t* pSize,                                ///< [out] size of build log string.
    char** pBuildLog                                ///< [out] pointer to null-terminated string of the log.
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hBuildLog, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pSize, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pBuildLog, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {dd35e7a2beba7be9b599e677ac04880f6512aa776568772d8cd128b65b7839d4}

    // @todo: insert <code> here

    /// @end   {dd35e7a2beba7be9b599e677ac04880f6512aa776568772d8cd128b65b7839d4}
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
///     - The native binary will retain debugging information that is associated
///       with a module.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hModule
///         + nullptr == pSize
///         + nullptr == pModuleNativeBinary
///         + invalid format
///         + 0 for inputSize
///     - ::XE_RESULT_ERROR_UNSUPPORTED
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
    // @todo: check_return(nullptr == hModule, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pSize, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pModuleNativeBinary, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {f86dcf1e7e87d03f26bddcbff99420a8d159e89f57619beaaeebfee453cfd62e}

    // @todo: insert <code> here

    /// @end   {f86dcf1e7e87d03f26bddcbff99420a8d159e89f57619beaaeebfee453cfd62e}
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hModule
///         + nullptr == desc
///         + nullptr == phFunction
///         + nullptr for desc->pFunctionName
///         + invalid name for desc->pFunctionName
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_FUNCTION_DESC_VERSION <= desc->version
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
    // @todo: check_return(nullptr == hModule, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == desc, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == phFunction, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(XE_FUNCTION_DESC_VERSION <= desc->version, XE_RESULT_ERROR_UNSUPPORTED);
    /// @begin {db1f3dd910ba87cc5f4943397310ef13073b227ef8aad92327a8183e14461837}

    // @todo: insert <code> here

    /// @end   {db1f3dd910ba87cc5f4943397310ef13073b227ef8aad92327a8183e14461837}
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hFunction
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeFunctionDestroy(
    xe_function_handle_t hFunction                  ///< [in] handle of the function object
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hFunction, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {81a8e4126290acff1c7d8a2abbac4698476a5f69abd668a5098199163cfb01c7}

    // @todo: insert <code> here

    /// @end   {81a8e4126290acff1c7d8a2abbac4698476a5f69abd668a5098199163cfb01c7}
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hFunction
///         + nullptr == phFunctionArgs
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeFunctionCreateFunctionArgs(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function
    xe_function_args_handle_t* phFunctionArgs       ///< [out] handle of the Function arguments object
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hFunction, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == phFunctionArgs, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {d28a8e65c3c7b08efac12f45a3b9ec5fb16dbfe81f6c2d1fda1625887b62a478}

    // @todo: insert <code> here

    /// @end   {d28a8e65c3c7b08efac12f45a3b9ec5fb16dbfe81f6c2d1fda1625887b62a478}
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hFunctionArgs
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeFunctionArgsDestroy(
    xe_function_args_handle_t hFunctionArgs         ///< [in] handle of the function arguments buffer object
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hFunctionArgs, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {188738a5c24e1cfdced709bf247351be2c54076aeb5641fd6618850d3ad6d050}

    // @todo: insert <code> here

    /// @end   {188738a5c24e1cfdced709bf247351be2c54076aeb5641fd6618850d3ad6d050}
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hFunctionArgs
///         + nullptr == pArgValue
///         + invalid argument index
///         + invalid size specified
///     - ::XE_RESULT_ERROR_UNSUPPORTED
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
    // @todo: check_return(nullptr == hFunctionArgs, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pArgValue, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {a996568e450c8eba49523b384b4ad4b08e476e3e527d9ce286766ccf7d2a05e9}

    // @todo: insert <code> here

    /// @end   {a996568e450c8eba49523b384b4ad4b08e476e3e527d9ce286766ccf7d2a05e9}
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hFunctionArgs
///         + invalid value for attr
///         + invalid value for value
///     - ::XE_RESULT_ERROR_UNSUPPORTED
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
    // @todo: check_return(nullptr == hFunctionArgs, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {e8873190019647e8d9f6a5b6f325014dbea173082544527129680e4cc9451b04}

    // @todo: insert <code> here

    /// @end   {e8873190019647e8d9f6a5b6f325014dbea173082544527129680e4cc9451b04}
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hFunction
///         + nullptr == pValue
///         + invalid value for attr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
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
    // @todo: check_return(nullptr == hFunction, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pValue, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {cd0ca73d29fe12490a3a61992e20a5d3aeac34c8260b038d069a8e380af49c0a}

    // @todo: insert <code> here

    /// @end   {cd0ca73d29fe12490a3a61992e20a5d3aeac34c8260b038d069a8e380af49c0a}
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == hFunction
///         + nullptr == hFunctionArgs
///         + nullptr == pDispatchFuncArgs
///         + invalid group count range for dispatch
///         + invalid dispatch count range for dispatch
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandListEncodeDispatchFunction(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    xe_function_args_handle_t hFunctionArgs,        ///< [in] handle to function arguments buffer.
    const xe_dispatch_function_arguments_t* pDispatchFuncArgs,  ///< [in] dispatch function arguments.
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == hFunction, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == hFunctionArgs, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pDispatchFuncArgs, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {de4ec8dc364024f41980b93d7021d402e874ac946ffb59ea3eb5aa9ab3301066}

    // @todo: insert <code> here

    /// @end   {de4ec8dc364024f41980b93d7021d402e874ac946ffb59ea3eb5aa9ab3301066}
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandGraph
///         + nullptr == hFunction
///         + nullptr == hFunctionArgs
///         + nullptr == pDispatchFuncArgs
///         + invalid group count range for dispatch
///         + invalid dispatch count range for dispatch
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandGraphEncodeDispatchFunction(
    xe_command_graph_handle_t hCommandGraph,        ///< [in] handle of the command graph
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    xe_function_args_handle_t hFunctionArgs,        ///< [in] handle to function arguments buffer.
    const xe_dispatch_function_arguments_t* pDispatchFuncArgs,  ///< [in] dispatch function arguments.
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandGraph, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == hFunction, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == hFunctionArgs, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pDispatchFuncArgs, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {87e742e574cd46be6071af89e21e2ded1f39f92798fdf538870a4187533af411}

    // @todo: insert <code> here

    /// @end   {87e742e574cd46be6071af89e21e2ded1f39f92798fdf538870a4187533af411}
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == hFunction
///         + nullptr == hFunctionArgs
///         + nullptr == pDispatchArgumentsBuffer
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandListEncodeDispatchFunctionIndirect(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    xe_function_args_handle_t hFunctionArgs,        ///< [in] handle to function arguments buffer.
    const xe_dispatch_function_indirect_arguments_t* pDispatchArgumentsBuffer,  ///< [in] Pointer to buffer that will contain dispatch arguments.
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == hFunction, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == hFunctionArgs, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pDispatchArgumentsBuffer, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {57fb8d85b4c8cc16e07ad3342db0be97e5c18c19b72c8ceb3dcbd20f88a98eea}

    // @todo: insert <code> here

    /// @end   {57fb8d85b4c8cc16e07ad3342db0be97e5c18c19b72c8ceb3dcbd20f88a98eea}
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandGraph
///         + nullptr == hFunction
///         + nullptr == hFunctionArgs
///         + nullptr == pDispatchArgumentsBuffer
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandGraphEncodeDispatchFunctionIndirect(
    xe_command_graph_handle_t hCommandGraph,        ///< [in] handle of the command graph
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    xe_function_args_handle_t hFunctionArgs,        ///< [in] handle to function arguments buffer.
    const xe_dispatch_function_indirect_arguments_t* pDispatchArgumentsBuffer,  ///< [in] Pointer to buffer that will contain dispatch arguments.
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandGraph, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == hFunction, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == hFunctionArgs, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pDispatchArgumentsBuffer, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {47643fb62b1afef97af02b4695028e484c973c06d358233559925f0353f8e845}

    // @todo: insert <code> here

    /// @end   {47643fb62b1afef97af02b4695028e484c973c06d358233559925f0353f8e845}
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
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hFunction
///         + nullptr == groupSizeX
///         + nullptr == groupSizeY
///         + nullptr == groupSizeZ
///         + invalid number of threads.
///     - ::XE_RESULT_ERROR_UNSUPPORTED
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
    // @todo: check_return(nullptr == hFunction, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == groupSizeX, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == groupSizeY, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == groupSizeZ, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {f3c0ffef33c7e902e382ada2d1fac7966afd96c3c9989bf29a9917e4ae2856d2}

    // @todo: insert <code> here

    /// @end   {f3c0ffef33c7e902e382ada2d1fac7966afd96c3c9989bf29a9917e4ae2856d2}
    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Dispatch host function. All work after this command in the command
///        list will block until host function completes.
/// 
/// @details
///     - This function may **not** be called from simultaneous threads.
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
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == pUserData
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandListEncodeDispatchHostFunction(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_host_pfn_t pfnHostFunc,                      ///< [in] pointer to host function.
    void* pUserData                                 ///< [in] pointer to user data to pass to host function.
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pUserData, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {63f4382ff32ea764dd175c3c286a9799cd23b3e32aa90c1b948a6b1e0405b4ba}

    // @todo: insert <code> here

    /// @end   {63f4382ff32ea764dd175c3c286a9799cd23b3e32aa90c1b948a6b1e0405b4ba}
    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Dispatch host function. All work after this command in the command
///        list will block until host function completes.
/// 
/// @details
///     - This function may **not** be called from simultaneous threads.
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
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandGraph
///         + nullptr == pUserData
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandGraphEncodeDispatchHostFunction(
    xe_command_graph_handle_t hCommandGraph,        ///< [in] handle of the command graph
    xe_host_pfn_t pfnHostFunc,                      ///< [in] pointer to host function.
    void* pUserData                                 ///< [in] pointer to user data to pass to host function.
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandGraph, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pUserData, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {25ee33b5152b0dcbfaa702a00fef20f87383ad225fa62703b0344b6bd4569eee}

    // @todo: insert <code> here

    /// @end   {25ee33b5152b0dcbfaa702a00fef20f87383ad225fa62703b0344b6bd4569eee}
    return XE_RESULT_SUCCESS;
}

