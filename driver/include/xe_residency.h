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
* @file xe_residency.h
*
* @brief Intel Xe Driver APIs for Memory
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/residency.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_RESIDENCY_H
#define _XE_RESIDENCY_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Makes memory resident for the device.
/// @returns
/// - ::XE_RESULT_SUCCESS
/// - ::XE_RESULT_ERROR_UNINITIALIZED
/// - ::XE_RESULT_ERROR_INVALID_PARAMETER
///     + nullptr for ptr
xe_result_t __xecall
  xeDeviceMakeMemoryResident(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_ptr_t ptr,                            ///< [in] pointer to memory to make resident
    size_t size                                     ///< [in] size in bytes to make resident
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Allows memory to be evicted from the device.
/// @returns
/// - ::XE_RESULT_SUCCESS
/// - ::XE_RESULT_ERROR_UNINITIALIZED
/// - ::XE_RESULT_ERROR_INVALID_PARAMETER
///     + nullptr for ptr
xe_result_t __xecall
  xeDeviceEvictMemory(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_ptr_t ptr,                            ///< [in] pointer to memory to evict
    size_t size                                     ///< [in] size in bytes to evict
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Makes memory resident for the device.
/// @returns
/// - ::XE_RESULT_SUCCESS
/// - ::XE_RESULT_ERROR_UNINITIALIZED
/// - ::XE_RESULT_ERROR_INVALID_PARAMETER
///     + nullptr for ptr
xe_result_t __xecall
  xeDeviceMakeResourceResident(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_resource_handle_t hResource                  ///< [in] handle of resource to make resident
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Allows resource to be evicted from the device.
/// @returns
/// - ::XE_RESULT_SUCCESS
/// - ::XE_RESULT_ERROR_UNINITIALIZED
/// - ::XE_RESULT_ERROR_INVALID_PARAMETER
///     + nullptr for ptr
xe_result_t __xecall
  xeDeviceEvictResource(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_resource_handle_t hResource                  ///< [in] handle of resource to make evict
    );

#endif // _XE_RESIDENCY_H
