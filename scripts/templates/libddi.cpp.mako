<%!
import re
from templates import helper as th
%><%
    n=namespace
    N=n.upper()

    x=tags['$x']
    X=x.upper()
%>/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}.cpp
 *
 */
#include "${x}_lib.h"

namespace ${x}_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    __zedlllocal ${x}_result_t context_t::${n}Init()
    {
        ${x}_result_t result = ${X}_RESULT_SUCCESS;

    %for tbl in th.get_pfntables(specs, meta, n, tags):
        if( ${X}_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<${tbl['pfn']}>(
                GET_FUNCTION_PTR(loader, "${tbl['export']['name']}") );
            result = getTable( ${X}_API_VERSION_0_91, &${n}DdiTable.${tbl['name']} );
        }

    %endfor
        return result;
    }
} // namespace ${x}_lib
