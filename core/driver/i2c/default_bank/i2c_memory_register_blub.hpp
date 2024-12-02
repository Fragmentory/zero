/**
 * \file i2c_memory_register_blub.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "i2c_memory_register.hpp"
#include "i2c_memory_register_identifier.hpp"

#include <cstdint>

namespace core
{
    namespace driver
    {
        namespace i2c
        {
            namespace memory
            {
                namespace blub
                {
                    struct blub_t
                    {
                        uint16_t x;
                        uint8_t a;
                        uint8_t b;
                    } __attribute__((packed));

                    struct register_t : public Register
                    {
                        static const REGISTER ADDRESS = REGISTER::BLUB;
                        static const size_t SIZE = sizeof(blub_t);
                        union
                        {
                            uint8_t byte[SIZE];
                            blub_t value;
                        };

                        virtual void get_byte(uint8_t &_byte) override { get_chunk_byte(chunk_t{byte, SIZE}, _byte); }

                        virtual void set_byte(const uint8_t _byte) override { set_chunk_byte(chunk_t{byte, SIZE}, _byte); }

                    } __attribute__((packed));
                }
            }
        }
    }
}