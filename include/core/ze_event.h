/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_event.h
 *
 * @brief Intel 'One API' Level-Zero APIs for Event
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/event.yml
 * @endcond
 *
 */
#ifndef _ZE_EVENT_H
#define _ZE_EVENT_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_ZE_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_event_pool_desc_t
typedef enum _ze_event_pool_desc_version_t
{
    ZE_EVENT_POOL_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),   ///< version 1.0

} ze_event_pool_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported event pool creation flags
typedef enum _ze_event_pool_flag_t
{
    ZE_EVENT_POOL_FLAG_DEFAULT = 0,                 ///< signals and waits visible to the entire device and peer devices
    ZE_EVENT_POOL_FLAG_HOST_VISIBLE = ZE_BIT(0),    ///< signals and waits are also visible to host
    ZE_EVENT_POOL_FLAG_IPC = ZE_BIT(1),             ///< signals and waits may be shared across processes

} ze_event_pool_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Event pool descriptor
typedef struct _ze_event_pool_desc_t
{
    ze_event_pool_desc_version_t version;           ///< [in] ::ZE_EVENT_POOL_DESC_VERSION_CURRENT
    ze_event_pool_flag_t flags;                     ///< [in] creation flags
    uint32_t count;                                 ///< [in] number of events within the pool

} ze_event_pool_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a pool for a set of event(s) for the driver
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == desc
///         + nullptr == phEventPool
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + ::ZE_EVENT_POOL_DESC_VERSION_CURRENT < desc->version
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
ze_result_t __zecall
zeEventPoolCreate(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const ze_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
    uint32_t numDevices,                            ///< [in] number of device handles
    ze_device_handle_t* phDevices,                  ///< [in][optional][range(0, numDevices)] array of device handles which
                                                    ///< have visibility to the event pool.
                                                    ///< if nullptr, then event pool is visible to all devices supported by the
                                                    ///< driver instance.
    ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes an event pool object.
/// 
/// @details
///     - The application is responsible for destroying all event handles
///       created from the pool before destroying the pool itself
///     - The application is responsible for making sure the device is not
///       currently referencing the any event within the pool before it is
///       deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this event pool
///     - The application may **not** call this function from simultaneous
///       threads with the same event pool handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEventPool
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeEventPoolDestroy(
    ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_event_desc_t
typedef enum _ze_event_desc_version_t
{
    ZE_EVENT_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),///< version 1.0

} ze_event_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported event scope flags
typedef enum _ze_event_scope_flag_t
{
    ZE_EVENT_SCOPE_FLAG_NONE = 0,                   ///< execution synchronization only; no cache hierarchies are flushed or
                                                    ///< invalidated
    ZE_EVENT_SCOPE_FLAG_SUBDEVICE = ZE_BIT(0),      ///< cache hierarchies are flushed or invalidated sufficient for local
                                                    ///< sub-device access
    ZE_EVENT_SCOPE_FLAG_DEVICE = ZE_BIT(1),         ///< cache hierarchies are flushed or invalidated sufficient for global
                                                    ///< device access and peer device access
    ZE_EVENT_SCOPE_FLAG_HOST = ZE_BIT(2),           ///< cache hierarchies are flushed or invalidated sufficient for device and
                                                    ///< host access

} ze_event_scope_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Event descriptor
typedef struct _ze_event_desc_t
{
    ze_event_desc_version_t version;                ///< [in] ::ZE_EVENT_DESC_VERSION_CURRENT
    uint32_t index;                                 ///< [in] index of the event within the pool; must be less-than the count
                                                    ///< specified during pool creation
    ze_event_scope_flag_t signal;                   ///< [in] defines the scope of relevant cache hierarchies to flush on a
                                                    ///< signal action before the event is triggered
    ze_event_scope_flag_t wait;                     ///< [in] defines the scope of relevant cache hierarchies to invalidate on
                                                    ///< a wait action after the event is complete

} ze_event_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an event on the device.
/// 
/// @details
///     - Multiple events cannot be created using the same location within the
///       same pool.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clCreateUserEvent**
///     - vkCreateEvent
///     - cuEventCreate
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEventPool
///         + nullptr == desc
///         + nullptr == phEvent
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + ::ZE_EVENT_DESC_VERSION_CURRENT < desc->version
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
ze_result_t __zecall
zeEventCreate(
    ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
    const ze_event_desc_t* desc,                    ///< [in] pointer to event descriptor
    ze_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes an event object.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the event before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this event
///     - The application may **not** call this function from simultaneous
///       threads with the same event handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clReleaseEvent**
///     - vkDestroyEvent
///     - cuEventDestroy
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEvent
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeEventDestroy(
    ze_event_handle_t hEvent                        ///< [in][release] handle of event object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets an IPC event pool handle for the specified event handle that can
///        be shared with another process.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @remarks
///   _Analogues_
///     - **cuIpcGetEventHandle**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEventPool
///         + nullptr == phIpc
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeEventPoolGetIpcHandle(
    ze_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
    ze_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Opens an IPC event pool handle to retrieve an event pool handle from
///        another process.
/// 
/// @details
///     - The event handle in this process should not be freed with
///       ::zeEventPoolDestroy, but rather with ::zeEventPoolCloseIpcHandle.
///     - The application may call this function from simultaneous threads.
/// 
/// @remarks
///   _Analogues_
///     - **cuIpcOpenMemHandle**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDriver
///         + nullptr == phEventPool
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeEventPoolOpenIpcHandle(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver to associate with the IPC event pool handle
    ze_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event handle
    ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes an IPC event handle in the current process.
/// 
/// @details
///     - Closes an IPC event handle by destroying events that were opened in
///       this process using ::zeEventPoolOpenIpcHandle.
///     - The application may **not** call this function from simultaneous
///       threads with the same event pool handle.
/// 
/// @remarks
///   _Analogues_
///     - **cuIpcCloseMemHandle**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEventPool
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeEventPoolCloseIpcHandle(
    ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends a signal of the event from the device into a command list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clSetUserEventStatus**
///     - cuEventRecord
///     - vkCmdSetEvent
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hEvent
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeCommandListAppendSignalEvent(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_event_handle_t hEvent                        ///< [in] handle of the event
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends wait on event(s) on the device into a command list.
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
///         + nullptr == phEvents
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeCommandListAppendWaitOnEvents(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
    ze_event_handle_t* phEvents                     ///< [in][range(0, numEvents)] handle of the events to wait on before
                                                    ///< continuing
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Signals a event from host.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clSetUserEventStatus
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEvent
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeEventHostSignal(
    ze_event_handle_t hEvent                        ///< [in] handle of the event
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief The current host thread waits on an event to be signalled.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clWaitForEvents
///     - cuEventSynchronize
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEvent
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///     - ::ZE_RESULT_NOT_READY
///         + timeout expired
ze_result_t __zecall
zeEventHostSynchronize(
    ze_event_handle_t hEvent,                       ///< [in] handle of the event
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                    ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                    ///< if zero, then operates exactly like ::zeEventQueryStatus;
                                                    ///< if UINT32_MAX, then function will not return until complete or device
                                                    ///< is lost.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries an event object's status.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clGetEventInfo**
///     - vkGetEventStatus
///     - cuEventQuery
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEvent
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///     - ::ZE_RESULT_NOT_READY
///         + not signaled
ze_result_t __zecall
zeEventQueryStatus(
    ze_event_handle_t hEvent                        ///< [in] handle of the event
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset an event back to not signaled state
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - vkResetEvent
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hEvent
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeCommandListAppendEventReset(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_event_handle_t hEvent                        ///< [in] handle of the event
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset an event back to not signaled state
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - vkResetEvent
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEvent
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeEventHostReset(
    ze_event_handle_t hEvent                        ///< [in] handle of the event
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZE_EVENT_H
