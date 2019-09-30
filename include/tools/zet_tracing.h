/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_tracing.h
 *
 * @brief Intel 'One API' Level-Zero Tool APIs for API Tracing
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/tracing.yml
 * @endcond
 *
 */
#ifndef _ZET_TRACING_H
#define _ZET_TRACING_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_ZET_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif
#include "ze_callbacks.h"
#include "zex_callbacks.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Alias the existing callbacks definition for 'core' callbacks
typedef ze_callbacks_t zet_core_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Alias the existing callbacks definition for 'experimental' callbacks
typedef zex_callbacks_t zet_experimental_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::zet_tracer_desc_t
typedef enum _zet_tracer_desc_version_t
{
    ZET_TRACER_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),  ///< version 1.0

} zet_tracer_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Tracer descriptor
typedef struct _zet_tracer_desc_t
{
    zet_tracer_desc_version_t version;              ///< [in] ::ZET_TRACER_DESC_VERSION_CURRENT
    void* pUserData;                                ///< [in] pointer passed to every tracer's callbacks

} zet_tracer_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a tracer for the specified device.
/// 
/// @details
///     - The tracer can only be used on the device on which it was created.
///     - The tracer is created in the disabled state.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == desc
///         + nullptr == phTracer
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + ::ZET_TRACER_DESC_VERSION_CURRENT < desc->version
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
ze_result_t __zecall
zetTracerCreate(
    zet_device_handle_t hDevice,                    ///< [in] handle of the device
    const zet_tracer_desc_t* desc,                  ///< [in] pointer to tracer descriptor
    zet_tracer_handle_t* phTracer                   ///< [out] pointer to handle of tracer object created
    );

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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hTracer
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetTracerDestroy(
    zet_tracer_handle_t hTracer                     ///< [in][release] handle of tracer object to destroy
    );

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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hTracer
///         + nullptr == pCoreCbs
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetTracerSetPrologues(
    zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
    zet_core_callbacks_t* pCoreCbs,                 ///< [in] pointer to table of 'core' callback function pointers
    zet_experimental_callbacks_t* pExperimentalCbs  ///< [in][optional] pointer to table of 'experimental' callback function
                                                    ///< pointers
    );

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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hTracer
///         + nullptr == pCoreCbs
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetTracerSetEpilogues(
    zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
    zet_core_callbacks_t* pCoreCbs,                 ///< [in] pointer to table of 'core' callback function pointers
    zet_experimental_callbacks_t* pExperimentalCbs  ///< [in][optional] pointer to table of 'experimental' callback function
                                                    ///< pointers
    );

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
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hTracer
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zetTracerSetEnabled(
    zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
    ze_bool_t enable                                ///< [in] enable the tracer if true; disable if false
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZET_TRACING_H
