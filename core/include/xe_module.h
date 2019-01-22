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
    XE_MODULE_IL_SPIRV_TEXT = 0,                    ///< Format is SPIRV IL text format
    XE_MODULE_ISA,                                  ///< Format is Gen ISA format

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
/// @brief Creates module object from an input IL or ISA.
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
  xeModuleGetISA(
    xe_module_handle_t hModule,                     ///< [in] handle of the device
    uint32_t* pIsaSize,                             ///< [out] size of ISA buffer provided by pModuleISA.
    char** pModuleISA                               ///< [out] pointer to IL or ISA
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Releases module
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
  xeReleaseModulef(
    xe_module_handle_t hModule                      ///< [in] handle of the module
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Create Function object from Module by name
/// 
/// @remarks
///   _Analogues_
///     - **cuModuleGetGlobal**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hModule
///         + null ptr for pGlobalName
///         + invalid name for pGlobalName
///         + null ptr for pGlobalValue
xe_result_t __xecall
  xeModuleGetGlobal(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const char* pGlobalName,                        ///< [in] name of function in global
    size_t valueSize,                               ///< [out] size of value type
    void* pGlobalValue                              ///< [out] pointer to global value
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
  xeCreateFunctionFromModule(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const char* pFunctionName,                      ///< [in] null-terminated name of function in Module
    xe_function_handle_t* phFunction                ///< [out] handle of the Function object
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Releases Function object
/// 
/// @remarks
///   _Analogues_
///     - **cuModuleUnload**
///     - cuCtxGetCurrent
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hFunction
xe_result_t __xecall
  xeReleaseFunction(
    xe_function_handle_t hFunction                  ///< [in] handle of the function object
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Create Function arguments buffer needed to pass arguments to a
///        function.
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
  xeCreateFunctionArgsBuffer(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function
    xe_function_args_handle_t* phFunctionArgs       ///< [out] handle of the Function arguments object
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Releases Function arguments buffer object
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
  xeReleaseFunctionArgsBuffer(
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
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
    size_t argSize,                                 ///< [in] size of argument type
    const void* pArgValue,                          ///< [in] argument value represented as matching arg type
    x_function_args_handle_t hFunctionArgs          ///< [in/out] handle of the function arguments buffer object
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
/// @brief Dispatch function to queue.
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
  xeDispatchFunction(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    x_function_args_handle_t pFunctionArgs,         ///< [in] pointer to function arguments buffer.
    uint32_t groupCountX,                           ///< [in] width of group in X dimension
    uint32_t groupCountY,                           ///< [in] width of group in Y dimension
    uint32_t groupCountZ,                           ///< [in] width of group in Z dimension
    uint32_t dispatchCountX,                        ///< [in] width of dispatches in X dimension
    uint32_t dispatchCountY,                        ///< [in] width of dispatches in Y dimension
    uint32_t dispatchCountZ                         ///< [in] width of dispatches in Z dimension
    );

#endif // _XE_MODULE_H
