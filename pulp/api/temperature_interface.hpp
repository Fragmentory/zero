/**
 * \file temperature_interface.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>

namespace pulp
{
    namespace temperature
    {
        struct Interface
        {
            virtual float get_value(void) const = 0;
            virtual uint16_t get_raw_value(void) const = 0;
        };
    }
}