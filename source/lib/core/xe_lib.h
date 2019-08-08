/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_lib.h
 *
 */
#pragma once
#include "xe_api.hpp"
#include "xe_ddi.h"
#include "xe_util.h"
#include "xe_singleton.h"
#include <vector>

namespace xe_lib
{
    using driver_factory_t = singleton_factory_t<xe::Driver, xe::driver_handle_t>;
    using device_factory_t = singleton_factory_t<xe::Device, xe::device_handle_t>;

    ///////////////////////////////////////////////////////////////////////////////
    class context_t
    {
    public:
        HMODULE loader = nullptr;

        context_t();
        ~context_t();

        xe_result_t Init();

        xe_dditable_t   ddiTable = {};

        driver_factory_t    driverFactory;
        device_factory_t    deviceFactory;
    };

    extern context_t context;

} // namespace xe_lib
