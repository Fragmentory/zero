/**
 * \file pulp_defines.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>

namespace pulp
{
    struct Undefined
    {
    };

    namespace defines
    {
        enum class Identifier
        {
            TEST_APPLICATION = 1, /* test and demo application */
            APPLICATION = 2,      /* main application */
        };
    }
}
