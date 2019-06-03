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
* @file xe_cmdlist.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Command List
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/cmdlist.yml
* @endcond
*
******************************************************************************/
#include "xe_lib.h"

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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == desc
///         + nullptr == phCommandList
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_COMMAND_LIST_DESC_VERSION_CURRENT < desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeCommandListCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
    xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    )
{
    auto pfnCreate = xe_lib::lib.ddiTable.CommandList.pfnCreate;

#if _DEBUG
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == altdesc
///         + nullptr == phCommandList
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_COMMAND_QUEUE_DESC_VERSION_CURRENT < altdesc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeCommandListCreateImmediate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_queue_desc_t* altdesc,         ///< [in] pointer to command queue descriptor
    xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    )
{
    auto pfnCreateImmediate = xe_lib::lib.ddiTable.CommandList.pfnCreateImmediate;

#if _DEBUG
    if( nullptr == pfnCreateImmediate )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListDestroy(
    xe_command_list_handle_t hCommandList           ///< [in][release] handle of command list object to destroy
    )
{
    auto pfnDestroy = xe_lib::lib.ddiTable.CommandList.pfnDestroy;

#if _DEBUG
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListClose(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
    )
{
    auto pfnClose = xe_lib::lib.ddiTable.CommandList.pfnClose;

#if _DEBUG
    if( nullptr == pfnClose )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListReset(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
    )
{
    auto pfnReset = xe_lib::lib.ddiTable.CommandList.pfnReset;

#if _DEBUG
    if( nullptr == pfnReset )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnReset( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets a command list's parameter.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - cuCtxSetCacheConfig
///     - cuCtxSetLimit
///     - cuCtxSetSharedMemConfig
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + invalid value for attribute
///         + invalid value for value
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListSetParameter(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_command_list_parameter_t parameter,          ///< [in] parameter to change
    uint32_t value                                  ///< [in] value of attribute
    )
{
    auto pfnSetParameter = xe_lib::lib.ddiTable.CommandList.pfnSetParameter;

#if _DEBUG
    if( nullptr == pfnSetParameter )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnSetParameter( hCommandList, parameter, value );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves a command list's parameter.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - cuCtxGetCacheConfig
///     - cuCtxGetLimit
///     - cuCtxGetSharedMemConfig
///     - cuCtxGetStreamPriorityRange
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == value
///         + invalid value for attribute
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListGetParameter(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_command_list_parameter_t parameter,          ///< [in] parameter to retrieve
    uint32_t* value                                 ///< [out] value of attribute
    )
{
    auto pfnGetParameter = xe_lib::lib.ddiTable.CommandList.pfnGetParameter;

#if _DEBUG
    if( nullptr == pfnGetParameter )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetParameter( hCommandList, parameter, value );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Resets all command list parameters to default state.
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
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListResetParameters(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    )
{
    auto pfnResetParameters = xe_lib::lib.ddiTable.CommandList.pfnResetParameters;

#if _DEBUG
    if( nullptr == pfnResetParameters )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnResetParameters( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reserve a section of contiguous command buffer space within the
///        command list.
/// 
/// @details
///     - The pointer returned is valid for both Host and device access.
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
///         + nullptr == ptr
///         + 0 for size
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListReserveSpace(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    size_t size,                                    ///< [in] size (in bytes) to reserve
    void** ptr                                      ///< [out] pointer to command buffer space reserved
    )
{
    auto pfnReserveSpace = xe_lib::lib.ddiTable.CommandList.pfnReserveSpace;

#if _DEBUG
    if( nullptr == pfnReserveSpace )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnReserveSpace( hCommandList, size, ptr );
}

} // extern "C"

namespace xe
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
    CommandList* __xecall
    CommandList::Create(
        Device* pDevice,                                ///< [in] pointer to the device object
        const desc_t* desc                              ///< [in] pointer to command list descriptor
        )
    {
        xe_command_list_handle_t hCommandList;

        auto result = static_cast<result_t>( ::xeCommandListCreate(
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const xe_command_list_desc_t*>( desc ),
            &hCommandList ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::Create" );

        CommandList* pCommandList = nullptr;

        try
        {
            pCommandList = new CommandList( reinterpret_cast<command_list_handle_t>( hCommandList ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pCommandList;
            pCommandList = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xe::CommandList::Create" );
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
    CommandList* __xecall
    CommandList::CreateImmediate(
        Device* pDevice,                                ///< [in] pointer to the device object
        const CommandQueue::desc_t* altdesc             ///< [in] pointer to command queue descriptor
        )
    {
        xe_command_list_handle_t hCommandList;

        auto result = static_cast<result_t>( ::xeCommandListCreateImmediate(
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const xe_command_queue_desc_t*>( altdesc ),
            &hCommandList ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::CreateImmediate" );

        CommandList* pCommandList = nullptr;

        try
        {
            pCommandList = new CommandList( reinterpret_cast<command_list_handle_t>( hCommandList ), pDevice, nullptr );
        }
        catch( std::bad_alloc& )
        {
            delete pCommandList;
            pCommandList = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xe::CommandList::CreateImmediate" );
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
    void __xecall
    CommandList::Destroy(
        CommandList* pCommandList                       ///< [in][release] pointer to command list object to destroy
        )
    {
        auto result = static_cast<result_t>( ::xeCommandListDestroy(
            reinterpret_cast<xe_command_list_handle_t>( pCommandList->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::Destroy" );

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
    void __xecall
    CommandList::Close(
        void
        )
    {
        auto result = static_cast<result_t>( ::xeCommandListClose(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::Close" );
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
    void __xecall
    CommandList::Reset(
        void
        )
    {
        auto result = static_cast<result_t>( ::xeCommandListReset(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::Reset" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sets a command list's parameter.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - cuCtxSetCacheConfig
    ///     - cuCtxSetLimit
    ///     - cuCtxSetSharedMemConfig
    /// 
    /// @throws result_t
    void __xecall
    CommandList::SetParameter(
        parameter_t parameter,                          ///< [in] parameter to change
        uint32_t value                                  ///< [in] value of attribute
        )
    {
        auto result = static_cast<result_t>( ::xeCommandListSetParameter(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ),
            static_cast<xe_command_list_parameter_t>( parameter ),
            value ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::SetParameter" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves a command list's parameter.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - cuCtxGetCacheConfig
    ///     - cuCtxGetLimit
    ///     - cuCtxGetSharedMemConfig
    ///     - cuCtxGetStreamPriorityRange
    /// 
    /// @returns
    ///     - uint32_t: value of attribute
    /// 
    /// @throws result_t
    uint32_t __xecall
    CommandList::GetParameter(
        parameter_t parameter                           ///< [in] parameter to retrieve
        )
    {
        uint32_t value;

        auto result = static_cast<result_t>( ::xeCommandListGetParameter(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ),
            static_cast<xe_command_list_parameter_t>( parameter ),
            &value ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::GetParameter" );

        return value;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Resets all command list parameters to default state.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    CommandList::ResetParameters(
        void
        )
    {
        auto result = static_cast<result_t>( ::xeCommandListResetParameters(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::ResetParameters" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reserve a section of contiguous command buffer space within the
    ///        command list.
    /// 
    /// @details
    ///     - The pointer returned is valid for both Host and device access.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - void*: pointer to command buffer space reserved
    /// 
    /// @throws result_t
    void* __xecall
    CommandList::ReserveSpace(
        size_t size                                     ///< [in] size (in bytes) to reserve
        )
    {
        void* ptr;

        auto result = static_cast<result_t>( ::xeCommandListReserveSpace(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ),
            size,
            &ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::ReserveSpace" );

        return ptr;
    }

} // namespace xe

#ifdef _DEBUG
namespace std
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::CommandList::desc_version_t to std::string
    string to_string( const xe::CommandList::desc_version_t val )
    {
        string str;

        switch( val )
        {
        case xe::CommandList::desc_version_t::CURRENT:
            str = "xe::CommandList::desc_version_t::CURRENT";
            break;

        default:
            str = "xe::CommandList::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::CommandList::flag_t to std::string
    string to_string( const xe::CommandList::flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );
        if( 0 == bits ) return string("{}");

        string str;
        
        if( static_cast<uint32_t>(xe::CommandList::flag_t::NONE) & bits )
            str += "xe::CommandList::flag_t::NONE | ";
        
        if( static_cast<uint32_t>(xe::CommandList::flag_t::COPY_ONLY) & bits )
            str += "xe::CommandList::flag_t::COPY_ONLY | ";
        
        if( static_cast<uint32_t>(xe::CommandList::flag_t::RELAXED_ORDERING) & bits )
            str += "xe::CommandList::flag_t::RELAXED_ORDERING | ";

        return "{ " + str.substr(0, str.size() - 3) + " }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::CommandList::parameter_t to std::string
    string to_string( const xe::CommandList::parameter_t val )
    {
        string str;

        switch( val )
        {
        case xe::CommandList::parameter_t::TBD:
            str = "xe::CommandList::parameter_t::TBD";
            break;

        default:
            str = "xe::CommandList::parameter_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::CommandList::memory_advice_t to std::string
    string to_string( const xe::CommandList::memory_advice_t val )
    {
        string str;

        switch( val )
        {
        case xe::CommandList::memory_advice_t::SET_READ_MOSTLY:
            str = "xe::CommandList::memory_advice_t::SET_READ_MOSTLY";
            break;

        case xe::CommandList::memory_advice_t::CLEAR_READ_MOSTLY:
            str = "xe::CommandList::memory_advice_t::CLEAR_READ_MOSTLY";
            break;

        case xe::CommandList::memory_advice_t::SET_PREFERRED_LOCATION:
            str = "xe::CommandList::memory_advice_t::SET_PREFERRED_LOCATION";
            break;

        case xe::CommandList::memory_advice_t::CLEAR_PREFERRED_LOCATION:
            str = "xe::CommandList::memory_advice_t::CLEAR_PREFERRED_LOCATION";
            break;

        case xe::CommandList::memory_advice_t::SET_ACCESSED_BY:
            str = "xe::CommandList::memory_advice_t::SET_ACCESSED_BY";
            break;

        case xe::CommandList::memory_advice_t::CLEAR_ACCESSED_BY:
            str = "xe::CommandList::memory_advice_t::CLEAR_ACCESSED_BY";
            break;

        case xe::CommandList::memory_advice_t::SET_NON_ATOMIC_MOSTLY:
            str = "xe::CommandList::memory_advice_t::SET_NON_ATOMIC_MOSTLY";
            break;

        case xe::CommandList::memory_advice_t::CLEAR_NON_ATOMIC_MOSTLY:
            str = "xe::CommandList::memory_advice_t::CLEAR_NON_ATOMIC_MOSTLY";
            break;

        case xe::CommandList::memory_advice_t::BIAS_CACHED:
            str = "xe::CommandList::memory_advice_t::BIAS_CACHED";
            break;

        case xe::CommandList::memory_advice_t::BIAS_UNCACHED:
            str = "xe::CommandList::memory_advice_t::BIAS_UNCACHED";
            break;

        default:
            str = "xe::CommandList::memory_advice_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::CommandList::desc_t to std::string
    string to_string( const xe::CommandList::desc_t val )
    {
        string str;
        
        str += "xe::CommandList::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "xe::CommandList::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::CommandList::copy_region_t to std::string
    string to_string( const xe::CommandList::copy_region_t val )
    {
        string str;
        
        str += "xe::CommandList::copy_region_t::originX : ";
        str += to_string(val.originX);
        str += "\n";
        
        str += "xe::CommandList::copy_region_t::originY : ";
        str += to_string(val.originY);
        str += "\n";
        
        str += "xe::CommandList::copy_region_t::width : ";
        str += to_string(val.width);
        str += "\n";
        
        str += "xe::CommandList::copy_region_t::height : ";
        str += to_string(val.height);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::CommandList::image_region_t to std::string
    string to_string( const xe::CommandList::image_region_t val )
    {
        string str;
        
        str += "xe::CommandList::image_region_t::originX : ";
        str += to_string(val.originX);
        str += "\n";
        
        str += "xe::CommandList::image_region_t::originY : ";
        str += to_string(val.originY);
        str += "\n";
        
        str += "xe::CommandList::image_region_t::originZ : ";
        str += to_string(val.originZ);
        str += "\n";
        
        str += "xe::CommandList::image_region_t::width : ";
        str += to_string(val.width);
        str += "\n";
        
        str += "xe::CommandList::image_region_t::height : ";
        str += to_string(val.height);
        str += "\n";
        
        str += "xe::CommandList::image_region_t::depth : ";
        str += to_string(val.depth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts xe::CommandList::thread_group_dimensions_t to std::string
    string to_string( const xe::CommandList::thread_group_dimensions_t val )
    {
        string str;
        
        str += "xe::CommandList::thread_group_dimensions_t::groupCountX : ";
        str += to_string(val.groupCountX);
        str += "\n";
        
        str += "xe::CommandList::thread_group_dimensions_t::groupCountY : ";
        str += to_string(val.groupCountY);
        str += "\n";
        
        str += "xe::CommandList::thread_group_dimensions_t::groupCountZ : ";
        str += to_string(val.groupCountZ);
        str += "\n";

        return str;
    }

} // namespace std
#endif // _DEBUG
