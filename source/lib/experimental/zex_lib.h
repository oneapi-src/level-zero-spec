/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zex_lib.h
 *
 */
#pragma once
#include "zex_api.h"
#include "zex_ddi.h"
#include "ze_util.h"
#include <vector>

namespace zex_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    class context_t
    {
    public:
        HMODULE loader = nullptr;

        context_t();
        ~context_t();

        ze_result_t Init();

        zex_dditable_t  ddiTable = {};
    };

    extern context_t context;

} // namespace zex_lib
