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
    )
{
    auto pfnCreate = xe_lib::context.ddiTable.CommandQueue.pfnCreate;
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    xe_command_queue_handle_t hCommandQueue         ///< [in][release] handle of command queue object to destroy
    )
{
    auto pfnDestroy = xe_lib::context.ddiTable.CommandQueue.pfnDestroy;
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    auto pfnExecuteCommandLists = xe_lib::context.ddiTable.CommandQueue.pfnExecuteCommandLists;
    if( nullptr == pfnExecuteCommandLists )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
                                                    ///< if UINT32_MAX, then function will not return until complete or device
                                                    ///< is lost.
    )
{
    auto pfnSynchronize = xe_lib::context.ddiTable.CommandQueue.pfnSynchronize;
    if( nullptr == pfnSynchronize )
        return XE_RESULT_ERROR_UNSUPPORTED;

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

        CommandQueue* pCommandQueue = nullptr;

        try
        {
            pCommandQueue = new CommandQueue( reinterpret_cast<command_queue_handle_t>( hCommandQueue ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pCommandQueue;
            pCommandQueue = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xe::CommandQueue::Create" );
        }

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
        CommandQueue* pCommandQueue                     ///< [in][release] pointer to command queue object to destroy
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
    ///     - bool_t:'0' when RESULT_NOT_READY
    /// @throws result_t
    bool_t __xecall
    CommandQueue::Synchronize(
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                        ///< returning ::RESULT_SUCCESS or ::RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::FenceQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        auto result = static_cast<result_t>( ::xeCommandQueueSynchronize(
            reinterpret_cast<xe_command_queue_handle_t>( getHandle() ),
            timeout ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandQueue::Synchronize" );
        return 1; // true
    }

} // namespace xe

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::desc_version_t to std::string
    std::string to_string( const CommandQueue::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case CommandQueue::desc_version_t::CURRENT:
            str = "CommandQueue::desc_version_t::CURRENT";
            break;

        default:
            str = "CommandQueue::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::flag_t to std::string
    std::string to_string( const CommandQueue::flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(CommandQueue::flag_t::COPY_ONLY) & bits )
            str += "COPY_ONLY | ";
        
        if( static_cast<uint32_t>(CommandQueue::flag_t::LOGICAL_ONLY) & bits )
            str += "LOGICAL_ONLY | ";
        
        if( static_cast<uint32_t>(CommandQueue::flag_t::SINGLE_SLICE_ONLY) & bits )
            str += "SINGLE_SLICE_ONLY | ";

        return ( str.size() > 3 ) 
            ? "CommandQueue::flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "CommandQueue::flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::mode_t to std::string
    std::string to_string( const CommandQueue::mode_t val )
    {
        std::string str;

        switch( val )
        {
        case CommandQueue::mode_t::DEFAULT:
            str = "CommandQueue::mode_t::DEFAULT";
            break;

        case CommandQueue::mode_t::SYNCHRONOUS:
            str = "CommandQueue::mode_t::SYNCHRONOUS";
            break;

        case CommandQueue::mode_t::ASYNCHRONOUS:
            str = "CommandQueue::mode_t::ASYNCHRONOUS";
            break;

        default:
            str = "CommandQueue::mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::priority_t to std::string
    std::string to_string( const CommandQueue::priority_t val )
    {
        std::string str;

        switch( val )
        {
        case CommandQueue::priority_t::NORMAL:
            str = "CommandQueue::priority_t::NORMAL";
            break;

        case CommandQueue::priority_t::LOW:
            str = "CommandQueue::priority_t::LOW";
            break;

        case CommandQueue::priority_t::HIGH:
            str = "CommandQueue::priority_t::HIGH";
            break;

        default:
            str = "CommandQueue::priority_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::desc_t to std::string
    std::string to_string( const CommandQueue::desc_t val )
    {
        std::string str;
        
        str += "CommandQueue::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "CommandQueue::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "CommandQueue::desc_t::mode : ";
        str += to_string(val.mode);
        str += "\n";
        
        str += "CommandQueue::desc_t::priority : ";
        str += to_string(val.priority);
        str += "\n";
        
        str += "CommandQueue::desc_t::ordinal : ";
        str += std::to_string(val.ordinal);
        str += "\n";

        return str;
    }

} // namespace xe
