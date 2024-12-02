<%
import re
from templates import helper as th
%><%
    n=namespace
    N=n.upper()

    x=tags['$x']
    X=x.upper()
%>/*
 *
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${n}_ddi_common.h
 * @version v${ver}-r${rev}
 *
 */
#ifndef _${N}_DDI_COMMON_H
#define _${N}_DDI_COMMON_H
#if defined(__cplusplus)
#pragma once
#endif
#include "ze_ddi.h"
#include "zet_ddi.h"
#include "zes_ddi.h"

#if defined(__cplusplus)
extern "C" {
#endif

/// @brief Handle with pointers to Dispatch Tables allocated by the driver at the beginning of every L0 object handle.
typedef struct _${n}_handle_t
{
    ze_dditable_driver_t *pCore; // [in] pointer to _ze_dditable_t_ object related to this handle
    zet_dditable_driver_t *pTools; // [in] pointer to _zet_dditable_t_ object related to this handle
    zes_dditable_driver_t *pSysman; // [in] pointer to _zes_dditable_t_ object related to this handle
} ${n}_handle_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _${N}_DDI_COMMON_H