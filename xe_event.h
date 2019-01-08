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
* @file xe_event.h
* 
* @brief Intel Xe Driver APIs for Event
* 
******************************************************************************/
#ifndef _XE_EVENT_H
#define _XE_EVENT_H
#if defined( __cplusplus )
#pragma once
#endif
#include "xe_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported event creation flags
XE_DECLARE_ENUM( xe_event_flags_t )
{
    XE_EVENT_FLAG_HOST_TO_DEVICE = XE_BIT(0),   ///< signals from host, waits on device
    XE_EVENT_FLAG_DEVICE_TO_HOST = XE_BIT(1),   ///< signals from device, waits on host
    XE_EVENT_FLAG_DEVICE_TO_DEVICE = XE_BIT(2)  ///< signals from device, waits on another device
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Event descriptor
typedef struct _xe_event_desc_t
{
    uint32_t version;                       ///< [in] descriptor version

    xe_event_flags_t flags;                 ///< [in] creation flags
} xe_event_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of xe_event_desc_t
#define XE_EVENT_DESC_VERSION   XE_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an event object
/// @remarks _Analogues:_
///     - **cuEventCreate**
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + nullptr for desc
///         + nullptr for phEvent
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
  xeEventCreate( 
    xe_device_handle_t hDevice,             ///< [in] handle of the device
    xe_event_desc_t* desc,                  ///< [in] pointer to event descriptor
    xe_event_handle_t* phEvent              ///< [out] pointer to handle of event object created
    );
    
///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes an event object
/// @remarks _Analogues:_
///     - **cuEventDestroy**
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hEvent
xe_result_t __xecall
  xeEventDestroy(
    xe_event_handle_t hEvent                ///< [in] handle of event object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes a signal of the event from the device into a command list
/// @remarks _Analogues:_
///     - **cuEventRecord**
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
///         + invalid handle for hEvent
///         + event creation flag did not set ::XE_EVENT_FLAG_DEVICE_TO_HOST or ::XE_EVENT_FLAG_DEVICE_TO_DEVICE
///         + event is in signaled state
///         + event is used by another command list
xe_result_t __xecall
  xeCommandListEncodeSignalEvent(
    xe_command_list_handle_t hCommandList,  ///< [in] handle of the command list
    xe_event_handle_t hEvent                ///< [in] handle of the event 
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes a wait on event from a host signal into a command list
/// @remarks _Analogues:_
///     - none
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
///         + invalid handle for hEvent
///         + event creation flag did not set ::XE_EVENT_FLAG_HOST_TO_DEVICE or ::XE_EVENT_FLAG_DEVICE_TO_DEVICE
///         + event is used by another command list
xe_result_t __xecall
  xeCommandListEncodeWaitOnEvent(
    xe_command_list_handle_t hCommandList,  ///< [in] handle of the command list
    xe_event_handle_t hEvent                ///< [in] handle of the event 
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes a signal of multiple events from the device into a command list
/// @remarks _Analogues:_
///     - **cuEventRecord**
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
///         + invalid handle for hEvent
///         + event creation flag did not set ::XE_EVENT_FLAG_DEVICE_TO_HOST or ::XE_EVENT_FLAG_DEVICE_TO_DEVICE
///         + event is in signaled state
///         + event is used by another command list
xe_result_t __xecall
  xeCommandListEncodeSignalMultipleEvents(
    xe_command_list_handle_t hCommandList,  ///< [in] handle of the command list
    uint32_t numEvents,                     ///< [in] number of events in hEvents
    xe_event_handle_t* hEvents              ///< [in] pointer to array of handles of the events 
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes a wait on multiple events from a host signal into a command list
/// @remarks _Analogues:_
///     - none
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
///         + invalid handle for hEvent
///         + event creation flag did not set ::XE_EVENT_FLAG_HOST_TO_DEVICE or ::XE_EVENT_FLAG_DEVICE_TO_DEVICE
///         + event is used by another command list
xe_result_t __xecall
  xeCommandListEncodeWaitOnMultipleEvents(
    xe_command_list_handle_t hCommandList,  ///< [in] handle of the command list
    uint32_t numEvents,                     ///< [in] number of events in hEvents
    xe_event_handle_t* hEvents              ///< [in] pointer to array of handles of the events 
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Signals a event from host
/// @remarks _Analogues:_
///     - none
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hEvent
///         + event creation flag did not set ::XE_EVENT_FLAG_HOST_TO_DEVICE or ::XE_EVENT_FLAG_DEVICE_TO_DEVICE
///         + event is in signaled state
xe_result_t __xecall
  xeSignalEvent(
    xe_event_handle_t hEvent                ///< [in] handle of the event 
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief The current host thread waits on an event from a device signal
/// @remarks _Analogues:_
///     - **cuEventSynchronize**
/// @returns
///     - ::XE_RESULT_SUCCESS - signaled
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hEvent
///         + event creation flag did not set ::XE_EVENT_FLAG_DEVICE_TO_HOST or ::XE_EVENT_FLAG_DEVICE_TO_DEVICE
xe_result_t __xecall
  xeWaitOnEvent(
    xe_event_handle_t hEvent                ///< [in] handle of the event 
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Signals multiple events from host
/// @remarks _Analogues:_
///     - none
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle in hFences
///         + event creation flag did not set ::XE_EVENT_FLAG_HOST_TO_DEVICE or ::XE_EVENT_FLAG_DEVICE_TO_DEVICE
///         + event is in signaled state
xe_result_t __xecall
  xeSignalMultipleEvents(
    uint32_t numEvents,                     ///< [in] number of events in hEvents
    xe_event_handle_t* hEvents              ///< [in] pointer to handles of the events 
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief The current host thread waits on multiple events from a device signal
/// @remarks _Analogues:_
///     - none
/// @returns
///     - ::XE_RESULT_SUCCESS - signaled
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle in hEvents
///         + event creation flag did not set ::XE_EVENT_FLAG_DEVICE_TO_HOST or ::XE_EVENT_FLAG_DEVICE_TO_DEVICE
xe_result_t __xecall
  xeWaitOnMultipleEvents(
    uint32_t numEvents,                     ///< [in] number of events in hEvents
    xe_event_handle_t* hEvents              ///< [in] pointer to array of handles of the events 
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries an event object's status
/// @remarks _Analogues:_
///     - **cuEventQuery**
/// @returns
///     - ::XE_RESULT_SUCCESS - signaled
///     - ::XE_RESULT_NOT_READY - not signaled
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hEvent
xe_result_t __xecall
  xeEventQueryStatus(
    xe_event_handle_t hEvent                ///< [in] handle of the event 
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries the elapsed time between two events
/// @remarks _Analogues:_
///     - **cuEventElapsedTime**
/// @returns
///     - ::XE_RESULT_SUCCESS - signaled
///     - ::XE_RESULT_NOT_READY - not signaled
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hEvent
///         + either event not enqueued
///         + nullptr for pTime
xe_result_t __xecall
  xeEventQueryElapsedTime(
    xe_event_handle_t hEventStart,          ///< [in] handle of the event 
    xe_event_handle_t hEventEnd,            ///< [in] handle of the event 
    double_t* pTime                         ///< [out] time in milliseconds
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset an event back to not signaled state
/// @remarks _Analogues:_
///     - none
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hEvent
xe_result_t __xecall
  xeEventReset(
    xe_event_handle_t hEvent                ///< [in] handle of the event 
    );

#endif // _XE_EVENT_H