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
* @file xe_sampler.h
*
* @brief Intel Xe Level-Zero APIs for Sampler
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/sampler.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_SAMPLER_H
#define _XE_SAMPLER_H
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
/// @brief API version of ::xe_sampler_desc_t
typedef enum _xe_sampler_desc_version_t
{
    XE_SAMPLER_DESC_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ),  ///< version 1.0

} xe_sampler_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Sampler addressing modes
typedef enum _xe_sampler_address_mode_t
{
    XE_SAMPLER_ADDRESS_MODE_NONE = 0,               ///< No coordinate modifications for out-of-bounds image access.
    XE_SAMPLER_ADDRESS_MODE_REPEAT,                 ///< Out-of-bounds coordinates are wrapped back around.
    XE_SAMPLER_ADDRESS_MODE_CLAMP,                  ///< Out-of-bounds coordinates are clamped to edge.
    XE_SAMPLER_ADDRESS_MODE_MIRROR,                 ///< Out-of-bounds coordinates are mirrored starting from edge.

} xe_sampler_address_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Sampler filtering modes
typedef enum _xe_sampler_filter_mode_t
{
    XE_SAMPLER_FILTER_MODE_NEAREST = 0,             ///< No coordinate modifications for out of bounds image access.
    XE_SAMPLER_FILTER_MODE_LINEAR,                  ///< Out-of-bounds coordinates are wrapped back around.

} xe_sampler_filter_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Sampler descriptor
typedef struct _xe_sampler_desc_t
{
    xe_sampler_desc_version_t version;              ///< [in] ::XE_SAMPLER_DESC_VERSION_CURRENT
    xe_sampler_address_mode_t addressMode;          ///< [in] Sampler addressing mode to determine how out-of-bounds
                                                    ///< coordinates are handled.
    xe_sampler_filter_mode_t filterMode;            ///< [in] Sampler filter mode to determine how samples are filtered.
    xe_bool_t isNormalized;                         ///< [in] Are coordinates normalized [0, 1] or not.

} xe_sampler_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates sampler object.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuTexObjectCreate**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == pDesc
///         + nullptr == phSampler
///         + invalid pDesc->addressMode
///         + invalid pDesc->filterMode
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_SAMPLER_DESC_VERSION_CURRENT < pDesc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
xe_result_t __xecall
xeSamplerCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_sampler_desc_t* pDesc,                 ///< [in] pointer to sampler descriptor
    xe_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys sampler object
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the sampler before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this module
///     - The application may **not** call this function from simultaneous
///       threads with the same sampler handle.
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
///         + nullptr == hSampler
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeSamplerDestroy(
    xe_sampler_handle_t hSampler                    ///< [in] handle of the sampler
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XE_SAMPLER_H
