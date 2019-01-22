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
* @file xe_common.h
*
* @brief Intel Xe Driver API common types
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/common.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_COMMON_H
#define _XE_COMMON_H
#if defined(__cplusplus)
#pragma once
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Generates generic Xe API versions
#define XE_MAKE_VERSION( _major, _minor )  (( _major << 16 )|( _minor & 0x0000ffff))

///////////////////////////////////////////////////////////////////////////////
/// @brief Extracts Xe API major version
#define XE_MAJOR_VERSION( _ver )  ( _ver >> 16 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Extracts Xe API minor version
#define XE_MINOR_VERSION( _ver )  ( _ver & 0x0000ffff )

///////////////////////////////////////////////////////////////////////////////
/// @brief Current header file version
#define XE_UMD_HEADER_VERSION  XE_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Calling convention for all API functions
#if defined(_WIN32)
#define __xecall  __stdcall
#else
#define __xecall
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's device object
#if defined( __cplusplus )
struct xe_device_handle_t
{
    void* pDriverData;

    xe_device_handle_t( void ) : pDriverData( nullptr ) {}        ///< default constructor
    explicit xe_device_handle_t( void* p ) : pDriverData( p ) {}  ///< initialize from pointer

    inline bool operator==( const xe_device_handle_t& other ) const   ///< is equal to other
    { return pDriverData == other.pDriverData; }
    inline bool operator!=( const xe_device_handle_t& other ) const   ///< not equal to other
    { return pDriverData != other.pDriverData; }

};
#else
typedef struct _xe_device_handle_t
{
    void* pDriverData;

} xe_device_handle_t;
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's command queue object
#if defined( __cplusplus )
struct xe_command_queue_handle_t
{
    void* pDriverData;

    xe_command_queue_handle_t( void ) : pDriverData( nullptr ) {}        ///< default constructor
    explicit xe_command_queue_handle_t( void* p ) : pDriverData( p ) {}  ///< initialize from pointer

    inline bool operator==( const xe_command_queue_handle_t& other ) const   ///< is equal to other
    { return pDriverData == other.pDriverData; }
    inline bool operator!=( const xe_command_queue_handle_t& other ) const   ///< not equal to other
    { return pDriverData != other.pDriverData; }

};
#else
typedef struct _xe_command_queue_handle_t
{
    void* pDriverData;

} xe_command_queue_handle_t;
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's command list object
#if defined( __cplusplus )
struct xe_command_list_handle_t
{
    void* pDriverData;

    xe_command_list_handle_t( void ) : pDriverData( nullptr ) {}        ///< default constructor
    explicit xe_command_list_handle_t( void* p ) : pDriverData( p ) {}  ///< initialize from pointer

    inline bool operator==( const xe_command_list_handle_t& other ) const   ///< is equal to other
    { return pDriverData == other.pDriverData; }
    inline bool operator!=( const xe_command_list_handle_t& other ) const   ///< not equal to other
    { return pDriverData != other.pDriverData; }

};
#else
typedef struct _xe_command_list_handle_t
{
    void* pDriverData;

} xe_command_list_handle_t;
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's fence object
#if defined( __cplusplus )
struct xe_fence_handle_t
{
    void* pDriverData;

    xe_fence_handle_t( void ) : pDriverData( nullptr ) {}        ///< default constructor
    explicit xe_fence_handle_t( void* p ) : pDriverData( p ) {}  ///< initialize from pointer

    inline bool operator==( const xe_fence_handle_t& other ) const   ///< is equal to other
    { return pDriverData == other.pDriverData; }
    inline bool operator!=( const xe_fence_handle_t& other ) const   ///< not equal to other
    { return pDriverData != other.pDriverData; }

};
#else
typedef struct _xe_fence_handle_t
{
    void* pDriverData;

} xe_fence_handle_t;
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's semaphore object
#if defined( __cplusplus )
struct xe_semaphore_handle_t
{
    void* pDriverData;

    xe_semaphore_handle_t( void ) : pDriverData( nullptr ) {}        ///< default constructor
    explicit xe_semaphore_handle_t( void* p ) : pDriverData( p ) {}  ///< initialize from pointer

    inline bool operator==( const xe_semaphore_handle_t& other ) const   ///< is equal to other
    { return pDriverData == other.pDriverData; }
    inline bool operator!=( const xe_semaphore_handle_t& other ) const   ///< not equal to other
    { return pDriverData != other.pDriverData; }

};
#else
typedef struct _xe_semaphore_handle_t
{
    void* pDriverData;

} xe_semaphore_handle_t;
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's event object
#if defined( __cplusplus )
struct xe_event_handle_t
{
    void* pDriverData;

    xe_event_handle_t( void ) : pDriverData( nullptr ) {}        ///< default constructor
    explicit xe_event_handle_t( void* p ) : pDriverData( p ) {}  ///< initialize from pointer

    inline bool operator==( const xe_event_handle_t& other ) const   ///< is equal to other
    { return pDriverData == other.pDriverData; }
    inline bool operator!=( const xe_event_handle_t& other ) const   ///< not equal to other
    { return pDriverData != other.pDriverData; }

};
#else
typedef struct _xe_event_handle_t
{
    void* pDriverData;

} xe_event_handle_t;
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's resource object
#if defined( __cplusplus )
struct xe_resource_handle_t
{
    void* pDriverData;

    xe_resource_handle_t( void ) : pDriverData( nullptr ) {}        ///< default constructor
    explicit xe_resource_handle_t( void* p ) : pDriverData( p ) {}  ///< initialize from pointer

    inline bool operator==( const xe_resource_handle_t& other ) const   ///< is equal to other
    { return pDriverData == other.pDriverData; }
    inline bool operator!=( const xe_resource_handle_t& other ) const   ///< not equal to other
    { return pDriverData != other.pDriverData; }

};
#else
typedef struct _xe_resource_handle_t
{
    void* pDriverData;

} xe_resource_handle_t;
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's module object
#if defined( __cplusplus )
struct xe_module_handle_t
{
    void* pDriverData;

    xe_module_handle_t( void ) : pDriverData( nullptr ) {}        ///< default constructor
    explicit xe_module_handle_t( void* p ) : pDriverData( p ) {}  ///< initialize from pointer

    inline bool operator==( const xe_module_handle_t& other ) const   ///< is equal to other
    { return pDriverData == other.pDriverData; }
    inline bool operator!=( const xe_module_handle_t& other ) const   ///< not equal to other
    { return pDriverData != other.pDriverData; }

};
#else
typedef struct _xe_module_handle_t
{
    void* pDriverData;

} xe_module_handle_t;
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's function object
#if defined( __cplusplus )
struct xe_function_handle_t
{
    void* pDriverData;

    xe_function_handle_t( void ) : pDriverData( nullptr ) {}        ///< default constructor
    explicit xe_function_handle_t( void* p ) : pDriverData( p ) {}  ///< initialize from pointer

    inline bool operator==( const xe_function_handle_t& other ) const   ///< is equal to other
    { return pDriverData == other.pDriverData; }
    inline bool operator!=( const xe_function_handle_t& other ) const   ///< not equal to other
    { return pDriverData != other.pDriverData; }

};
#else
typedef struct _xe_function_handle_t
{
    void* pDriverData;

} xe_function_handle_t;
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Generic macro for enumerator bit masks
#define XE_BIT( _i )  ( 1 << _i )

///////////////////////////////////////////////////////////////////////////////
/// @brief Defines Return/Error codes
/// @remarks
///   _Analogues_
///     - **CUresult**
typedef enum _xe_result_t
{
    XE_RESULT_SUCCESS = 0,                          ///< success
    XE_RESULT_NOT_READY = 1,                        ///< synchronization primitive not signaled
    XE_RESULT_ERROR_UNINITIALIZED,                  ///< driver is not initialized
    XE_RESULT_ERROR_UNSUPPORTED,                    ///< device does not support feature requested
    XE_RESULT_ERROR_INVALID_PARAMETER,              ///< invalid parameter provided
    XE_RESULT_ERROR_OUT_OF_HOST_MEMORY,             ///< insufficient host memory to satisfy call
    XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY,           ///< insufficient device memory to satisfy call
    XE_RESULT_ERROR_UNKNOWN = 0x7fffffff,           ///< unknown or internal error

} xe_result_t;

#endif // _XE_COMMON_H
