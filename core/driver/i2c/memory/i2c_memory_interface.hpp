/**
 * \file i2c_memory_interface.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>

namespace core::driver::i2c
{
    namespace memory
    {
        struct Interface
        {
            virtual bool set_address(const uint8_t) = 0;
            virtual bool is_address(void) = 0;
            virtual void reset(void) = 0;
            virtual bool get_byte(uint8_t &) const = 0;
            virtual bool set_byte(const uint8_t _byte) = 0;
            virtual void finish(void) = 0;
            virtual void handle_byte(const uint8_t) = 0;
        };
    }
}
