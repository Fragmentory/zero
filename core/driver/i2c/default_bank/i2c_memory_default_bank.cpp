/**
 * \file i2c_memory_bank.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "i2c_memory_default_bank.hpp"

#include "i2c_memory_register_identifier.hpp"

namespace core
{
    namespace driver
    {
        namespace i2c
        {
            namespace memory
            {
                void DefaultBank::initialize(void)
                {
                    bla_register.reset();
                    blub_register.reset();
                    serial_register.reset();
                }

                bool DefaultBank::set_address(const uint8_t _address)
                {
                    current_register = nullptr;
                    // const REGISTER val = static_cast<REGISTER>(_address);

                    if (_address == 0xab)
                    {
                        current_register = &bla_register;
                        bla_register.reset();
                    }
                    else if (_address == 0xba)
                    {
                        current_register = &blub_register;
                        blub_register.reset();
                    }
                    else if (_address == 0x02)
                    {
                        current_register = &serial_register;
                        serial_register.reset();
                    }
                    else
                    {
                    }
                    return current_register != nullptr;
                }
            }
        }
    }
}