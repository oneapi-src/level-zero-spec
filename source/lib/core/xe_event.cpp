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
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Event
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/event.yml
* @endcond
*
******************************************************************************/
#include "xe_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a pool for a set of event(s) on the device.
/// 
/// @details
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
///         + nullptr == phEventPool
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_EVENT_POOL_DESC_VERSION_CURRENT < desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeEventPoolCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
    xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    )
{
    auto pfnCreate = xe_lib::lib.ddiTable.EventPool.pfnCreate;

#if _DEBUG
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnCreate( hDevice, desc, phEventPool );
}

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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEventPool
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeEventPoolDestroy(
    xe_event_pool_handle_t hEventPool               ///< [in] handle of event pool object to destroy
    )
{
    auto pfnDestroy = xe_lib::lib.ddiTable.EventPool.pfnDestroy;

#if _DEBUG
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnDestroy( hEventPool );
}

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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEventPool
///         + nullptr == desc
///         + nullptr == phEvent
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_EVENT_DESC_VERSION_CURRENT < desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
xe_result_t __xecall
xeEventCreate(
    xe_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
    const xe_event_desc_t* desc,                    ///< [in] pointer to event descriptor
    xe_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    )
{
    auto pfnCreate = xe_lib::lib.ddiTable.Event.pfnCreate;

#if _DEBUG
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnCreate( hEventPool, desc, phEvent );
}

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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEvent
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeEventDestroy(
    xe_event_handle_t hEvent                        ///< [in] handle of event object to destroy
    )
{
    auto pfnDestroy = xe_lib::lib.ddiTable.Event.pfnDestroy;

#if _DEBUG
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnDestroy( hEvent );
}

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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEventPool
///         + nullptr == phIpc
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeEventPoolGetIpcHandle(
    xe_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
    xe_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
    )
{
    auto pfnGetIpcHandle = xe_lib::lib.ddiTable.EventPool.pfnGetIpcHandle;

#if _DEBUG
    if( nullptr == pfnGetIpcHandle )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetIpcHandle( hEventPool, phIpc );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Opens an IPC event pool handle to retrieve an event pool handle from
///        another process.
/// 
/// @details
///     - The event handle in this process should not be freed with
///       ::xeEventPoolDestroy, but rather with ::xeEventPoolCloseIpcHandle.
///     - The application may call this function from simultaneous threads.
/// 
/// @remarks
///   _Analogues_
///     - **cuIpcOpenMemHandle**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == hIpc
///         + nullptr == phEventPool
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeEventPoolOpenIpcHandle(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC event pool handle
    xe_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event handle
    xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    )
{
    auto pfnOpenIpcHandle = xe_lib::lib.ddiTable.EventPool.pfnOpenIpcHandle;

#if _DEBUG
    if( nullptr == pfnOpenIpcHandle )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnOpenIpcHandle( hDevice, hIpc, phEventPool );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes an IPC event handle in the current process.
/// 
/// @details
///     - Closes an IPC event handle by destroying events that were opened in
///       this process using ::xeEventPoolOpenIpcHandle.
///     - The application may **not** call this function from simultaneous
///       threads with the same event pool handle.
/// 
/// @remarks
///   _Analogues_
///     - **cuIpcCloseMemHandle**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEventPool
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeEventPoolCloseIpcHandle(
    xe_event_pool_handle_t hEventPool               ///< [in] handle of event pool object
    )
{
    auto pfnCloseIpcHandle = xe_lib::lib.ddiTable.EventPool.pfnCloseIpcHandle;

#if _DEBUG
    if( nullptr == pfnCloseIpcHandle )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnCloseIpcHandle( hEventPool );
}

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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hEvent
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendSignalEvent(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    auto pfnAppendSignalEvent = xe_lib::lib.ddiTable.CommandList.pfnAppendSignalEvent;

#if _DEBUG
    if( nullptr == pfnAppendSignalEvent )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnAppendSignalEvent( hCommandList, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends wait on event(s) on the device into a command list.
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
///         + nullptr == phEvents
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendWaitOnEvents(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
    xe_event_handle_t* phEvents                     ///< [in][range(0, numEvents)] handle of the events to wait on before
                                                    ///< continuing
    )
{
    auto pfnAppendWaitOnEvents = xe_lib::lib.ddiTable.CommandList.pfnAppendWaitOnEvents;

#if _DEBUG
    if( nullptr == pfnAppendWaitOnEvents )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnAppendWaitOnEvents( hCommandList, numEvents, phEvents );
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
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEvent
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeEventHostSignal(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    auto pfnHostSignal = xe_lib::lib.ddiTable.Event.pfnHostSignal;

#if _DEBUG
    if( nullptr == pfnHostSignal )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnHostSignal( hEvent );
}

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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEvent
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_NOT_READY
///         + timeout expired
xe_result_t __xecall
xeEventHostSynchronize(
    xe_event_handle_t hEvent,                       ///< [in] handle of the event
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                    ///< returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY;
                                                    ///< if zero, then operates exactly like ::xeEventQueryStatus;
                                                    ///< if MAX_UINT32, then function will not return until complete or device
                                                    ///< is lost.
    )
{
    auto pfnHostSynchronize = xe_lib::lib.ddiTable.Event.pfnHostSynchronize;

#if _DEBUG
    if( nullptr == pfnHostSynchronize )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnHostSynchronize( hEvent, timeout );
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
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEvent
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_NOT_READY
///         + not signaled
xe_result_t __xecall
xeEventQueryStatus(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    auto pfnQueryStatus = xe_lib::lib.ddiTable.Event.pfnQueryStatus;

#if _DEBUG
    if( nullptr == pfnQueryStatus )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnQueryStatus( hEvent );
}

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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hEvent
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendEventReset(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    auto pfnAppendEventReset = xe_lib::lib.ddiTable.CommandList.pfnAppendEventReset;

#if _DEBUG
    if( nullptr == pfnAppendEventReset )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnAppendEventReset( hCommandList, hEvent );
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
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEvent
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeEventReset(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    auto pfnReset = xe_lib::lib.ddiTable.Event.pfnReset;

#if _DEBUG
    if( nullptr == pfnReset )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnReset( hEvent );
}

} // extern "C"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    EventPool::EventPool( 
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t& desc                              ///< [in] descriptor of the event object
        ) :
        m_pDevice( pDevice ),
        m_desc( desc )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    Event::Event( 
        EventPool* pEventPool                           ///< [in] pointer to owner object
        ) :
        m_pEventPool( pEventPool )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a pool for a set of event(s) on the device.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - EventPool: pointer handle of event pool object created
    /// 
    /// @throws result_t
    EventPool* __xecall
    EventPool::Create(
        Device* pDevice,                                ///< [in] pointer to the device
        const desc_t* desc                              ///< [in] pointer to event pool descriptor
        )
    {
        // auto result = ::xeEventPoolCreate( handle, pDevice, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::EventPool::Create");

        return (EventPool*)0;
    }

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
    /// @throws result_t
    void __xecall
    EventPool::Destroy(
        EventPool* pEventPool                           ///< [in] pointer to event pool object to destroy
        )
    {
        // auto result = ::xeEventPoolDestroy( handle, pEventPool );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::EventPool::Destroy");
    }

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
    ///     - Event: pointer to handle of event object created
    /// 
    /// @throws result_t
    Event* __xecall
    Event::Create(
        EventPool* pEventPool,                          ///< [in] pointer to the event pool
        const desc_t* desc                              ///< [in] pointer to event descriptor
        )
    {
        // auto result = ::xeEventCreate( handle, pEventPool, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Event::Create");

        return (Event*)0;
    }

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
    /// @throws result_t
    void __xecall
    Event::Destroy(
        Event* pEvent                                   ///< [in] pointer to event object to destroy
        )
    {
        // auto result = ::xeEventDestroy( handle, pEvent );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Event::Destroy");
    }

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
    ///     - ipc_event_pool_handle_t: Returned IPC event handle
    /// 
    /// @throws result_t
    ipc_event_pool_handle_t __xecall
    EventPool::GetIpcHandle(
        void
        )
    {
        // auto result = ::xeEventPoolGetIpcHandle( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::EventPool::GetIpcHandle");

        return ipc_event_pool_handle_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Opens an IPC event pool handle to retrieve an event pool handle from
    ///        another process.
    /// 
    /// @details
    ///     - The event handle in this process should not be freed with
    ///       ::EventPoolDestroy, but rather with ::EventPoolCloseIpcHandle.
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuIpcOpenMemHandle**
    /// 
    /// @returns
    ///     - EventPool: pointer handle of event pool object created
    /// 
    /// @throws result_t
    EventPool* __xecall
    EventPool::OpenIpcHandle(
        Device* pDevice,                                ///< [in] pointer to the device to associate with the IPC event pool handle
        ipc_event_pool_handle_t pIpc                    ///< [in] IPC event handle
        )
    {
        // auto result = ::xeEventPoolOpenIpcHandle( handle, pDevice, pIpc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::EventPool::OpenIpcHandle");

        return (EventPool*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Closes an IPC event handle in the current process.
    /// 
    /// @details
    ///     - Closes an IPC event handle by destroying events that were opened in
    ///       this process using ::EventPoolOpenIpcHandle.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same event pool handle.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuIpcCloseMemHandle**
    /// 
    /// @throws result_t
    void __xecall
    EventPool::CloseIpcHandle(
        void
        )
    {
        // auto result = ::xeEventPoolCloseIpcHandle( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::EventPool::CloseIpcHandle");
    }

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
    /// @throws result_t
    void __xecall
    CommandList::AppendSignalEvent(
        Event* pEvent                                   ///< [in] pointer to the event
        )
    {
        // auto result = ::xeCommandListAppendSignalEvent( handle, pEvent );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendSignalEvent");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends wait on event(s) on the device into a command list.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendWaitOnEvents(
        uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
        Event* phEvents                                 ///< [in][range(0, numEvents)] pointer to the events to wait on before
                                                        ///< continuing
        )
    {
        // auto result = ::xeCommandListAppendWaitOnEvents( handle, numEvents, phEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendWaitOnEvents");
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
    /// @throws result_t
    void __xecall
    Event::HostSignal(
        void
        )
    {
        // auto result = ::xeEventHostSignal( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Event::HostSignal");
    }

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
    /// @throws result_t
    void __xecall
    Event::HostSynchronize(
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                        ///< returning ::RESULT_SUCCESS or ::RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::EventQueryStatus;
                                                        ///< if MAX_UINT32, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        // auto result = ::xeEventHostSynchronize( handle, timeout );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Event::HostSynchronize");
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
    /// @throws result_t
    void __xecall
    Event::QueryStatus(
        void
        )
    {
        // auto result = ::xeEventQueryStatus( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Event::QueryStatus");
    }

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
    /// @throws result_t
    void __xecall
    CommandList::AppendEventReset(
        Event* pEvent                                   ///< [in] pointer to the event
        )
    {
        // auto result = ::xeCommandListAppendEventReset( handle, pEvent );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendEventReset");
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
    /// @throws result_t
    void __xecall
    Event::Reset(
        void
        )
    {
        // auto result = ::xeEventReset( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Event::Reset");
    }

} // namespace xe

#ifdef _DEBUG
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::desc_version_t to std::string
    std::string to_string( xe::EventPool::desc_version_t val )
    {
        switch( val )
        {
        case xe::EventPool::desc_version_t::CURRENT:
            return std::string("xe::EventPool::desc_version_t::CURRENT");
        };
        return std::string("xe::EventPool::desc_version_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::flag_t to std::string
    std::string to_string( xe::EventPool::flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );
        if( 0 == bits ) return std::string("{}");
        std::string str;
        if( static_cast<uint32_t>(xe::EventPool::flag_t::DEFAULT) & bits )
            str += "xe::EventPool::flag_t::DEFAULT | ";
        if( static_cast<uint32_t>(xe::EventPool::flag_t::HOST_VISIBLE) & bits )
            str += "xe::EventPool::flag_t::HOST_VISIBLE | ";
        if( static_cast<uint32_t>(xe::EventPool::flag_t::IPC) & bits )
            str += "xe::EventPool::flag_t::IPC | ";
        return "{ " + str.substr(0, str.size() - 3) + " }";
    }


    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::desc_version_t to std::string
    std::string to_string( xe::Event::desc_version_t val )
    {
        switch( val )
        {
        case xe::Event::desc_version_t::CURRENT:
            return std::string("xe::Event::desc_version_t::CURRENT");
        };
        return std::string("xe::Event::desc_version_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::scope_flag_t to std::string
    std::string to_string( xe::Event::scope_flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );
        if( 0 == bits ) return std::string("{}");
        std::string str;
        if( static_cast<uint32_t>(xe::Event::scope_flag_t::NONE) & bits )
            str += "xe::Event::scope_flag_t::NONE | ";
        if( static_cast<uint32_t>(xe::Event::scope_flag_t::SUBDEVICE) & bits )
            str += "xe::Event::scope_flag_t::SUBDEVICE | ";
        if( static_cast<uint32_t>(xe::Event::scope_flag_t::DEVICE) & bits )
            str += "xe::Event::scope_flag_t::DEVICE | ";
        if( static_cast<uint32_t>(xe::Event::scope_flag_t::HOST) & bits )
            str += "xe::Event::scope_flag_t::HOST | ";
        return "{ " + str.substr(0, str.size() - 3) + " }";
    }


#endif // _DEBUG
