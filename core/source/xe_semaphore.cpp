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
* DO NOT EDIT: generated from /scripts/<type>/semaphore.yml
*
******************************************************************************/
#include "../include/xe_semaphore.h"

#include <exception>    // @todo: move to common and/or precompiled header

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
///
/// @hash {bc7abd02e1ba7c06025ed3c7d01f144f18685dd525e498c6509a8bb82faf788e}
///
__xedllexport xe_result_t __xecall
  xeDeviceCreateSemaphore(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_semaphore_desc_t* desc,                ///< [in] pointer to semaphore descriptor
    xe_semaphore_handle_t* phSemaphore              ///< [out] pointer to handle of semaphore object created
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;

            // Check parameters
            if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == phSemaphore ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( XE_SEMAPHORE_DESC_VERSION <= desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;
        }
        /// @begin

        // @todo: insert <code> here

        /// @end
        return XE_RESULT_SUCCESS;
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
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
///
/// @hash {43bb60d0801393aa47dec1e05417fc2e6081d35e5278113300295bb24aa17f78}
///
__xedllexport xe_result_t __xecall
  xeSemaphoreDestroy(
    xe_semaphore_handle_t hSemaphore                ///< [in] handle of semaphore object to destroy
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;

            // Check parameters
            if( nullptr == hSemaphore ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        // @todo: insert <code> here

        /// @end
        return XE_RESULT_SUCCESS;
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
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
///
/// @hash {12b429a676cf34244774ff30ac1e0dda194e98d90f481a8fb280f8582c21e030}
///
__xedllexport xe_result_t __xecall
  xeCommandListEncodeSemaphoreSignal(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_semaphore_handle_t hSemaphore,               ///< [in] handle of the semaphore
    xe_semaphore_value_t value                      ///< [in] the value to write on signal
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;

            // Check parameters
            if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == hSemaphore ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        // @todo: insert <code> here

        /// @end
        return XE_RESULT_SUCCESS;
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
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
///
/// @hash {887d86319b5e817467bb2593eb1854d47ab9fb2a64cfa9532f4355eb8035e660}
///
__xedllexport xe_result_t __xecall
  xeCommandListEncodeSemaphoreWait(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_semaphore_handle_t hSemaphore,               ///< [in] handle of the semaphore
    xe_semaphore_wait_operation_t operation,        ///< [in] wait operation type
    xe_semaphore_value_t value                      ///< [in] the value to wait upon
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;

            // Check parameters
            if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == hSemaphore ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        // @todo: insert <code> here

        /// @end
        return XE_RESULT_SUCCESS;
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
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
///
/// @hash {7554d75e51006df2fed4431132d3a6a6f5402c4bda1a118fe028ee58c400063c}
///
__xedllexport xe_result_t __xecall
  xeSemaphoreQueryValue(
    xe_semaphore_handle_t hSemaphore                ///< [in] handle of the semaphore
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;

            // Check parameters
            if( nullptr == hSemaphore ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        // @todo: insert <code> here

        /// @end
        return XE_RESULT_SUCCESS;
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
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
///
/// @hash {528c3f956a9521cef0604f1cc9dcdbf0bbdfb65160893e20d167acdb89ab4878}
///
__xedllexport xe_result_t __xecall
  xeSemaphoreReset(
    xe_semaphore_handle_t hSemaphore                ///< [in] handle of the semaphore
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;

            // Check parameters
            if( nullptr == hSemaphore ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        // @todo: insert <code> here

        /// @end
        return XE_RESULT_SUCCESS;
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

