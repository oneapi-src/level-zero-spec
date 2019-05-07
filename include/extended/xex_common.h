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
* @file xex_common.h
*
* @brief Intel Xe Level-Zero Extended API common types
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/extended/common.yml
* @endcond
*
******************************************************************************/
#ifndef _XEX_COMMON_H
#define _XEX_COMMON_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_XEX_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif
#include <stdint.h>
#include <string.h>
#include "xe_api.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's command graph object
typedef struct _xex_command_graph_handle_t *xex_command_graph_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xex_command_graph_desc_t
typedef struct _xex_command_graph_desc_t xex_command_graph_desc_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XEX_COMMON_H
