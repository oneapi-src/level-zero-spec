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
* @file xe_event.h
* 
* @brief Intel Xe Driver APIs for Event
* 
******************************************************************************/
#ifndef _XE_EVENT_H
#define _XE_EVENT_H
#if defined( __cplusplus )
#pragma once
#endif
#include "xe_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Event creation flags
XE_DECLARE_ENUM( xe_event_flags_t )
{
    XE_EVENT_FLAG_NONE = 0                  ///< default behavior
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Event descriptor
typedef struct _xe_event_desc_t
{
    xe_event_flags_t flags;                 ///< [in] creation flags
} xe_event_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an event object
/// @remarks _Analogues:_
///     - **cuEventCreate**
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeEventCreate( 
    xe_device_handle_t hDevice,             ///< [in] handle of the device
    xe_event_desc_t* desc,                  ///< [in] pointer to event descriptor
    xe_event_handle_t* phEvent              ///< [out] pointer to handle of event object created
    );
    
///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes an event object
/// @remarks _Analogues:_
///     - **cuEventDestroy**
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeEventDestroy(
    xe_event_handle_t hEvent                ///< [in] handle of event object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Encodes an event object into a command list
/// @remarks _Analogues:_
///     - **cuEventRecord**
/// @returns XE_RESULT_SUCCESS, ...
xe_result_t __xecall
  xeCommandListEncodeEvent(
    xe_command_list_handle_t hCommandList,  ///< [in] handle of the command list
    xe_event_handle_t hEvent                ///< [in] handle of the event 
    );

#endif // _XE_EVENT_H