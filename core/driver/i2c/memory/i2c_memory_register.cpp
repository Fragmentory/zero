/**
 * \file i2c_memory_register.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "i2c_memory_register.hpp"

#include "chunk.h"

#include <cstdint>
#include <cstdlib>

namespace core::driver::i2c
{
    namespace memory
    {
        bool Register::reset()
        {
            finish_data();
            return true;
        }

        void Register::get_chunk_byte(const chunk_t &_chunk, uint8_t &_byte)
        {
            _byte = _chunk.space[position];
            if (!(++position < _chunk.size))
            {
                finish_data();
                operation_get_done();
            }
        }

        void Register::set_chunk_byte(const chunk_t &_chunk, const uint8_t _byte)
        {
            _chunk.space[position] = _byte;
            if (!(++position < _chunk.size))
            {
                finish_data();
                operation_set_done();
            }
        }
    }
}
