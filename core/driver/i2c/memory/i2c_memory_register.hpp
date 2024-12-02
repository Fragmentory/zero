/**
 * \file i2c_memory_register.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "chunk.h"
#include "i2c_memory_interface.hpp"

#include <cstdint>
#include <cstdlib>

namespace core
{
    namespace driver
    {
        namespace i2c
        {
            namespace memory
            {
                struct Register
                {
                    enum class ACCESS
                    {
                        READ,
                        WRITE,
                        READ_WRITE
                    };

                    virtual void get_byte(uint8_t &) = 0;
                    virtual void set_byte(const uint8_t _byte) = 0;
                    inline virtual void operation_set_done() {};
                    inline virtual void operation_get_done() {};

                    bool reset();

                    inline bool is_full() const { return full; }

                    inline bool is_locked() const { return locked; }
                    inline void set_locked(const bool _value) { locked = _value; }

                    void get_chunk_byte(const chunk_t &, uint8_t &);
                    void set_chunk_byte(const chunk_t &, const uint8_t);
                    inline void finish_data(void)
                    {
                        full = true;
                        position = 0;
                    }

                    ACCESS access{ACCESS::READ_WRITE};

                  protected:
                    size_t position{0};
                    bool full{false};
                    bool locked{false};
                };
            }
        }
    }
}
