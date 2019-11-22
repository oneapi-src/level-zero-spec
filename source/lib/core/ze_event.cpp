/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_event.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Event
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/event.yml
 * @endcond
 *
 */
#include "ze_lib.h"

extern "C" {

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
    )
{
    auto pfnCreate = ze_lib::context.ddiTable.EventPool.pfnCreate;
    if( nullptr == pfnCreate )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEventPool
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeEventPoolDestroy(
    ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object to destroy
    )
{
    auto pfnDestroy = ze_lib::context.ddiTable.EventPool.pfnDestroy;
    if( nullptr == pfnDestroy )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnCreate = ze_lib::context.ddiTable.Event.pfnCreate;
    if( nullptr == pfnCreate )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEvent
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeEventDestroy(
    ze_event_handle_t hEvent                        ///< [in][release] handle of event object to destroy
    )
{
    auto pfnDestroy = ze_lib::context.ddiTable.Event.pfnDestroy;
    if( nullptr == pfnDestroy )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnGetIpcHandle = ze_lib::context.ddiTable.EventPool.pfnGetIpcHandle;
    if( nullptr == pfnGetIpcHandle )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnGetIpcHandle( hEventPool, phIpc );
}

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
    )
{
    auto pfnOpenIpcHandle = ze_lib::context.ddiTable.EventPool.pfnOpenIpcHandle;
    if( nullptr == pfnOpenIpcHandle )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnOpenIpcHandle( hDriver, hIpc, phEventPool );
}

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
    )
{
    auto pfnCloseIpcHandle = ze_lib::context.ddiTable.EventPool.pfnCloseIpcHandle;
    if( nullptr == pfnCloseIpcHandle )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnAppendSignalEvent = ze_lib::context.ddiTable.CommandList.pfnAppendSignalEvent;
    if( nullptr == pfnAppendSignalEvent )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnAppendWaitOnEvents = ze_lib::context.ddiTable.CommandList.pfnAppendWaitOnEvents;
    if( nullptr == pfnAppendWaitOnEvents )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEvent
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeEventHostSignal(
    ze_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    auto pfnHostSignal = ze_lib::context.ddiTable.Event.pfnHostSignal;
    if( nullptr == pfnHostSignal )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnHostSynchronize = ze_lib::context.ddiTable.Event.pfnHostSynchronize;
    if( nullptr == pfnHostSynchronize )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnQueryStatus = ze_lib::context.ddiTable.Event.pfnQueryStatus;
    if( nullptr == pfnQueryStatus )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
    )
{
    auto pfnAppendEventReset = ze_lib::context.ddiTable.CommandList.pfnAppendEventReset;
    if( nullptr == pfnAppendEventReset )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hEvent
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeEventHostReset(
    ze_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    auto pfnHostReset = ze_lib::context.ddiTable.Event.pfnHostReset;
    if( nullptr == pfnHostReset )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnHostReset( hEvent );
}

} // extern "C"

namespace ze
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
    EventPool* __zecall
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
        thread_local std::vector<ze_device_handle_t> hDevices;
        hDevices.resize( 0 );
        hDevices.reserve( numDevices );
        for( uint32_t i = 0; i < numDevices; ++i )
            hDevices.emplace_back( ( ppDevices ) ? reinterpret_cast<ze_device_handle_t>( ppDevices[ i ]->getHandle() ) : nullptr );

        ze_event_pool_handle_t hEventPool;

        auto result = static_cast<result_t>( ::zeEventPoolCreate(
            reinterpret_cast<ze_driver_handle_t>( pDriver->getHandle() ),
            reinterpret_cast<const ze_event_pool_desc_t*>( desc ),
            numDevices,
            hDevices.data(),
            &hEventPool ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::EventPool::Create" );

        EventPool* pEventPool = nullptr;

        try
        {
            pEventPool = new EventPool( reinterpret_cast<event_pool_handle_t>( hEventPool ), pDriver, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pEventPool;
            pEventPool = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::EventPool::Create" );
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
    void __zecall
    EventPool::Destroy(
        EventPool* pEventPool                           ///< [in][release] pointer to event pool object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zeEventPoolDestroy(
            reinterpret_cast<ze_event_pool_handle_t>( pEventPool->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::EventPool::Destroy" );

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
    Event* __zecall
    Event::Create(
        EventPool* pEventPool,                          ///< [in] pointer to the event pool
        const desc_t* desc                              ///< [in] pointer to event descriptor
        )
    {
        ze_event_handle_t hEvent;

        auto result = static_cast<result_t>( ::zeEventCreate(
            reinterpret_cast<ze_event_pool_handle_t>( pEventPool->getHandle() ),
            reinterpret_cast<const ze_event_desc_t*>( desc ),
            &hEvent ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Event::Create" );

        Event* pEvent = nullptr;

        try
        {
            pEvent = new Event( reinterpret_cast<event_handle_t>( hEvent ), pEventPool, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pEvent;
            pEvent = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::Event::Create" );
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
    void __zecall
    Event::Destroy(
        Event* pEvent                                   ///< [in][release] pointer to event object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zeEventDestroy(
            reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Event::Destroy" );

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
    ipc_event_pool_handle_t __zecall
    EventPool::GetIpcHandle(
        void
        )
    {
        ze_ipc_event_pool_handle_t hIpc;

        auto result = static_cast<result_t>( ::zeEventPoolGetIpcHandle(
            reinterpret_cast<ze_event_pool_handle_t>( getHandle() ),
            &hIpc ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::EventPool::GetIpcHandle" );

        return *reinterpret_cast<ipc_event_pool_handle_t*>( &hIpc );
    }

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
    ///     - EventPool*: pointer handle of event pool object created
    /// 
    /// @throws result_t
    EventPool* __zecall
    EventPool::OpenIpcHandle(
        Driver* pDriver,                                ///< [in] pointer to the driver to associate with the IPC event pool handle
        ipc_event_pool_handle_t pIpc                    ///< [in] IPC event handle
        )
    {
        ze_event_pool_handle_t hEventPool;

        auto result = static_cast<result_t>( ::zeEventPoolOpenIpcHandle(
            reinterpret_cast<ze_driver_handle_t>( pDriver->getHandle() ),
            *reinterpret_cast<ze_ipc_event_pool_handle_t*>( &pIpc ),
            &hEventPool ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::EventPool::OpenIpcHandle" );

        EventPool* pEventPool = nullptr;

        try
        {
            pEventPool = new EventPool( reinterpret_cast<event_pool_handle_t>( hEventPool ), pDriver, nullptr );
        }
        catch( std::bad_alloc& )
        {
            delete pEventPool;
            pEventPool = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::EventPool::OpenIpcHandle" );
        }

        return pEventPool;
    }

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
    /// @throws result_t
    void __zecall
    EventPool::CloseIpcHandle(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeEventPoolCloseIpcHandle(
            reinterpret_cast<ze_event_pool_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::EventPool::CloseIpcHandle" );
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
    void __zecall
    CommandList::AppendSignalEvent(
        Event* pEvent                                   ///< [in] pointer to the event
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendSignalEvent(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendSignalEvent" );
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
    void __zecall
    CommandList::AppendWaitOnEvents(
        uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
        Event** ppEvents                                ///< [in][range(0, numEvents)] pointer to the events to wait on before
                                                        ///< continuing
        )
    {
        thread_local std::vector<ze_event_handle_t> hEvents;
        hEvents.resize( 0 );
        hEvents.reserve( numEvents );
        for( uint32_t i = 0; i < numEvents; ++i )
            hEvents.emplace_back( reinterpret_cast<ze_event_handle_t>( ppEvents[ i ]->getHandle() ) );

        auto result = static_cast<result_t>( ::zeCommandListAppendWaitOnEvents(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            numEvents,
            hEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendWaitOnEvents" );
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
    void __zecall
    Event::HostSignal(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeEventHostSignal(
            reinterpret_cast<ze_event_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Event::HostSignal" );
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
    bool_t __zecall
    Event::HostSynchronize(
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeEventQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        auto result = static_cast<result_t>( ::zeEventHostSynchronize(
            reinterpret_cast<ze_event_handle_t>( getHandle() ),
            timeout ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Event::HostSynchronize" );
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
    bool_t __zecall
    Event::QueryStatus(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeEventQueryStatus(
            reinterpret_cast<ze_event_handle_t>( getHandle() ) ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Event::QueryStatus" );
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
    void __zecall
    CommandList::AppendEventReset(
        Event* pEvent                                   ///< [in] pointer to the event
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendEventReset(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendEventReset" );
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
    void __zecall
    Event::HostReset(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeEventHostReset(
            reinterpret_cast<ze_event_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Event::HostReset" );
    }

} // namespace ze

namespace ze
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

} // namespace ze
