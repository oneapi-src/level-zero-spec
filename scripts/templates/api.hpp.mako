<%
import re
%><%
    n=namespace
    N=n.upper()

    x=tags['$x']
    common_header=n+"_common.hpp"
%>/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${n}_api.hpp
 *
 */
#ifndef _${N}_API_HPP
#define _${N}_API_HPP
#if defined(__cplusplus)
#pragma once

// C API headers
#include "${n}_api.h"

%if n != x:
// 'core' C++ API headers
#include "${x}_api.hpp"
%else:
// standard headers
#include <stdint.h>
#include <string.h>
#include <exception>
#include <tuple>
#include <vector>
#include <string>
#include <sstream>
%endif

// '${section}' API headers
#include "${common_header}"
%for f in files:
%if not re.match(common_header, f):
#include "${f}"
%endif
%endfor

#endif // defined(__cplusplus)
#endif // _${N}_API_HPP