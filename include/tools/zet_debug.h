/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_debug.h
 *
 * @brief Intel 'One API' Level-Zero Tool APIs for Program Debug
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/debug.yml
 * @endcond
 *
 */
#ifndef _ZET_DEBUG_H
#define _ZET_DEBUG_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_ZET_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug session handle
typedef struct _zet_debug_session_handle_t *zet_debug_session_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug attach flags.
typedef enum _zet_debug_attach_flags_t
{
    ZET_DEBUG_ATTACH_NONE = 0,                      ///< No attach flags

} zet_debug_attach_flags_t;

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
    );

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
    );

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug wait flags.
typedef enum _zet_debug_wait_flags_t
{
    ZET_DEBUG_WAIT_NONE = 0,                        ///< No wait flags

} zet_debug_wait_flags_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DEBUG_TIMEOUT_INFINITE
/// @brief An infinite timeout.
#define ZET_DEBUG_TIMEOUT_INFINITE  0xffffffffffffffffull
#endif // ZET_DEBUG_TIMEOUT_INFINITE

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug event flags.
typedef enum _zet_debug_event_flags_t
{
    ZET_DEBUG_EVENT_FLAG_NONE = 0,                  ///< No event flags
    ZET_DEBUG_EVENT_FLAG_STOPPED = (1 << 0),        ///< The reporting thread stopped

} zet_debug_event_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug event types.
typedef enum _zet_debug_event_type_t
{
    ZET_DEBUG_EVENT_INVALID = 0,                    ///< The event is invalid
    ZET_DEBUG_EVENT_DETACHED,                       ///< The tool was detached
    ZET_DEBUG_EVENT_PROCESS_ENTRY,                  ///< The debuggee process created command queues on the device
    ZET_DEBUG_EVENT_PROCESS_EXIT,                   ///< The debuggee process destroyed all command queues on the device
    ZET_DEBUG_EVENT_MODULE_LOAD,                    ///< An in-memory module was loaded onto the device
    ZET_DEBUG_EVENT_EXCEPTION,                      ///< The thread stopped due to a device exception

} zet_debug_event_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug detach reason.
typedef enum _zet_debug_detach_reason_t
{
    ZET_DEBUG_DETACH_INVALID = 0,                   ///< The detach reason is not valid
    ZET_DEBUG_DETACH_HOST_EXIT,                     ///< The host process exited

} zet_debug_detach_reason_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DEBUG_THREAD_NONE
/// @brief No thread on the device.
#define ZET_DEBUG_THREAD_NONE  0xffffffffffffffffull
#endif // ZET_DEBUG_THREAD_NONE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DEBUG_THREAD_ALL
/// @brief All threads on the device.
#define ZET_DEBUG_THREAD_ALL  0xfffffffffffffffeull
#endif // ZET_DEBUG_THREAD_ALL

///////////////////////////////////////////////////////////////////////////////
/// @brief Event information for ::ZET_DEBUG_EVENT_DETACHED
typedef struct _zet_debug_event_info_detached_t
{
    uint8_t reason;                                 ///< The detach reason

} zet_debug_event_info_detached_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Event information for ::ZET_DEBUG_EVENT_MODULE_LOAD
typedef struct _zet_debug_event_info_module_t
{
    uint64_t moduleBegin;                           ///< The begin address of the in-memory module
    uint64_t moduleEnd;                             ///< The end address of the in-memory module
    uint64_t loadBegin;                             ///< The begin address of the loaded module on the device
    uint64_t loadEnd;                               ///< The end address of the loaded module on the device

} zet_debug_event_info_module_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Event information for ::ZET_DEBUG_EVENT_EXCEPTION
typedef struct _zet_debug_event_info_exception_t
{
    uint64_t code;                                  ///< The device-specific exception code
    uint64_t ip;                                    ///< The instruction pointer
    uint64_t sp;                                    ///< The stack pointer

} zet_debug_event_info_exception_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Event type specific information
typedef union _zet_debug_event_info_t
{
    zet_debug_event_info_detached_t detached;       ///< type == ::ZET_DEBUG_EVENT_DETACHED
    zet_debug_event_info_module_t module;           ///< type == ::ZET_DEBUG_EVENT_MODULE_LOAD
    zet_debug_event_info_exception_t exception;     ///< type == ::ZET_DEBUG_EVENT_EXCEPTION

} zet_debug_event_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief A debug event on the device.
typedef struct _zet_debug_event_t
{
    uint16_t size;                                  ///< The size of the event object in bytes
    uint8_t type;                                   ///< The event type
    uint64_t flags;                                 ///< A bit-vector of ::zet_debug_event_flags_t
    uint64_t thread;                                ///< The thread reporting the event
    zet_debug_event_info_t info;                    ///< Event type specific information

} zet_debug_event_t;

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Interrupt device threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDebug
///         + an invalid debug handle or thread identifier has been supplied
///         + the thread is already stopped or unavailable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetDebugInterrupt(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid                               ///< [in] the thread to inerrupt or ::ZET_DEBUG_THREAD_ALL
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Resume device threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDebug
///         + an invalid debug handle or thread identifier has been supplied
///         + the thread is already running or unavailable
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetDebugResume(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid                               ///< [in] the thread to resume or ::ZET_DEBUG_THREAD_ALL
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZET_DEBUG_H
