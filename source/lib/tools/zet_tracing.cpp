/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_tracing.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for API Tracing
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/tracing.yml
 * @endcond
 *
 */
#include "zet_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a tracer for the specified driver.
/// 
/// @details
///     - The tracer can only be used on the driver on which it was created.
///     - The tracer is created in the disabled state.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == desc->pUserData`
///         + `nullptr == phTracer`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZET_TRACER_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
ze_result_t __zecall
zetTracerCreate(
    zet_driver_handle_t hDriver,                    ///< [in] handle of the driver
    const zet_tracer_desc_t* desc,                  ///< [in] pointer to tracer descriptor
    zet_tracer_handle_t* phTracer                   ///< [out] pointer to handle of tracer object created
    )
{
    auto pfnCreate = zet_lib::context.ddiTable.Tracer.pfnCreate;
    if( nullptr == pfnCreate )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnCreate( hDriver, desc, phTracer );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a tracer.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same tracer handle.
///     - The implementation of this function will stall and wait on any
///       outstanding threads executing callbacks before freeing any Host
///       allocations associated with this tracer.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTracer`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t __zecall
zetTracerDestroy(
    zet_tracer_handle_t hTracer                     ///< [in][release] handle of tracer object to destroy
    )
{
    auto pfnDestroy = zet_lib::context.ddiTable.Tracer.pfnDestroy;
    if( nullptr == pfnDestroy )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDestroy( hTracer );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the collection of callbacks to be executed **before** driver
///        execution.
/// 
/// @details
///     - The application only needs to set the function pointers it is
///       interested in receiving; all others should be 'nullptr'
///     - The application must ensure that no other threads are executing
///       functions for which the tracing functions are changing.
///     - The application may **not** call this function from simultaneous
///       threads with the same tracer handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTracer`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCoreCbs`
ze_result_t __zecall
zetTracerSetPrologues(
    zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
    zet_core_callbacks_t* pCoreCbs,                 ///< [in] pointer to table of 'core' callback function pointers
    zet_experimental_callbacks_t* pExperimentalCbs  ///< [in][optional] pointer to table of 'experimental' callback function
                                                    ///< pointers
    )
{
    auto pfnSetPrologues = zet_lib::context.ddiTable.Tracer.pfnSetPrologues;
    if( nullptr == pfnSetPrologues )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetPrologues( hTracer, pCoreCbs, pExperimentalCbs );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the collection of callbacks to be executed **after** driver
///        execution.
/// 
/// @details
///     - The application only needs to set the function pointers it is
///       interested in receiving; all others should be 'nullptr'
///     - The application must ensure that no other threads are executing
///       functions for which the tracing functions are changing.
///     - The application may **not** call this function from simultaneous
///       threads with the same tracer handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTracer`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCoreCbs`
ze_result_t __zecall
zetTracerSetEpilogues(
    zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
    zet_core_callbacks_t* pCoreCbs,                 ///< [in] pointer to table of 'core' callback function pointers
    zet_experimental_callbacks_t* pExperimentalCbs  ///< [in][optional] pointer to table of 'experimental' callback function
                                                    ///< pointers
    )
{
    auto pfnSetEpilogues = zet_lib::context.ddiTable.Tracer.pfnSetEpilogues;
    if( nullptr == pfnSetEpilogues )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetEpilogues( hTracer, pCoreCbs, pExperimentalCbs );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Enables (or disables) the tracer
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same tracer handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTracer`
ze_result_t __zecall
zetTracerSetEnabled(
    zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
    ze_bool_t enable                                ///< [in] enable the tracer if true; disable if false
    )
{
    auto pfnSetEnabled = zet_lib::context.ddiTable.Tracer.pfnSetEnabled;
    if( nullptr == pfnSetEnabled )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetEnabled( hTracer, enable );
}

} // extern "C"

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    Tracer::Tracer( 
        tracer_handle_t handle,                         ///< [in] handle of tracer object
        Driver* pDriver,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the tracer object
        ) :
        m_handle( handle ),
        m_pDriver( pDriver ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a tracer for the specified driver.
    /// 
    /// @details
    ///     - The tracer can only be used on the driver on which it was created.
    ///     - The tracer is created in the disabled state.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - Tracer*: pointer to handle of tracer object created
    /// 
    /// @throws result_t
    Tracer* __zecall
    Tracer::Create(
        Driver* pDriver,                                ///< [in] pointer to the driver
        const desc_t* desc                              ///< [in] pointer to tracer descriptor
        )
    {
        zet_tracer_handle_t hTracer;

        auto result = static_cast<result_t>( ::zetTracerCreate(
            reinterpret_cast<zet_driver_handle_t>( pDriver->getHandle() ),
            reinterpret_cast<const zet_tracer_desc_t*>( desc ),
            &hTracer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Tracer::Create" );

        Tracer* pTracer = nullptr;

        try
        {
            pTracer = new Tracer( reinterpret_cast<tracer_handle_t>( hTracer ), pDriver, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pTracer;
            pTracer = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "zet::Tracer::Create" );
        }

        return pTracer;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys a tracer.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same tracer handle.
    ///     - The implementation of this function will stall and wait on any
    ///       outstanding threads executing callbacks before freeing any Host
    ///       allocations associated with this tracer.
    /// 
    /// @throws result_t
    void __zecall
    Tracer::Destroy(
        Tracer* pTracer                                 ///< [in][release] pointer to tracer object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zetTracerDestroy(
            reinterpret_cast<zet_tracer_handle_t>( pTracer->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Tracer::Destroy" );

        delete pTracer;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sets the collection of callbacks to be executed **before** driver
    ///        execution.
    /// 
    /// @details
    ///     - The application only needs to set the function pointers it is
    ///       interested in receiving; all others should be 'nullptr'
    ///     - The application must ensure that no other threads are executing
    ///       functions for which the tracing functions are changing.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same tracer handle.
    /// 
    /// @throws result_t
    void __zecall
    Tracer::SetPrologues(
        core_callbacks_t* pCoreCbs,                     ///< [in] pointer to table of 'core' callback function pointers
        experimental_callbacks_t* pExperimentalCbs      ///< [in][optional] pointer to table of 'experimental' callback function
                                                        ///< pointers
        )
    {
        auto result = static_cast<result_t>( ::zetTracerSetPrologues(
            reinterpret_cast<zet_tracer_handle_t>( getHandle() ),
            reinterpret_cast<zet_core_callbacks_t*>( pCoreCbs ),
            reinterpret_cast<zet_experimental_callbacks_t*>( pExperimentalCbs ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Tracer::SetPrologues" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sets the collection of callbacks to be executed **after** driver
    ///        execution.
    /// 
    /// @details
    ///     - The application only needs to set the function pointers it is
    ///       interested in receiving; all others should be 'nullptr'
    ///     - The application must ensure that no other threads are executing
    ///       functions for which the tracing functions are changing.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same tracer handle.
    /// 
    /// @throws result_t
    void __zecall
    Tracer::SetEpilogues(
        core_callbacks_t* pCoreCbs,                     ///< [in] pointer to table of 'core' callback function pointers
        experimental_callbacks_t* pExperimentalCbs      ///< [in][optional] pointer to table of 'experimental' callback function
                                                        ///< pointers
        )
    {
        auto result = static_cast<result_t>( ::zetTracerSetEpilogues(
            reinterpret_cast<zet_tracer_handle_t>( getHandle() ),
            reinterpret_cast<zet_core_callbacks_t*>( pCoreCbs ),
            reinterpret_cast<zet_experimental_callbacks_t*>( pExperimentalCbs ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Tracer::SetEpilogues" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Enables (or disables) the tracer
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same tracer handle.
    /// 
    /// @throws result_t
    void __zecall
    Tracer::SetEnabled(
        ze::bool_t enable                               ///< [in] enable the tracer if true; disable if false
        )
    {
        auto result = static_cast<result_t>( ::zetTracerSetEnabled(
            reinterpret_cast<zet_tracer_handle_t>( getHandle() ),
            static_cast<ze_bool_t>( enable ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Tracer::SetEnabled" );
    }

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Tracer::desc_version_t to std::string
    std::string to_string( const Tracer::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Tracer::desc_version_t::CURRENT:
            str = "Tracer::desc_version_t::CURRENT";
            break;

        default:
            str = "Tracer::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Tracer::desc_t to std::string
    std::string to_string( const Tracer::desc_t val )
    {
        std::string str;
        
        str += "Tracer::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Tracer::desc_t::pUserData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pUserData);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

} // namespace zet
