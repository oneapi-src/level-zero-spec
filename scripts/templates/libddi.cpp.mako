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
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/templates/libddi.cpp.mako
 * @endcond
 *
 */
#include "${n}_lib.h"

namespace ${n}_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    ${x}_result_t context_t::Init()
    {
        loader = LOAD_DRIVER_LIBRARY( MAKE_DRIVER_NAME( "${x}_loader" ) );

        if( NULL == loader )
            return ${X}_RESULT_ERROR_UNINITIALIZED;

        ${x}_result_t result = ${X}_RESULT_SUCCESS;

    %for tbl in th.get_pfntables(specs, meta, n, tags):
        if( ${X}_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<${tbl['pfn']}>(
                GET_FUNCTION_PTR(loader, "${tbl['export']['name']}") );
            result = getTable( ${X}_API_VERSION_0_91, &ddiTable.${tbl['name']} );
        }

    %endfor
        return result;
    }
} // namespace ${n}_lib
