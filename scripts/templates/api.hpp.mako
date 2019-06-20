<%
import re
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
 * @file ${n}_api.hpp
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/${section}
 * @endcond
 *
 */
#ifndef _${N}_API_HPP
#define _${N}_API_HPP
#if defined(__cplusplus)
#pragma once

%if n != x:
// 'core' API headers
#include "${x}_api.hpp"
%else:
// standard headers
#include <stdint.h>
#include <string.h>
#include <exception>
#include <tuple>
#include <string>
#include <sstream>
%endif

// '${section}' API headers
%for f in files:
#include "${f}"
%endfor

#endif // defined(__cplusplus)
#endif // _${N}_API_HPP