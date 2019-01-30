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
* @file xe_barrier.h
*
* @brief Intel Xe Driver APIs for Barrier
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/barrier.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_BARRIER_H
#define _XE_BARRIER_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes an execution barrier into a command list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkCmdPipelineBarrier**
///     - clEnqueueBarrierWithWaitList
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
xe_result_t __xecall
  xeCommandListEncodeExecutionBarrier(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes a memory barrier into a command list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkCmdPipelineBarrier**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
xe_result_t __xecall
  xeCommandListEncodeMemoryBarrier(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    );

#endif // _XE_BARRIER_H
