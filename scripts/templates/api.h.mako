<%
import re
from templates import helper as th
%><%
    n=namespace
    N=n.upper()

    x=tags['$x']
%>/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${n}_api.h
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/${section}
 * @endcond
 *
 */
#ifndef _${N}_API_H
#define _${N}_API_H
#if defined(__cplusplus)
#pragma once
#endif

%if n != x:
// 'core' API headers
#include "${x}_api.h"
%else:
// standard headers
#include <stdint.h>
%endif

// '${section}' API headers
%for f in files:
#include "${f}"
%endfor

#endif // _${N}_API_H