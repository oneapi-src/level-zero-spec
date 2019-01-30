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
* @file xe_event.cpp
*
* @brief Intel Xe Driver APIs for Event
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/event.yml
* @endcond
*
******************************************************************************/
#include "../include/xe_event.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an event object on the device.
/// 
/// @details
///     - This function may be called from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clCreateUserEvent**
///     - vkCreateEvent
///     - cuEventCreate
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + nullptr for desc
///         + nullptr for phEvent
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceCreateEvent(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_event_desc_t* desc,                    ///< [in] pointer to event descriptor
    xe_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_device_handle_t() == hDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == desc, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == phEvent, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an event object on the device from existing memory.
/// 
/// @details
///     - This function is intended for sharing fences with peer devices or
///       across processes
///     - This function may be called from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + nullptr for desc
///         + nullptr for ptr
///         + nullptr for phEvent
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDevicePlaceEvent(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_event_desc_t* desc,                    ///< [in] pointer to event descriptor
    void* ptr,                                      ///< [in] pointer to the device pointer where the event should be placed
    xe_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_device_handle_t() == hDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == desc, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == ptr, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == phEvent, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes an event object.
/// 
/// @details
///     - The application is responsible for making sure the GPU is not
///       currently referencing the event before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this event
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clReleaseEvent**
///     - vkDestroyEvent
///     - cuEventDestroy
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hEvent
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeEventDestroy(
    xe_event_handle_t hEvent                        ///< [in] handle of event object to destroy
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_event_handle_t() == hEvent, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes a signal of the event from the device into a command list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clSetUserEventStatus**
///     - cuEventRecord
///     - vkCmdSetEvent
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
///         + invalid handle for hEvent
///         + event creation flag did not set ::XE_EVENT_FLAG_DEVICE_TO_HOST or ::XE_EVENT_FLAG_DEVICE_TO_DEVICE
///         + event is in signaled state
///         + event is used by another command list
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandListEncodeSignalEvent(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_command_list_handle_t() == hCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(xe_event_handle_t() == hEvent, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes a wait on event from a host signal into a command list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
///         + invalid handle for hEvent
///         + event creation flag did not set ::XE_EVENT_FLAG_HOST_TO_DEVICE or ::XE_EVENT_FLAG_DEVICE_TO_DEVICE
///         + event is used by another command list
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandListEncodeWaitOnEvent(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_command_list_handle_t() == hCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(xe_event_handle_t() == hEvent, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes signals of multiple event from the device into a command list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
///         + nullptr for phEvents
///         + invalid handle in phEvents
///         + any event creation flag did not set ::XE_EVENT_FLAG_DEVICE_TO_HOST or ::XE_EVENT_FLAG_DEVICE_TO_DEVICE
///         + any event is in signaled state
///         + any event is used by another command list
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandListEncodeSignalMultipleEvents(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numEvents,                             ///< [in] number of events pointed to by phEvents
    xe_event_handle_t* phEvents                     ///< [in] pointer to array of handles of the events
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_command_list_handle_t() == hCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == phEvents, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes waits on multiple event from a host signal into a command
///        list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandList
///         + nullptr for phEvents
///         + invalid handle in phEvents
///         + any event creation flag did not set ::XE_EVENT_FLAG_HOST_TO_DEVICE or ::XE_EVENT_FLAG_DEVICE_TO_DEVICE
///         + any event is used by another command list
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandListEncodeWaitOnMultipleEvents(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numEvents,                             ///< [in] number of events pointed to by phEvents
    xe_event_handle_t* phEvents                     ///< [in] pointer to array of handles of the events
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_command_list_handle_t() == hCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == phEvents, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hEvent
///         + event creation flag did not set ::XE_EVENT_FLAG_HOST_TO_DEVICE or ::XE_EVENT_FLAG_DEVICE_TO_DEVICE
///         + event is in signaled state
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeHostSignalEvent(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_event_handle_t() == hEvent, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief The current host thread waits on an event from a device signal.
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hEvent
///         + event creation flag did not set ::XE_EVENT_FLAG_DEVICE_TO_HOST or ::XE_EVENT_FLAG_DEVICE_TO_DEVICE
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeHostWaitOnEvent(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_event_handle_t() == hEvent, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Signals multiple events from host.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr for phEvents
///         + invalid handle in phEvents
///         + any event creation flag did not set ::XE_EVENT_FLAG_HOST_TO_DEVICE or ::XE_EVENT_FLAG_DEVICE_TO_DEVICE
///         + any event is in signaled state
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeHostSignalMultipleEvents(
    uint32_t numEvents,                             ///< [in] number of events pointed to by phEvents
    xe_event_handle_t* phEvents                     ///< [in] pointer to array of handles of the events
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == phEvents, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief The current host thread waits on multiple events from a device signal.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clWaitForEvents
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr for phEvents
///         + invalid handle in phEvents
///         + any event creation flag did not set ::XE_EVENT_FLAG_DEVICE_TO_HOST or ::XE_EVENT_FLAG_DEVICE_TO_DEVICE
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeHostWaitOnMultipleEvents(
    uint32_t numEvents,                             ///< [in] number of events pointed to by phEvents
    xe_event_handle_t* phEvents                     ///< [in] pointer to array of handles of the events
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == phEvents, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_NOT_READY
///         + not signaled
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hEvent
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeEventQueryStatus(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_event_handle_t() == hEvent, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries the elapsed time between two signaled events.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuEventElapsedTime**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hEventStart
///         + invalid handle for hEventEnd
///         + either event not signaled
///         + nullptr for pTime
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeEventQueryElapsedTime(
    xe_event_handle_t hEventStart,                  ///< [in] handle of the event
    xe_event_handle_t hEventEnd,                    ///< [in] handle of the event
    double_t* pTime                                 ///< [out] time in milliseconds
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_event_handle_t() == hEventStart, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(xe_event_handle_t() == hEventEnd, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pTime, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hEvent
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeEventReset(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_event_handle_t() == hEvent, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

