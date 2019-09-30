/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_cmdlist.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Command List
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/cmdlist.yml
 * @endcond
 *
 */
#include "ze_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command list on the device for submitting commands to any
///        command queue.
/// 
/// @details
///     - The command list can only be used on the device on which it was
///       created.
///     - The command list is created in the 'open' state.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == desc
///         + nullptr == phCommandList
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + ::ZE_COMMAND_LIST_DESC_VERSION_CURRENT < desc->version
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
ze_result_t __zecall
zeCommandListCreate(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    const ze_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
    ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    )
{
    auto pfnCreate = ze_lib::context.ddiTable.CommandList.pfnCreate;
    if( nullptr == pfnCreate )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnCreate( hDevice, desc, phCommandList );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command list on the device with an implicit command queue
///        for immediate submission of commands.
/// 
/// @details
///     - The command list can only be used on the device on which it was
///       created.
///     - The command list is created in the 'open' state and never needs to be
///       closed.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == altdesc
///         + nullptr == phCommandList
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + ::ZE_COMMAND_QUEUE_DESC_VERSION_CURRENT < altdesc->version
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
ze_result_t __zecall
zeCommandListCreateImmediate(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    const ze_command_queue_desc_t* altdesc,         ///< [in] pointer to command queue descriptor
    ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    )
{
    auto pfnCreateImmediate = ze_lib::context.ddiTable.CommandList.pfnCreateImmediate;
    if( nullptr == pfnCreateImmediate )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnCreateImmediate( hDevice, altdesc, phCommandList );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command list.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the command list before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this command list.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeCommandListDestroy(
    ze_command_list_handle_t hCommandList           ///< [in][release] handle of command list object to destroy
    )
{
    auto pfnDestroy = ze_lib::context.ddiTable.CommandList.pfnDestroy;
    if( nullptr == pfnDestroy )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnDestroy( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes a command list; ready to be executed by a command queue.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeCommandListClose(
    ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
    )
{
    auto pfnClose = ze_lib::context.ddiTable.CommandList.pfnClose;
    if( nullptr == pfnClose )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnClose( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset a command list to initial (empty) state; ready for appending
///        commands.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the command list before it is reset
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeCommandListReset(
    ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
    )
{
    auto pfnReset = ze_lib::context.ddiTable.CommandList.pfnReset;
    if( nullptr == pfnReset )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnReset( hCommandList );
}

} // extern "C"

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    CommandList::CommandList( 
        command_list_handle_t handle,                   ///< [in] handle of command list object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the command list object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a command list on the device for submitting commands to any
    ///        command queue.
    /// 
    /// @details
    ///     - The command list can only be used on the device on which it was
    ///       created.
    ///     - The command list is created in the 'open' state.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - CommandList*: pointer to handle of command list object created
    /// 
    /// @throws result_t
    CommandList* __zecall
    CommandList::Create(
        Device* pDevice,                                ///< [in] pointer to the device object
        const desc_t* desc                              ///< [in] pointer to command list descriptor
        )
    {
        ze_command_list_handle_t hCommandList;

        auto result = static_cast<result_t>( ::zeCommandListCreate(
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const ze_command_list_desc_t*>( desc ),
            &hCommandList ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::Create" );

        CommandList* pCommandList = nullptr;

        try
        {
            pCommandList = new CommandList( reinterpret_cast<command_list_handle_t>( hCommandList ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pCommandList;
            pCommandList = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::CommandList::Create" );
        }

        return pCommandList;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a command list on the device with an implicit command queue
    ///        for immediate submission of commands.
    /// 
    /// @details
    ///     - The command list can only be used on the device on which it was
    ///       created.
    ///     - The command list is created in the 'open' state and never needs to be
    ///       closed.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - CommandList*: pointer to handle of command list object created
    /// 
    /// @throws result_t
    CommandList* __zecall
    CommandList::CreateImmediate(
        Device* pDevice,                                ///< [in] pointer to the device object
        const CommandQueue::desc_t* altdesc             ///< [in] pointer to command queue descriptor
        )
    {
        ze_command_list_handle_t hCommandList;

        auto result = static_cast<result_t>( ::zeCommandListCreateImmediate(
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const ze_command_queue_desc_t*>( altdesc ),
            &hCommandList ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::CreateImmediate" );

        CommandList* pCommandList = nullptr;

        try
        {
            pCommandList = new CommandList( reinterpret_cast<command_list_handle_t>( hCommandList ), pDevice, nullptr );
        }
        catch( std::bad_alloc& )
        {
            delete pCommandList;
            pCommandList = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::CommandList::CreateImmediate" );
        }

        return pCommandList;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys a command list.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the command list before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this command list.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::Destroy(
        CommandList* pCommandList                       ///< [in][release] pointer to command list object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListDestroy(
            reinterpret_cast<ze_command_list_handle_t>( pCommandList->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::Destroy" );

        delete pCommandList;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Closes a command list; ready to be executed by a command queue.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::Close(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListClose(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::Close" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reset a command list to initial (empty) state; ready for appending
    ///        commands.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the command list before it is reset
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::Reset(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListReset(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::Reset" );
    }

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::desc_version_t to std::string
    std::string to_string( const CommandList::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case CommandList::desc_version_t::CURRENT:
            str = "CommandList::desc_version_t::CURRENT";
            break;

        default:
            str = "CommandList::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::flag_t to std::string
    std::string to_string( const CommandList::flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(CommandList::flag_t::COPY_ONLY) & bits )
            str += "COPY_ONLY | ";
        
        if( static_cast<uint32_t>(CommandList::flag_t::RELAXED_ORDERING) & bits )
            str += "RELAXED_ORDERING | ";
        
        if( static_cast<uint32_t>(CommandList::flag_t::MAXIMIZE_THROUGHPUT) & bits )
            str += "MAXIMIZE_THROUGHPUT | ";
        
        if( static_cast<uint32_t>(CommandList::flag_t::EXPLICIT_ONLY) & bits )
            str += "EXPLICIT_ONLY | ";

        return ( str.size() > 3 ) 
            ? "CommandList::flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "CommandList::flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::memory_advice_t to std::string
    std::string to_string( const CommandList::memory_advice_t val )
    {
        std::string str;

        switch( val )
        {
        case CommandList::memory_advice_t::SET_READ_MOSTLY:
            str = "CommandList::memory_advice_t::SET_READ_MOSTLY";
            break;

        case CommandList::memory_advice_t::CLEAR_READ_MOSTLY:
            str = "CommandList::memory_advice_t::CLEAR_READ_MOSTLY";
            break;

        case CommandList::memory_advice_t::SET_PREFERRED_LOCATION:
            str = "CommandList::memory_advice_t::SET_PREFERRED_LOCATION";
            break;

        case CommandList::memory_advice_t::CLEAR_PREFERRED_LOCATION:
            str = "CommandList::memory_advice_t::CLEAR_PREFERRED_LOCATION";
            break;

        case CommandList::memory_advice_t::SET_ACCESSED_BY:
            str = "CommandList::memory_advice_t::SET_ACCESSED_BY";
            break;

        case CommandList::memory_advice_t::CLEAR_ACCESSED_BY:
            str = "CommandList::memory_advice_t::CLEAR_ACCESSED_BY";
            break;

        case CommandList::memory_advice_t::SET_NON_ATOMIC_MOSTLY:
            str = "CommandList::memory_advice_t::SET_NON_ATOMIC_MOSTLY";
            break;

        case CommandList::memory_advice_t::CLEAR_NON_ATOMIC_MOSTLY:
            str = "CommandList::memory_advice_t::CLEAR_NON_ATOMIC_MOSTLY";
            break;

        case CommandList::memory_advice_t::BIAS_CACHED:
            str = "CommandList::memory_advice_t::BIAS_CACHED";
            break;

        case CommandList::memory_advice_t::BIAS_UNCACHED:
            str = "CommandList::memory_advice_t::BIAS_UNCACHED";
            break;

        default:
            str = "CommandList::memory_advice_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::desc_t to std::string
    std::string to_string( const CommandList::desc_t val )
    {
        std::string str;
        
        str += "CommandList::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "CommandList::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::copy_region_t to std::string
    std::string to_string( const CommandList::copy_region_t val )
    {
        std::string str;
        
        str += "CommandList::copy_region_t::originX : ";
        str += std::to_string(val.originX);
        str += "\n";
        
        str += "CommandList::copy_region_t::originY : ";
        str += std::to_string(val.originY);
        str += "\n";
        
        str += "CommandList::copy_region_t::width : ";
        str += std::to_string(val.width);
        str += "\n";
        
        str += "CommandList::copy_region_t::height : ";
        str += std::to_string(val.height);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::image_region_t to std::string
    std::string to_string( const CommandList::image_region_t val )
    {
        std::string str;
        
        str += "CommandList::image_region_t::originX : ";
        str += std::to_string(val.originX);
        str += "\n";
        
        str += "CommandList::image_region_t::originY : ";
        str += std::to_string(val.originY);
        str += "\n";
        
        str += "CommandList::image_region_t::originZ : ";
        str += std::to_string(val.originZ);
        str += "\n";
        
        str += "CommandList::image_region_t::width : ";
        str += std::to_string(val.width);
        str += "\n";
        
        str += "CommandList::image_region_t::height : ";
        str += std::to_string(val.height);
        str += "\n";
        
        str += "CommandList::image_region_t::depth : ";
        str += std::to_string(val.depth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::thread_group_dimensions_t to std::string
    std::string to_string( const CommandList::thread_group_dimensions_t val )
    {
        std::string str;
        
        str += "CommandList::thread_group_dimensions_t::groupCountX : ";
        str += std::to_string(val.groupCountX);
        str += "\n";
        
        str += "CommandList::thread_group_dimensions_t::groupCountY : ";
        str += std::to_string(val.groupCountY);
        str += "\n";
        
        str += "CommandList::thread_group_dimensions_t::groupCountZ : ";
        str += std::to_string(val.groupCountZ);
        str += "\n";

        return str;
    }

} // namespace ze
