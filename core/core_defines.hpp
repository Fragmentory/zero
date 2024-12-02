/**
 * \file core_defines.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "revision.h"

#include <cstdint>

namespace core
{
    struct Undefined
    {
    };

    namespace defines
    {
        enum class IDENTIFIER
        {
            PLATFORM_PROTO = 1,
            PLATFORM_SERIE = 2,
        };

        namespace usb
        {
            static const uint16_t PID_MASK = 0xffe0;
            /* mask: 0xffe0, 5 lsb are reserved for product interface capabilities */
            static const uint16_t PID = (identity::firmware::IDENTIFIER << 5) & PID_MASK;
            static const uint16_t VID = identity::firmware::VENDOR;
        }
    }
}
