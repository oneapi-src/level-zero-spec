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
* @file xe_fence.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Fence
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/fence.yml
* @endcond
*
******************************************************************************/
#include "xe_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a fence object on the device's command queue.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkCreateFence**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandQueue
///         + nullptr == desc
///         + nullptr == phFence
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_FENCE_DESC_VERSION_CURRENT < desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeFenceCreate(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
    const xe_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
    xe_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
    )
{
#if _DEBUG
    if( nullptr == context.xeFence.pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return context.xeFence.pfnCreate( hCommandQueue, desc, phFence );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a fence object.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the fence before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this fence
///     - The application may **not** call this function from simultaneous
///       threads with the same fence handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkDestroyFence**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFence
///         + fence is enqueued in a command queue
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeFenceDestroy(
    xe_fence_handle_t hFence                        ///< [in] handle of fence object to destroy
    )
{
#if _DEBUG
    if( nullptr == context.xeFence.pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return context.xeFence.pfnDestroy( hFence );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief The current host thread waits on a fence to be signaled.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkWaitForFences**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFence
///         + fence is not enqueued in a command queue
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_NOT_READY
///         + timeout expired
xe_result_t __xecall
xeFenceHostSynchronize(
    xe_fence_handle_t hFence,                       ///< [in] handle of the fence
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                    ///< returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY;
                                                    ///< if zero, then operates exactly like ::xeFenceQueryStatus;
                                                    ///< if MAX_UINT32, then function will not return until complete or device
                                                    ///< is lost.
    )
{
#if _DEBUG
    if( nullptr == context.xeFence.pfnHostSynchronize )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return context.xeFence.pfnHostSynchronize( hFence, timeout );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries a fence object's status.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkGetFenceStatus**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFence
///         + fence is not enqueued in a command queue
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_NOT_READY
///         + not signaled
xe_result_t __xecall
xeFenceQueryStatus(
    xe_fence_handle_t hFence                        ///< [in] handle of the fence
    )
{
#if _DEBUG
    if( nullptr == context.xeFence.pfnQueryStatus )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return context.xeFence.pfnQueryStatus( hFence );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset a fence back to the not signaled state.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkResetFences**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hFence
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeFenceReset(
    xe_fence_handle_t hFence                        ///< [in] handle of the fence
    )
{
#if _DEBUG
    if( nullptr == context.xeFence.pfnReset )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return context.xeFence.pfnReset( hFence );
}

} // extern "C"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    Fence::Fence( 
        CommandQueue* pCommandQueue,                    ///< [in] pointer to parent object
        const desc_t& desc                              ///< [in] descriptor of the fence object
        ) :
        m_pCommandQueue( pCommandQueue ),
        m_desc( desc )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a fence object on the device's command queue.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkCreateFence**
    /// 
    /// @returns
    ///     - Fence: pointer to handle of fence object created
    /// 
    /// @throws result_t
    Fence* __xecall
    Fence::Create(
        CommandQueue* pCommandQueue,                    ///< [in] pointer to command queue
        const desc_t* desc                              ///< [in] pointer to fence descriptor
        )
    {
        // auto result = ::xeFenceCreate( handle, pCommandQueue, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Fence::Create");

        return (Fence*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Deletes a fence object.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the fence before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this fence
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same fence handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkDestroyFence**
    /// 
    /// @throws result_t
    void __xecall
    Fence::Destroy(
        Fence* pFence                                   ///< [in] pointer to fence object to destroy
        )
    {
        // auto result = ::xeFenceDestroy( handle, pFence );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Fence::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief The current host thread waits on a fence to be signaled.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkWaitForFences**
    /// 
    /// @throws result_t
    void __xecall
    Fence::HostSynchronize(
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                        ///< returning ::RESULT_SUCCESS or ::RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::FenceQueryStatus;
                                                        ///< if MAX_UINT32, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        // auto result = ::xeFenceHostSynchronize( handle, timeout );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Fence::HostSynchronize");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Queries a fence object's status.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkGetFenceStatus**
    /// 
    /// @throws result_t
    void __xecall
    Fence::QueryStatus(
        void
        )
    {
        // auto result = ::xeFenceQueryStatus( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Fence::QueryStatus");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reset a fence back to the not signaled state.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkResetFences**
    /// 
    /// @throws result_t
    void __xecall
    Fence::Reset(
        void
        )
    {
        // auto result = ::xeFenceReset( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Fence::Reset");
    }

} // namespace xe

#ifdef _DEBUG
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fence::desc_version_t to std::string
    std::string to_string( xe::Fence::desc_version_t val )
    {
        switch( val )
        {
        case xe::Fence::desc_version_t::CURRENT:
            return std::string("xe::Fence::desc_version_t::CURRENT");
        };
        return std::string("xe::Fence::desc_version_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fence::flag_t to std::string
    std::string to_string( xe::Fence::flag_t val )
    {
        switch( val )
        {
        case xe::Fence::flag_t::NONE:
            return std::string("xe::Fence::flag_t::NONE");
        };
        return std::string("xe::Fence::flag_t::?");
    }


#endif // _DEBUG
