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
#include "xe_api.hpp"
#include "xe_ddi.h"
#include "xe_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command list on the device for submitting commands to any
///        command queue.
/// 
/// @details
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
    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command list on the device with an implicit command queue
///        for immediate submission of commands.
/// 
/// @details
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
///         + nullptr == desc
///         + nullptr == phCommandList
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_COMMAND_QUEUE_DESC_VERSION_CURRENT < desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeCommandListCreateImmediate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
    xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    )
{
    return XE_RESULT_SUCCESS;
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
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to destroy
    )
{
    return XE_RESULT_SUCCESS;
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
    return XE_RESULT_SUCCESS;
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
    return XE_RESULT_SUCCESS;
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
    return XE_RESULT_SUCCESS;
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
    return XE_RESULT_SUCCESS;
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
    return XE_RESULT_SUCCESS;
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
    return XE_RESULT_SUCCESS;
}

} // extern "C"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    CommandList::CommandList( 
        Device* pDevice,                                ///< [in] pointer to parent object
        const desc_t& desc                              ///< [in] descriptor of the command list object
        ) :
        m_pDevice( pDevice ),
        m_desc( desc )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a command list on the device for submitting commands to any
    ///        command queue.
    /// 
    /// @details
    ///     - The command list is created in the 'open' state.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - CommandList: pointer to handle of command list object created
    /// 
    /// @throws result_t
    CommandList* __xecall
    CommandList::Create(
        Device* pDevice,                                ///< [in] pointer to the device object
        const desc_t* desc                              ///< [in] pointer to command list descriptor
        )
    {
        // auto result = ::xeCommandListCreate( handle, pDevice, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::Create");

        return (CommandList*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a command list on the device with an implicit command queue
    ///        for immediate submission of commands.
    /// 
    /// @details
    ///     - The command list is created in the 'open' state and never needs to be
    ///       closed.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - CommandList: pointer to handle of command list object created
    /// 
    /// @throws result_t
    CommandList* __xecall
    CommandList::CreateImmediate(
        Device* pDevice,                                ///< [in] pointer to the device object
        const CommandQueue::desc_t* desc                ///< [in] pointer to command queue descriptor
        )
    {
        // auto result = ::xeCommandListCreateImmediate( handle, pDevice, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::CreateImmediate");

        return (CommandList*)0;
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
        CommandList* pCommandList                       ///< [in] pointer to command list object to destroy
        )
    {
        // auto result = ::xeCommandListDestroy( handle, pCommandList );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::Destroy");
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
        // auto result = ::xeCommandListClose( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::Close");
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
        // auto result = ::xeCommandListReset( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::Reset");
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
        // auto result = ::xeCommandListSetParameter( handle, parameter, value );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::SetParameter");
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
        // auto result = ::xeCommandListGetParameter( handle, parameter );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::GetParameter");

        return uint32_t{};
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
        // auto result = ::xeCommandListResetParameters( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::ResetParameters");
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
        // auto result = ::xeCommandListReserveSpace( handle, size );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::ReserveSpace");

        return (void*)0;
    }

} // namespace xe

#ifdef _DEBUG
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::desc_version_t to std::string
    std::string to_string( xe::CommandList::desc_version_t val )
    {
        switch( val )
        {
        case xe::CommandList::desc_version_t::CURRENT:
            return std::string("xe::CommandList::desc_version_t::CURRENT");
        };
        return std::string("xe::CommandList::desc_version_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::flag_t to std::string
    std::string to_string( xe::CommandList::flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );
        if( 0 == bits ) return std::string("{}");
        std::string str;
        if( static_cast<uint32_t>(xe::CommandList::flag_t::NONE) & bits )
            str += "xe::CommandList::flag_t::NONE | ";
        if( static_cast<uint32_t>(xe::CommandList::flag_t::COPY_ONLY) & bits )
            str += "xe::CommandList::flag_t::COPY_ONLY | ";
        if( static_cast<uint32_t>(xe::CommandList::flag_t::RELAXED_ORDERING) & bits )
            str += "xe::CommandList::flag_t::RELAXED_ORDERING | ";
        return "{ " + str.substr(0, str.size() - 3) + " }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::parameter_t to std::string
    std::string to_string( xe::CommandList::parameter_t val )
    {
        switch( val )
        {
        case xe::CommandList::parameter_t::TBD:
            return std::string("xe::CommandList::parameter_t::TBD");
        };
        return std::string("xe::CommandList::parameter_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::memory_advice_t to std::string
    std::string to_string( xe::CommandList::memory_advice_t val )
    {
        switch( val )
        {
        case xe::CommandList::memory_advice_t::SET_READ_MOSTLY:
            return std::string("xe::CommandList::memory_advice_t::SET_READ_MOSTLY");
        case xe::CommandList::memory_advice_t::CLEAR_READ_MOSTLY:
            return std::string("xe::CommandList::memory_advice_t::CLEAR_READ_MOSTLY");
        case xe::CommandList::memory_advice_t::SET_PREFERRED_LOCATION:
            return std::string("xe::CommandList::memory_advice_t::SET_PREFERRED_LOCATION");
        case xe::CommandList::memory_advice_t::CLEAR_PREFERRED_LOCATION:
            return std::string("xe::CommandList::memory_advice_t::CLEAR_PREFERRED_LOCATION");
        case xe::CommandList::memory_advice_t::SET_ACCESSED_BY:
            return std::string("xe::CommandList::memory_advice_t::SET_ACCESSED_BY");
        case xe::CommandList::memory_advice_t::CLEAR_ACCESSED_BY:
            return std::string("xe::CommandList::memory_advice_t::CLEAR_ACCESSED_BY");
        case xe::CommandList::memory_advice_t::SET_NON_ATOMIC_MOSTLY:
            return std::string("xe::CommandList::memory_advice_t::SET_NON_ATOMIC_MOSTLY");
        case xe::CommandList::memory_advice_t::CLEAR_NON_ATOMIC_MOSTLY:
            return std::string("xe::CommandList::memory_advice_t::CLEAR_NON_ATOMIC_MOSTLY");
        case xe::CommandList::memory_advice_t::BIAS_CACHED:
            return std::string("xe::CommandList::memory_advice_t::BIAS_CACHED");
        case xe::CommandList::memory_advice_t::BIAS_UNCACHED:
            return std::string("xe::CommandList::memory_advice_t::BIAS_UNCACHED");
        };
        return std::string("xe::CommandList::memory_advice_t::?");
    }


#endif // _DEBUG
