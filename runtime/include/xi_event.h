/**************************************************************************//**
*
* INTEL CONFIDENTIAL
* Copyright 2019
* Intel Corporation All Rights Reserved.
*
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
*
* @file xi_event.h
*
* @brief Intel Xi Runtime APIs for Event
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/event.yml
* @endcond
*
******************************************************************************/
#ifndef _XI_EVENT_H
#define _XI_EVENT_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xi_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xi_event_desc_t
#define XI_EVENT_DESC_VERSION  XI_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported event creation flags
typedef enum _xi_event_flags_t
{
    XI_EVENT_FLAG_HOST_TO_DEVICE = XI_BIT(0),       ///< signals from host, waits on device
    XI_EVENT_FLAG_DEVICE_TO_HOST = XI_BIT(1),       ///< signals from device, waits on host
    XI_EVENT_FLAG_DEVICE_TO_DEVICE = XI_BIT(2),     ///< signals from device, waits on another device

} xi_event_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Event descriptor
typedef struct _xi_event_desc_t
{
    uint32_t version;                               ///< [in] ::XI_EVENT_DESC_VERSION
    xi_event_flags_t flags;                         ///< [in] creation flags

} xi_event_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an event object.
/// @remarks
///   _Analogues_
///     - **cudaEventCreate**
///     - clCreateUserEvent
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hDevice
///     + nullptr for desc
///     + nullptr for phEvent
/// - ::XI_RESULT_ERROR_OUT_OF_HOST_MEMORY
/// - ::XI_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xi_result_t __xicall
  xiEventCreate(
    xi_device_handle_t hDevice,                     ///< [in] handle of the device
    const xi_event_desc_t* desc,                    ///< [in] pointer to event descriptor
    xi_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an event object from existing memory.
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hDevice
///     + nullptr for desc
///     + nullptr for ptr
///     + nullptr for phEvent
/// - ::XI_RESULT_ERROR_OUT_OF_HOST_MEMORY
xi_result_t __xicall
  xiEventPlacement(
    xi_device_handle_t hDevice,                     ///< [in] handle of the device
    const xi_event_desc_t* desc,                    ///< [in] pointer to event descriptor
    void* ptr,                                      ///< [in] pointer to the device pointer where the event should be placed
    xi_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes an event object.
/// @remarks
///   _Analogues_
///     - **cudaEventDestroy**
///     - clReleaseEvent
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hEvent
xi_result_t __xicall
  xiEventDestroy(
    xi_event_handle_t hEvent                        ///< [in] handle of event object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes a signal of the event from the device into a command list.
/// @remarks
///   _Analogues_
///     - **cudaEventRecord**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hCommandList
///     + invalid handle for hEvent
///     + event creation flag did not set ::XI_EVENT_FLAG_DEVICE_TO_HOST or ::XI_EVENT_FLAG_DEVICE_TO_DEVICE
///     + event is in signaled state
///     + event is used by another command list
xi_result_t __xicall
  xiCommandListEncodeSignalEvent(
    xi_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xi_event_handle_t hEvent                        ///< [in] handle of the event
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes a wait on event from a host signal into a command list.
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hCommandList
///     + invalid handle for hEvent
///     + event creation flag did not set ::XI_EVENT_FLAG_HOST_TO_DEVICE or ::XI_EVENT_FLAG_DEVICE_TO_DEVICE
///     + event is used by another command list
xi_result_t __xicall
  xiCommandListEncodeWaitOnEvent(
    xi_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xi_event_handle_t hEvent                        ///< [in] handle of the event
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes signals of multiple event from the device into a command list.
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hCommandList
///     + nullptr for phEvents
///     + invalid handle in phEvents
///     + any event creation flag did not set ::XI_EVENT_FLAG_DEVICE_TO_HOST or ::XI_EVENT_FLAG_DEVICE_TO_DEVICE
///     + any event is in signaled state
///     + any event is used by another command list
xi_result_t __xicall
  xiCommandListEncodeSignalMultipleEvents(
    xi_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numEvents,                             ///< [in] number of events pointed to by phEvents
    xi_event_handle_t* phEvents                     ///< [in] pointer to array of handles of the events
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes waits on multiple event from a host signal into a command
///        list.
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hCommandList
///     + nullptr for phEvents
///     + invalid handle in phEvents
///     + any event creation flag did not set ::XI_EVENT_FLAG_HOST_TO_DEVICE or ::XI_EVENT_FLAG_DEVICE_TO_DEVICE
///     + any event is used by another command list
xi_result_t __xicall
  xiCommandListEncodeWaitOnMultipleEvents(
    xi_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numEvents,                             ///< [in] number of events pointed to by phEvents
    xi_event_handle_t* phEvents                     ///< [in] pointer to array of handles of the events
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Signals a event from host.
/// @remarks
///   _Analogues_
///     - clSetUserEventStatus
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hEvent
///     + event creation flag did not set ::XI_EVENT_FLAG_HOST_TO_DEVICE or ::XI_EVENT_FLAG_DEVICE_TO_DEVICE
///     + event is in signaled state
xi_result_t __xicall
  xiSignalEvent(
    xi_event_handle_t hEvent                        ///< [in] handle of the event
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief The current host thread waits on an event from a device signal.
/// @remarks
///   _Analogues_
///     - **cudaEventSynchronize**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hEvent
///     + event creation flag did not set ::XI_EVENT_FLAG_DEVICE_TO_HOST or ::XI_EVENT_FLAG_DEVICE_TO_DEVICE
xi_result_t __xicall
  xiWaitOnEvent(
    xi_event_handle_t hEvent                        ///< [in] handle of the event
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Signals multiple events from host. @todo move to runtime?
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + nullptr for phEvents
///     + invalid handle in phEvents
///     + any event creation flag did not set ::XI_EVENT_FLAG_HOST_TO_DEVICE or ::XI_EVENT_FLAG_DEVICE_TO_DEVICE
///     + any event is in signaled state
xi_result_t __xicall
  xiSignalMultipleEvents(
    uint32_t numEvents,                             ///< [in] number of events pointed to by phEvents
    xi_event_handle_t* phEvents                     ///< [in] pointer to array of handles of the events
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief The current host thread waits on multiple events from a device signal.
/// @remarks
///   _Analogues_
///     - clWaitForEvents
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + nullptr for phEvents
///     + invalid handle in phEvents
///     + any event creation flag did not set ::XI_EVENT_FLAG_DEVICE_TO_HOST or ::XI_EVENT_FLAG_DEVICE_TO_DEVICE
xi_result_t __xicall
  xiWaitOnMultipleEvents(
    uint32_t numEvents,                             ///< [in] number of events pointed to by phEvents
    xi_event_handle_t* phEvents                     ///< [in] pointer to array of handles of the events
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries an event object's status.
/// @remarks
///   _Analogues_
///     - **cudaEventQuery**
///     - clGetEventInfo
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_NOT_READY
///     + not signaled
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hEvent
xi_result_t __xicall
  xiEventQueryStatus(
    xi_event_handle_t hEvent                        ///< [in] handle of the event
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries the elapsed time between two signaled events.
/// @remarks
///   _Analogues_
///     - **cudaEventElapsedTime**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hEventStart
///     + invalid handle for hEventEnd
///     + either event not signaled
///     + nullptr for pTime
xi_result_t __xicall
  xiEventQueryElapsedTime(
    xi_event_handle_t hEventStart,                  ///< [in] handle of the event
    xi_event_handle_t hEventEnd,                    ///< [in] handle of the event
    double_t* pTime                                 ///< [out] time in milliseconds
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset an event back to not signaled state
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - ::XI_RESULT_ERROR_INVALID_PARAMETER
///     + invalid handle for hEvent
xi_result_t __xicall
  xiEventReset(
    xi_event_handle_t hEvent                        ///< [in] handle of the event
    );

#endif // _XI_EVENT_H
