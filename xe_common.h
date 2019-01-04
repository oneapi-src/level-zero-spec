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
******************************************************************************/
#ifndef _XE_COMMON_H
#define _XE_COMMON_H
#if defined( __cplusplus )
#pragma once
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Generic macros for creating and extracting versions
#define XE_MAKE_VERSION( MAJOR, MINOR ) (( MAJOR << 16 )|( MINOR & 0x0000ffff))
#define XE_MAJOR_VERSION( V ) ( V >> 16 )
#define XE_MINOR_VERSION( V ) ( V & 0x0000ffff )

///////////////////////////////////////////////////////////////////////////////
/// @brief Current header file version
#define XE_UMD_HEADER_VERSION   XE_MAKE_VERSION( 1, 0 ) ///< 1.0

///////////////////////////////////////////////////////////////////////////////
#if !defined( __cplusplus )
/// @brief Declare C++ types
typedef unsigned int uint32_t;
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Calling convention for all APIs
#define __xecall __stdcall


///////////////////////////////////////////////////////////////////////////////
/// @brief Declares a strongly typed handle
#if defined( __cplusplus )
#define XE_DECLARE_HANDLE( NAME )                                                       \
    struct NAME                                                                         \
    {                                                                                   \
        void* pDriverData;          /*!< pointer to driver object (opaque)*/            \
                                                                                        \
        NAME( void ) : pDriverData( nullptr ) {}        /*!< default constructor */     \
        explicit NAME( void* p ) : pDriverData( p ) {}  /*!< initialize from pointer */ \
                                                                                        \
        inline bool operator==( const NAME& other ) const   /*!< is equal to other */   \
        { return pDriverData == other.pDriverData; }                                    \
        inline bool operator!=( const NAME& other ) const   /*!< not equal to other */  \
        { return pDriverData != other.pDriverData; }                                    \
    }
#else
#define XE_DECLARE_HANDLE( NAME )   \
    typedef struct _NAME            \
    {                               \
        void* pDriverData;          \
    } NAME
#endif

///////////////////////////////////////////////////////////////////////////////
XE_DECLARE_HANDLE( xe_device_handle_t );            ///< handle of driver's device object
XE_DECLARE_HANDLE( xe_command_queue_handle_t );     ///< handle of driver's command queue object
XE_DECLARE_HANDLE( xe_command_list_handle_t );      ///< handle of driver's command list object
XE_DECLARE_HANDLE( xe_event_handle_t );             ///< handle of driver's event object
XE_DECLARE_HANDLE( xe_resource_handle_t );          ///< handle of driver's resource object


///////////////////////////////////////////////////////////////////////////////
/// @brief Declares typed enumeration
#if defined( __cplusplus )
#define XE_DECLARE_ENUM( NAME ) \
    enum NAME : uint32_t
#else
#define XE_DECLARE_ENUM( NAME ) \
    typedef uint32_t NAME;  \
    enum _##NAME
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Generic macros for enumerator bit masks
#define XE_BIT( N ) ( 1 << N )


///////////////////////////////////////////////////////////////////////////////
/// @brief Defines Return/Error codes
/// @remarks _Analogues:_
///     - **CUresult**
XE_DECLARE_ENUM( xe_result_t )
{
    XE_RESULT_SUCCESS = 0,                  ///< success
    XE_RESULT_ERROR_INVALID_PARAMETER,      ///< invalid parameter provided
    XE_RESULT_ERROR_OUT_OF_MEMORY,          ///< insufficient memory to satisfy call
    XE_RESULT_ERROR_UNKNOWN = 0xffffffff    ///< internal error
};


#endif // _XE_COMMON_H