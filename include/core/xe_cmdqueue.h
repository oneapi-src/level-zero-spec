/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_cmdqueue.h
 *
 * @brief Intel 'One API' Level-Zero APIs for Command Queue
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/cmdqueue.yml
 * @endcond
 *
 */
#ifndef _XE_CMDQUEUE_H
#define _XE_CMDQUEUE_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_XE_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xe_command_queue_desc_t
typedef enum _xe_command_queue_desc_version_t
{
    XE_COMMAND_QUEUE_DESC_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ),///< version 1.0

} xe_command_queue_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command queue flags
typedef enum _xe_command_queue_flag_t
{
    XE_COMMAND_QUEUE_FLAG_NONE = 0,                 ///< default behavior
    XE_COMMAND_QUEUE_FLAG_COPY_ONLY = XE_BIT(0),    ///< command queue only supports enqueing copy-only command lists
    XE_COMMAND_QUEUE_FLAG_LOGICAL_ONLY = XE_BIT(1), ///< command queue is not tied to a physical command queue; driver may
                                                    ///< dynamically assign based on usage
    XE_COMMAND_QUEUE_FLAG_SINGLE_SLICE_ONLY = XE_BIT(2),///< command queue reserves and cannot comsume more than a single slice.
                                                    ///< 'slice' size is device-specific.  cannot be combined with COPY_ONLY.

} xe_command_queue_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command queue modes
typedef enum _xe_command_queue_mode_t
{
    XE_COMMAND_QUEUE_MODE_DEFAULT = 0,              ///< implicit default behavior; uses driver-based heuristics
    XE_COMMAND_QUEUE_MODE_SYNCHRONOUS,              ///< Device execution always completes immediately on execute;
                                                    ///< Host thread is blocked using wait on implicit synchronization object
    XE_COMMAND_QUEUE_MODE_ASYNCHRONOUS,             ///< Device execution is scheduled and will complete in future;
                                                    ///< explicit synchronization object must be used to determine completeness

} xe_command_queue_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command queue priorities
typedef enum _xe_command_queue_priority_t
{
    XE_COMMAND_QUEUE_PRIORITY_NORMAL = 0,           ///< [default] normal priority
    XE_COMMAND_QUEUE_PRIORITY_LOW,                  ///< lower priority than normal
    XE_COMMAND_QUEUE_PRIORITY_HIGH,                 ///< higher priority than normal

} xe_command_queue_priority_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Command Queue descriptor
typedef struct _xe_command_queue_desc_t
{
    xe_command_queue_desc_version_t version;        ///< [in] ::XE_COMMAND_QUEUE_DESC_VERSION_CURRENT
    xe_command_queue_flag_t flags;                  ///< [in] creation flags
    xe_command_queue_mode_t mode;                   ///< [in] operation mode
    xe_command_queue_priority_t priority;           ///< [in] priority
    uint32_t ordinal;                               ///< [in] if logical-only flag is set, then will be ignored;
                                                    ///< else-if copy-only flag is set, then must be less than ::xe_device_properties_t.numAsyncCopyEngines;
                                                    ///< otherwise must be less than
                                                    ///< ::xe_device_properties_t.numAsyncComputeEngines. When using sub-devices
                                                    ///< the ::xe_device_properties_t.numAsyncComputeEngines must be queried
                                                    ///< from the sub-device being used.

} xe_command_queue_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command queue on the device.
/// 
/// @details
///     - The command queue can only be used on the device on which it was
///       created.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clCreateCommandQueue**
///     - cuCtxCreate
///     - cuCtxGetCurrent
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == desc
///         + nullptr == phCommandQueue
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_COMMAND_QUEUE_DESC_VERSION_CURRENT < desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeCommandQueueCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
    xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command queue.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the command queue before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this command queue
///     - The application may **not** call this function from simultaneous
///       threads with the same command queue handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clReleaseCommandQueue**
///     - cuCtxDestroy
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandQueue
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandQueueDestroy(
    xe_command_queue_handle_t hCommandQueue         ///< [in][release] handle of command queue object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Executes a command list in a command queue.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - vkQueueSubmit
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandQueue
///         + nullptr == phCommandLists
///         + 0 for numCommandLists
///         + hFence is in signaled state
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandQueueExecuteCommandLists(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint32_t numCommandLists,                       ///< [in] number of command lists to execute
    xe_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                    ///< to execute
    xe_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Synchronizes a command queue by waiting on the host.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandQueue
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_NOT_READY
///         + timeout expired
xe_result_t __xecall
xeCommandQueueSynchronize(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                    ///< returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY;
                                                    ///< if zero, then operates exactly like ::xeFenceQueryStatus;
                                                    ///< if UINT32_MAX, then function will not return until complete or device
                                                    ///< is lost.
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XE_CMDQUEUE_H
