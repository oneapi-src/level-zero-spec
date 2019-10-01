/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_debug.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for Program Debug
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/debug.yml
 * @endcond
 *
 */
#include "zet_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Attach to a device.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == hDebug
///         + an invalid device handle has been supplied
///         + an invalid process identifier has been supplied
///         + an invalid flag has been supplied
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + attaching to this device is not supported
///     - ::ZE_RESULT_ERROR_INSUFFICENT_PERMISSIONS
///         + caller is not authorized to debug that process
///     - ::ZE_RESULT_ERROR_DEVICE_ACCESS
///         + a debugger is already attached
ze_result_t __zecall
zetDebugAttach(
    zet_device_handle_t hDevice,                    ///< [in] device handle
    int pid,                                        ///< [in] host process identifier
    uint64_t flags,                                 ///< [in] a bit-vector of ::zet_debug_attach_flags_t
    zet_debug_session_handle_t* hDebug              ///< [out] debug session handle
    )
{
    auto pfnAttach = zet_lib::context.ddiTable.Debug.pfnAttach;
    if( nullptr == pfnAttach )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnAttach( hDevice, pid, flags, hDebug );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Close a debug session.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDebug
///         + an invalid debug handle has been supplied
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetDebugDetach(
    zet_debug_session_handle_t hDebug               ///< [in][release] debug session handle
    )
{
    auto pfnDetach = zet_lib::context.ddiTable.Debug.pfnDetach;
    if( nullptr == pfnDetach )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnDetach( hDebug );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Query the number of device threads for a debug session.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDebug
///         + an invalid debug handle has been supplied
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetDebugGetNumThreads(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t numThreads                             ///< [out] the maximal number of threads
    )
{
    auto pfnGetNumThreads = zet_lib::context.ddiTable.Debug.pfnGetNumThreads;
    if( nullptr == pfnGetNumThreads )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetNumThreads( hDebug, numThreads );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Wait for a debug event on the device.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDebug
///         + nullptr == size
///         + an invalid debug handle or size pointer has been supplied
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetDebugWaitForEvent(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t timeout,                               ///< [in] timeout in milliseconds (UINT64_MAX for infinite)
    uint64_t flags,                                 ///< [in] a bit-vector of ::zet_debug_wait_flags_t
    size_t* size                                    ///< [out] size of the topmost event in bytes
    )
{
    auto pfnWaitForEvent = zet_lib::context.ddiTable.Debug.pfnWaitForEvent;
    if( nullptr == pfnWaitForEvent )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnWaitForEvent( hDebug, timeout, flags, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Read the topmost debug event.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDebug
///         + nullptr == buffer
///         + an invalid debug handle or buffer pointer has been supplied
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///         + the output buffer is too small to hold the event
///     - ::ZE_RESULT_NOT_READY
///         + there is no event
ze_result_t __zecall
zetDebugReadEvent(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    size_t size,                                    ///< [in] the size of the buffer in bytes
    void* buffer                                    ///< [in,out] a buffer to hold the event data
    )
{
    auto pfnReadEvent = zet_lib::context.ddiTable.Debug.pfnReadEvent;
    if( nullptr == pfnReadEvent )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnReadEvent( hDebug, size, buffer );
}

} // extern "C"

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    Debug::Debug( 
        debug_session_handle_t* hDebug                  ///< [in] debug session handle
        ) :
        m_hDebug( hDebug )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Attach to a device.
    /// 
    /// @returns
    ///     - debug_session_handle_t: debug session handle
    /// 
    /// @throws result_t
    debug_session_handle_t __zecall
    Debug::Attach(
        Device* pDevice,                                ///< [in] device handle
        int pid,                                        ///< [in] host process identifier
        uint64_t flags                                  ///< [in] a bit-vector of ::zet_debug_attach_flags_t
        )
    {
        zet_debug_session_handle_t hDebug;

        auto result = static_cast<result_t>( ::zetDebugAttach(
            reinterpret_cast<zet_device_handle_t>( pDevice->getHandle() ),
            pid,
            flags,
            &hDebug ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Debug::Attach" );

        return reinterpret_cast<debug_session_handle_t>( hDebug );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Close a debug session.
    /// 
    /// @throws result_t
    void __zecall
    Debug::Detach(
        void
        )
    {
        auto result = static_cast<result_t>( ::zetDebugDetach(
            reinterpret_cast<zet_debug_session_handle_t>( pDebug ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Debug::Detach" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Query the number of device threads for a debug session.
    /// 
    /// @returns
    ///     - uint64_t: the maximal number of threads
    /// 
    /// @throws result_t
    uint64_t __zecall
    Debug::GetNumThreads(
        void
        )
    {
        uint64_t numThreads;

        auto result = static_cast<result_t>( ::zetDebugGetNumThreads(
            reinterpret_cast<zet_debug_session_handle_t>( pDebug ),
            &numThreads ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Debug::GetNumThreads" );

        return numThreads;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Wait for a debug event on the device.
    /// 
    /// @returns
    ///     - size_t: size of the topmost event in bytes
    /// 
    /// @throws result_t
    size_t __zecall
    Debug::WaitForEvent(
        uint64_t timeout,                               ///< [in] timeout in milliseconds (UINT64_MAX for infinite)
        uint64_t flags                                  ///< [in] a bit-vector of ::zet_debug_wait_flags_t
        )
    {
        size_t size;

        auto result = static_cast<result_t>( ::zetDebugWaitForEvent(
            reinterpret_cast<zet_debug_session_handle_t>( pDebug ),
            timeout,
            flags,
            &size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Debug::WaitForEvent" );

        return size;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Read the topmost debug event.
    /// 
    /// @returns
    ///     - ze::bool_t:'0' when ZE::RESULT_NOT_READY
    /// @throws result_t
    ze::bool_t __zecall
    Debug::ReadEvent(
        size_t size,                                    ///< [in] the size of the buffer in bytes
        void* buffer                                    ///< [in,out] a buffer to hold the event data
        )
    {
        auto result = static_cast<result_t>( ::zetDebugReadEvent(
            reinterpret_cast<zet_debug_session_handle_t>( pDebug ),
            size,
            buffer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Debug::ReadEvent" );
    }

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::attach_flags_t to std::string
    std::string to_string( const Debug::attach_flags_t val )
    {
        std::string str;

        switch( val )
        {
        case Debug::attach_flags_t::DEBUG_ATTACH_NONE:
            str = "Debug::attach_flags_t::DEBUG_ATTACH_NONE";
            break;

        default:
            str = "Debug::attach_flags_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::wait_flags_t to std::string
    std::string to_string( const Debug::wait_flags_t val )
    {
        std::string str;

        switch( val )
        {
        case Debug::wait_flags_t::DEBUG_WAIT_NONE:
            str = "Debug::wait_flags_t::DEBUG_WAIT_NONE";
            break;

        default:
            str = "Debug::wait_flags_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_flags_t to std::string
    std::string to_string( const Debug::event_flags_t val )
    {
        std::string str;

        switch( val )
        {
        case Debug::event_flags_t::DEBUG_EVENT_FLAG_NONE:
            str = "Debug::event_flags_t::DEBUG_EVENT_FLAG_NONE";
            break;

        case Debug::event_flags_t::DEBUG_EVENT_FLAG_STOPPED:
            str = "Debug::event_flags_t::DEBUG_EVENT_FLAG_STOPPED";
            break;

        default:
            str = "Debug::event_flags_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_type_t to std::string
    std::string to_string( const Debug::event_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Debug::event_type_t::DEBUG_EVENT_INVALID:
            str = "Debug::event_type_t::DEBUG_EVENT_INVALID";
            break;

        case Debug::event_type_t::DEBUG_EVENT_DETACHED:
            str = "Debug::event_type_t::DEBUG_EVENT_DETACHED";
            break;

        case Debug::event_type_t::DEBUG_EVENT_PROCESS_ENTRY:
            str = "Debug::event_type_t::DEBUG_EVENT_PROCESS_ENTRY";
            break;

        case Debug::event_type_t::DEBUG_EVENT_PROCESS_EXIT:
            str = "Debug::event_type_t::DEBUG_EVENT_PROCESS_EXIT";
            break;

        case Debug::event_type_t::DEBUG_EVENT_MODULE_LOAD:
            str = "Debug::event_type_t::DEBUG_EVENT_MODULE_LOAD";
            break;

        case Debug::event_type_t::DEBUG_EVENT_EXCEPTION:
            str = "Debug::event_type_t::DEBUG_EVENT_EXCEPTION";
            break;

        default:
            str = "Debug::event_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::detach_reason_t to std::string
    std::string to_string( const Debug::detach_reason_t val )
    {
        std::string str;

        switch( val )
        {
        case Debug::detach_reason_t::DEBUG_DETACH_INVALID:
            str = "Debug::detach_reason_t::DEBUG_DETACH_INVALID";
            break;

        case Debug::detach_reason_t::DEBUG_DETACH_HOST_EXIT:
            str = "Debug::detach_reason_t::DEBUG_DETACH_HOST_EXIT";
            break;

        default:
            str = "Debug::detach_reason_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_detached_t to std::string
    std::string to_string( const Debug::event_info_detached_t val )
    {
        std::string str;
        
        str += "Debug::event_info_detached_t::reason : ";
        str += std::to_string(val.reason);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_module_t to std::string
    std::string to_string( const Debug::event_info_module_t val )
    {
        std::string str;
        
        str += "Debug::event_info_module_t::moduleBegin : ";
        str += std::to_string(val.moduleBegin);
        str += "\n";
        
        str += "Debug::event_info_module_t::moduleEnd : ";
        str += std::to_string(val.moduleEnd);
        str += "\n";
        
        str += "Debug::event_info_module_t::loadBegin : ";
        str += std::to_string(val.loadBegin);
        str += "\n";
        
        str += "Debug::event_info_module_t::loadEnd : ";
        str += std::to_string(val.loadEnd);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_exception_t to std::string
    std::string to_string( const Debug::event_info_exception_t val )
    {
        std::string str;
        
        str += "Debug::event_info_exception_t::code : ";
        str += std::to_string(val.code);
        str += "\n";
        
        str += "Debug::event_info_exception_t::ip : ";
        str += std::to_string(val.ip);
        str += "\n";
        
        str += "Debug::event_info_exception_t::sp : ";
        str += std::to_string(val.sp);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_t to std::string
    std::string to_string( const Debug::event_info_t val )
    {
        std::string str;
        
        str += "Debug::event_info_t::detached : ";
        str += to_string(val.detached);
        str += "\n";
        
        str += "Debug::event_info_t::module : ";
        str += to_string(val.module);
        str += "\n";
        
        str += "Debug::event_info_t::exception : ";
        str += to_string(val.exception);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_t to std::string
    std::string to_string( const Debug::event_t val )
    {
        std::string str;
        
        str += "Debug::event_t::size : ";
        str += std::to_string(val.size);
        str += "\n";
        
        str += "Debug::event_t::type : ";
        str += std::to_string(val.type);
        str += "\n";
        
        str += "Debug::event_t::flags : ";
        str += std::to_string(val.flags);
        str += "\n";
        
        str += "Debug::event_t::thread : ";
        str += std::to_string(val.thread);
        str += "\n";
        
        str += "Debug::event_t::info : ";
        str += to_string(val.info);
        str += "\n";

        return str;
    }

} // namespace zet
