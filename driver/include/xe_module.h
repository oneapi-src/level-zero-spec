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
/// @brief Creates module object from ISA
/// @remarks
///   _Analogues_
///     - **cuCtxCreate**
///     - cuCtxGetCurrent
/// @returns
/// - ::XE_RESULT_SUCCESS
/// - ::XE_RESULT_ERROR_UNINITIALIZED
/// - ::XE_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hDevice
///     + nullptr for pISAModule
///     + nullptr for phModule
///     + 0 for isaSize
/// - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
/// - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeCreateModuleFromISA(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const char** pISAModule,                        ///< [in] pointer to ISA module buffer
    size_t isaSize,                                 ///< [in] size of ISA module buffer
    xe_module_handle_t* phModule                    ///< [out] pointer to handle of module object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported IR types
typedef enum _xe_module_ir_type_t
{
    XE_MODULE_IR_SPIRV_TEXT = 0,                    ///< IR is spirv text format

} xe_module_ir_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates module object from IR
/// @remarks
///   _Analogues_
///     - **cuCtxCreate**
///     - cuCtxGetCurrent
/// @returns
/// - ::XE_RESULT_SUCCESS
/// - ::XE_RESULT_ERROR_UNINITIALIZED
/// - ::XE_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hDevice
///     + nullptr for pIRModule
///     + nullptr for phModule
///     + 0 for irSize
/// - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
/// - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeCreateModuleFromIR(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_module_ir_type_t irType,                     ///< [in] IR type that is passed in with pIRModule
    const char** pIRModule,                         ///< [in] pointer to IR module buffer
    size_t irSize,                                  ///< [in] size of IR module buffer
    xe_module_handle_t* phModule                    ///< [out] pointer to handle of module object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates module ISA object from IR
/// @remarks
///   _Analogues_
///     - **cuCtxCreate**
///     - cuCtxGetCurrent
/// @returns
/// - ::XE_RESULT_SUCCESS
/// - ::XE_RESULT_ERROR_UNINITIALIZED
/// - ::XE_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hDevice
///     + nullptr for pIRModule
///     + nullptr for pISAModule
///     + 0 for irSize
/// - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
/// - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeCreateModuleISAFromIR(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_module_ir_type_t irType,                     ///< [in] IR type that is passed in with pIRModule
    const char** pIRModule,                         ///< [in] pointer to IR module buffer
    size_t irSize,                                  ///< [in] size of IR module buffer
    const char** pISAModule,                        ///< [out] pointer to module ISA
    size_t isaSize                                  ///< [out] size of ISA module buffer
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates module object from IR
/// @remarks
///   _Analogues_
///     - **cuCtxCreate**
///     - cuCtxGetCurrent
/// @returns
/// - ::XE_RESULT_SUCCESS
/// - ::XE_RESULT_ERROR_UNINITIALIZED
/// - ::XE_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hDevice
///     + nullptr for pIRModule
///     + nullptr for phModule
///     + 0 for irSize
/// - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
/// - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeCreateModuleFromIR(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_module_ir_type_t irType,                     ///< [in] IR type that is passed in with pIRModule
    const char** pIRModule,                         ///< [in] pointer to IR module buffer
    size_t irSize,                                  ///< [in] size of IR module buffer
    xe_module_handle_t* phModule                    ///< [out] pointer to handle of module object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Releases module
/// @remarks
///   _Analogues_
///     - **cuCtxCreate**
///     - cuCtxGetCurrent
/// @returns
/// - ::XE_RESULT_SUCCESS
/// - ::XE_RESULT_ERROR_UNINITIALIZED
/// - ::XE_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hModule
xe_result_t __xecall
  xeReleaseModule(
    xe_module_handle_t hModule                      ///< [in] handle of the module
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Create Function object from Module by name
/// @remarks
///   _Analogues_
///     - **cuCtxCreate**
///     - cuCtxGetCurrent
/// @returns
/// - ::XE_RESULT_SUCCESS
/// - ::XE_RESULT_ERROR_UNINITIALIZED
/// - ::XE_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hModule
///     + null ptr for pFunctionName
///     + invalid name for pFunctionName
xe_result_t __xecall
  xeCreateFunctionFromModule(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const char* pFunctionName,                      ///< [in] name of function in Module
    xe_function_handle_t* phFunction                ///< [out] handle of the Function object
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Releases Function object
/// @remarks
///   _Analogues_
///     - **cuCtxCreate**
///     - cuCtxGetCurrent
/// @returns
/// - ::XE_RESULT_SUCCESS
/// - ::XE_RESULT_ERROR_UNINITIALIZED
/// - ::XE_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hModule
xe_result_t __xecall
  xeReleaseFunction(
    xe_function_handle_t hModule                    ///< [in] handle of the function object
    );

#endif // _XE_MODULE_H
