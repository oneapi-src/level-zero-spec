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
* @file xe_cmdqueue.cpp
*
* @brief Intel Xe Driver APIs for Command Queue
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/cmdqueue.yml
* @endcond
*
******************************************************************************/
#include "../include/xe_cmdqueue.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command queue on the device.
/// 
/// @details
///     - This function may be called from simultaneous threads.
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
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == desc
///         + nullptr == phCommandQueue
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_COMMAND_QUEUE_DESC_VERSION <= desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceCreateCommandQueue(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
    xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == desc, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == phCommandQueue, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(XE_COMMAND_QUEUE_DESC_VERSION <= desc->version, XE_RESULT_ERROR_UNSUPPORTED);
    /// @begin {64cb11be0bd61d15890524c332cd41e37a7ff6c4b24ce3b3bdb3b0d19d687ad8}

    // @todo: insert <code> here

    /// @end   {64cb11be0bd61d15890524c332cd41e37a7ff6c4b24ce3b3bdb3b0d19d687ad8}
    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command queue.
/// 
/// @details
///     - The application is responsible for making sure the GPU is not
///       currently referencing the command queue before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this command queue
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
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandQueue
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandQueueDestroy(
    xe_command_queue_handle_t hCommandQueue         ///< [in] handle of command queue object to destroy
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandQueue, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {d2b4274520dcb902a966ba04f31f4c7e3976a1a6e0b6ad73d64713baa10785d4}

    // @todo: insert <code> here

    /// @end   {d2b4274520dcb902a966ba04f31f4c7e3976a1a6e0b6ad73d64713baa10785d4}
    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Enqueues a command list into a command queue for immediate execution.
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
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandQueue
///         + nullptr == phCommandLists
///         + 0 for numCommandLists
///         + hFence is in signaled state
///         + hFence is enqueued in another command queue
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandQueueEnqueueCommandLists(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint32_t numCommandLists,                       ///< [in] number of command lists to enqueue
    xe_command_list_handle_t* phCommandLists,       ///< [in] list of handles of the command lists to enqueue for execution
    xe_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandQueue, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == phCommandLists, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {3d9d4e4b61d47939ee851c18dce4cb2d2e5d99585ca8349927a49a7ee1aaceab}

    // @todo: insert <code> here

    /// @end   {3d9d4e4b61d47939ee851c18dce4cb2d2e5d99585ca8349927a49a7ee1aaceab}
    return XE_RESULT_SUCCESS;
}

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
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandQueue
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_NOT_READY
///         + timeout expired
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandQueueSynchronize(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    xe_synchronization_mode_t mode,                 ///< [in] synchronization mode
    uint32_t delay,                                 ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then time (in
                                                    ///< microseconds) to poll before putting Host thread to sleep; otherwise,
                                                    ///< must be zero.
    uint32_t interval,                              ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then maximum time (in
                                                    ///< microseconds) to put Host thread to sleep between polling; otherwise,
                                                    ///< must be zero.
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to poll or sleep
                                                    ///< before returning; if zero, then only a single status check is made
                                                    ///< before immediately returning; if -1, then function will not return
                                                    ///< until complete.
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandQueue, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {643f20374b51ae704dcb5e1c4d9e883d481cec8ce0ab0ebe52eb12aa25a2956e}

    // @todo: insert <code> here

    /// @end   {643f20374b51ae704dcb5e1c4d9e883d481cec8ce0ab0ebe52eb12aa25a2956e}
    return XE_RESULT_SUCCESS;
}

