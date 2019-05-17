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
* @file xe_barrier.h
*
* @brief Intel Xe Level-Zero APIs for Barrier
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/barrier.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_BARRIER_H
#define _XE_BARRIER_H
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
/// @brief Appends an execution and global memory barrier into a command list.
/// 
/// @details
///     - If numWaitEvents is zero, then all previous commands are completed
///       prior to the execution of the barrier.
///     - If numWaitEvents is non-zero, then then all phWaitEvents must be
///       signalled prior to the execution of the barrier.
///     - This command blocks all following commands from beginning until the
///       execution of the barrier completes.
///     - Memory and cache hierarchies are flushed and invalidated sufficient
///       for device and host access.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendBarrier(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before executing barrier
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends a global memory ranges barrier into a command list.
/// 
/// @details
///     - If numWaitEvents is zero, then all previous commands are completed
///       prior to the execution of the barrier.
///     - If numWaitEvents is non-zero, then then all phWaitEvents must be
///       signalled prior to the execution of the barrier.
///     - This command blocks all following commands from beginning until the
///       execution of the barrier completes.
///     - Memory and cache hierarchies are flushed and invalidated sufficient
///       for device and host access.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == pRangeSizes
///         + nullptr == pRanges
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendMemoryRangesBarrier(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numRanges,                             ///< [in] number of memory ranges
    const size_t* pRangeSizes,                      ///< [in][range(0, numRanges)] array of sizes of memory range
    const void** pRanges,                           ///< [in][range(0, numRanges)] array of memory ranges
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before executing barrier
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Ensures in-bound writes to the device are globally observable.
/// 
/// @details
///     - This is a special-case system level barrier that can be used to ensure
///       global observability of writes; typically needed after a producer
///       (e.g., NIC) performs direct writes to the device's memory (e.g.,
///       Direct RDMA writes).  This is typically required when the memory
///       corresponding to the writes is subsequently accessed from a remote
///       device.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceSystemBarrier(
    xe_device_handle_t hDevice                      ///< [in] handle of the device
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XE_BARRIER_H
