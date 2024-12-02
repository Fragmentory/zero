/**
 * \file ticker_interface.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

namespace pulp::ticker
{
    struct Callback
    {
        virtual void invoke() = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
    };

}