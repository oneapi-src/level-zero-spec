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
* @file xet_tracing.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Tool APIs for API Tracing
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/tracing.yml
* @endcond
*
******************************************************************************/
#include "xet_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a tracer on the device group.
/// 
/// @details
///     - The tracer can only be used on the device group on which it was
///       created.
///     - The tracer is created in the disabled state.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDeviceGroup
///         + nullptr == desc
///         + nullptr == phTracer
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XET_TRACER_DESC_VERSION_CURRENT < desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
xe_result_t __xecall
xetTracerCreate(
    xet_device_group_handle_t hDeviceGroup,         ///< [in] handle of the device group
    const xet_tracer_desc_t* desc,                  ///< [in] pointer to tracer descriptor
    xet_tracer_handle_t* phTracer                   ///< [out] pointer to handle of tracer object created
    )
{
    auto pfnCreate = xet_lib::context.ddiTable.Tracer.pfnCreate;

#if _DEBUG
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnCreate( hDeviceGroup, desc, phTracer );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a tracer.
/// 
/// @details
///     - The application is responsible for making sure the driver is not
///       currently referencing the tracer before it is deleted.
///     - The implementation of this function will immediately free all Host
///       allocations associated with this tracer.
///     - The application may **not** call this function from simultaneous
///       threads with the same tracer handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hTracer
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetTracerDestroy(
    xet_tracer_handle_t hTracer                     ///< [in][release] handle of tracer object to destroy
    )
{
    auto pfnDestroy = xet_lib::context.ddiTable.Tracer.pfnDestroy;

#if _DEBUG
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hTracer
///         + nullptr == pCoreCbs
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetTracerSetPrologues(
    xet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
    xet_core_callbacks_t* pCoreCbs,                 ///< [in] pointer to table of 'core' callback function pointers
    xet_extended_callbacks_t* pExtendedCbs          ///< [in][optional] pointer to table of 'extended' callback function
                                                    ///< pointers
    )
{
    auto pfnSetPrologues = xet_lib::context.ddiTable.Tracer.pfnSetPrologues;

#if _DEBUG
    if( nullptr == pfnSetPrologues )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnSetPrologues( hTracer, pCoreCbs, pExtendedCbs );
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
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hTracer
///         + nullptr == pCoreCbs
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetTracerSetEpilogues(
    xet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
    xet_core_callbacks_t* pCoreCbs,                 ///< [in] pointer to table of 'core' callback function pointers
    xet_extended_callbacks_t* pExtendedCbs          ///< [in][optional] pointer to table of 'extended' callback function
                                                    ///< pointers
    )
{
    auto pfnSetEpilogues = xet_lib::context.ddiTable.Tracer.pfnSetEpilogues;

#if _DEBUG
    if( nullptr == pfnSetEpilogues )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnSetEpilogues( hTracer, pCoreCbs, pExtendedCbs );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Enables (or disables) the tracer
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same tracer handle.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hTracer
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetTracerSetEnabled(
    xet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
    xe_bool_t enable                                ///< [in] enable the tracer if true; disable if false
    )
{
    auto pfnSetEnabled = xet_lib::context.ddiTable.Tracer.pfnSetEnabled;

#if _DEBUG
    if( nullptr == pfnSetEnabled )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnSetEnabled( hTracer, enable );
}

} // extern "C"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    Tracer::Tracer( 
        tracer_handle_t handle,                         ///< [in] handle of tracer object
        DeviceGroup* pDeviceGroup,                      ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the tracer object
        ) :
        m_handle( handle ),
        m_pDeviceGroup( pDeviceGroup ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a tracer on the device group.
    /// 
    /// @details
    ///     - The tracer can only be used on the device group on which it was
    ///       created.
    ///     - The tracer is created in the disabled state.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - Tracer*: pointer to handle of tracer object created
    /// 
    /// @throws result_t
    Tracer* __xecall
    Tracer::Create(
        DeviceGroup* pDeviceGroup,                      ///< [in] pointer to the device group
        const desc_t* desc                              ///< [in] pointer to tracer descriptor
        )
    {
        xet_tracer_handle_t hTracer;

        auto result = static_cast<result_t>( ::xetTracerCreate(
            reinterpret_cast<xet_device_group_handle_t>( pDeviceGroup->getHandle() ),
            reinterpret_cast<const xet_tracer_desc_t*>( desc ),
            &hTracer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Tracer::Create" );

        Tracer* pTracer = nullptr;

        try
        {
            pTracer = new Tracer( reinterpret_cast<tracer_handle_t>( hTracer ), pDeviceGroup, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pTracer;
            pTracer = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xet::Tracer::Create" );
        }

        return pTracer;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys a tracer.
    /// 
    /// @details
    ///     - The application is responsible for making sure the driver is not
    ///       currently referencing the tracer before it is deleted.
    ///     - The implementation of this function will immediately free all Host
    ///       allocations associated with this tracer.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same tracer handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Tracer::Destroy(
        Tracer* pTracer                                 ///< [in][release] pointer to tracer object to destroy
        )
    {
        auto result = static_cast<result_t>( ::xetTracerDestroy(
            reinterpret_cast<xet_tracer_handle_t>( pTracer->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Tracer::Destroy" );

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
    void __xecall
    Tracer::SetPrologues(
        core_callbacks_t* pCoreCbs,                     ///< [in] pointer to table of 'core' callback function pointers
        extended_callbacks_t* pExtendedCbs              ///< [in][optional] pointer to table of 'extended' callback function
                                                        ///< pointers
        )
    {
        auto result = static_cast<result_t>( ::xetTracerSetPrologues(
            reinterpret_cast<xet_tracer_handle_t>( getHandle() ),
            reinterpret_cast<xet_core_callbacks_t*>( pCoreCbs ),
            reinterpret_cast<xet_extended_callbacks_t*>( pExtendedCbs ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Tracer::SetPrologues" );
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
    void __xecall
    Tracer::SetEpilogues(
        core_callbacks_t* pCoreCbs,                     ///< [in] pointer to table of 'core' callback function pointers
        extended_callbacks_t* pExtendedCbs              ///< [in][optional] pointer to table of 'extended' callback function
                                                        ///< pointers
        )
    {
        auto result = static_cast<result_t>( ::xetTracerSetEpilogues(
            reinterpret_cast<xet_tracer_handle_t>( getHandle() ),
            reinterpret_cast<xet_core_callbacks_t*>( pCoreCbs ),
            reinterpret_cast<xet_extended_callbacks_t*>( pExtendedCbs ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Tracer::SetEpilogues" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Enables (or disables) the tracer
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same tracer handle.
    /// 
    /// @throws result_t
    void __xecall
    Tracer::SetEnabled(
        xe::bool_t enable                               ///< [in] enable the tracer if true; disable if false
        )
    {
        auto result = static_cast<result_t>( ::xetTracerSetEnabled(
            reinterpret_cast<xet_tracer_handle_t>( getHandle() ),
            static_cast<xe_bool_t>( enable ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Tracer::SetEnabled" );
    }

} // namespace xet

namespace xet
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
        
        str += "Tracer::desc_t::pGlobalUserData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pGlobalUserData);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

} // namespace xet
