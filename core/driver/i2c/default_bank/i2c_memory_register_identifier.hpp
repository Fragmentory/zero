/**
 * \file i2c_memory_register_identifier.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>

namespace core
{
    namespace driver
    {
        namespace i2c
        {
            namespace memory
            {
                enum REGISTER : uint8_t
                {
                    BLA = 0xAB,
                    BLUB = 0xBA,
                    SERIAL = 0x02,

                    UNDEFINED = 0xFF,
                };
            }
        }
    }
}