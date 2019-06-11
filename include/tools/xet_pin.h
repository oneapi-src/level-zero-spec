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
* @file xet_pin.h
*
* @brief Intel Xe Level-Zero Tool APIs for Program Instrumentation (PIN)
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/pin.yml
* @endcond
*
******************************************************************************/
#ifndef _XET_PIN_H
#define _XET_PIN_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_XET_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Reserve a section of contiguous buffer space within the module.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same module handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModule
///         + nullptr == hostptr
///         + nullptr == deviceptr
///         + 0 for size
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetModuleReserveSpace(
    xet_module_handle_t hModule,                    ///< [in] handle of the module
    size_t size,                                    ///< [in] size (in bytes) to reserve
    void** hostptr,                                 ///< [out] Host visible pointer to space reserved
    void** deviceptr                                ///< [out] device visible pointer to space reserved
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XET_PIN_H
