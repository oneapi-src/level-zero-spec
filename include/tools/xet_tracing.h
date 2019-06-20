/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xet_tracing.h
 *
 * @brief Intel 'One API' Level-Zero Tool APIs for API Tracing
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/tracing.yml
 * @endcond
 *
 */
#ifndef _XET_TRACING_H
#define _XET_TRACING_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_XET_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif
#include "xe_callbacks.h"
#include "xex_callbacks.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Alias the existing callbacks definition for 'core' callbacks
typedef xe_callbacks_t xet_core_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Alias the existing callbacks definition for 'experimental' callbacks
typedef xex_callbacks_t xet_experimental_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xet_tracer_desc_t
typedef enum _xet_tracer_desc_version_t
{
    XET_TRACER_DESC_VERSION_CURRENT = XE_MAKE_VERSION( 1, 0 ),  ///< version 1.0

} xet_tracer_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Tracer descriptor
typedef struct _xet_tracer_desc_t
{
    xet_tracer_desc_version_t version;              ///< [in] ::XET_TRACER_DESC_VERSION_CURRENT
    void* pGlobalUserData;                          ///< [in] pointer to global data passes to every callback

} xet_tracer_desc_t;

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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a tracer.
/// 
/// @details
///     - The implementation of this function will stall and wait on any
///       outstanding threads executing callbacks before freeing any Host
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
    xet_experimental_callbacks_t* pExperimentalCbs  ///< [in][optional] pointer to table of 'experimental' callback function
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
    xet_experimental_callbacks_t* pExperimentalCbs  ///< [in][optional] pointer to table of 'experimental' callback function
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
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XET_TRACING_H
