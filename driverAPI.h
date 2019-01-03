#ifndef _DRIVER_API_H
#define _DRIVER_API_H
#if defined( __cplusplus )
#pragma once
#endif

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
    };                          \
#else
#define DECLARE_HANDLE( NAME )  \
    typedef struct _NAME        \
    {                           \
        void* pDriverData;      \
    } NAME;                     \
#endif

DECLARE_HANDLE( $oa_device_handle_t );
DECLARE_HANDLE( $oa_command_queue_handle_t );
DECLARE_HANDLE( $oa_command_list_handle_t );
DECLARE_HANDLE( $oa_event_handle_t );
DECLARE_HANDLE( $oa_resource_handle_t );


///////////////////////////////////////////////////////////////////////////////
/// @brief Defines Return/Error codes
enum $oa_result_t : uint32_t
{
    $OA_RESULT_SUCCESS = 0,             ///< success
    $OA_RESULT_ERROR_INVALID_PARAMETER, ///< invalid parameter provided
    $OA_RESULT_ERROR_OUT_OF_MEMORY,     ///< insufficient memory to satisfy call
    $OA_RESULT_ERROR_UNKNOWN = -1       ///< internal error
};


///////////////////////////////////////////////////////////////////////////////
/// @brief Device descriptor
typedef struct _$oa_device_desc
{
    uint32_t flags; ///< [in] must be 0
} $oa_device_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a device object
/// @returns OA_RESULT_SUCCESS, ...
$oa_result_t $oaCreateDevice( 
    $oa_device_desc_t desc,             ///< [in] device descriptor
    $oa_device_handle_t* phDevice       ///< [out] handle to device object created
	);
    
///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a device object
/// @returns OA_RESULT_SUCCESS, ...
$oa_result_t $oaDestroyDevice(
    $oa_device_handle_t hDevice     ///< [in] handle to device object to destroy
	);


///////////////////////////////////////////////////////////////////////////////
/// @brief Command Queue descriptor
typedef struct _$oa_command_queue_desc_t
{
    $oa_device_handle_t hDevice; ///< [in] handle to the device
    uint32_t flags;              ///< [in] must be 0
} $oa_command_queue_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command queue
/// @returns OA_RESULT_SUCCESS, ...
$oa_result_t $oaCreateCommandQueue(
    $oa_command_queue_desc_t desc,                  ///< [in] command queue descriptor
    $oa_command_queue_handle_t* phCommandQueue      ///< [out] handle to command queue object created
	);

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command queue
/// @returns OA_RESULT_SUCCESS, ...
$oa_result_t $oaDestroyCommandQueue(
    $oa_command_queue_handle_t hCommandQueue        ///< [in] handle to command queue object to destroy
	);


///////////////////////////////////////////////////////////////////////////////
/// @brief Command List descriptor
typedef struct _$oa_command_list_desc_t
{
    $oa_device_handle_t hDevice; ///< [in] handle to the device
    uint32_t flags;              ///< [in] must be 0
} $oa_command_list_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command list
/// @returns OA_RESULT_SUCCESS, ...
$oa_result_t $oaCreateCommandList(
    $oa_command_list_desc_t desc,                   ///< [in] command list descriptor
    $oa_command_list_handle_t* phCommandList        ///< [out] handle to command list object created
	);

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command list
/// @returns OA_RESULT_SUCCESS, ...
$oa_result_t $oaDestroyCommandList(
    $oa_command_list_handle_t hCommandList          ///< [in] handle to command list object to destroy
	);

///////////////////////////////////////////////////////////////////////////////
/// @brief Enqueues a command list to a command queue
/// @returns OA_RESULT_SUCCESS, ...
$oa_result_t $oaEnqueueCommandList(
    $oa_command_queue_handle_t hCommandQueue,   ///< [in] handle to the command queue
    $oa_command_list_handle_t hCommandList      ///< [in] handle to the command list to execute
	);


///////////////////////////////////////////////////////////////////////////////
/// @brief Event descriptor
typedef struct _$oa_event_desc_t
{
    $oa_device_handle_t hDevice; ///< [in] handle to the device
    uint32_t flags;              ///< [in] must be 0
} $oa_event_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a synchronization object
/// @returns OA_RESULT_SUCCESS, ...
$oa_result_t $oaCreateEvent( 
    $oa_event_desc_t desc,          ///< [in] event descriptor
    $oa_event_handle_t* phEvent     ///< [out] handle to event object created
	);
    
///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a synchronization object
/// @returns OA_RESULT_SUCCESS, ...
$oa_result_t $oaDestroyEvent(
    $oa_event_handle_t hEvent       ///< [in] handle to event object to destroy
	);

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes a synchronization object into a command list
/// @returns OA_RESULT_SUCCESS, ...
$oa_result_t $oaEncodeEvent(
    $oa_command_list_handle_t hCommandList, ///< [in] handle to the command list
    $oa_event_handle_t hEvent               ///< [in] handle to the event 
	);
    

///////////////////////////////////////////////////////////////////////////////
/// @brief Resource descriptor
typedef struct _$oa_resource_desc_t
{
    $oa_device_handle_t hDevice; ///< [in] handle to the device
    uint32_t flags;              ///< [in] must be 0
} $oa_resource_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a resource object
/// @returns OA_RESULT_SUCCESS, ...
$oa_result_t $oaCreateResource( 
    $oa_resource_desc_t desc,           ///< [in] resource descriptor
    $oa_resource_handle_t* phResource   ///< [out] handle to resource object created
	);
    
///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a resource object
/// @returns OA_RESULT_SUCCESS, ...
$oa_result_t $oaDestroyResource(
    $oa_resource_handle_t hResource     ///< [in] handle to resource object to destroy
	);


#endif // _DRIVER_API_H