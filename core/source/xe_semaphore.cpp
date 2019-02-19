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
* @file xe_semaphore.cpp
*
* @brief Intel Xe Driver APIs for Semaphore
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/semaphore.yml
* @endcond
*
******************************************************************************/
#include "../include/xe_semaphore.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an semaphore object on the device.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkCreateSemaphore**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == desc
///         + nullptr == phSemaphore
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_SEMAPHORE_DESC_VERSION <= desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceCreateSemaphore(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_semaphore_desc_t* desc,                ///< [in] pointer to semaphore descriptor
    xe_semaphore_handle_t* phSemaphore              ///< [out] pointer to handle of semaphore object created
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == desc, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == phSemaphore, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(XE_SEMAPHORE_DESC_VERSION <= desc->version, XE_RESULT_ERROR_UNSUPPORTED);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes an semaphore object.
/// 
/// @details
///     - The application is responsible for making sure the GPU is not
///       currently referencing the semaphore before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this semaphore
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkDestroySemaphore**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hSemaphore
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeSemaphoreDestroy(
    xe_semaphore_handle_t hSemaphore                ///< [in] handle of semaphore object to destroy
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hSemaphore, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes an semaphore signal into a command list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == hSemaphore
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandListEncodeSemaphoreSignal(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_semaphore_handle_t hSemaphore,               ///< [in] handle of the semaphore
    xe_semaphore_value_t value                      ///< [in] the value to write on signal
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == hSemaphore, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes an semaphore wait into a command list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == hSemaphore
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandListEncodeSemaphoreWait(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_semaphore_handle_t hSemaphore,               ///< [in] handle of the semaphore
    xe_semaphore_wait_operation_t operation,        ///< [in] wait operation type
    xe_semaphore_value_t value                      ///< [in] the value to wait upon
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == hSemaphore, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries an semaphore object's value.
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
///         + nullptr == hSemaphore
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeSemaphoreQueryValue(
    xe_semaphore_handle_t hSemaphore                ///< [in] handle of the semaphore
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hSemaphore, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset a semaphore back to the value of 0.
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
///         + nullptr == hSemaphore
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeSemaphoreReset(
    xe_semaphore_handle_t hSemaphore                ///< [in] handle of the semaphore
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hSemaphore, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

