/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xex_lib.h
 *
 */
#pragma once
#include "xex_api.hpp"
#include "xex_ddi.h"
#include "xe_util.h"
#include <vector>

namespace xex_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    class context_t
    {
    public:
        HMODULE loader = nullptr;

        context_t();
        ~context_t();

        xe_result_t Init();

        xex_dditable_t  ddiTable = {};
    };

    extern context_t context;

} // namespace xex_lib
