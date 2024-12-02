/**
 * \file i2c_master_serie.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>
#include <hardware/i2c.h>
#include <pico/stdlib.h>

namespace core
{
    namespace driver
    {
        namespace i2c
        {
            namespace master
            {
                struct Serie
                {
                    static constexpr uint8_t SDA_PIN = 14;
                    static constexpr uint8_t SCL_PIN = 15;
                    static constexpr uint8_t ADDRESS = 0x34;
                    static constexpr uint32_t BAUDRATE = 100 * 1000;
                    static constexpr i2c_inst_t *INSTANCE = &i2c1_inst;
                };
            }
        }
    }
}
