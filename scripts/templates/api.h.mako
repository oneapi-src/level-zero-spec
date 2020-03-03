<%
import re
from templates import helper as th
%><%
    n=namespace
    N=n.upper()

    x=tags['$x']
    common_header=n+"_common.h"
%>/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${n}_api.h
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
#include <stddef.h>
%endif

// '${section}' API headers
#include "${common_header}"
%for f in files:
%if not re.match(common_header, f):
#include "${f}"
%endif
%endfor

#endif // _${N}_API_H