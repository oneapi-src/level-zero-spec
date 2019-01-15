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
* @file xi_common.h
*
* @brief Intel Xi Runtime API common types
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/common.yml
* @endcond
*
******************************************************************************/
#ifndef _XI_COMMON_H
#define _XI_COMMON_H
#if defined(__cplusplus)
#pragma once
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Generates generic Xi API versions
#define XI_MAKE_VERSION( _major, _minor )  (( _major << 16 )|( _minor & 0x0000ffff))

///////////////////////////////////////////////////////////////////////////////
/// @brief Extracts Xi API major version
#define XI_MAJOR_VERSION( _ver )  ( _ver >> 16 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Extracts Xi API minor version
#define XI_MINOR_VERSION( _ver )  ( _ver & 0x0000ffff )

///////////////////////////////////////////////////////////////////////////////
/// @brief Current header file version
#define XI_UMD_HEADER_VERSION  XI_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Calling convention for all API functions
#if defined(_WIN32)
#define __xicall  __stdcall
#else
#define __xicall
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of runtime's context object
#if defined( __cplusplus )
struct xi_context_handle_t
{
    void* pDriverData;

    xi_context_handle_t( void ) : pDriverData( nullptr ) {}        ///< default constructor
    explicit xi_context_handle_t( void* p ) : pDriverData( p ) {}  ///< initialize from pointer

    inline bool operator==( const xi_context_handle_t& other ) const   ///< is equal to other
    { return pDriverData == other.pDriverData; }
    inline bool operator!=( const xi_context_handle_t& other ) const   ///< not equal to other
    { return pDriverData != other.pDriverData; }

};
#else
typedef struct _xi_context_handle_t
{
    void* pDriverData;

} xi_context_handle_t;
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of runtime's device object
#if defined( __cplusplus )
struct xi_device_handle_t
{
    void* pDriverData;

    xi_device_handle_t( void ) : pDriverData( nullptr ) {}        ///< default constructor
    explicit xi_device_handle_t( void* p ) : pDriverData( p ) {}  ///< initialize from pointer

    inline bool operator==( const xi_device_handle_t& other ) const   ///< is equal to other
    { return pDriverData == other.pDriverData; }
    inline bool operator!=( const xi_device_handle_t& other ) const   ///< not equal to other
    { return pDriverData != other.pDriverData; }

};
#else
typedef struct _xi_device_handle_t
{
    void* pDriverData;

} xi_device_handle_t;
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of runtime's command queue object
#if defined( __cplusplus )
struct xi_command_queue_handle_t
{
    void* pDriverData;

    xi_command_queue_handle_t( void ) : pDriverData( nullptr ) {}        ///< default constructor
    explicit xi_command_queue_handle_t( void* p ) : pDriverData( p ) {}  ///< initialize from pointer

    inline bool operator==( const xi_command_queue_handle_t& other ) const   ///< is equal to other
    { return pDriverData == other.pDriverData; }
    inline bool operator!=( const xi_command_queue_handle_t& other ) const   ///< not equal to other
    { return pDriverData != other.pDriverData; }

};
#else
typedef struct _xi_command_queue_handle_t
{
    void* pDriverData;

} xi_command_queue_handle_t;
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of runtime's command list object
#if defined( __cplusplus )
struct xi_command_list_handle_t
{
    void* pDriverData;

    xi_command_list_handle_t( void ) : pDriverData( nullptr ) {}        ///< default constructor
    explicit xi_command_list_handle_t( void* p ) : pDriverData( p ) {}  ///< initialize from pointer

    inline bool operator==( const xi_command_list_handle_t& other ) const   ///< is equal to other
    { return pDriverData == other.pDriverData; }
    inline bool operator!=( const xi_command_list_handle_t& other ) const   ///< not equal to other
    { return pDriverData != other.pDriverData; }

};
#else
typedef struct _xi_command_list_handle_t
{
    void* pDriverData;

} xi_command_list_handle_t;
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of runtime's fence object
#if defined( __cplusplus )
struct xi_fence_handle_t
{
    void* pDriverData;

    xi_fence_handle_t( void ) : pDriverData( nullptr ) {}        ///< default constructor
    explicit xi_fence_handle_t( void* p ) : pDriverData( p ) {}  ///< initialize from pointer

    inline bool operator==( const xi_fence_handle_t& other ) const   ///< is equal to other
    { return pDriverData == other.pDriverData; }
    inline bool operator!=( const xi_fence_handle_t& other ) const   ///< not equal to other
    { return pDriverData != other.pDriverData; }

};
#else
typedef struct _xi_fence_handle_t
{
    void* pDriverData;

} xi_fence_handle_t;
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of runtime's resource object
#if defined( __cplusplus )
struct xi_resource_handle_t
{
    void* pDriverData;

    xi_resource_handle_t( void ) : pDriverData( nullptr ) {}        ///< default constructor
    explicit xi_resource_handle_t( void* p ) : pDriverData( p ) {}  ///< initialize from pointer

    inline bool operator==( const xi_resource_handle_t& other ) const   ///< is equal to other
    { return pDriverData == other.pDriverData; }
    inline bool operator!=( const xi_resource_handle_t& other ) const   ///< not equal to other
    { return pDriverData != other.pDriverData; }

};
#else
typedef struct _xi_resource_handle_t
{
    void* pDriverData;

} xi_resource_handle_t;
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Generic macro for enumerator bit masks
#define XI_BIT( _i )  ( 1 << _i )

///////////////////////////////////////////////////////////////////////////////
/// @brief Defines Return/Error codes
/// @remarks
///   _Analogues_
///     - **CUDAresult**
typedef enum _xi_result_t
{
    XI_RESULT_SUCCESS = 0,                          ///< success
    XI_RESULT_NOT_READY,                            ///< synchronization primitive not signaled
    XI_RESULT_ERROR_UNINITIALIZED,                  ///< runtime is not initialized
    XI_RESULT_ERROR_INVALID_PARAMETER,              ///< invalid parameter provided
    XI_RESULT_ERROR_OUT_OF_HOST_MEMORY,             ///< insufficient host memory to satisfy call
    XI_RESULT_ERROR_OUT_OF_DEVICE_MEMORY,           ///< insufficient device memory to satisfy call
    XI_RESULT_ERROR_UNKNOWN = 0x7fffffff,           ///< internal error

} xi_result_t;

#endif // _XI_COMMON_H
