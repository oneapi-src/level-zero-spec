/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xex_common.h
 *
 * @brief Intel 'One API' Level-Zero Experimental API common types
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/experimental/common.yml
 * @endcond
 *
 */
#ifndef _XEX_COMMON_H
#define _XEX_COMMON_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_XEX_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of command list object
typedef xe_command_list_handle_t xex_command_list_handle_t;

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
