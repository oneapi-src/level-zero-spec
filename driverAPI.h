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
* @file driverAPI.h
* 
* @brief Intel "One API" Driver API
* 
******************************************************************************/
#ifndef _DRIVER_API_H
#define _DRIVER_API_H
#if defined( __cplusplus )
#pragma once
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Calling convention for all APIs
#define IOA_ENTRY __stdcall

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

DECLARE_HANDLE( ioa_device_handle_t );
DECLARE_HANDLE( ioa_command_queue_handle_t );
DECLARE_HANDLE( ioa_command_list_handle_t );
DECLARE_HANDLE( ioa_event_handle_t );
DECLARE_HANDLE( ioa_resource_handle_t );


///////////////////////////////////////////////////////////////////////////////
/// @brief Defines Return/Error codes
enum ioa_result_t : uint32_t
{
    IOA_RESULT_SUCCESS = 0,             ///< success
    IOA_RESULT_ERROR_INVALID_PARAMETER, ///< invalid parameter provided
    IOA_RESULT_ERROR_OUT_OF_MEMORY,     ///< insufficient memory to satisfy call
    IOA_RESULT_ERROR_UNKNOWN = -1       ///< internal error
};


///////////////////////////////////////////////////////////////////////////////
/// @brief Device creation flags
enum ioa_device_flags : uint32_t
{
    IOA_DEVICE_FLAG_NONE = 0            ///< default behavior
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Device descriptor
typedef struct _ioa_device_desc
{
    ioa_device_flags flags;             ///< [in] creation flags
} ioa_device_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a device object
/// @returns IOA_RESULT_SUCCESS, ...
ioa_result_t IOA_ENTRY
  ioaCreateDevice( 
    ioa_device_desc_t desc,             ///< [in] device descriptor
    ioa_device_handle_t* phDevice       ///< [out] pointer to handle of device object created
    );
    
///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a device object
/// @returns IOA_RESULT_SUCCESS, ...
ioa_result_t IOA_ENTRY
  ioaDestroyDevice(
    ioa_device_handle_t hDevice         ///< [in] handle of device object to destroy
    );


///////////////////////////////////////////////////////////////////////////////
/// @brief Command Queue creation flags
enum ioa_command_queue_flags : uint32_t
{
    IOA_COMMAND_QUEUE_FLAG_NONE = 0             ///< default behavior
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Command Queue descriptor
typedef struct _ioa_command_queue_desc_t
{
    ioa_command_queue_flags flags;              ///< [in] creation flags
} ioa_command_queue_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command queue
/// @returns IOA_RESULT_SUCCESS, ...
ioa_result_t IOA_ENTRY
  ioaCreateCommandQueue(
    ioa_device_handle_t hDevice,                ///< [in] handle of the device
    ioa_command_queue_desc_t desc,              ///< [in] command queue descriptor
    ioa_command_queue_handle_t* phCommandQueue  ///< [out] pointer to handle of command queue object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command queue
/// @returns IOA_RESULT_SUCCESS, ...
ioa_result_t IOA_ENTRY
  ioaDestroyCommandQueue(
    ioa_device_handle_t hDevice,                ///< [in] handle of the device
    ioa_command_queue_handle_t hCommandQueue    ///< [in] handle of command queue object to destroy
    );


///////////////////////////////////////////////////////////////////////////////
/// @brief Command List creation flags
enum ioa_command_list_flags : uint32_t
{
    IOA_COMMAND_LIST_FLAG_NONE = 0              ///< default behavior
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Command List descriptor
typedef struct _ioa_command_list_desc_t
{
    ioa_command_list_flags flags;               ///< [in] creation flags
} ioa_command_list_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command list
/// @returns IOA_RESULT_SUCCESS, ...
ioa_result_t IOA_ENTRY
  ioaCreateCommandList(
    ioa_device_handle_t hDevice,                ///< [in] handle of the device
    ioa_command_list_desc_t desc,               ///< [in] command list descriptor
    ioa_command_list_handle_t* phCommandList    ///< [out] pointer to handle of command list object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command list
/// @returns IOA_RESULT_SUCCESS, ...
ioa_result_t IOA_ENTRY
  ioaDestroyCommandList(
    ioa_device_handle_t hDevice,                ///< [in] handle of the device
    ioa_command_list_handle_t hCommandList      ///< [in] handle of command list object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Enqueues a command list to a command queue
/// @returns IOA_RESULT_SUCCESS, ...
ioa_result_t IOA_ENTRY
  ioaEnqueueCommandList(
    ioa_command_queue_handle_t hCommandQueue,   ///< [in] handle of the command queue
    ioa_command_list_handle_t hCommandList      ///< [in] handle of the command list to execute
    );


///////////////////////////////////////////////////////////////////////////////
/// @brief Event creation flags
enum ioa_event_flags : uint32_t
{
    IOA_EVENT_FLAG_NONE = 0                 ///< default behavior
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Event descriptor
typedef struct _ioa_event_desc_t
{
    ioa_event_flags flags;                  ///< [in] creation flags
} ioa_event_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an event object
/// @returns IOA_RESULT_SUCCESS, ...
ioa_result_t IOA_ENTRY
  ioaCreateEvent( 
    ioa_device_handle_t hDevice,            ///< [in] handle of the device
    ioa_event_desc_t desc,                  ///< [in] event descriptor
    ioa_event_handle_t* phEvent             ///< [out] pointer to handle of event object created
    );
    
///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes an event object
/// @returns IOA_RESULT_SUCCESS, ...
ioa_result_t IOA_ENTRY
  ioaDestroyEvent(
    ioa_device_handle_t hDevice,            ///< [in] handle of the device
    ioa_event_handle_t hEvent               ///< [in] handle of event object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes an event object into a command list
/// @returns IOA_RESULT_SUCCESS, ...
ioa_result_t IOA_ENTRY
  ioaEncodeEvent(
    ioa_command_list_handle_t hCommandList, ///< [in] handle of the command list
    ioa_event_handle_t hEvent               ///< [in] handle of the event 
    );
    

///////////////////////////////////////////////////////////////////////////////
/// @brief Resource creation flags
enum ioa_resource_flags : uint32_t
{
    IOA_RESOURCE_FLAG_NONE = 0          ///< default behavior
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Resource descriptor
typedef struct _ioa_resource_desc_t
{
    ioa_resource_flags flags;           ///< [in] creation flags
} ioa_resource_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a resource object
/// @returns IOA_RESULT_SUCCESS, ...
ioa_result_t IOA_ENTRY
  ioaCreateResource( 
    ioa_device_handle_t hDevice,        ///< [in] handle of the device
    ioa_resource_desc_t desc,           ///< [in] resource descriptor
    ioa_resource_handle_t* phResource   ///< [out] pointer to handle of resource object created
    );
    
///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a resource object
/// @returns IOA_RESULT_SUCCESS, ...
ioa_result_t IOA_ENTRY
  ioaDestroyResource(
    ioa_device_handle_t hDevice,        ///< [in] handle of the device
    ioa_resource_handle_t hResource     ///< [in] handle of resource object to destroy
    );


#endif // _DRIVER_API_H