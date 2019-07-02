/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_common.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero API common types
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/common.yml
 * @endcond
 *
 */
#ifndef _XE_COMMON_HPP
#define _XE_COMMON_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

///////////////////////////////////////////////////////////////////////////////
#ifndef XE_MAKE_VERSION
/// @brief Generates generic 'One API' API versions
#define XE_MAKE_VERSION( _major, _minor )  (( _major << 16 )|( _minor & 0x0000ffff))
#endif // XE_MAKE_VERSION

///////////////////////////////////////////////////////////////////////////////
#ifndef XE_MAJOR_VERSION
/// @brief Extracts 'One API' API major version
#define XE_MAJOR_VERSION( _ver )  ( _ver >> 16 )
#endif // XE_MAJOR_VERSION

///////////////////////////////////////////////////////////////////////////////
#ifndef XE_MINOR_VERSION
/// @brief Extracts 'One API' API minor version
#define XE_MINOR_VERSION( _ver )  ( _ver & 0x0000ffff )
#endif // XE_MINOR_VERSION

///////////////////////////////////////////////////////////////////////////////
#ifndef __xecall
#if defined(_WIN32)
/// @brief Calling convention for all API functions
#define __xecall  __cdecl
#else
#define __xecall  
#endif // defined(_WIN32)
#endif // __xecall

///////////////////////////////////////////////////////////////////////////////
#ifndef __xedllexport
#if defined(_WIN32)
/// @brief Microsoft-specific dllexport storage-class attribute
#define __xedllexport  __declspec(dllexport)
#else
#define __xedllexport  
#endif // defined(_WIN32)
#endif // __xedllexport

///////////////////////////////////////////////////////////////////////////////
#ifndef XE_ENABLE_OCL_INTEROP
#if !defined(XE_ENABLE_OCL_INTEROP)
/// @brief Disable OpenCL interoperability functions if not explicitly defined
#define XE_ENABLE_OCL_INTEROP  0
#endif // !defined(XE_ENABLE_OCL_INTEROP)
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
#ifndef XE_BIT
/// @brief Generic macro for enumerator bit masks
#define XE_BIT( _i )  ( 1 << _i )
#endif // XE_BIT

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief compiler-independent type
    using bool_t = uint8_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's device group object
    class DeviceGroup;
    struct _device_group_handle_t;
    using device_group_handle_t = _device_group_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's device object
    class Device;
    struct _device_handle_t;
    using device_handle_t = _device_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's command queue object
    class CommandQueue;
    struct _command_queue_handle_t;
    using command_queue_handle_t = _command_queue_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's command list object
    class CommandList;
    struct _command_list_handle_t;
    using command_list_handle_t = _command_list_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's fence object
    class Fence;
    struct _fence_handle_t;
    using fence_handle_t = _fence_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's event pool object
    class EventPool;
    struct _event_pool_handle_t;
    using event_pool_handle_t = _event_pool_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's event object
    class Event;
    struct _event_handle_t;
    using event_handle_t = _event_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's image object
    class Image;
    struct _image_handle_t;
    using image_handle_t = _image_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's module object
    class Module;
    struct _module_handle_t;
    using module_handle_t = _module_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of module's build log object
    class ModuleBuildLog;
    struct _module_build_log_handle_t;
    using module_build_log_handle_t = _module_build_log_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's function object
    class Function;
    struct _function_handle_t;
    using function_handle_t = _function_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's sampler object
    class Sampler;
    struct _sampler_handle_t;
    using sampler_handle_t = _sampler_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief IPC handle to a memory allocation
    struct _ipc_mem_handle_t;
    using ipc_mem_handle_t = _ipc_mem_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief IPC handle to a event pool allocation
    struct _ipc_event_pool_handle_t;
    using ipc_event_pool_handle_t = _ipc_event_pool_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Defines Return/Error codes
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **CUresult**
    enum class result_t
    {
        SUCCESS = 0,                                    ///< success
        NOT_READY = 1,                                  ///< synchronization primitive not signaled
        ERROR_UNINITIALIZED,                            ///< driver is not initialized
        ERROR_DEVICE_LOST,                              ///< device hung, reset, was removed, or driver update occurred
        ERROR_UNSUPPORTED,                              ///< device does not support feature requested
        ERROR_INVALID_ARGUMENT,                         ///< invalid argument provided
        ERROR_OUT_OF_HOST_MEMORY,                       ///< insufficient host memory to satisfy call
        ERROR_OUT_OF_DEVICE_MEMORY,                     ///< insufficient device memory to satisfy call
        ERROR_MODULE_BUILD_FAILURE,                     ///< error in building module
        XE_ERROR_ACCESS_DENIED,                         ///< access denied
        ERROR_UNKNOWN = 0x7fffffff,                     ///< unknown or internal error

    };

} // namespace xe

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts result_t to std::string
    std::string to_string( const result_t val );

} // namespace xe

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    class exception_t : public std::exception
    {
    protected:
        static std::string formatted( const result_t, const char*, const char*, const char* );

        const std::string _msg;
        const result_t _result;

    public:
        exception_t() = delete;

        exception_t( const result_t result, const char* file, const char* line, const char* func )
            : std::exception(),
            _msg( formatted(result, file, line, func) ),
            _result(result)
        {
        }

        const char* what() const noexcept { return _msg.c_str(); }
        result_t value() const noexcept { return _result; }
    };

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_COMMON_HPP
