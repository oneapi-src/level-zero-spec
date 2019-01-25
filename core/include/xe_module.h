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
/// @brief API version of ::xe_command_queue_desc_t
#define XE_MODULE_DESC_VERSION  XE_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported module creation input formats
typedef enum _xe_module_format_t
{
    XE_MODULE_IL_SPIRV = 0,                         ///< Format is SPIRV IL format
    XE_MODULE_NATIVE,                               ///< Format is Gen native format

} xe_module_format_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates module object from an input IL or ISA.
/// 
/// @remarks
///   _Analogues_
///     - **cuModuleLoad**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + invalid format
///         + nullptr for pInputModule
///         + nullptr for phModule
///         + 0 for inputSize
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeCreateModule(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_module_format_t format,                      ///< [in] Module format passed in with pInputModule
    uint32_t inputSize,                             ///< [in] size of input IL or ISA from pInputModule.
    const char* pInputModule,                       ///< [in] pointer to IL or ISA
    xe_module_handle_t* phModule                    ///< [out] pointer to handle of module object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys module
/// 
/// @remarks
///   _Analogues_
///     - **cuModuleUnload**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hModule
xe_result_t __xecall
  xeDestroyModule(
    xe_module_handle_t hModule                      ///< [in] handle of the module
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve native binary from Module.
/// 
/// @remarks
///   _Analogues_
///     - **cuModuleLoad**
///     - cuCtxGetCurrent
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
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
    uint32_t* pIsaSize,                             ///< [out] size of ISA buffer provided by pModuleISA.
    char** pModuleNativeBinary                      ///< [out] pointer to native binary
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve a function argument index from name.
/// 
/// @remarks
///   _Analogues_
///     - **cuModuleGetTexRef**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hFunction
///         + null ptr for pName
///         + null ptr for pArgIndex
xe_result_t __xecall
  xeFunctionGetArgIndexFromName(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function
    const char* pName,                              ///< [in] name of function argument
    uint32_t* pArgIndex                             ///< [out] Function argument index that can be used for ::xeSetFunctionArgValue
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Create Function object from Module by name
/// 
/// @remarks
///   _Analogues_
///     - **cuModuleGetFunction**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hModule
///         + null ptr for pFunctionName
///         + invalid name for pFunctionName
xe_result_t __xecall
  xeModuleCreateFunction(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const char* pFunctionName,                      ///< [in] null-terminated name of function in Module
    xe_function_handle_t* phFunction                ///< [out] handle of the Function object
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys Function object
/// 
/// @remarks
///   _Analogues_
///     - 
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hFunction
xe_result_t __xecall
  xeDestroyFunction(
    xe_function_handle_t hFunction                  ///< [in] handle of the function object
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Create Function arguments needed to pass arguments to a function.
/// 
/// @remarks
///   _Analogues_
///     - 
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hFunction
///         + nullptr for phFunctionArgs
xe_result_t __xecall
  xeCreateFunctionArgs(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function
    xe_function_args_handle_t* phFunctionArgs       ///< [out] handle of the Function arguments object
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys Function arguments object
/// 
/// @remarks
///   _Analogues_
///     - 
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hFunctionArgs
xe_result_t __xecall
  xeDestroyFunctionArgs(
    xe_function_args_handle_t hFunctionArgs         ///< [in] handle of the function arguments buffer object
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set function arguments within arguments buffer.
/// 
/// @remarks
///   _Analogues_
///     - **cuCtxCreate**
///     - cuCtxGetCurrent
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hFunction
///         + invalid argument index
///         + null ptr for pArgValue
///         + invalid size specified
///         + invalid handle for hFunctionArgs
xe_result_t __xecall
  xeSetFunctionArgValue(
    xe_function_args_handle_t hFunctionArgs,        ///< [in/out] handle of the function args object.
    uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
    size_t argSize,                                 ///< [in] size of argument type
    const void* pArgValue                           ///< [in] argument value represented as matching arg type
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
    XE_FUNCTION_ATTR_MAX_THREADS_PER_GROUP,         ///< Maximum threads required for this function
    XE_FUNCTION_ATTR_MAX_SHARED_MEM_SIZE,           ///< Maximum shared memory required for this function

} xe_function_attribute_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Query a function attribute.
/// 
/// @remarks
///   _Analogues_
///     - **cuFuncGetAttribute**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hFunction
///         + invalid value for attr
///         + null ptr for pValue
xe_result_t __xecall
  xeQueryFunctionAttribute(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    xe_function_attribute_t attr,                   ///< [in] attribute to query
    uint32_t* pValue                                ///< [out] returned attribute value
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Dispatch command over one or more work groups.
/// 
/// @remarks
///   _Analogues_
///     - **cuLaunchKernel**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandQueue
///         + invalid handle for hFunction
///         + null ptr for function arguments buffer
///         + invalid group count range for dispatch
///         + invalid dispatch count range for dispatch
xe_result_t __xecall
  xeCommandListEncodeDispatchFunction(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    xe_function_args_handle_t hFunctionArgs,        ///< [in] handle to function arguments buffer.
    uint32_t threadCountX,                          ///< [in] width of group in threads for X dimension
    uint32_t threadCountY,                          ///< [in] width of group in threads for Y dimension
    uint32_t threadCountZ,                          ///< [in] width of group in threads for Z dimension
    uint32_t groupCountX,                           ///< [in] width of dispatches in X dimension
    uint32_t groupCountY,                           ///< [in] width of dispatches in Y dimension
    uint32_t groupCountZ                            ///< [in] width of dispatches in Z dimension
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Device properties queried using ::xeDeviceGetProperties
typedef struct _xe_dispatch_function_arguments_t
{
    uint32_t threadCountX;                          ///< [in] width of group in threads for X dimension
    uint32_t threadCountY;                          ///< [in] width of group in threads for Y dimension
    uint32_t threadCountZ;                          ///< [in] width of group in threads for Z dimension
    uint32_t groupCountX;                           ///< [in] width of dispatches in X dimension
    uint32_t groupCountY;                           ///< [in] width of dispatches in Y dimension
    uint32_t groupCountZ;                           ///< [in] width of dispatches in Z dimension

} xe_dispatch_function_arguments_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Dispatch command over one or more work groups using indirect dispatch
///        arguments.
/// 
/// @remarks
///   _Analogues_
///     - **cuLaunchKernel**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandQueue
///         + invalid handle for hFunction
///         + invalid handle for hFunctionArgs.
///         + null ptr for dispatch arguments buffer
xe_result_t __xecall
  xeCommandListEncodeDispatchFunctionIndirect(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    xe_function_args_handle_t hFunctionArgs,        ///< [in] handle to function arguments buffer.
    const xe_dispatch_function_arguments_t* pDispatchArgumentsBuffer///< [in] Pointer to buffer that will contain dispatch arguments.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Compute max groups that can occupy per sublice.
/// 
/// @remarks
///   _Analogues_
///     - **cuOccupancyMaxActiveBlocksPerMultiprocessor**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hFunction
///         + null ptr for pDispatchArgumentsBuffer.
///         + null ptr for pMax Groups
xe_result_t __xecall
  xeOccupancyMaxGroupsPerSublice(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    xe_dispatch_function_arguments_t* pDispatchArgumentsBuffer, ///< [in] Pointer to buffer that will contain dispatch arguments.
    uint32_t* pMaxGroups                            ///< [out] Pointer to maximum groups that can occupy subslice for this function.
    );

#endif // _XE_MODULE_H
