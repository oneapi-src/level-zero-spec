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
* @file xe_barrier.cpp
*
* @brief Intel Xe Driver APIs for Barrier
*
* DO NOT EDIT: generated from /scripts/core/barrier.yml
*
******************************************************************************/
#if defined(XE_CPP)
#include "../include/xe_barrier.hpp"
#else
#include "../include/xe_barrier.h"
#endif
#if !defined(XE_NULLDRV)
#include "barrier.h"
#endif

#include <exception>    // @todo: move to common and/or precompiled header
#include <new>

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends an execution barrier into a command list.
/// 
/// @details
///     - This may **not** be called for a command list created with
///       ::XE_COMMAND_LIST_FLAG_COPY_ONLY.
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
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {b7f3f20a5e54174f765a7560d254515c25d90ace7add120975c8136f78e62775}
///
__xedllexport xe_result_t __xecall
xeCommandListAppendExecutionBarrier(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::CommandList::fromHandle(hCommandList)->appendExecutionBarrier();
#endif
        /// @end
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

