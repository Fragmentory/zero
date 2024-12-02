/**
 * \file timestamp_interface.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>

namespace pulp
{
    namespace timestamp
    {
        struct Interface
        {
            virtual uint64_t get_value(void) const = 0;
        };
    }
}