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
* @file xe_umd_api.h
* 
* @brief Intel Xe User-Mode Driver API
* 
******************************************************************************/
#ifndef _XE_UMD_API_H
#define _XE_UMD_API_H
#if defined( __cplusplus )
#pragma once
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Calling convention for all APIs
#define __xecall __stdcall

///////////////////////////////////////////////////////////////////////////////
/// @brief Declares a strongly typed handle
#if defined( __cplusplus )
#define DECLARE_HANDLE( NAME )  \
    struct NAME                 \
    {                           \
        void* pDriverData;      \
                                \
        NAME( void ) : pDriverData( nullptr ) {}        \
        explicit NAME( void* p ) : pDriverData( p ) {}  \
                                \
        inline bool operator==( const NAME& other ) const { return pDriverData == other.pDriverData; } \
        inline bool operator!=( const NAME& other ) const { return pDriverData != other.pDriverData; } \
    };
#else
#define DECLARE_HANDLE( NAME )  \
    typedef struct _NAME        \
    {                           \
        void* pDriverData;      \
    } NAME;
#endif

DECLARE_HANDLE( xe_device_handle_t );
DECLARE_HANDLE( xe_command_queue_handle_t );
DECLARE_HANDLE( xe_command_list_handle_t );
DECLARE_HANDLE( xe_event_handle_t );
DECLARE_HANDLE( xe_resource_handle_t );


///////////////////////////////////////////////////////////////////////////////
/// @brief Defines Return/Error codes
enum xe_result_t : uint32_t
{
    XE_RESULT_SUCCESS = 0,             ///< success
    XE_RESULT_ERROR_INVALID_PARAMETER, ///< invalid parameter provided
    XE_RESULT_ERROR_OUT_OF_MEMORY,     ///< insufficient memory to satisfy call
    XE_RESULT_ERROR_UNKNOWN = -1       ///< internal error
};


///////////////////////////////////////////////////////////////////////////////
/// @brief Device creation flags
enum xe_device_flags : uint32_t
{
    XE_DEVICE_FLAG_NONE = 0            ///< default behavior
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Device descriptor
typedef struct _xe_device_desc
{
    xe_device_flags flags;             ///< [in] creation flags
} xe_device_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a device object
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeCreateDevice( 
    xe_device_desc_t desc,             ///< [in] device descriptor
    xe_device_handle_t* phDevice       ///< [out] pointer to handle of device object created
    );
    
///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a device object
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeDestroyDevice(
    xe_device_handle_t hDevice         ///< [in] handle of device object to destroy
    );


///////////////////////////////////////////////////////////////////////////////
/// @brief Command Queue creation flags
enum xe_command_queue_flags : uint32_t
{
    XE_COMMAND_QUEUE_FLAG_NONE = 0             ///< default behavior
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Command Queue descriptor
typedef struct _xe_command_queue_desc_t
{
    xe_command_queue_flags flags;              ///< [in] creation flags
} xe_command_queue_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command queue
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeCreateCommandQueue(
    xe_device_handle_t hDevice,                ///< [in] handle of the device
    xe_command_queue_desc_t desc,              ///< [in] command queue descriptor
    xe_command_queue_handle_t* phCommandQueue  ///< [out] pointer to handle of command queue object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command queue
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeDestroyCommandQueue(
    xe_device_handle_t hDevice,                ///< [in] handle of the device
    xe_command_queue_handle_t hCommandQueue    ///< [in] handle of command queue object to destroy
    );


///////////////////////////////////////////////////////////////////////////////
/// @brief Command List creation flags
enum xe_command_list_flags : uint32_t
{
    XE_COMMAND_LIST_FLAG_NONE = 0              ///< default behavior
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Command List descriptor
typedef struct _xe_command_list_desc_t
{
    xe_command_list_flags flags;               ///< [in] creation flags
} xe_command_list_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command list
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeCreateCommandList(
    xe_device_handle_t hDevice,                ///< [in] handle of the device
    xe_command_list_desc_t desc,               ///< [in] command list descriptor
    xe_command_list_handle_t* phCommandList    ///< [out] pointer to handle of command list object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command list
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeDestroyCommandList(
    xe_device_handle_t hDevice,                ///< [in] handle of the device
    xe_command_list_handle_t hCommandList      ///< [in] handle of command list object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Enqueues a command list to a command queue
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeEnqueueCommandList(
    xe_command_queue_handle_t hCommandQueue,   ///< [in] handle of the command queue
    xe_command_list_handle_t hCommandList      ///< [in] handle of the command list to execute
    );


///////////////////////////////////////////////////////////////////////////////
/// @brief Event creation flags
enum xe_event_flags : uint32_t
{
    XE_EVENT_FLAG_NONE = 0                 ///< default behavior
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Event descriptor
typedef struct _xe_event_desc_t
{
    xe_event_flags flags;                  ///< [in] creation flags
} xe_event_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an event object
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeCreateEvent( 
    xe_device_handle_t hDevice,            ///< [in] handle of the device
    xe_event_desc_t desc,                  ///< [in] event descriptor
    xe_event_handle_t* phEvent             ///< [out] pointer to handle of event object created
    );
    
///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes an event object
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeDestroyEvent(
    xe_device_handle_t hDevice,            ///< [in] handle of the device
    xe_event_handle_t hEvent               ///< [in] handle of event object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes an event object into a command list
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeEncodeEvent(
    xe_command_list_handle_t hCommandList, ///< [in] handle of the command list
    xe_event_handle_t hEvent               ///< [in] handle of the event 
    );
    

///////////////////////////////////////////////////////////////////////////////
/// @brief Resource creation flags
enum xe_resource_flags : uint32_t
{
    XE_RESOURCE_FLAG_NONE = 0          ///< default behavior
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Resource descriptor
typedef struct _xe_resource_desc_t
{
    xe_resource_flags flags;           ///< [in] creation flags
} xe_resource_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a resource object
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeCreateResource( 
    xe_device_handle_t hDevice,        ///< [in] handle of the device
    xe_resource_desc_t desc,           ///< [in] resource descriptor
    xe_resource_handle_t* phResource   ///< [out] pointer to handle of resource object created
    );
    
///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a resource object
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeDestroyResource(
    xe_device_handle_t hDevice,        ///< [in] handle of the device
    xe_resource_handle_t hResource     ///< [in] handle of resource object to destroy
    );


#endif // _XE_UMD_API_H