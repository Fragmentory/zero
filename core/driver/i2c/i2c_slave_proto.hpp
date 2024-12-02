/**
 * \file i2c_slave_proto.hpp
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
            namespace slave
            {
                struct Proto
                {
                    static constexpr uint8_t SDA_PIN = 12;
                    static constexpr uint8_t SCL_PIN = 13;
                    static constexpr uint8_t ADDRESS = 0x34;
                    static constexpr uint32_t BAUDRATE = 100 * 1000;
                    static constexpr i2c_inst_t *INSTANCE = &i2c0_inst;
                };
            }
        }
    }
}
