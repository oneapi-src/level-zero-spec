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
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Command Queue
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/cmdqueue.yml
* @endcond
*
******************************************************************************/
#include "xe_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command queue on the device.
/// 
/// @details
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
    )
{
    auto pfnCreate = xe_lib::lib.ddiTable.CommandQueue.pfnCreate;

#if _DEBUG
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnCreate( hDevice, desc, phCommandQueue );
}

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
    xe_command_queue_handle_t hCommandQueue         ///< [in] handle of command queue object to destroy
    )
{
    auto pfnDestroy = xe_lib::lib.ddiTable.CommandQueue.pfnDestroy;

#if _DEBUG
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnDestroy( hCommandQueue );
}

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
    )
{
    auto pfnExecuteCommandLists = xe_lib::lib.ddiTable.CommandQueue.pfnExecuteCommandLists;

#if _DEBUG
    if( nullptr == pfnExecuteCommandLists )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );
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
                                                    ///< if MAX_UINT32, then function will not return until complete or device
                                                    ///< is lost.
    )
{
    auto pfnSynchronize = xe_lib::lib.ddiTable.CommandQueue.pfnSynchronize;

#if _DEBUG
    if( nullptr == pfnSynchronize )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnSynchronize( hCommandQueue, timeout );
}

} // extern "C"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    CommandQueue::CommandQueue( 
        command_queue_handle_t handle,                  ///< [in] handle of command queue object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the command queue object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a command queue on the device.
    /// 
    /// @details
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
    ///     - CommandQueue*: pointer to handle of command queue object created
    /// 
    /// @throws result_t
    CommandQueue* __xecall
    CommandQueue::Create(
        Device* pDevice,                                ///< [in] pointer to the device object
        const desc_t* desc                              ///< [in] pointer to command queue descriptor
        )
    {
        xe_command_queue_handle_t hCommandQueue;

        auto result = static_cast<result_t>( ::xeCommandQueueCreate(
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const xe_command_queue_desc_t*>( desc ),
            &hCommandQueue ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandQueue::Create" );

        auto pCommandQueue = new CommandQueue( reinterpret_cast<command_queue_handle_t>( hCommandQueue ), pDevice, desc );

        return pCommandQueue;
    }

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
    /// @throws result_t
    void __xecall
    CommandQueue::Destroy(
        CommandQueue* pCommandQueue                     ///< [in] pointer to command queue object to destroy
        )
    {
        auto result = static_cast<result_t>( ::xeCommandQueueDestroy(
            reinterpret_cast<xe_command_queue_handle_t>( pCommandQueue->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandQueue::Destroy" );

        delete pCommandQueue;
    }

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
    /// @throws result_t
    void __xecall
    CommandQueue::ExecuteCommandLists(
        uint32_t numCommandLists,                       ///< [in] number of command lists to execute
        CommandList** ppCommandLists,                   ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                        ///< to execute
        Fence* pFence                                   ///< [in][optional] pointer to the fence to signal on completion
        )
    {
        thread_local std::vector<xe_command_list_handle_t> hCommandLists;
        hCommandLists.resize( 0 );
        hCommandLists.reserve( numCommandLists );
        for( uint32_t i = 0; i < numCommandLists; ++i )
            hCommandLists.emplace_back( reinterpret_cast<xe_command_list_handle_t>( ppCommandLists[ i ]->getHandle() ) );

        auto result = static_cast<result_t>( ::xeCommandQueueExecuteCommandLists(
            reinterpret_cast<xe_command_queue_handle_t>( getHandle() ),
            numCommandLists,
            hCommandLists.data(),
            ( pFence ) ? reinterpret_cast<xe_fence_handle_t>( pFence->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandQueue::ExecuteCommandLists" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Synchronizes a command queue by waiting on the host.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    CommandQueue::Synchronize(
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                        ///< returning ::RESULT_SUCCESS or ::RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::FenceQueryStatus;
                                                        ///< if MAX_UINT32, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        auto result = static_cast<result_t>( ::xeCommandQueueSynchronize(
            reinterpret_cast<xe_command_queue_handle_t>( getHandle() ),
            timeout ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandQueue::Synchronize" );
    }

} // namespace xe

#ifdef _DEBUG
///////////////////////////////////////////////////////////////////////////////
/// @brief Converts CommandQueue::desc_version_t to std::string
std::string to_string( xe::CommandQueue::desc_version_t val )
{
    switch( val )
    {
    case xe::CommandQueue::desc_version_t::CURRENT:
        return std::string("xe::CommandQueue::desc_version_t::CURRENT");
    };
    return std::string("xe::CommandQueue::desc_version_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts CommandQueue::flag_t to std::string
std::string to_string( xe::CommandQueue::flag_t val )
{
    const auto bits = static_cast<uint32_t>( val );
    if( 0 == bits ) return std::string("{}");
    std::string str;
    if( static_cast<uint32_t>(xe::CommandQueue::flag_t::NONE) & bits )
        str += "xe::CommandQueue::flag_t::NONE | ";
    if( static_cast<uint32_t>(xe::CommandQueue::flag_t::COPY_ONLY) & bits )
        str += "xe::CommandQueue::flag_t::COPY_ONLY | ";
    if( static_cast<uint32_t>(xe::CommandQueue::flag_t::LOGICAL_ONLY) & bits )
        str += "xe::CommandQueue::flag_t::LOGICAL_ONLY | ";
    if( static_cast<uint32_t>(xe::CommandQueue::flag_t::SINGLE_SLICE_ONLY) & bits )
        str += "xe::CommandQueue::flag_t::SINGLE_SLICE_ONLY | ";
    return "{ " + str.substr(0, str.size() - 3) + " }";
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts CommandQueue::mode_t to std::string
std::string to_string( xe::CommandQueue::mode_t val )
{
    switch( val )
    {
    case xe::CommandQueue::mode_t::DEFAULT:
        return std::string("xe::CommandQueue::mode_t::DEFAULT");
    case xe::CommandQueue::mode_t::SYNCHRONOUS:
        return std::string("xe::CommandQueue::mode_t::SYNCHRONOUS");
    case xe::CommandQueue::mode_t::ASYNCHRONOUS:
        return std::string("xe::CommandQueue::mode_t::ASYNCHRONOUS");
    };
    return std::string("xe::CommandQueue::mode_t::?");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts CommandQueue::priority_t to std::string
std::string to_string( xe::CommandQueue::priority_t val )
{
    switch( val )
    {
    case xe::CommandQueue::priority_t::NORMAL:
        return std::string("xe::CommandQueue::priority_t::NORMAL");
    case xe::CommandQueue::priority_t::LOW:
        return std::string("xe::CommandQueue::priority_t::LOW");
    case xe::CommandQueue::priority_t::HIGH:
        return std::string("xe::CommandQueue::priority_t::HIGH");
    };
    return std::string("xe::CommandQueue::priority_t::?");
}


#endif // _DEBUG
