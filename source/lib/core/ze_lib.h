/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_lib.h
 *
 */
#pragma once
#include "ze_api.hpp"
#include "ze_ddi.h"
#include "ze_util.h"
#include "ze_singleton.h"
#include <vector>

namespace ze_lib
{
    using driver_factory_t = singleton_factory_t<ze::Driver, ze::driver_handle_t>;
    using device_factory_t = singleton_factory_t<ze::Device, ze::device_handle_t>;

    ///////////////////////////////////////////////////////////////////////////////
    class context_t
    {
    public:
        HMODULE loader = nullptr;

        context_t();
        ~context_t();

        ze_result_t Init();

        ze_dditable_t   ddiTable = {};

        driver_factory_t    driverFactory;
        device_factory_t    deviceFactory;
    };

    extern context_t context;

} // namespace ze_lib
