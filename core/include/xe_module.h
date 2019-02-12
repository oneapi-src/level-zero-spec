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
* @file xe_module.h
*
* @brief Intel Xe Driver APIs for Module
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/module.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_MODULE_H
#define _XE_MODULE_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xe_module_desc_t
#define XE_MODULE_DESC_VERSION  XE_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported module creation input formats
typedef enum _xe_module_format_t
{
    XE_MODULE_IL_SPIRV = 0,                         ///< Format is SPIRV IL format
    XE_MODULE_NATIVE,                               ///< Format is device native format

} xe_module_format_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Module descriptor
typedef struct _xe_module_desc_t
{
    uint32_t version;                               ///< [in] ::XE_MODULE_DESC_VERSION
    xe_module_format_t format;                      ///< [in] Module format passed in with pInputModule
    uint32_t inputSize;                             ///< [in] size of input IL or ISA from pInputModule.
    const char* pInputModule;                       ///< [in] pointer to IL or ISA
    const char* pBuildFlags;                        ///< [in] string containing compiler flags. See documentation for build
                                                    ///< flags.

} xe_module_desc_t;

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
xe_result_t __xecall
  xeDeviceCreateModule(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_module_desc_t* desc,                   ///< [in] pointer to module descriptor
    xe_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
    xe_module_build_log_handle_t* phBuildLog        ///< [out][optional] pointer to handle of module's build log.
    );

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
xe_result_t __xecall
  xeModuleDestroy(
    xe_module_handle_t hModule                      ///< [in] handle of the module
    );

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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hBuildLog
xe_result_t __xecall
  xeModuleBuildLogDestroy(
    xe_module_build_log_handle_t hBuildLog          ///< [in] handle of the module build log object.
    );

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
xe_result_t __xecall
  xeModuleBuildLogGetString(
    xe_module_build_log_handle_t hBuildLog,         ///< [in] handle of the module build log object.
    uint32_t* pSize,                                ///< [out] size of build log string.
    char** pBuildLog                                ///< [out] pointer to null-terminated string of the log.
    );

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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + invalid format
///         + nullptr for pInputModule
///         + nullptr for phModule
///         + 0 for inputSize
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeModuleGetNativeBinary(
    xe_module_handle_t hModule,                     ///< [in] handle of the device
    uint32_t* pSize,                                ///< [out] size of native binary.
    char** pModuleNativeBinary                      ///< [out] pointer to native binary
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xe_function_desc_t
#define XE_FUNCTION_DESC_VERSION  XE_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported function creation flags
typedef enum _xe_function_flags_t
{
    XE_FUNCTION_FLAG_NONE = 0,                      ///< default driver behavior
    XE_FUNCTION_FLAG_FORCE_RESIDENCY,               ///< force all device allocations to be resident during execution

} xe_function_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Function descriptor
typedef struct _xe_function_desc_t
{
    uint32_t version;                               ///< [in] ::XE_FUNCTION_DESC_VERSION
    xe_function_flags_t flags;                      ///< [in] creation flags
    const char* pFunctionName;                      ///< [in] null-terminated name of function in Module

} xe_function_desc_t;

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
xe_result_t __xecall
  xeModuleCreateFunction(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const xe_function_desc_t* desc,                 ///< [in] pointer to function descriptor
    xe_function_handle_t* phFunction                ///< [out] handle of the Function object
    );

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
xe_result_t __xecall
  xeFunctionDestroy(
    xe_function_handle_t hFunction                  ///< [in] handle of the function object
    );

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
xe_result_t __xecall
  xeFunctionCreateFunctionArgs(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function
    xe_function_args_handle_t* phFunctionArgs       ///< [out] handle of the Function arguments object
    );

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
xe_result_t __xecall
  xeFunctionArgsDestroy(
    xe_function_args_handle_t hFunctionArgs         ///< [in] handle of the function arguments buffer object
    );

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
xe_result_t __xecall
  xeFunctionArgsSetValue(
    xe_function_args_handle_t hFunctionArgs,        ///< [in/out] handle of the function args object.
    uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
    size_t argSize,                                 ///< [in] size of argument type
    const void* pArgValue                           ///< [in] argument value represented as matching arg type
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function argument attributes
/// 
/// @remarks
///   _Analogues_
///     - **cl_kernel_exec_info**
typedef enum _xe_function_argument_attribute_t
{
    XE_FUNCTION_ARG_ATTR_INDIRECT_HOST_ACCESS = 0,  ///< Indicates that the function accesses host allocations indirectly
                                                    ///< (default: false)
    XE_FUNCTION_ARG_ATTR_INDIRECT_DEVICE_ACCESS,    ///< Indicates that the function accesses device allocations indirectly
                                                    ///< (default: false)
    XE_FUNCTION_ARG_ATTR_INDIRECT_SHARED_ACCESS,    ///< Indicates that the function accesses shared allocations indirectly
                                                    ///< (default: false)

} xe_function_argument_attribute_t;

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
xe_result_t __xecall
  xeFunctionArgsSetAttribute(
    xe_function_args_handle_t hFunctionArgs,        ///< [in/out] handle of the function args object.
    xe_function_argument_attribute_t attr,          ///< [in] attribute to set
    uint32_t value                                  ///< [in] attribute value to set
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function attributes
/// 
/// @remarks
///   _Analogues_
///     - **CUfunction_attribute**
typedef enum _xe_function_attribute_t
{
    XE_FUNCTION_ATTR_MAX_REGS_USED = 0,             ///< Maximum device registers used for this function
    XE_FUNCTION_ATTR_NUM_THREAD_DIMENSIONS,         ///< Maximum dimensions for group for this function
    XE_FUNCTION_ATTR_MAX_SHARED_MEM_SIZE,           ///< Maximum shared memory required for this function
    XE_FUNCTION_ATTR_HAS_SPILL_FILL,                ///< Function required spill/fills.
    XE_FUNCTION_ATTR_HAS_BARRIERS,                  ///< Function contains barriers.
    XE_FUNCTION_ATTR_HAS_DPAS,                      ///< Function contains DPAs.

} xe_function_attribute_t;

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
xe_result_t __xecall
  xeFunctionQueryAttribute(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    xe_function_attribute_t attr,                   ///< [in] attribute to query
    uint32_t* pValue                                ///< [out] returned attribute value
    );

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
///         + invalid handle for hCommandList
///         + invalid handle for hFunction
///         + nullptr for function arguments buffer
///         + invalid group count range for dispatch
///         + invalid dispatch count range for dispatch
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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Indirect function arguments. These arguments are device visible.
typedef struct _xe_dispatch_function_indirect_arguments_t
{
    uint32_t groupSizeX;                            ///< [in] group size for X dimension
    uint32_t groupSizeY;                            ///< [in] group size for Y dimension
    uint32_t groupSizeZ;                            ///< [in] group size for Z dimension
    uint32_t groupCountX;                           ///< [in] width of dispatches in X dimension
    uint32_t groupCountY;                           ///< [in] width of dispatches in Y dimension
    uint32_t groupCountZ;                           ///< [in] width of dispatches in Z dimension

} xe_dispatch_function_indirect_arguments_t;

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
///         + invalid handle for hCommandList
///         + invalid handle for hFunction
///         + invalid handle for hFunctionArgs.
///         + nullptr for dispatch arguments buffer
xe_result_t __xecall
  xeCommandListEncodeDispatchFunctionIndirect(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    xe_function_args_handle_t hFunctionArgs,        ///< [in] handle to function arguments buffer.
    const xe_dispatch_function_indirect_arguments_t* pDispatchArgumentsBuffer,  ///< [in] Pointer to buffer that will contain dispatch arguments.
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    );

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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hFunction
///         + invalid number of threads.
xe_result_t __xecall
  xeFunctionSuggestGroupSize(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    uint32_t globalSizeX,                           ///< [in] global width for X dimension.
    uint32_t globalSizeY,                           ///< [in] global width for Y dimension.
    uint32_t globalSizeZ,                           ///< [in] global width for Z dimension.
    uint32_t* groupSizeX,                           ///< [out] recommended size of group for X dimension.
    uint32_t* groupSizeY,                           ///< [out] recommended size of group for Y dimension.
    uint32_t* groupSizeZ                            ///< [out] recommended size of group for Z dimension.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief type definition for host function pointers used with
///        ::xeCommandListEncodeDispatchHostFunction
/// 
/// @details
///     - This function may be called from simultaneous threads.
///     - The implementation of this function should be lock-free.
typedef void(__xecall *xe_host_pfn_t)(
  void* pUserData                                 ///< [in] Pointer to user data to pass to host function.
  );

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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
///         + null ptr for pfnHostFunc
///         + null ptr for pUserData.
xe_result_t __xecall
  xeCommandListEncodeDispatchHostFunction(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_host_pfn_t pfnHostFunc,                      ///< [in] pointer to host function.
    void* pUserData                                 ///< [in] pointer to user data to pass to host function.
    );

#endif // _XE_MODULE_H
