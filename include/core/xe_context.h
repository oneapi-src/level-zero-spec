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
* @file xe_context.h
*
* @brief Intel Xe Level-Zero APIs for Context
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/context.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_CONTEXT_H
#define _XE_CONTEXT_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_XE_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif
#include "xe_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a context.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clCreateContext**
///     - cuCtxCreate
///     - cuCtxGetCurrent
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == phDevice
///         + nullptr == phContext
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeContextCreate(
    size_t numDevices,                              ///< [in] number of devices in phDevice
    xe_device_handle_t* phDevice,                   ///< [in][range(0, numDevices)] pointer to array of handle of the device
                                                    ///< objects
    xe_context_handle_t* phContext                  ///< [out] pointer to handle of context object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a context.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the context before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this context
///     - The application may **not** call this function from simultaneous
///       threads with the same context handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clReleaseContext**
///     - cuCtxDestroy
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hContext
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeContextDestroy(
    xe_context_handle_t hContext                    ///< [in] handle of context object to destroy
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XE_CONTEXT_H
