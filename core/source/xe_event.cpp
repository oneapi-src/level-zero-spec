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
* @file xe_event.cpp
*
* @brief Intel Xe Driver APIs for Event
*
* DO NOT EDIT: generated from /scripts/<type>/event.yml
*
******************************************************************************/
#include "../include/xe_event.h"
#include "event.h"

#include <exception>    // @todo: move to common and/or precompiled header
#include <new>

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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == desc
///         + nullptr == phEvent
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_EVENT_DESC_VERSION < desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///
/// @hash {2c5763b8ec9726ab95422bca4616275ec9ed4e3d4b7a42a8b4e7089c813350d6}
///
__xedllexport xe_result_t __xecall
  xeDeviceCreateEvent(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_event_desc_t* desc,                    ///< [in] pointer to event descriptor
    xe_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == phEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( XE_EVENT_DESC_VERSION < desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;
        }
        /// @begin

        return L0::Device::fromHandle(hDevice)->createEvent(desc, phEvent);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == desc
///         + nullptr == ptr
///         + nullptr == phEvent
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_EVENT_DESC_VERSION < desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///
/// @hash {ff2fcb0cf2905079d5fb305c78b9dc0d9f1c4e5ab7792007b01cd832e94bae5c}
///
__xedllexport xe_result_t __xecall
  xeDevicePlaceEvent(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_event_desc_t* desc,                    ///< [in] pointer to event descriptor
    void* ptr,                                      ///< [in] pointer to the device pointer where the event should be placed
    xe_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == phEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( XE_EVENT_DESC_VERSION < desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;
        }
        /// @begin

        return L0::Device::fromHandle(hDevice)->placeEvent(desc, ptr, phEvent);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hEvent
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {0e82f51d7da70ece36da3299c7607c0ce273c15a6401a026d89b8a6e24b52985}
///
__xedllexport xe_result_t __xecall
  xeEventDestroy(
    xe_event_handle_t hEvent                        ///< [in] handle of event object to destroy
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::Event::fromHandle(hEvent)->destroy();

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes a signal of the event from the device into a command list.
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == hEvent
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {f66119ce56a773182ebed031c151a8faf6280e74d7b56718b71177f01141bc97}
///
__xedllexport xe_result_t __xecall
  xeCommandListEncodeSignalEvent(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::CommandList::fromHandle(hCommandList)->encodeSignalEvent(hEvent);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes a wait on event from a host signal into a command list.
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
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == hEvent
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {b8409ab2ea47c3520b0faabc15232c79b1b0494defcc29b08c09a95b5b4e97df}
///
__xedllexport xe_result_t __xecall
  xeCommandListEncodeWaitOnEvent(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::CommandList::fromHandle(hCommandList)->encodeWaitOnEvent(hEvent);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes signals of multiple event from the device into a command list.
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
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == phEvents
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {b6c4b3102db77f8114696fb2f220387c48408770e4bed49fa83d44159b8af5f6}
///
__xedllexport xe_result_t __xecall
  xeCommandListEncodeSignalMultipleEvents(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numEvents,                             ///< [in] number of events pointed to by phEvents
    xe_event_handle_t* phEvents                     ///< [in] pointer to array of handles of the events
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == phEvents ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::CommandList::fromHandle(hCommandList)->encodeSignalMultipleEvents(numEvents, phEvents);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes waits on multiple event from a host signal into a command
///        list.
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
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == phEvents
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {9bc2eeadc113dfc5be97a3a4590743a2b7b4ee4e12237b86fc7be4f208da95d8}
///
__xedllexport xe_result_t __xecall
  xeCommandListEncodeWaitOnMultipleEvents(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numEvents,                             ///< [in] number of events pointed to by phEvents
    xe_event_handle_t* phEvents                     ///< [in] pointer to array of handles of the events
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == phEvents ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::CommandList::fromHandle(hCommandList)->encodeWaitOnMultipleEvents(numEvents, phEvents);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hEvent
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {809272a0febf2e56f09e04c5a53b8568b0c6905e5acd124c0e1e4151b542dab6}
///
__xedllexport xe_result_t __xecall
  xeHostSignalEvent(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::hostSignalEvent(hEvent);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hEvent
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_NOT_READY
///         + timeout expired
///
/// @hash {580d70d65f44535c9b2585408c20f2c0af086f6b54945445e7b09d31493403e0}
///
__xedllexport xe_result_t __xecall
  xeHostWaitOnEvent(
    xe_event_handle_t hEvent,                       ///< [in] handle of the event
    xe_synchronization_mode_t mode,                 ///< [in] synchronization mode
    uint32_t delay,                                 ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then time (in
                                                    ///< microseconds) to poll before putting Host thread to sleep; otherwise,
                                                    ///< must be zero.
    uint32_t interval,                              ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then maximum time (in
                                                    ///< microseconds) to put Host thread to sleep between polling; otherwise,
                                                    ///< must be zero.
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to poll or sleep
                                                    ///< before returning; if zero, then only a single status check is made
                                                    ///< before immediately returning; if MAX_UINT32, then function will not
                                                    ///< return until complete.
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::hostWaitOnEvent(hEvent, mode, delay, interval, timeout);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == phEvents
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {6bfaa4edb5accb4ff4433b13b89b7371377931bb1eb613bb04878ef02ac4f666}
///
__xedllexport xe_result_t __xecall
  xeHostSignalMultipleEvents(
    uint32_t numEvents,                             ///< [in] number of events pointed to by phEvents
    xe_event_handle_t* phEvents                     ///< [in] pointer to array of handles of the events
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == phEvents ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::hostSignalMultipleEvents(numEvents, phEvents);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == phEvents
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_NOT_READY
///         + timeout expired
///
/// @hash {e52ffd62217e9fcf9ed29e74f4453d0d1930803fe7e4289225b27f2526df83d0}
///
__xedllexport xe_result_t __xecall
  xeHostWaitOnMultipleEvents(
    uint32_t numEvents,                             ///< [in] number of events pointed to by phEvents
    xe_event_handle_t* phEvents,                    ///< [in] pointer to array of handles of the events
    xe_synchronization_mode_t mode,                 ///< [in] synchronization mode
    uint32_t delay,                                 ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then time (in
                                                    ///< microseconds) to poll before putting Host thread to sleep; otherwise,
                                                    ///< must be zero.
    uint32_t interval,                              ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then maximum time (in
                                                    ///< microseconds) to put Host thread to sleep between polling; otherwise,
                                                    ///< must be zero.
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to poll or sleep
                                                    ///< before returning; if zero, then only a single status check is made
                                                    ///< before immediately returning; if MAX_UINT32, then function will not
                                                    ///< return until complete.
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == phEvents ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::hostWaitOnMultipleEvents(numEvents, phEvents, mode, delay, interval, timeout);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hEvent
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_NOT_READY
///         + not signaled
///
/// @hash {1091660d20f5595dad7bbbf969b0a8e9238f218438ff4f2c908b93135147cfa6}
///
__xedllexport xe_result_t __xecall
  xeEventQueryStatus(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::Event::fromHandle(hEvent)->queryStatus();

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries the elapsed time between two device-signaled events.
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hEventStart
///         + nullptr == hEventEnd
///         + nullptr == pTime
///         + either event not signaled by device
///         + either event not created with ::XE_EVENT_FLAG_TIMESTAMP
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {e27fc7ab1b4c00fd10605fd7c45adee5ce6b22dc102ee8450ab689a513de4314}
///
__xedllexport xe_result_t __xecall
  xeEventQueryElapsedTime(
    xe_event_handle_t hEventStart,                  ///< [in] handle of the start event
    xe_event_handle_t hEventEnd,                    ///< [in] handle of the end event
    double_t* pTime                                 ///< [out] time in milliseconds
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hEventStart ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == hEventEnd ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pTime ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::eventQueryElapsedTime(hEventStart, hEventEnd, pTime);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries performance metrics between two device-signaled events.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hEventStart
///         + nullptr == hEventEnd
///         + nullptr == pReportData
///         + either event not signaled by device
///         + either event not created with ::XE_EVENT_FLAG_PERFORMANCE_METRICS
///         + report size too small
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {86bf02b143940d38911ff1c385a99d93c8aa0d6aef16ee9e18cddb4e1c51dfa5}
///
__xedllexport xe_result_t __xecall
  xeEventQueryMetricsData(
    xe_event_handle_t hEventStart,                  ///< [in] handle of the start event
    xe_event_handle_t hEventEnd,                    ///< [in] handle of the end event
    size_t reportSize,                              ///< [in] size of the report data buffer in bytes
    uint32_t* pReportData                           ///< [out] report data buffer
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hEventStart ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == hEventEnd ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pReportData ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::eventQueryMetricsData(hEventStart, hEventEnd, reportSize, pReportData);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset an event back to not signaled state
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - vkResetEvent
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == hEvent
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {06205f20ab4babe3494b5f61b9e94ba192b5f0f68c0f27e75651983ccc6f0b3e}
///
__xedllexport xe_result_t __xecall
  xeCommandListEncodeEventReset(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::CommandList::fromHandle(hCommandList)->encodeEventReset(hEvent);

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
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
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hEvent
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {8bd5a629cd3d5cdbf21ba95b68945eb87003476ae6e65e32a1da5666b9851719}
///
__xedllexport xe_result_t __xecall
  xeEventReset(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        return L0::Event::fromHandle(hEvent)->reset();

        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

