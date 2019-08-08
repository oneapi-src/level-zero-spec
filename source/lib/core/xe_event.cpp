/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_event.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Event
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/event.yml
 * @endcond
 *
 */
#include "xe_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a pool for a set of event(s) for the driver
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
///         + nullptr == hDriver
///         + nullptr == desc
///         + nullptr == phEventPool
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_EVENT_POOL_DESC_VERSION_CURRENT < desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeEventPoolCreate(
    xe_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const xe_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
    uint32_t numDevices,                            ///< [in] number of device handles
    xe_device_handle_t* phDevices,                  ///< [in][optional][range(0, numDevices)] array of device handles which
                                                    ///< have visibility to the event pool.
                                                    ///< if nullptr, then event pool is visible to all devices supported by the
                                                    ///< driver instance.
    xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    )
{
    auto pfnCreate = xe_lib::context.ddiTable.EventPool.pfnCreate;
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnCreate( hDriver, desc, numDevices, phDevices, phEventPool );
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
    xe_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object to destroy
    )
{
    auto pfnDestroy = xe_lib::context.ddiTable.EventPool.pfnDestroy;
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    auto pfnCreate = xe_lib::context.ddiTable.Event.pfnCreate;
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    xe_event_handle_t hEvent                        ///< [in][release] handle of event object to destroy
    )
{
    auto pfnDestroy = xe_lib::context.ddiTable.Event.pfnDestroy;
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    auto pfnGetIpcHandle = xe_lib::context.ddiTable.EventPool.pfnGetIpcHandle;
    if( nullptr == pfnGetIpcHandle )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
///         + nullptr == phEventPool
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeEventPoolOpenIpcHandle(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC event pool handle
    xe_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event handle
    xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    )
{
    auto pfnOpenIpcHandle = xe_lib::context.ddiTable.EventPool.pfnOpenIpcHandle;
    if( nullptr == pfnOpenIpcHandle )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    xe_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object
    )
{
    auto pfnCloseIpcHandle = xe_lib::context.ddiTable.EventPool.pfnCloseIpcHandle;
    if( nullptr == pfnCloseIpcHandle )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    auto pfnAppendSignalEvent = xe_lib::context.ddiTable.CommandList.pfnAppendSignalEvent;
    if( nullptr == pfnAppendSignalEvent )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    auto pfnAppendWaitOnEvents = xe_lib::context.ddiTable.CommandList.pfnAppendWaitOnEvents;
    if( nullptr == pfnAppendWaitOnEvents )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    auto pfnHostSignal = xe_lib::context.ddiTable.Event.pfnHostSignal;
    if( nullptr == pfnHostSignal )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                    ///< yield before returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY;
                                                    ///< if zero, then operates exactly like ::xeEventQueryStatus;
                                                    ///< if UINT32_MAX, then function will not return until complete or device
                                                    ///< is lost.
    )
{
    auto pfnHostSynchronize = xe_lib::context.ddiTable.Event.pfnHostSynchronize;
    if( nullptr == pfnHostSynchronize )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    auto pfnQueryStatus = xe_lib::context.ddiTable.Event.pfnQueryStatus;
    if( nullptr == pfnQueryStatus )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    auto pfnAppendEventReset = xe_lib::context.ddiTable.CommandList.pfnAppendEventReset;
    if( nullptr == pfnAppendEventReset )
        return XE_RESULT_ERROR_UNSUPPORTED;

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
    auto pfnReset = xe_lib::context.ddiTable.Event.pfnReset;
    if( nullptr == pfnReset )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnReset( hEvent );
}

} // extern "C"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    EventPool::EventPool( 
        event_pool_handle_t handle,                     ///< [in] handle of event pool object
        Driver* pDriver,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the event pool object
        ) :
        m_handle( handle ),
        m_pDriver( pDriver ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    Event::Event( 
        event_handle_t handle,                          ///< [in] handle of event object
        EventPool* pEventPool,                          ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the event object
        ) :
        m_handle( handle ),
        m_pEventPool( pEventPool ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a pool for a set of event(s) for the driver
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - EventPool*: pointer handle of event pool object created
    /// 
    /// @throws result_t
    EventPool* __xecall
    EventPool::Create(
        Driver* pDriver,                                ///< [in] pointer to the driver instance
        const desc_t* desc,                             ///< [in] pointer to event pool descriptor
        uint32_t numDevices,                            ///< [in] number of device handles
        Device** ppDevices                              ///< [in][optional][range(0, numDevices)] array of device handles which
                                                        ///< have visibility to the event pool.
                                                        ///< if nullptr, then event pool is visible to all devices supported by the
                                                        ///< driver instance.
        )
    {
        thread_local std::vector<xe_device_handle_t> hDevices;
        hDevices.resize( 0 );
        hDevices.reserve( numDevices );
        for( uint32_t i = 0; i < numDevices; ++i )
            hDevices.emplace_back( ( ppDevices ) ? reinterpret_cast<xe_device_handle_t>( ppDevices[ i ]->getHandle() ) : nullptr );

        xe_event_pool_handle_t hEventPool;

        auto result = static_cast<result_t>( ::xeEventPoolCreate(
            reinterpret_cast<xe_driver_handle_t>( pDriver->getHandle() ),
            reinterpret_cast<const xe_event_pool_desc_t*>( desc ),
            numDevices,
            hDevices.data(),
            &hEventPool ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::EventPool::Create" );

        EventPool* pEventPool = nullptr;

        try
        {
            pEventPool = new EventPool( reinterpret_cast<event_pool_handle_t>( hEventPool ), pDriver, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pEventPool;
            pEventPool = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xe::EventPool::Create" );
        }

        return pEventPool;
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
        EventPool* pEventPool                           ///< [in][release] pointer to event pool object to destroy
        )
    {
        auto result = static_cast<result_t>( ::xeEventPoolDestroy(
            reinterpret_cast<xe_event_pool_handle_t>( pEventPool->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::EventPool::Destroy" );

        delete pEventPool;
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
    ///     - Event*: pointer to handle of event object created
    /// 
    /// @throws result_t
    Event* __xecall
    Event::Create(
        EventPool* pEventPool,                          ///< [in] pointer to the event pool
        const desc_t* desc                              ///< [in] pointer to event descriptor
        )
    {
        xe_event_handle_t hEvent;

        auto result = static_cast<result_t>( ::xeEventCreate(
            reinterpret_cast<xe_event_pool_handle_t>( pEventPool->getHandle() ),
            reinterpret_cast<const xe_event_desc_t*>( desc ),
            &hEvent ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Event::Create" );

        Event* pEvent = nullptr;

        try
        {
            pEvent = new Event( reinterpret_cast<event_handle_t>( hEvent ), pEventPool, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pEvent;
            pEvent = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xe::Event::Create" );
        }

        return pEvent;
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
        Event* pEvent                                   ///< [in][release] pointer to event object to destroy
        )
    {
        auto result = static_cast<result_t>( ::xeEventDestroy(
            reinterpret_cast<xe_event_handle_t>( pEvent->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Event::Destroy" );

        delete pEvent;
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
        xe_ipc_event_pool_handle_t hIpc;

        auto result = static_cast<result_t>( ::xeEventPoolGetIpcHandle(
            reinterpret_cast<xe_event_pool_handle_t>( getHandle() ),
            &hIpc ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::EventPool::GetIpcHandle" );

        return *reinterpret_cast<ipc_event_pool_handle_t*>( &hIpc );
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
    ///     - EventPool*: pointer handle of event pool object created
    /// 
    /// @throws result_t
    EventPool* __xecall
    EventPool::OpenIpcHandle(
        Device* pDevice,                                ///< [in] pointer to the device to associate with the IPC event pool handle
        ipc_event_pool_handle_t pIpc                    ///< [in] IPC event handle
        )
    {
        xe_event_pool_handle_t hEventPool;

        auto result = static_cast<result_t>( ::xeEventPoolOpenIpcHandle(
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
            *reinterpret_cast<xe_ipc_event_pool_handle_t*>( &pIpc ),
            &hEventPool ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::EventPool::OpenIpcHandle" );

        EventPool* pEventPool = nullptr;

        try
        {
            pEventPool = new EventPool( reinterpret_cast<event_pool_handle_t>( hEventPool ), nullptr, nullptr );
        }
        catch( std::bad_alloc& )
        {
            delete pEventPool;
            pEventPool = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xe::EventPool::OpenIpcHandle" );
        }

        return pEventPool;
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
    /// @throws result_t
    void __xecall
    EventPool::CloseIpcHandle(
        void
        )
    {
        auto result = static_cast<result_t>( ::xeEventPoolCloseIpcHandle(
            reinterpret_cast<xe_event_pool_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::EventPool::CloseIpcHandle" );
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
        auto result = static_cast<result_t>( ::xeCommandListAppendSignalEvent(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ),
            reinterpret_cast<xe_event_handle_t>( pEvent->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendSignalEvent" );
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
        Event** ppEvents                                ///< [in][range(0, numEvents)] pointer to the events to wait on before
                                                        ///< continuing
        )
    {
        thread_local std::vector<xe_event_handle_t> hEvents;
        hEvents.resize( 0 );
        hEvents.reserve( numEvents );
        for( uint32_t i = 0; i < numEvents; ++i )
            hEvents.emplace_back( reinterpret_cast<xe_event_handle_t>( ppEvents[ i ]->getHandle() ) );

        auto result = static_cast<result_t>( ::xeCommandListAppendWaitOnEvents(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ),
            numEvents,
            hEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendWaitOnEvents" );
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
        auto result = static_cast<result_t>( ::xeEventHostSignal(
            reinterpret_cast<xe_event_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Event::HostSignal" );
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
    ///     - bool_t:'0' when RESULT_NOT_READY
    /// @throws result_t
    bool_t __xecall
    Event::HostSynchronize(
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::xeEventQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        auto result = static_cast<result_t>( ::xeEventHostSynchronize(
            reinterpret_cast<xe_event_handle_t>( getHandle() ),
            timeout ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Event::HostSynchronize" );
        return 1; // true
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
    ///     - bool_t:'0' when RESULT_NOT_READY
    /// @throws result_t
    bool_t __xecall
    Event::QueryStatus(
        void
        )
    {
        auto result = static_cast<result_t>( ::xeEventQueryStatus(
            reinterpret_cast<xe_event_handle_t>( getHandle() ) ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Event::QueryStatus" );
        return 1; // true
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
        auto result = static_cast<result_t>( ::xeCommandListAppendEventReset(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ),
            reinterpret_cast<xe_event_handle_t>( pEvent->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendEventReset" );
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
        auto result = static_cast<result_t>( ::xeEventReset(
            reinterpret_cast<xe_event_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Event::Reset" );
    }

} // namespace xe

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::desc_version_t to std::string
    std::string to_string( const EventPool::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case EventPool::desc_version_t::CURRENT:
            str = "EventPool::desc_version_t::CURRENT";
            break;

        default:
            str = "EventPool::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::flag_t to std::string
    std::string to_string( const EventPool::flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "DEFAULT   ";
        
        if( static_cast<uint32_t>(EventPool::flag_t::HOST_VISIBLE) & bits )
            str += "HOST_VISIBLE | ";
        
        if( static_cast<uint32_t>(EventPool::flag_t::IPC) & bits )
            str += "IPC | ";

        return ( str.size() > 3 ) 
            ? "EventPool::flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "EventPool::flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::desc_t to std::string
    std::string to_string( const EventPool::desc_t val )
    {
        std::string str;
        
        str += "EventPool::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "EventPool::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "EventPool::desc_t::count : ";
        str += std::to_string(val.count);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::desc_version_t to std::string
    std::string to_string( const Event::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Event::desc_version_t::CURRENT:
            str = "Event::desc_version_t::CURRENT";
            break;

        default:
            str = "Event::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::scope_flag_t to std::string
    std::string to_string( const Event::scope_flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(Event::scope_flag_t::SUBDEVICE) & bits )
            str += "SUBDEVICE | ";
        
        if( static_cast<uint32_t>(Event::scope_flag_t::DEVICE) & bits )
            str += "DEVICE | ";
        
        if( static_cast<uint32_t>(Event::scope_flag_t::HOST) & bits )
            str += "HOST | ";

        return ( str.size() > 3 ) 
            ? "Event::scope_flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Event::scope_flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::desc_t to std::string
    std::string to_string( const Event::desc_t val )
    {
        std::string str;
        
        str += "Event::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Event::desc_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "Event::desc_t::signal : ";
        str += to_string(val.signal);
        str += "\n";
        
        str += "Event::desc_t::wait : ";
        str += to_string(val.wait);
        str += "\n";

        return str;
    }

} // namespace xe
